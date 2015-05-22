package com.holub.tools;

public class Assert
{
	public final static void failure( String message )
	{}

	public final static void is_true( boolean expression )
	{}

	public final static void is_false( boolean expression )
	{}

	public final static void is_true(boolean expression, String message)
	{}

	public final static void is_false(boolean expression,String message)
	{}

	static public class Failed extends RuntimeException
	{	public Failed( 		      ){ super("Assert Failed"); }
		public Failed( String msg ){ super(msg); 		     }
	}
}	
