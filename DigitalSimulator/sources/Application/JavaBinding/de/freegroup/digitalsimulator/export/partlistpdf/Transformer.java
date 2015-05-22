package de.freegroup.digitalsimulator.export.partlistpdf;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */

import java.io.*;

import org.xml.sax.InputSource;
import org.xml.sax.XMLReader;

import org.apache.fop.apps.Driver;
import org.apache.fop.apps.Version;
import org.apache.fop.apps.XSLTInputHandler;
import java.net.*;

import org.apache.fop.messaging.MessageHandler;
import org.apache.avalon.framework.logger.ConsoleLogger;
import org.apache.avalon.framework.logger.Logger;

import de.freegroup.digitalsimulator.export.*;
import Configuration;
import Trace;

public class Transformer extends ITransformer
{
//    static int counter =-1;
    Logger log = null;

    public void transformAndDisplay(String xmlData)
    {
         de.freegroup.digitalsimulator.export.wired.Transformer trans = (de.freegroup.digitalsimulator.export.wired.Transformer)ExportManager.getModul("02 Teileliste im XML-Format");
         displayPDF(transform(trans.transform( xmlData)));
    }

    public byte[] transform(String xmlData)
    {
        try
        {
           File f = new File("c:test.txt");
           PrintStream out = new PrintStream( new FileOutputStream(f));
           System.setOut(out);
           System.setErr(out);
           System.getProperties().list(out);
        }
        catch (Exception ex)
        {
        }
        System.setProperty("jaxp.debug","true");

        Trace.info(xmlData);
        System.setProperty("javax.xml.transformer.TransformerFactory","org.apache.xalan.processor.TransformerFactoryImpl");
        if(log == null)
        {
         log = new ConsoleLogger(ConsoleLogger.LEVEL_WARN);
         MessageHandler.setScreenLogger(log);
        }

        String xsl = Configuration.getString(Configuration.APPLICATION_PATH) +"xslt/partlist.xsl";
        //xsl = (Transformer.class.getResource("test.xsl")).openStream();

        //Trace.info("xsl template ["+xsl+"]");
        File   xmlFile=null;
         try
         {
             // create the tmp XML file for the XSLT/FOP parser
             //
             xmlFile = new File(Configuration.getString(Configuration.TEMP_PATH)+"circuit.xml");

             if(xmlFile.exists())
                xmlFile.delete();
             xmlFile.createNewFile();
             FileWriter writer = new FileWriter(xmlFile);

             writer.write("<?xml version=\"1.0\"  encoding=\"ISO-8859-1\"?>\n");
             writer.write(xmlData);
             writer.close();


             //
             //
             XSLTInputHandler input = new XSLTInputHandler(xmlFile, new File(xsl));
             return renderXML(input);
         }
          catch (Exception ex)
         {
             Trace.error(ex);
         }
         finally
         {
             xmlFile.delete();
         }
         return null;
    }

    /**
     *
     */
    public byte[] renderXML(XSLTInputHandler input)
    {
        try
        {
            ByteArrayOutputStream out = new ByteArrayOutputStream();

            Driver driver = new Driver();
            driver.setLogger(log);
            driver.setRenderer(Driver.RENDER_PDF);
            driver.setOutputStream(out);
            driver.render(input.getParser(), input.getInputSource());

            return out.toByteArray();
        }
        catch (Exception ex)
        {
            Trace.error(ex);
            ex.printStackTrace();
        }
        return  null;
    }
    /**
     * creates a SAX parser, using the value of org.xml.sax.parser
     * defaulting to org.apache.xerces.parsers.SAXParser
     *
     * @return the created SAX parser
     */
    static XMLReader createParser() throws Exception
    {
        String parserClassName = System.getProperty("org.xml.sax.parser");
        if (parserClassName == null)
        {
            parserClassName = "org.apache.xerces.parsers.SAXParser";
        }
        return (XMLReader) Class.forName( parserClassName).newInstance();
     }

   /**
    *
    */
   public String getShortName()
   {
      return "03 Teileliste im PDF-Format";
   }

   public String getDescription()
   {
      return "Teileliste/Verbindugnsliste als PDF Dokument.\n"+
             "\n"+
             "ALLE benötigten elektronischen Teile und Verbindungen der\n"+
             "Schaltung werden berechnet und aufgelistet.\n\n"+
             "Im Moment werden die 74LSxx Logigbausteine verwendet.Andere\n"+
             "Datensätze sind bereits in Vorbereitung (CMOS)\n\n\n"+
             "Diese Ausgabe ist noch als Testversion zu verstehen. Es\n"+
             "kann keine Garantie für das funktionieren der Schaltung\n"+
             "übernommen werden.";
   }
}
