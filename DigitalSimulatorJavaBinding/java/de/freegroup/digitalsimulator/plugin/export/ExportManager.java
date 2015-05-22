package de.freegroup.digitalsimulator.plugin.export;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import JUtil;

import java.util.HashMap;

import javax.swing.plaf.OptionPaneUI;

import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.dialogs.MsgBox;
import de.freegroup.digitalsimulator.dialogs.ProgressDialog;
import de.freegroup.digitalsimulator.dialogs.WaitDialog;

public class ExportManager
{
   protected static HashMap exportModuls = new HashMap();

   public static HashMap getExportModuls()
   {
      return exportModuls;
   }

   public static IExport getModul(String modulName)
   {
      return (IExport)exportModuls.get(modulName);
   }

   /**
    * Shows an selection dialog and calls the export modul
    * if you press ok in the selection dialog. The exported
    * data will been shown in the associated application for
    * the exported file format.
    * 
    * @param xmlData
    */
   public static void export(String xmlData)
   {
      try
			{
				SelectExportModulDialog dlg = new SelectExportModulDialog();
				if(dlg.isOk())
				{
				    IExport trans = dlg.getTransformer();
				    if(trans!=null)
				    {  
				      Trace.info("Transformer ="+trans.getMenyEntry());
              
              WaitDialog pd = new WaitDialog("Generieren","create data....");
				      trans.run(xmlData);
              pd.dispose();
              pd=null;
				    }
				}
			}
			catch (Throwable e)
			{
				// TODO Auto-generated catch block
				Trace.info(e);
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
         IExport trans = (IExport) Class.forName(clazz).newInstance();
         exportModuls.put(trans.getMenyEntry(), trans);
      }
      catch (Exception ex)
      {
      	  Trace.warning(ex);
      }
   }


//   static
//   {
//      registerExportModul("de.freegroup.digitalsimulator.plugin.export.wired.Transformer");
//      registerExportModul("de.freegroup.digitalsimulator.plugin.export.rawxml.Transformer");
//      registerExportModul("de.freegroup.digitalsimulator.plugin.export.partlistpdf.Transformer");
//   }
}