package com.holub.io;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;

/** Convenience wrappers that hide the complexity of creating
 *	<code>Readers</code> and <code>Writers</code> simply to access standard input and output.
 *  For example, a call to
 *	<PRE>
 *	Std.out().println("hello world");
 *	</PRE>
 *	is identical in function to:
 *	<PRE>
 *	new PrintWriter(System.out, true).println("hello world");
 *	</PRE>
 *	and
 *	<PRE>
 *	String line = Std.in().readLine();
 *	</PRE>
 *	is identical in function to:
 *	<PRE>
 *	String line;
 *	try
 *	{	line = new BufferedReader(new InputStreamReader(System.in)).readLine();
 *	}
 *	catch( Exception e )
 *	{	throw new Error( e.getMessage() );
 *	}
 *	</PRE>
 *	Equivalent methods provide access to standard error
 *	and a "bit bucket" that just absorbs output without printing it.
 *
 *	<p>All of these methods create Singleton objects. For example, the
 *	same <code>PrintWriter</code> object that is created the first time
 *	you call <code>Std.out()</code> is returned by all subsequent calls.
 *  This way you don't incur the overhead of a <code>new</code> with
 *	each I/O request.
 *
 *	<table>
 *	<tr><td>6-13-00</td><td>	Modified to initialize all fields at
 *								class-load time to eliminate SMP-related
 *								synchronization problems.
 *	</td></tr>
 *	</table>
 *
 * <table border=1 cellspacing=0 cellpadding=5><tr><td><font size=-1><i>
 * <center>(c) 2000, Allen I. Holub.</center>
 * <p>
 * This code may not be distributed by yourself except in binary form,
 * incorporated into a java .class file. You may use this code freely
 * for personal purposes, but you may not incorporate it into any
 * commercial product without
 * the express written permission of Allen I. Holub.
 * </font></i></td></tr></table>
 *
 * @see com.holub.tools.P
 * @see com.holub.tools.R
 * @see com.holub.tools.E
 * @author Allen I. Holub
 */

public final class Std
{
// 	static{ new JDK_11_unloading_bug_fix(Std.class); }	//#bug_fix

	private static BufferedReader input;		//= null
	private static PrintWriter 	  output; 		//= null
	private static PrintWriter 	  error;  		//= null
	private static PrintWriter 	  bit_bucket;	//= null

	// These are static because they're used to implement
	// critical sections.

	private static final Object	input_lock		= new Object();
	private static final Object	output_lock		= new Object();
	private static final Object	error_lock		= new Object();
	private static final Object	bit_bucket_lock	= new Object();

	/*******************************************************************
	 * A private constructor prevents anyone from manufacturing an
	 * instance.
	 */
	private Std(){}

	/*******************************************************************
	 * Get a BufferedReader that wraps System.in
	 */
	public static BufferedReader in()
	{	synchronized( input_lock )
		{	if( input == null )
		    {	try
				{	input =	new BufferedReader(
									new InputStreamReader(System.in));
				}
				catch( Exception e )
				{	throw new Error( e.getMessage() );
				}
			}
			return input;
		}
	}

	/*******************************************************************
	 * Get a PrintWriter that wraps System.out.
	 */
	public static PrintWriter out()
	{	synchronized( output_lock )
		{	if( output == null )
				output = new PrintWriter( System.out, true );
			return output;
		}
	}

	/*******************************************************************
	 * Get a PrintWriter that wraps System.err.
	 */

	public static PrintWriter err()
	{	synchronized( error_lock )
		{	if( error == null )
				error = new PrintWriter( System.err, true );
			return error;
		}
	}

	/*******************************************************************
	 * Get an output stream that just discards the characters that are
	 * sent to it. This convenience class makes it easy to write methods
	 * that are passed a "Writer" to which error messages or status information
	 * is logged. You could log output to standard output like this:
	 *	<PRE>
	 *	x.method( Std.out() );	// pass in the stream to which messages are logged
	 *	</PRE>
	 *	But you could cause the logged messages to simply disappear
	 *	by calling:
	 *	<PRE>
	 *	x.method( Std.bit_bucket() );	// discard normal logging messages
	 *	</PRE>
	 */

	public static PrintWriter bit_bucket()
	{	synchronized( bit_bucket_lock )
		{	if( bit_bucket == null )
				bit_bucket = new Bit_bucket();
			return bit_bucket;
		}
	}

	/**	A small test class. This class reads a line from standard input and
	 *	echoes it to standard output and standard error. Run it
	 *	with: <blockquote><i>java com.holub.tools.Std\$Test</i></blockquote>
	 *	(Don't type in the \ when using a Microsoft-style shell.)
	 */

	static public class Test
	{
		static public void main( String[] args ) throws IOException
		{	String s;
			while( (s = Std.in().readLine()) != null )
			{	Std.out().println( s );
				Std.err().println( s );
				Std.bit_bucket().println( s );
			}
		}
	}
}
