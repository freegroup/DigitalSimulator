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
import java.util.Arrays;
import java.util.Comparator;

class Lock_manager
{
	private static  int[]	id_lock = new int[1];
	private static  int		id_pool = 0;

	public static int new_id( )
	{
		int id;
		synchronized( id_lock )	{
			id = id_pool++;		}
		return id;
	}

	/**
	 *	Every mutex is given a unique int ID when it's created. This
	 *	function returns once all of the locks in the incoming
	 *  array have been successfully acquired. Locks are always
	 *  acquired in ascending order of id to attempt to avoid
	 *  deadlock situations.
	 *
	 *	@param <b>locks</b>	All of these locks must be acquired before
	 *			acquire_multiple returns.
	 *	@param <b>timeout</b> Maximum time to wait to acquire each
	 *			lock (milliseconds). The total time for the multiple
	 *			acquire operation could be (timeout * locks.length).
	 **/

	public static void acquire_multiple( Semaphore[] locks, long timeout )
												throws InterruptedException
	{
		Arrays.sort(locks, new Lock_comparator() );
		for( int i = 0; i < locks.length; ++i )
			locks[i].acquire( timeout ) ;
	}

	private static class Lock_comparator implements Comparator
	{	public int compare(Object a, Object b)
		{	return ((Semaphore)a).id() - ((Semaphore)b).id();
		}
		public boolean equals(Object obj)
		{	return obj instanceof Lock_comparator;
		}
	}
}
