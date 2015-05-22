package de.freegroup.digitalsimulator.export.wired;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.export.wired.db.*;
import java.util.ArrayList;
import java.util.Iterator;

import org.w3c.dom.*;

import javax.swing.ImageIcon;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.xml.sax.*;
import java.io.*;
import java.util.*;
import de.freegroup.digitalsimulator.plugin.export.IExport;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;
import de.freegroup.util.file.Display;


public class Export  implements IExport, ILiveUpdateObject
{
   private HashMap pinMap    = null;
   private HashMap objectMap = null;
   private HashMap pin2Fanout= null;
   
   /**
    * Interface implementation for ILiveUpdateObject
    */
   public int getVersion()
   {
    return 2;
   }
  
   /**
    * 
    */
   public void run(String xmlInput)
   {
      Display.displayFile(transform(xmlInput),"circuit.xml");
   }

   /**
    * Transform the DigitalSimulator raw XML to the partlist of real world electric objects
    * and the connection list.
    * 
    * @param xmlInput
    * @return
    */
   public String transform(String xmlInput)
   {
        try
        {
            ObjectFactory.reset();
            pinMap    = new HashMap();
            objectMap = new HashMap();
            pin2Fanout= new HashMap();
            
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder        builder = factory.newDocumentBuilder();
            Document doc = builder.parse(new StringBufferInputStream( xmlInput));

            Element		root = doc.getDocumentElement ();
            String    imagePath = root.getElementsByTagName("imagePath").item(0).getChildNodes().item(0).getNodeValue();
            // Alle Output-Ports finden und den fanout bestimmen und merken. Dies ist für Optimierungen
            // notwendig, z.B. Bei LED's. Hat ein TTL-Baustein nur eine LED nachgeschaltet, dann ist es nicht
            // notwendig noch ein Transistor als Treiber vorzusehen. Ist dieser Ausgang jedoch noch an 10 weitere
            // Eingange weitergeleitet, dann würde die LED denn max. Stromfluss des Ausganges sprengen und der Baustein
            // würde zerstört.
            //
            NodeList p = root.getElementsByTagName("port");
            for(int i=0 ; p.getLength() >i ;i++)
            {
              Element port =  (Element)p.item(i);
              if(port.getParentNode().getNodeName().equals("output"))
              {
                String   id      = port.getAttributes().getNamedItem("id").getNodeValue();
                String   fanout  = port.getAttributes().getNamedItem("fanOut").getNodeValue();
                System.out.println(id+":"+fanout);
                pin2Fanout.put(id,fanout);
              }
            }
            NodeList rootList = root.getElementsByTagName("link");
            for(int nodeIndex=0 ; rootList.getLength() >nodeIndex ;nodeIndex++)
            {
              Element  link  =  (Element)rootList.item(nodeIndex);
              String   port1 = link.getAttributes().getNamedItem("port1").getNodeValue();  // input
              String   port2 = link.getAttributes().getNamedItem("port2").getNodeValue();  // output
              pin2Fanout.put(port1, pin2Fanout.get(port2));
            }
            
            // Alle Objekte anlegen welche benötigt werden.
            //
            String name= root.getAttributes().getNamedItem("name").getNodeValue();
            rootList= root.getElementsByTagName("object");
            for(int nodeIndex=0 ; rootList.getLength() >nodeIndex ;nodeIndex++)
            {
                Element node   =  (Element)rootList.item(nodeIndex);
                String  type   = node.getAttributes().getNamedItem("type").getNodeValue();
                String  nodeId = node.getAttributes().getNamedItem("id").getNodeValue();

                // Anzahl der Eingangs und der Ausgangsports bestimmen
                //
                int inputCount   = 0;
                int outputCount  = 0;
                int maxFanout    = 0;
                NodeList ports = node.getElementsByTagName("port");
                for(int i=0 ; ports.getLength() >i ;i++)
                {
                  Element port =  (Element)ports.item(i);
                  String   id  = port.getAttributes().getNamedItem("id").getNodeValue();
                  try{
                    maxFanout = Math.max(maxFanout,Integer.parseInt(pin2Fanout.get(id).toString()));
                  }
									catch (Exception e)
									{
										//ignore
									}
                  if(port.getParentNode().getNodeName().equals("input"))
                     inputCount++;
                  else
                     outputCount++;
                }
                // Jetzt kommen die tollen Ausnahmen
                // 1. Wenn das Objekt ein OBJ_LED ist und die diese als einzigstes an einem Ausgang
                //    angeschlossen ist, dann kann man eine einfache Variante der LED nehmen (ohne Treiber
                //    Transistor)
                if(type.endsWith("OBJ_LED") && maxFanout==1)
                  type = "OBJ_LED_fanout(1)";
                
                // Entsprechndes Object aus der Datenbasis lesen
                // und reservieren
                //
                String objectName = type +"_" + inputCount +"_"+ outputCount;
                ElectricObject eObj = ObjectFactory.getElectricObject(objectName);
                if(eObj==null)
                {
                  Trace.error("unable to locate object ["+objectName+"]");
                }
                objectMap.put(nodeId, eObj);
                ports = node.getElementsByTagName("port");
                for(int i=0 ; ports.getLength() >i ;i++)
                {
                  Element port =  (Element)ports.item(i);
                  String id  = port.getAttributes().getNamedItem("id").getNodeValue();
                  pinMap.put(id, eObj.getCasePin(i+1));
                }
            }

            rootList = root.getElementsByTagName("link");
            for(int nodeIndex=0 ; rootList.getLength() >nodeIndex ;nodeIndex++)
            {
                Element  link  =  (Element)rootList.item(nodeIndex);
                String   port1 = link.getAttributes().getNamedItem("port1").getNodeValue();
                String   port2 = link.getAttributes().getNamedItem("port2").getNodeValue();

                CasePin cpin1 = (CasePin)pinMap.get(port1);
                CasePin cpin2 = (CasePin)pinMap.get(port2);

                ObjectFactory.connect(cpin1,cpin2);
             }

             String result = "";//"<?xml version=\"1.0\"  encoding=\"ISO-8859-1\"?>\n";
             result += "<circuit name=\""+name+"\">\n";

             result += "\t<imagePath>";
             result += imagePath;
             result += "</imagePath>\n";
             
             result += "\t<description>\n";
             result += "\t\tDer Autor des DigitalSimulators achten bei seiner Software, Dokumentation und Bauanleitungen auf Aktualität, Korrektheit und Vollständigkeit. \n";
             result += "\t\tSollte es trotzdem zu Schäden irgendeiner Art kommen, welche durch die Nutzung der Software verursacht wurden, werden Haftungsansprüche gegen den oder die Autoren grundsätzlich ausgeschlossen. \n";
             result += "\t\tDer Autor behält sich vor, die Software oder Daten ohne Ankündigung zu verändern, zu ergänzen oder die Veröffentlichung einzustellen. \n";
             result += "\t</description>\n";
             
             result += "\t<parts>\n";
             int counter=0;
             for(Iterator iter = ObjectFactory.getUsedCases().iterator(); iter.hasNext();)
             {
                 ElectricCase eCase = (ElectricCase)iter.next();
                 eCase.setPartNum(++counter);
                 result +="\t\t<part partNumber=\""+eCase.getPartNum()+"\" name=\""+eCase.getName()+"\"  dataSheetURL=\""+eCase.getDescriptionURL()+"\" />\n";
             }
             result += "\t</parts>\n";
             result += "\t<connections>\n";
             for(Iterator iter = ObjectFactory.getUsedConnections().iterator(); iter.hasNext();)
             {
                 ObjectFactory.Connection con = (ObjectFactory.Connection)iter.next();
                 CasePin fromPin = con.getFromCasePin();
                 CasePin toPin   = con.getToCasePin();
                 result +="\t\t<connection fromPart=\""+fromPin.getCurrentElectricCase().getPartNum()+"\" fromPin=\""+fromPin.getNumber()+"\" fromPinDesc=\""+fromPin.getDescription()+"\"   toPart=\""+toPin.getCurrentElectricCase().getPartNum()+"\" toPin=\""+toPin.getNumber()+"\"  toPinDesc=\""+toPin.getDescription()+"\"   />\n";
             }
             result += "\t</connections>\n";
             result +="</circuit>\n";
             return result;
        }
        catch (SAXParseException err)
        {
            String errorMessage = "** Parsing error"
                                 + ", line " + err.getLineNumber ()
                               + ", uri " + err.getSystemId ();
            errorMessage += "   " + err.getMessage ();
            Trace.error(err);
            return errorMessage;
        }
        catch (SAXException e)
        {
            Trace.error(e);
            return "Es ist ein interner Fehler aufgetretten:\n\n"+ e.getMessage ();
        }
        catch (Throwable e)
        {
            Trace.error(e);
            return "Es ist ein interner Fehler aufgetretten:\n\n"+ e.getMessage ();
        }
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
    return "MENU.ENTRY.EXPORT.WIRED";
   }

   public String getDescription()
   {
      return "EXPORT.WIRED.DESCRIPTION";
      /*
      return "Teileliste/Verbindugnsliste als XML.\n"+
             "\n"+
             "ALLE benötigten elektronischen Teile und Verbindungen der\n"+
             "Schaltung werden berechnet und aufgelistet.\n\n"+
             "Im Moment werden die 74LSxx Logigbausteine verwendet.Andere\n"+
             "Datensätze sind bereits in Vorbereitung (CMOS)\n\n\n"+
             "Diese Ausgabe ist noch als Testversion zu verstehen. Es\n"+
             "kann keine Garantie für das funktionieren der Schaltung\n"+
             "übernommen werden.";
      */             
   }

}