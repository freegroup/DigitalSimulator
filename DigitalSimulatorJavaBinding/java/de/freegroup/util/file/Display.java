/*
 * Created on Jan 16, 2004
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.util.file;

import java.io.*;

import de.freegroup.digitalsimulator.Configuration;
import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.dialogs.MsgBox;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class Display
{
  /**
   * Helper function to display plain text
   * 
   * @param textInput
   */
 
  public static void displayFile(String textInput, String fileName)
  {
    displayFile(textInput.getBytes(),fileName);
  }

  /**
   * Helper function to display a byte array which contains a PDF document
   * 
   * @param pdfInput
   */
  public static void displayFile(byte[] pdfInput, String fileName)
  {
    try
    {
      File tmpFile = new File(Configuration.getString(Configuration.TEMP_PATH)+fileName);
      if(tmpFile.exists())
        tmpFile.delete();
      tmpFile.createNewFile();

      FileOutputStream of = new FileOutputStream( tmpFile);
      of.write(pdfInput);
      of.close();
      Trace.info("start shell to display:"+tmpFile.getAbsolutePath());
      Runtime.getRuntime().exec("rundll32 SHELL32.DLL,ShellExec_RunDLL "+tmpFile.getAbsolutePath());
    }
    catch (Exception ex)
    {
      Trace.error(ex);
      new MsgBox(I18N.get("Es ist ein Fehler bei der Anzeige aufgetretten."));
    }
  }
}
