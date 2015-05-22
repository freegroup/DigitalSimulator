//----------------------------------------------------------------------
// This code (c) 1998 Allen I. Holub. All rights reserved.
//----------------------------------------------------------------------
// This code may not be distributed by yourself except in binary form,
// incorporated into a java .class file. You may use this code freely
// for personal purposes, but you may not incorporate it into any
// commercial product with express permission of Allen I. Holub in writing.
//----------------------------------------------------------------------

package com.holub.asynch;

import com.holub.asynch.Semaphore;

// Implementation of a mutual-exclusion semaphore. It can be owned by
// only one thread at a time. The thread can acquire it multiple times,
// but there must be a release for every acquire.

public class Mutex implements Semaphore
{
	private Thread	owner 	   = null;	// Owner of mutex, null if nobody
	private int 	lock_count = 0;

	private final int _id 	= Lock_manager.new_id();
	public 		  int id()	{ 	return _id; 		}

	/**
	 * Acquire the mutex. The mutex can be acquired multiple times
	 * by the same thread, provided that it is released as many
	 * times as it is acquired. The calling thread blocks until
	 * it has acquired the mutex. (There is no timeout).
	 *
	 * @param timeout If 0, then the behaviour of this function is
	 *				  identical to {@link acquire_without_blocking}.
	 *				  If nonzero, then the timeout is the the most
	 *				  amount of time that you'll wait (in milliseconds).
	 *				  Use Long.MAX_VALUE to wait forever.
	 *
	 * @throw InterruptedException if the waiting thread is interrupted
	 *				  before the timeout expires.
	 *
	 * @return false if you timed out, true if you got the mutex.
	 *
	 * @see release
	 * @see acquire_without_blocking
	 */

	public synchronized void acquire( long timeout )
										 throws InterruptedException,
												Semaphore.Timed_out
	{	
		if( timeout == 0 )						// don't wait at all
		{	acquire_without_blocking();
		}
		else if( timeout == Long.MAX_VALUE )	// wait forever
		{	while( !acquire_without_blocking() ) 
				this.wait( timeout );
		}
		else									// wait limited by timeout
		{	if( !acquire_without_blocking() )
			{	this.wait( timeout );
				if( !acquire_without_blocking() )
					throw new Semaphore.Timed_out();
			}
		}
	}
  public synchronized void acquire()  throws InterruptedException,             Semaphore.Timed_out
  {
    acquire(Long.MAX_VALUE);
  }
	/**
	 * Attempts to acquire the mutex. Returns false (and does not
	 * block) if it can't get it.
	 *
	 * @return true if you get the mutex, false otherwise.
	 * @see release
	 * @see acquire
	 */

	public synchronized boolean acquire_without_blocking()
	{
		if( owner == null )
		{	owner = Thread.currentThread();
			lock_count = 1;
			return true;
		}

		if( owner == Thread.currentThread() )
		{	++lock_count;
			return true;
		}

		return false;
	}

	/**
	 * Release the mutex. The mutex has to be released as many times
	 * as it was acquired to actually unlock the resource. The mutex
	 * must be released by the thread that acquired it
	 *
	 * @throws Mutex.OwnershipException (a RuntimeException) if a thread
	 *		other than the current owner tries to release the mutex.
	 */

	public synchronized void release()
	{
		if( owner != Thread.currentThread() )
			throw new OwnershipException();

		if( --lock_count <= 0 )
		{	owner = null;
			notify();
		}
	}

	public static class OwnershipException extends RuntimeException
	{	public OwnershipException()
		{	super("Thread calling release() doesn't own Mutex");
		}
	}
}
