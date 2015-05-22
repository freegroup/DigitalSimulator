package com.holub.asynch;

//----------------------------------------------------------------------
// This code (c) 1998 Allen I. Holub. All rights reserved.
//----------------------------------------------------------------------
// This code may not be distributed by yourself except in binary form,
// incorporated into a java .class file. You may use this code freely
// for personal purposes, but you may not incorporate it into any
// commercial product with express permission of Allen I. Holub in writing.
//----------------------------------------------------------------------

/**
 *	This class implements a simple "condition variable." The notion
 *	is that a thread waits for some condition to become true.
 *	If the condition is false, then no wait occurs.
 *
 *	Be very careful of nested-monitor-lockout here:
 * <PRE>
 *	 class lockout
 *	 {	Condition godot = new Condition(false);
 *	 
 *	 	synchronized void f()
 *	 	{	
 *	 		some_code();
 *	 		godot.wait_for_true();
 *	 	}
 *	 
 *	 	synchronzed void set() // <b>Deadlock if another thread is in f()</b>
 *	 	{	godot.set_true();
 *	 	}
 *	 }
 * </PRE>
 *	You enter f(), locking the monitor, then block waiting for the
 *  condition to become true. Note that you have not released the
 *  monitor for the "lockout" object. [The only way to set godot true
 *  is to call set(), but you'll block on entry to set() because
 *	the original caller to f() has the monitor containing "lockout"
 *	object.]
 *	<p>Solve the problem by releasing the monitor before waiting:
 * <PRE>
 *	 class okay
 *	 {	Condition godot = new Condition(false);
 *	 
 *	 	void f()
 *	 	{	synchronized( this )
 *	 		{	some_code();
 *	 		}
 *	 		godot.wait_for_true();	// <b>Move the wait outside the monitor</b>
 *	 	}
 *	 
 *	 	synchronzed void set()
 *	 	{	godot.set_true();
 *	 	}
 *	 }
 * </PRE>
 * or by not synchronizing the `set()` method:
 * <PRE>
 *	 class okay
 *	 {	Condition godot = new Condition(false);
 *	 
 *	 	synchronized void f()
 *	 	{	some_code();
 *	 		godot.wait_for_true();
 *	 	}
 *	 
 *	 	void set()				// <b>Remove the synchronized statement</b>
 *	 	{	godot.set_true();
 *	 	}
 *	}
 * </PRE>
 * The normal wait()/notify() mechanism doesn't have this problem since
 * wait() releases the monitor, but you can't always use wait()/notify().
 */


public class Condition
{
	private boolean _is_true;

	/**	Create a new condition variable in a known state.
	 */
	public Condition( boolean is_true ){ _is_true = is_true; }

	/** See if the condition variable is true (without releasing).
	 */
	public synchronized boolean is_true()  { return _is_true; }

	/** Set the condition to false. Waiting threads are not affected.
	 */
	public synchronized void set_false(){ _is_true = false; }

	/** Set the condition to true. Waiting threads are not released.
	 */
	public synchronized void set_true()	{ _is_true = true; notifyAll(); }

	/** Release all waiting threads without setting the condition true
	 */
	public synchronized void release_all(){ notifyAll(); }

	/** Release one waiting thread without setting the condition true
	 */
	public synchronized void release_one(){ notify(); }

	/** Wait for the condition to become true.
	 *  @param timeout Timeout in milliseconds
	 */
	public synchronized void wait_for_true( long timeout )
											throws InterruptedException
	{	if( !_is_true )
			wait( timeout );
	}

	/** Wait (potentially forever) for the condition to become true.
	 */
	public synchronized void wait_for_true() throws InterruptedException
	{	if( !_is_true )
			wait();
	}
}
