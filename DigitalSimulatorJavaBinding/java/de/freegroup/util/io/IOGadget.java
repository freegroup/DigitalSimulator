/*
 * Created on Jan 27, 2004
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.util.io;

import java.io.BufferedReader;
import java.io.InputStreamReader;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class IOGadget {
  private IOGadget(){}
  private static InputStreamReader isr = 
  new InputStreamReader(System.in);
  private static BufferedReader br = new
  BufferedReader(isr);
  public static final String readLine(String p) {
    String retVal = "";
    System.out.print(p+"> ");
    try {
      retVal = br.readLine();
    } 
    catch (Exception e) {
      System.err.println("IOGadget: " + e.getMessage());
    }
    return retVal;
  } // readLine
  public static int readInt(String prompt) {
    try {
      return Integer.parseInt(readLine(prompt));
    }
    catch(Exception e) {
      System.out.println("Error reading int");
      return 0;
    }
  }
  public static double readDouble(String prompt) {
    try {
      return Double.parseDouble(readLine(prompt));
    }
    catch(Exception e) {
      System.out.println("Error reading double");
      return 0.0;
    }
  }
} // IOGadget
