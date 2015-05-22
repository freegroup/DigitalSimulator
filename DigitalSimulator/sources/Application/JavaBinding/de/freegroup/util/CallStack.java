package de.freegroup.util;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import java.io.*;

public class CallStack {

    public CallStack()
    {
    }

   public String getCurrentMethod()
   {

      // Returns a string of the current method
      StringWriter sw = new StringWriter();
      PrintWriter pw = new PrintWriter(sw);

      (new Throwable()).printStackTrace(pw);

      // Get the whole stack trace
      String s = sw.toString();

      StringReader   sr = new StringReader(s);
      BufferedReader br = new BufferedReader(sr);


      // Get the calling function which is always the 4th line
      String methodName = "";
      String name = "";
      boolean search = true;
      int line = 0;
      while (search)
      {
         line++;
         try { methodName = br.readLine();}
         catch (Exception e)
         { return "Trace getCurrentMethod () STACK ERROR"; }


         if (methodName == null)
         {
            search = false;
         }

         if (line == 3)
         {
            name = methodName;
         }

      }

      methodName = name;

      System.out.println(methodName);

      // Strip off word "at"
      int start = methodName.indexOf("at");
      if (start >=0)
      {
         methodName = methodName.substring(start+2, methodName.length());
      }


      // Strip off the word "(Compiled Code)"
      start = methodName.indexOf("(Compiled Code)");
      if (start >=0)
      {
         methodName = methodName.substring(0, start);

      }

      // Trim leading blanks
      methodName = methodName.trim();

      return methodName;
   }
}