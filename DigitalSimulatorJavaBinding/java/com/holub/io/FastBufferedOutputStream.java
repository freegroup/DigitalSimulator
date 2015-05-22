package com.holub.io;
import  java.io.*;

import	com.holub.io.Std;		// for testing


/** This version of BufferedOutputStream isn't
 *	thread safe, so is much faster than the standard
 *	BufferedOutputStream in situations where the stream is not
 *	shared between threads; Otherwise, it works identically
 *	to {@link java.io.BufferedOutputStream}.
 */

public class FastBufferedOutputStream extends FilterOutputStream
{	
	private final int	   size;	  	// buffer size
	private		  byte[]   buffer;
	private 	  int	   current		 = 0;
	private		  boolean  flushed		 = false;
	private		  int	   bytes_written = 0;

	public static final int DEFAULT_SIZE = 2048*40;

	/**	Create a FastBufferedOutputStream whose buffer is
	 *	FastBufferedOutputStream.DEFULT_SIZE in size.
	 */
	public FastBufferedOutputStream( OutputStream out )
	{	this( out, DEFAULT_SIZE );
	}

	/**	Create a FastBufferedOutputStream whose buffer is
	 *	the indicated size.
	 */
	public FastBufferedOutputStream( OutputStream out, int size )
	{	super( out );
		this.size	= size;
		buffer		= new byte[ size ];
	}

	// Inherit write(byte[]);

	public void close() throws IOException
	{

		flush();
		buffer = null;
		current = 0;
		super.close();
	}

	public void flush() throws IOException
	{	if( current > 0 )
		{	
			out.write( buffer, 0, current );
			out.flush( );
			current = 0;
			flushed = true;
		}
	}

	/** Write a character on the stream. Flush the buffer
	 *	first if the buffer is full. That is, if you
	 *  have a 10-character buffer, the flush occurs
	 *  just before writing the 11th character.
	 */

	public void write(int the_byte) throws IOException
	{	
		if( current >= buffer.length )
			flush();	// resets current to 0

		buffer[current++] = (byte)the_byte;
		++bytes_written;
	}

	public void write(byte[] bytes, int offset, int length)
												throws IOException
	{	while( --length >= 0 )
			write( bytes[offset++] );
	}

	/**************************************************************
	 * Return the total number of bytes written to this stream.
	 */
	public int bytes_written(){ return bytes_written; }

	/**************************************************************
	 * Return the object wrapped by the FastBufferedOutputStream.
	 * (I don't consider this to be a violation of encapsulation
	 * because that object is passed into the Decorator, so is
	 * externally accessable anyway.) The internal buffer is
	 * flushed so it is safe to write directly to the
	 * "contents" object.
	 */

	public OutputStream contents() throws IOException
	{	flush();
		return out;
	}

	/**************************************************************
	 *	Return true if the buffer has been flushed to the underlying
	 *	stream.
	 */
	public boolean has_flushed(){ return flushed; }
	
	/**************************************************************
	 *	If the buffer has never been flushed to the wrapped stream,
	 *	copy it to <code>destination</code> stream and return true
	 *	(without sending the characters to the wrapped stream),
	 *  otherwise return false; in any event, close the stream.
	 *	@see #has_flushed
	 */

	public boolean export_buffer_and_close(OutputStream destination)
												throws IOException
	{	
		if( !flushed )
		{	destination.write( buffer, 0, current );
			current = 0;
		}
		close();
		return !flushed;
	}

	/**************************************************************
	 *	If the buffer has never been flushed to the wrapped stream,
	 *	return it;
	 *  otherwise return null. In any event, close the stream;
	 *	@see #has_flushed
	 */

	public byte[] export_buffer_and_close() throws IOException
	{	byte[] buffer = null;

		if( !flushed )
		{	buffer = this.buffer;
			current = 0;
		}
		close();
		return buffer ;
	}
}
