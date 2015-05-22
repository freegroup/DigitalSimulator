package de.freegroup.digitalsimulator.export.documentation;

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

import javax.swing.ImageIcon;

import org.apache.fop.messaging.MessageHandler;
import org.apache.avalon.framework.logger.ConsoleLogger;
import org.apache.avalon.framework.logger.Logger;
import org.apache.bcel.generic.IUSHR;

import de.freegroup.digitalsimulator.Configuration;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.plugin.export.*;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;
import de.freegroup.util.file.Display;

public class Export  implements IExport, ILiveUpdateObject
{
    Logger log = null;

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
    public void run(String xmlData)
    {
         Display.displayFile(transform(xmlData),"circuit.pdf");
    }

    /**
     * 
     * @param xmlData
     * @return
     */
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

        String xsl = Configuration.getString(Configuration.PLUGIN_PATH) +"ExportDocumentation/documentation.xsl";

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

    public ImageIcon getIcon()
    {
      return new ImageIcon(Export.class.getResource("icon.gif"));
    }

   /**
    *
    */
   public String getMenyEntry()
   {
      return "MENU.ENTRY.EXPORT.DOCUMENTATION";
   }

   public String getDescription()
   {
      return "EXPORT.DOCUMENTATION.DESCRIPTION";
   }
}
