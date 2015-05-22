package de.freegroup.digitalsimulator.export.rawxml;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import de.freegroup.digitalsimulator.export.ITransformer;

public class Transformer extends ITransformer
{

   public void transformAndDisplay(String xmlInput)
   {
        displayText(transform(xmlInput));
   }

   public String transform(String xmlInput)
   {
        return xmlInput;
   }

   /**
    *
    */
   public String getShortName()
   {
      return "01 Generisches XML-Format des Simulators";
   }

  public String getDescription()
   {
      return "Exportiert die Schaltung in ein allgemeines XML Format\n\n"+
             "Alle Elemente der Schaltung werden mit der internen\n"+
             "Objekt-Bezeichnung samt einer eindeutigen Objekt-Id aufgeführt.\n"+
             "\n"+
             "Dieses Format kann für eigene Tools (z.B. Konvertierung\n"+
             "nach Spice) verwendet werden.\n"+
             "Das Format dient bereits anderen Export-Modulen als Basis.\n" ;
   }
}

