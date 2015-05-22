package com.holub.tools;

import java.io.*;
import java.util.*;
import java.util.zip.*;
import com.holub.asynch.Mutex;
import com.holub.io.FastBufferedOutputStream;
import com.holub.io.DelayedOutputStream;

import com.holub.io.Std;		// for testing

/*********************************************************************
	A class that simplifies reading from, writing to, and modifying
	jar/zip files.

	<p>Sun's support for JAR files is dicey. It's not difficult to read
	them, but writing or updating is nigh on impossible. The only
	way to update a jar, for example, is to copy an existing jar
	into a new one, writing the changes as you copy, and then
	renaming the new file so that you overwrite the old one. If you
	have many updates to perform, then this is a time-consuming
	process, to say the least.

	<p>The <code>Archive</code> works by creating a second jar file
	that holds the modified files, then when you close the archive,
	the close method overwrites the original jar with the copy.

	<p>Note that the <code>internal_path</code> passed to the various
	methods of this class must be a fully formed path name
	(no .'s or ..'s) that uses forward slashes as a path separator.

	<p>This class is thread safe, but access to the Archive is
	serialized. Only one thread at a time can access the archive.
	You modify the Archive be requesting an output or input
	stream for a specific internal file. The returned
	InputStream or OutputStream must be closed before anyone
	else is grated access for read <em>or</em> write. In a
	muti-threaded scenario, the requesting threads will block
	until the Archive becomes available.

	<br><br>
	<table border=1 cellspacing=0 cellpadding=5>
	<tr><td><font size=-1><i>
		<center>(c) 2000, Allen I. Holub.</center>
		<p>You may not distribute this code except in binary form,
		incorporated into a java .class file. You may use this code
		freely for personal purposes, but you may not incorporate
		it into any product (commercial, shareware, or free) without
		the express written permission of Allen I. Holub.
	</font></i></td></tr>
	</table>

	@author Allen I. Holub
 */

public class Archive
{
	private File				source_file;
	private DelayedOutputStream	destination_stream;

	private ZipFile			source;
	private ZipOutputStream destination; // Temporary file that holds
										 // modified archive. Overwrites
										 // source file on close.

	private int	compression	= ZipEntry.DEFLATED ;

	private boolean closed	= false;
	private boolean archive_has_been_modified = false;

	private Mutex   lock	= new Mutex(); 	 // Locks Archive while read
										   	 // or write is in progress.
	private Map	 	entries	= new HashMap(); // Zip entries in the
											 // source archive, indexed
											 // by name.

	private static final boolean running_under_windows =
					System.getProperty("os.name").startsWith("Windows");

	/** Alias for true, useful as self-documenting second argument to 
	 *  {@link #Archive(String,boolean)}
	 */
	public static final boolean COMPRESSED   = true;

	/** Alias for false, useful as self-documenting second argument to 
	 *  {@link #Archive(String,boolean)}
	 */
	public static final boolean UNCOMPRESSED = false;

	/** Alias for true, useful as self-documenting second argument to 
	 *	{@link #output_stream_for}.
	 */
	public static final boolean APPEND = true;

	/** Alias for false, useful as self-documenting second argument to 
	 *	{@link #output_stream_for}.
	 */
	public static final boolean OVERWRITE = false;

	/*****************************************************************
	 *	Thrown by all methods of this class (except the constructor) if
	 *	you try to access a closed archive.
	 */
	public static class Closed extends RuntimeException
	{	Closed(){ super("Tried to modify a closed Archive"); }
	}

	/*****************************************************************
	 * Create a new <code>Archive</code> object that represents the
	 * <em>.zip</em> or <em>.jar</em> file at the indicated path.
	 *
	 * @param jar_file_path	The path in the file system to the .jar or
	 *						.zip file.
	 * @param compress		If true, new files written to the archive
	 *						(as compared to modifications of existing
	 *						files) are compressed, otherwise the data
	 *						in the file is simply stored. The
	 *						maximum possible compression level is used.
	 */
	public Archive( String jar_file_path, boolean compress )
												throws IOException
	{	source_file = new File( jar_file_path );
		try
		{	source = new ZipFile( jar_file_path );

			// Transfer all the zip entries into local memory to make
			// them easier to access and manipulate.
			for(Enumeration e = source.entries(); e.hasMoreElements();)
			{	
				ZipEntry current = (ZipEntry) e.nextElement();
				entries.put( current.getName(), current );
			}
		}
		catch( Exception e )	// Assume file doen't exist
		{	source = null;		// Since the "entries" list will be
		}						// empty, "source" won't be used

		// The folloing constuctor causes a temporary file to be created
		// when the first write occurs on the output stream. If no
		// writes happen, the file isn't created.

		destination_stream = new DelayedOutputStream(
								source_file.getName(), ".tmp");

		destination		   = new ZipOutputStream(
								new FastBufferedOutputStream(
												destination_stream));

		destination.setLevel(9);	// compression level == max

		this.compression=compress ? ZipEntry.DEFLATED : ZipEntry.STORED;
		destination.setMethod( compress ? ZipOutputStream.DEFLATED
										: ZipOutputStream.STORED   );
											 
	}

	/** Convenience method; creates a compressed archive
	 */

	public Archive( String jar_file_path ) throws IOException
	{	this( jar_file_path, true );
	}

	/*******************************************************************
	 * Clean up from a close, closing all handles and freeing memory.
	 */
	private final void deconstruct() throws IOException
	{
									 // The archive is now unusable,
		entries				= null;	// so free up any internal
		source				= null;	// memory in case it's needed
		destination			= null; // elsewhere and the Archive
		source_file			= null; // itself isn't freed for some
		destination_stream	= null; // reason.
	}

	/*******************************************************************
	 * Remove a file from the archive.
	 */
	public void remove( String internal_path )
								throws IOException, InterruptedException
	{
		lock.acquire();
		try
		{	if( closed )
				throw new Closed();

			// When the archive is closed, all files in the "entries"
			// list are copied from the original jar to the new
			// one. By removing the file from the list, you will
			// prevent that file from being copied to the new
			// archive.

			archive_has_been_modified = true;
			entries.remove( internal_path );
		}
		finally
		{	lock.release();
		}
	}

	/*******************************************************************
	 * Return an OutputStream that you can use to write to the indicated
	 * file.  The current <code>Archive</code> object
	 * is locked until the returned stream is closed. Any existing
	 * file that is overwritten will no longer be accessible for reading
	 * via the current `Archive` object. It's an error to call this
	 * method more than once with the same <code>internal_path</code>
	 * argument.
	 *
	 * <p>Note that the returned output stream <u>is not</u> thread
	 * safe. Two threads cannot write to the same output stream
	 * simultaneously without some sort of explicit synchronization.
	 * I've done it this way because output streams are typically not
	 * shared between threads, and the overhead of synchronization
	 * would be nontrivial.
	 *
	 * <p>The file is created within the archive if it doesn't
	 * already exist.
	 *
	 * @param internal_path The path (within the archive) to the desired
	 *						file.
	 * @param appending		true if you want the bytes written to the
	 *						returned <code>OutputStream</code> to be
	 *						appended to the original contents.
	 * @return 				A stream to receive the new data.
	 */

	public OutputStream output_stream_for( String internal_path,
												   boolean appending )
													throws IOException
	{	try
		{
			lock.acquire();	// Lock the archive. The lock is released
							// by write_accomplished when the stream
							// is closed.
			if( closed )
			{	lock.release();
				throw new Closed();
			}

			archive_has_been_modified = true;

			// See if it's an existing file, and if so, remove
			// it from the list of files that were in the original
			// archive. Otherwise the new contents will be
			// overwritten by the original when the Archive is closed.

			ZipEntry found = (ZipEntry)( entries.remove(internal_path));

			ZipEntry entry = new ZipEntry(internal_path);

			entry.setMethod( found != null 
								? found.getMethod() : compression ); 

			entry.setComment( entry.getMethod()==ZipEntry.DEFLATED
								? "compressed" : "uncompressed");

			OutputStream out = new Archive_OutputStream( entry );

			if( found != null && appending )
				copy_entry_to_stream( entry, out );

			return out;
		}
		catch(IOException e) // release on an exception toss, but
		{	lock.release();	 // not a finally.
			throw e;
		}
		catch(InterruptedException e)
		{	// fall through to null return.
		}
		return null;
	}

	/** Convenience method. Original file is overwritten if it's there.
	 */

	public OutputStream output_stream_for( String internal_path )
											throws IOException
	{	return output_stream_for( internal_path, false );
	}

	/*******************************************************************
	 * Copies the contents of a file in the source archive to the
	 * indicated destination stream. This method is private because
	 * it doesn't do any locking. The output stream is not closed
	 * by this method.
	 */

	private void copy_entry_to_stream(ZipEntry entry, OutputStream out)
													throws IOException
	{	InputStream in = source.getInputStream(entry);
		try
		{	byte[] buffer = new byte[1024];

			for(int got=0; (got = in.read(buffer,0,buffer.length)) >0 ;)
			{	out.write(buffer, 0, got);
			}
		}
		finally
		{	in.close();
		}
	}

	/*******************************************************************
	 * Called from the Archive_OutputStream's <code>close()</code>
	 * method. In the case of a compressed write, just releases
	 * the lock. In the case of a "stored" write, transfers from the
	 * ByteArrayOutputStream to the file, creating the necessary
	 * checksum.
	 */

	private void write_accomplished()
	{	lock.release();
	}

	/*******************************************************************
	 * Return an InputStream that you can use to read from the
	 * indicated file. The current <code>Archive</code>
	 * object is locked until the returned stream is closed. Once a
	 * particular archived file is overwritten (by a call to
	 * {@link #output_stream_for}), that file is no longer available
	 * for write, and an attempt to call <code>input_stream_for()</code>
	 * on that file will fail.
	 *
	 * @return a reference to an InputStream or null if no file
	 *			that matches internal_path exists.
	 *
	 * @throw ZIPException if the requested file doesn't exist.
	 * @throw IOException if an I/O error occurs when the method
	 *					  tries to open	the stream.
	 */

	public InputStream input_stream_for( String internal_path )
										throws ZipException, IOException
	{	
		Assert.is_true( source != null, "source is null" );

		try
		{	lock.acquire();	// Lock the archive. The lock is released
							// when the returned InputStream is closed.
			if( closed )
			{	lock.release();
				throw new Closed();
			}

			ZipEntry current = (ZipEntry)entries.get( internal_path );
			if( current == null )
				throw new ZipException(internal_path +" doesn't exist");

			InputStream in	= source.getInputStream(current);
			return new Archive_InputStream( in );
		}
		catch( IOException e )	// ZipException extends IOException
		{	lock.release();
			throw e;
		}
		catch(InterruptedException e)
		{	// fall through to null return.
		}
		return null;
	}

	/*******************************************************************
	 * Called from the Archive_InputStream's <code>close()</code>
	 * method.
	 */

	private void read_accomplished()
	{	lock.release();
	}

	/*******************************************************************
	 * Close the current <code>Archive</code> object (rendering it
	 * unusable) and overwrite the original archive with the new
	 * contents. The original archive is not actually modified until
	 * <code>close()</code> is called. A call to this method blocks
	 * until any ongoing read or write operations complete (and the
	 * associated stream is closed).
	 *
	 * @throws ZipException Zip files must have more than at least
	 *						one entry in them. A ZipException is thrown
	 *						if the destination file is empty, either
	 *						becuase you've removed everything or
	 *						becuase you never put anything into it.
	 *						The original archive will not have been
	 *						changed if this exception is thrown.
	 */

	public void close()
				throws IOException, InterruptedException, ZipException
	{	
		// The main thing that close() does is copy any files that
		// remain in the "entries" list from the original archive
		// to the new one. The original compression mode of the
		// file is preserved. Finally, the new archive is renamed
		// to the original archive's name (thereby blasting the
		// original out of existence.)

		lock.acquire();
		try
		{	if( !closed ) // Closing a closed archive is harmless
			{
				if( source != null ) // there is a source archive
				{
					if( archive_has_been_modified )
					  copy_remaining_files_from_source_to_destination();
					source.close();
				}

				if( archive_has_been_modified )
				{	
					destination.close();
					if( !destination_stream.rename_temporary_to(
														source_file ) )
					{	D.ebug("***\t\tTemporary file not renamed!");
					}
				}
				else
				{	destination_stream.close();
					destination_stream.delete_temporary();
				}

				closed = true;
				deconstruct();
			}
		}
		catch( ZipException e )
		{	// Thrown if the destination archive is empty.
		 	// Clean up the temporary file, then rethrow
			// the exception.

			destination_stream.close();
			destination_stream.delete_temporary();
			throw e;
		}
		finally
		{	lock.release();
		}
	}

	/*******************************************************************
	 * Copies any files from the source archive that have not been
	 * modified to the destination archive (and removes them from
	 * the entries list as they are copied).
	 */

	private void copy_remaining_files_from_source_to_destination()
													throws IOException
	{	for(Iterator i = entries.values().iterator(); i.hasNext() ;)
		{	ZipEntry current = (ZipEntry)i.next();
			i.remove();

			ZipEntry entry = new ZipEntry(current.getName());

			entry.setMethod	( current.getMethod()	);
			entry.setSize  	( current.getSize()		);
			entry.setCrc   	( current.getCrc()		);
			entry.setComment( current.getComment()	);

			D.ebug( "\t\tTransferring "+current.getName()+" to output");

			destination.putNextEntry( current );
			copy_entry_to_stream( current, destination );
		}
	}

	/*******************************************************************
	 * Close the archive, abandoning any changes that you've made. It's
	 * important to call this method (as compared to simply abandoning
	 * the <code>Archive</code> object) if you want to discard changes;
	 * otherwise, temporary files will be left on your disk. Reverting
	 * a closed archive is considered harmless, so is not flagged as
	 * an error.
	 */

	public void revert() throws IOException, InterruptedException
	{	
		// All that this method does is close, and then destroy, the
		// temporary file that contains the partially assembled
		// new archive. It also puts the Archive object into the
		// "closed" state so that no further modifications are
		// possible.

		lock.acquire();
		try
		{	if( closed )
				return;

			source.close();

			if( archive_has_been_modified )
				destination.close();
			else
				destination_stream.close();

			destination_stream.delete_temporary();
			closed = true;
			deconstruct();
		}
		finally
		{	lock.release();
		}
	}

	/*******************************************************************
	 *	A gang-of-four Decorator that wraps <code>InputStream</code> in
	 *	such a way that the <code>Archive</code> object that created it
	 *	is notified when the stream is closed.
	 */

	private class Archive_InputStream extends InputStream
	{	private final InputStream wrapped;

		public Archive_InputStream( InputStream wrapped )
		{	this.wrapped = wrapped;
		}

		public int available()	 throws IOException 
		{	return wrapped.available();
		}

		public void reset()	 throws IOException
		{	wrapped.reset();
		}

		public long skip(long n)throws IOException
		{	return wrapped.skip(n);
		}

		public int read() throws IOException
		{	return wrapped.read();
		}

		public int read(byte[] b)throws IOException
		{	return wrapped.read(b);
		}

		public void mark( int limit ) {		  wrapped.mark(limit);	  }
		public boolean markSupported(){return wrapped.markSupported();}

		public int read(byte[] b,int o,int l) throws IOException
		{	return wrapped.read(b,o,l);
		}

		public void close() throws IOException
		{	wrapped.close();
			read_accomplished();
		}
	}

	/*******************************************************************
	 *	The Archive_OutputStream is a real class, not a decorator.
	 *  The main problem is that "storing" a file mandates computing
	 *	a checksum before writing the bytes. Though it's tempting to
	 *	just save the file to a ByteArrayOutputStream and then get
	 *	the bytes, the in-memory footprint can be too large. The
	 *	current implementation transfers the bytes to a temporary
	 *	file, then transfers them from a temporary file to the archive.
	 *	The bytes are buffered internally, so for for small files
	 *	(under 2K in size), the temporary file is actually never
	 *	created.
	 */

	private class Archive_OutputStream extends OutputStream
	{
		private final   ZipEntry	 entry;
		private final   CRC32		 crc  = new CRC32();

		private 	    OutputStream 		out;
		private			DelayedOutputStream stream;

		public Archive_OutputStream( ZipEntry entry ) throws IOException
		{	this.entry	= entry;

			destination.setMethod( entry.getMethod()  );

			if( entry.getMethod() == ZipEntry.DEFLATED )
			{	destination.putNextEntry( entry );
				out = destination;
			}
			else
			{	stream = new DelayedOutputStream("Archive", ".tmp");
				out	   = new FastBufferedOutputStream( stream );
			}

			D.ebug("\t\tOpened " + entry.getComment() + " stream" );
		}

		public void flush(){ /* meaningless in context */ }

		public void write(int the_byte) throws IOException
		{	
			// The other variants of write are inherited from
			// OutputStream, and will call the current version.

			crc.update( the_byte );
			out.write ( the_byte );
		}

		public void close() throws IOException
		{	
			if( entry.getMethod() == ZipEntry.DEFLATED )
			{
				D.ebug("\t\tClosing compressed stream. crc="
									+ entry.getCrc()
									+ " size="
									+ entry.getSize() );
			}
			else
			{
				FastBufferedOutputStream buffer_stream =
										(FastBufferedOutputStream)out;

				entry.setCrc( crc.getValue() );
				entry.setSize( buffer_stream.bytes_written() );

				destination.putNextEntry( entry );

				D.ebug("\t\tClosing stored stream. crc="
										+ entry.getCrc()
										+ " size="
										+ entry.getSize() );


				// Transfer data from the buffer to the zip file

				if( buffer_stream.export_buffer_and_close(destination) )
					D.ebug("\t\t\tGot data from internal buffer");
				else
				{	
					D.ebug("\t\tCopying from temporary file");

					// If we get here, then the data couldn't be
					// transferred from the internal buffer to the
					// destination archive because the file was
					// large enough that the whole file wasn't
					// contained in the in-memory buffer.

					InputStream in = new FileInputStream(stream.temporary_file());

					byte[]	    buffer = new byte[1024];
					int			got    = 0;
					while( (got = in.read(buffer)) > 0 )
						destination.write( buffer, 0, got );
					in.close();
					stream.delete_temporary();
				}
			}

			destination.closeEntry();
			write_accomplished();	  
		}
	}
}
