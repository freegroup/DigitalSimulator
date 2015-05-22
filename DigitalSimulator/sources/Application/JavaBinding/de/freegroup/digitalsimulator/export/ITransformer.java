package de.freegroup.digitalsimulator.export;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import java.io.*;
import Trace;
import Configuration;
import I18N;

import de.freegroup.digitalsimulator.dialogs.MsgBox;

public abstract class ITransformer
{
   public abstract void   transformAndDisplay(String xmlData);
   public abstract String getShortName();
   public abstract String getDescription();

   public void displayText(String textInput)
   {
      try
      {
         File tmpFile = new File(Configuration.getString(Configuration.TEMP_PATH)+"circuit.txt");
   //      tmpFile.createNewFile();
         if(tmpFile.exists())
            tmpFile.delete();
         tmpFile.createNewFile();

         FileOutputStream of = new FileOutputStream( tmpFile);
         of.write(textInput.getBytes());
         of.close();
         java.lang.Runtime.getRuntime().exec("write.exe "+tmpFile.getAbsolutePath());
        }
        catch (Exception ex)
        {
            Trace.error(ex);
            new MsgBox(I18N.translate("Es ist ein Fehler bei der Anzeige aufgetretten."));
       }
   }

   public void displayPDF(byte[] pdfInput)
   {
      try
      {
         File tmpFile = new File(Configuration.getString(Configuration.TEMP_PATH)+"circuit.pdf");
         if(tmpFile.exists())
            tmpFile.delete();
         tmpFile.createNewFile();

         FileOutputStream of = new FileOutputStream( tmpFile);
         of.write(pdfInput);
         of.close();
         System.out.println(tmpFile.getAbsolutePath());
         java.lang.Runtime.getRuntime().exec("cmd /C  "+tmpFile.getAbsolutePath());

      }
      catch (Exception ex)
      {
         Trace.error(ex);
         new MsgBox(I18N.translate("Es ist ein Fehler bei der Anzeige aufgetretten."));
      }
   }
}