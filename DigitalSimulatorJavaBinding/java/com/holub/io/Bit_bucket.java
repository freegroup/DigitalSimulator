package com.holub.io;
import java.io.*;

/**
 * The Bit_bucket class overrides all methods of PrintWriter to
 * do nothing.
 *
 *	<table border=1 cellspacing=0 cellpadding=5><tr><td><font size=-1><i>
 *	<center>(c) 2000, Allen I. Holub.</center>
 *	<p>
 *	This code may not be distributed by yourself except in binary form,
 *	incorporated into a java .class file. You may use this code freely
 *	for personal purposes, but you may not incorporate it into any
 *	commercial product without
 *	the express written permission of Allen I. Holub.
 *	</font></i></td></tr></table>
 *
 *	@author Allen I. Holub
 */

public final class Bit_bucket extends PrintWriter
{
	public Bit_bucket(){ super( System.err ); }

	public void	   close()	   							{}
	public void	   flush()	   							{}
	public void	   print(boolean b)						{}
	public void	   print(char c)						{}
	public void	   print(char[] s)						{}
	public void	   print(double d)						{}
	public void	   print(float f)						{}
	public void	   print(int i)							{}
	public void	   print(long l)						{}
	public void	   print(Object o)						{}
	public void	   print(String  s)						{}
	public void	   println()							{}
	public void	   println(boolean b)					{}
	public void	   println(char c)						{}
	public void	   println(char[] s)					{}
	public void	   println(double d)					{}
	public void	   println(float f)						{}
	public void	   println(int i)						{}
	public void	   println(long l)						{}
	public void	   println(Object o)					{}
	public void	   write(char[] buf)					{}
	public void	   write(char[] buf, int off, int len)	{}
	public void	   write(int c)							{}
	public void	   write(String buf)					{}
	public void	   write(String buf, int off, int len)	{}
}
