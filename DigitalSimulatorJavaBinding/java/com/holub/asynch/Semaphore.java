//----------------------------------------------------------------------
// This code (c) 1998 Allen I. Holub. All rights reserved.
//----------------------------------------------------------------------
// This code may not be distributed by yourself except in binary form,
// incorporated into a java .class file. You may use this code freely
// for personal purposes, but you may not incorporate it into any
// commercial product with express permission of Allen I. Holub in writing.
//----------------------------------------------------------------------

package com.holub.asynch;

interface Semaphore
{
	int  id		();
	void acquire(long timeout)	throws InterruptedException,
									   Timed_out;
	void release();

	public static class Timed_out extends java.lang.RuntimeException
	{	Timed_out(){ super("Timed out while waiting to acquire semaphore"); };
	}
}
