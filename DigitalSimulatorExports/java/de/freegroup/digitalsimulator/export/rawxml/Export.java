package de.freegroup.digitalsimulator.export.rawxml;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import javax.swing.ImageIcon;

import de.freegroup.digitalsimulator.plugin.export.IExport;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;
import de.freegroup.util.file.Display;

public class Export  implements IExport, ILiveUpdateObject
{
  /**
   * Interface implementation for ILiveUpdateObject
   */
  public int getVersion()
  {
    return 2;
  }
  
   public void run(String xmlInput)
   {
        Display.displayFile(xmlInput, "circuit.xml");
   }

   public ImageIcon getIcon()
   {
   	return new ImageIcon(Export.class.getResource("icon.gif"));
   }

   /**
    *
    */
   public String getMenyEntry()
   {
    return "MENU.ENTRY.EXPORT.RAWXML";
   }

  public String getDescription()
   {
      return "EXPORT.RAWXML.DESCRIPTION";
      /*
      return "Exportiert die Schaltung in ein allgemeines XML Format\n\n"+
             "Alle Elemente der Schaltung werden mit der internen\n"+
             "Objekt-Bezeichnung samt einer eindeutigen Objekt-Id aufgeführt.\n"+
             "\n"+
             "Dieses Format kann für eigene Tools (z.B. Konvertierung\n"+
             "nach Spice) verwendet werden.\n"+
             "Das Format dient bereits anderen Export-Modulen als Basis.\n" ;
*/             
   }
}

