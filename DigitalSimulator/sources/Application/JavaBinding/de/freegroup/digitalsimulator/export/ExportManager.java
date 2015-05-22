package de.freegroup.digitalsimulator.export;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import java.util.HashMap;
import Trace;
import de.freegroup.digitalsimulator.dialogs.MsgBox;
import de.freegroup.digitalsimulator.export.dialog.*;
import JUtil;

public class ExportManager
{
   protected static HashMap exportModuls = new HashMap();

   public static HashMap getExportModuls()
   {
      return exportModuls;
   }

   public static ITransformer getModul(String modulName)
   {
      return (ITransformer)exportModuls.get(modulName);
   }

   public static void export(String xmlData)
   {
        SelectExportModulDialog dlg = new SelectExportModulDialog();

        JUtil.setWindowAlwaysOnTop(JUtil.getHwnd(dlg.getTitle()),true);
        dlg.show();
        if(dlg.isOk())
        {
            ITransformer trans = dlg.getTransformer();
            Trace.info("Transformer ="+trans.getShortName());
            trans.transformAndDisplay(xmlData);
        }
   }


   /**
    *
    */
   public static void registerExportModul(String clazz)
   {
      Trace.info("register export Modul ["+clazz+"]");
      try
      {
         ITransformer trans = (ITransformer) Class.forName(clazz).newInstance();
         exportModuls.put(trans.getShortName(), trans);
      }
      catch (Exception ex)
      {

      }
   }

   /**
    * only to debug this class
    *
    */
    public static void main(String[] args)
    {
      export(de.freegroup.digitalsimulator.export.wired.test.TestCase02.testXML);
    }

//   static
//   {
//      registerExportModul("de.freegroup.digitalsimulator.export.wired.Transformer");
//      registerExportModul("de.freegroup.digitalsimulator.export.rawxml.Transformer");
//      registerExportModul("de.freegroup.digitalsimulator.export.partlistpdf.Transformer");
//   }
}