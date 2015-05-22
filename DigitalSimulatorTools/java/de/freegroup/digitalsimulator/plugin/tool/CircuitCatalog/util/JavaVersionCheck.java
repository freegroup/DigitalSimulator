package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.util;

/**
 * Checks to make sure your Java version starts with at least X.X
 * <p/>
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class JavaVersionCheck {


   public static boolean checkMin(double minVersion) {
      String version = System.getProperty("java.version");
      double ver = 0.0;
      try {
         ver = Double.parseDouble(version.substring(0, 3));
      }
      catch (NumberFormatException e) {
         e.printStackTrace();
      }
      if (ver >= minVersion) {
         return true;
      }
      else {
         return false;
      }
   }

   /**
    * @param args the command line arguments
    */
   public static void main(String[] args) {
      System.out.println(checkMin(1.4));
   }


}
