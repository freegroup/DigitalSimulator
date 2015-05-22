package com.holub.io;
import  java.io.*;


import com.holub.io.Std;		// for testing
import com.holub.tools.Assert;	// for testing

// import com.holub.tools.debug.D;		// for testing
import com.holub.tools.D;		// for testing

/*	A DelayedOutputStream works like a FileOutputStream, except
 *	that the file is not opened until the first write occurs.
 *  Note that, though you'd like this class to extend
 *	<code>FileOutputStream</code> rather than <code>OutputStream</code>,
 *	that approach won't work here because all of the former's
 *	constructors actually open the file, and the whole point of
 *	the current exercise is not to do that.
 *
 *  <p>This class is not thread safe---two threads cannot safely
 *	write simultaneously to the same DelayedOutputStream without
 *	some sort of external synchronization.
 */

public class DelayedOutputStream extends OutputStream
{	
	private String  			file_name = null;
	private String				extension = null;
	private boolean				temporary = false;
	private File				file	  = null;
	private FileDescriptor		descriptor= null;
	private boolean				append	  = false;
	private boolean				closed	  = false;
	private FileOutputStream	out		  = null;

	//================================================================

	/** Creates a temporary file on first write. The file name
	 *	is the concatenation of the root, an arbitrary number,
	 *	and the extension.
	 *	@see #temporary_file
	 */
	public DelayedOutputStream( String root, String extension )
	{	Assert.is_true( root != null && extension != null );
		this.temporary = true;
		this.file_name = root;
		this.extension = extension;
	}

	public DelayedOutputStream( String file_name )
	{	Assert.is_true( file_name != null );

		this.file_name = file_name;
	}

	public DelayedOutputStream( String file_name, boolean append )
	{	Assert.is_true( file_name != null );

	 	this.file_name = file_name;
		this.append    = append;
	}

	public DelayedOutputStream( File file )
	{	Assert.is_true( file != null );

	 	this.file = file;
	}

	public DelayedOutputStream( FileDescriptor descriptor )
	{	Assert.is_true( descriptor != null );

	 	this.descriptor = descriptor;
	}

	//================================================================

	public void write(int the_byte) throws IOException
	{	open_file();
		out.write( the_byte );
	}

	public void write(byte[] bytes, int offset, int length)
												throws IOException
	{	Assert.is_true( bytes != null );

		open_file();
		out.write(bytes, offset, length);
	}

	public void write(byte[] bytes) throws IOException
	{	open_file();
		out.write(bytes, 0, bytes.length);
	}

	/** Close the stream. This method can be called even if the
	 *  underlying file has not been opened (because nobody's
	 *  written anything to it). It just silently does
	 *	nothing in this case.
	 */
	public void close()	throws IOException
	{	
		if( !closed )
		{
			closed = true;

			D.ebug("\t\tDelayedOutputStream closing "
				  +	( file!=null 	  ? file.getPath() :
				      file_name!=null ? file_name : "???"
					)
				  );

			if( out != null )
			{
				out.close();
				D.ebug("\t\t\tclose accomplished");
			}
			else D.ebug("\t\t\tno-op (file never opened)");

			// Null out all references *except* the "file"
			// reference for temporary files. (which might be
			// needed by a subsequent call to delete_temporary).

			file_name = null;
			extension = null;
			descriptor= null;
			out		  = null;

			if( !temporary )
				file = null;
		}
	}

	public void flush() throws IOException
	{	open_file();
		out.flush();
	}

	public FileDescriptor getFD() throws IOException
	{	if( out==null )
			throw new IOException("No FD yet in DelayedOutputStream");
		return out.getFD();
	}

	/** Return a <code>File</code> object that represents
	 *	the temporary file created by the
	 *	{@link DelayedOutputStream(String,String)} constructor.
	 *	@return the <code>File</code> reference or <code>null</code>
	 *	if the the temporary file hasn't been created (either
	 *  because nobody's written to the current stream or becuase
	 *	the current object doesn't represent a temporary file).
	 */
	public File temporary_file() throws IOException
	{	if( temporary )
			return file;
		return null;
	}

	/** If a temporary file has been created by a write operation,
	 *	delete it, otherwise do nothing.
	 *  @return true if the temporary file existed and was
	 *			successfully deleted, false if it didn't exist
	 *			or wasn't successfully deleted.
	 *  @throws IllegalStateException if the file hasn't been closed.
	 */
	public boolean delete_temporary()
	{	if( !closed )
			throw new IllegalStateException(
						  "Stream must be closed before underlying"
						+ " File can be deleted");

		boolean it_exists = temporary && (file != null);

		if( it_exists )
		{	D.ebug("\t\tDelayedOutputStream deleting " +file.getPath());

			if( !file.delete() )
				return false;
		}

		return it_exists;

	}

	/** If a temporary file has been created by a write operation,
	 *	rename it, otherwise do nothing. If a file with the same
	 *  name as the target exists, that file is deleted first.
	 *
	 *  @return true if the temporary file existed and was
	 *			successfully renamed, false if it didn't exist
	 *			or the rename attempt failed.
	 *  @throws IllegalStateException if the file hasn't been closed.
	 */

	public boolean rename_temporary_to( File new_name )
	{	if( !closed )
		{	throw new IllegalStateException(
						  "Stream must be closed before underlying"
						+ " File can be renamed");
		}
	
		boolean it_exists = temporary && (file != null);

		if( it_exists )
		{	D.ebug("\t\tDelayedOutputStream renaming "
				  	+	file.getPath()
					+ " to "
					+	new_name.getPath()
				  );

			if( new_name.exists() )
				if( !new_name.delete() )
					return false;

			if( !file.renameTo(new_name) )
				return false;
		}

		return it_exists;
	}

	/** Workhorse function called by write() variants before they
	 *  do any I/O in order to bring the file into existance.
	 */

	private void open_file() throws IOException
	{	
		if( closed )
			throw new IOException(
						"Tried to access closed DelayedOutputStream");
		if( out == null )
		{
			if( temporary )
			{	file = File.createTempFile(file_name,extension);
				file_name = null;
				extension = null;
			}

			if( file_name != null )
			{	out = new FileOutputStream(file_name, append);
				D.ebug("\t\tDelayedOutputStream created " + file_name );
			}
			else if( file != null )
			{	out = new FileOutputStream(file);
				D.ebug("\t\tDelayedOutputStream created " + file.getPath());
			}
			else if( descriptor != null )
			{	out = new FileOutputStream(descriptor);
				D.ebug("\t\tDelayedOutputStream created file from fd "
													+ descriptor.toString());
			}
			else
				Assert.failure(
					"DelayedOutputStream internal error: nothing to open");
		}
	}
}
