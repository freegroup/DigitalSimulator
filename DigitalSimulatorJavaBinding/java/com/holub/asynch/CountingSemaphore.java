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
import com.holub.asynch.Lock_manager;

class CountingSemaphore implements Semaphore
{
	private int			count;
	private final int	max_count;
  
	/*****************************************************************
	 *	Create a counting semaphore with the specified initial and
	 *	maximum counts. release(), which increments the count, is not
	 *  permitted to increment it past the maximum. If the initial_count
	 *  is larger than the max_count, it is silently truncated.
	 *
	 *  @see release
	 */
	CountingSemaphore( int initial_count, int max_count )
	{
		this.max_count	= max_count;
		this.count		= (initial_count > max_count)
									? max_count : initial_count ;
	}

	/*****************************************************************
	 *	Create a counting semaphore with a maximum count of
	 *  Integer.MAX_VALUE
	 */
	CountingSemaphore( int initial_count )
	{	this( initial_count, Integer.MAX_VALUE );
	}

	/*****************************************************************
	 *	Required override of Semaphore.id(). Don't call this function.
	 *  @see Lock_manager
	 */

	public 		  int  id() { return _id; }
	private	final int  _id = Lock_manager.new_id();

	/*****************************************************************
	 *	Acquire the semaphore, decrementing the count. Block if the
	 *  count goes to zero. Bug: It's possible in some situations
	 *	for the timeout to be exceeded.
	 *
	 *	<p>I have deliberately not implemented a variant that allows
	 *	acquisition of multiple slots in a single call because it's not
	 *	clear what you'd do if all requested slots aren't available.
	 *
	 *  @throws InterruptedException if interrupted while waiting
	 *			for the semaphore.
	 *  @return true if we got the slot.
	 */
	public synchronized void acquire(long timeout)
											throws InterruptedException
	{	while( count <= 0 )
			this.wait( timeout );
		--count;
	}

	/*****************************************************************
	 *	Release the semaphore and increment the count.
	 *  This one is the generic release required by the Semaphore
	 *  interface, so all it can do is throw an exception if
	 *  there's an error.
	 *	@throws Counting_semaphore.TooManyReleases (a RuntimeException)
	 * 		if you try to release a semaphore whose count is already
	 *		at the maximum value.
	 */
	public synchronized void release(){ release(1); }

	/*****************************************************************
	 *	Release "increment" slots in the semaphore all at once.
	 *	@param <b>increment</b> The amount to increment the count.
	 *		If this	value is zero, the current count is returned and
	 *		no threads are released.
	 *	@throws Counting_semaphore.TooManyReleases (a RuntimeException)
	 * 		if the current value + count is greater than the maximum.
	 *		The semaphore will not have been modified in this case.
	 *	@return the value of the count after the increment is added.
	 */
	public synchronized int release( int increment )
	{
		int current_count = count;
		int new_count	  = count + increment;

		if( new_count > max_count )
			throw new TooManyReleases();

		count = new_count;
		if( current_count == 0 && count > 0 )
			notifyAll();

		return count;
	}

	/** Thrown if you try to release more than the maximum number
	 * of slots.
	 */
	public static class TooManyReleases extends RuntimeException	
	{	private TooManyReleases()
		{	super("Released semaphore that was at capacity");
		}
	}

	/*****************************************************************
	 *	A semaphore-specific release function, returns an error status
	 *	if the count would go past the initially specified maximum.
	 *  @returns true if the semaphore was successfully released, false
	 *	otherwise.
	 */
	public synchronized boolean notifying_release()
	{
		if( count >= max_count )
			return false;

		if( ++count == 1 )
			notifyAll();
		return true;
	}
}	
