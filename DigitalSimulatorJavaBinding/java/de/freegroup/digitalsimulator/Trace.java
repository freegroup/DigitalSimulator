package de.freegroup.digitalsimulator;
import java.util.*;
import java.io.*;

public class Trace
{
	protected static native void n_error(String message);
  protected static native void n_warning(String message);
  protected static native void n_info(String message);
  
	public static void error(String message)
	{
		if (Application.isRunningInDigiSim())
			n_error(message);
		else
			System.out.println("error:"+message);
	}
  
  public static void warning(String message)
  {
  	if (Application.isRunningInDigiSim())
  		n_warning(message);
  	else
  		System.out.println("warning:" + message);
  }
  
  public static void info(String message)
  {
  	if (Application.isRunningInDigiSim())
  		n_info(message);
  	else
  		System.out.println("info:"+message);
  }

   public static void error(String message, Throwable exc)
   {
      error(message +"\n"+toString(exc));
   }

   public static void warning(String message, Throwable exc)
   {
      warning(message +"\n"+toString(exc));
   }

   public static void info(String message, Throwable exc)
   {
      info(message +"\n"+toString(exc));
   }

   public static void error( Throwable exc)
   {
      error(toString(exc));
   }

   public static void warning(Throwable exc)
   {
      warning(toString(exc));
   }

   public static void info( Throwable exc)
   {
      info(toString(exc));
   }

   public static String toString(Throwable exc)
   {
      StringWriter sw = new StringWriter();
      PrintWriter pw = new PrintWriter(sw);

      exc.printStackTrace(pw);
      return sw.toString();
   }
}

