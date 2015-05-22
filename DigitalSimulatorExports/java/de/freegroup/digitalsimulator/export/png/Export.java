package de.freegroup.digitalsimulator.export.png;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.StringBufferInputStream;

import javax.swing.ImageIcon;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

import de.freegroup.digitalsimulator.Configuration;
import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.plugin.export.IExport;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;
import de.freegroup.util.file.Display;
import de.freegroup.util.file.Stream;

public class Export  implements IExport, ILiveUpdateObject
{
  /**
   * Interface implementation for ILiveUpdateObject
   */
  public int getVersion()
  {
    return 2;
  }
  
   public void run(String xmlData)
   {
    try
    {
      // extract the tmp image name and the tmp file name for the upload
      // from the xml data.
      //
      DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
      DocumentBuilder        builder = factory.newDocumentBuilder();
      Document doc = builder.parse(new StringBufferInputStream(xmlData));
      
      Element   root;
      
      // find all Attributes and insert them in a map
      //
      root = doc.getDocumentElement ();
      NodeList rootList= root.getElementsByTagName("tmpCircuitPath");
      
      // create all nodes
      //
      String pngImage = "";
      String dsimFile = "";
      if(rootList.getLength() >= 1)
        dsimFile = rootList.item(0).getFirstChild().getNodeValue();
      
      rootList= root.getElementsByTagName("imagePath");
      if(rootList.getLength() >= 1)
        pngImage = rootList.item(0).getFirstChild().getNodeValue();
      Trace.info("image:"+pngImage);
      Trace.info("dsim:"+dsimFile);

    
      JFileChooser chooser = new JFileChooser();
      chooser.setDialogType(JFileChooser.SAVE_DIALOG);
      chooser.addChoosableFileFilter(new ExampleFileFilter("png", "PNG Image Files"));
      chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
      chooser.setMultiSelectionEnabled(false);
      
      // Init the last working directory
      //
      String path = Configuration.getString("WorkingDirectory");
      if(!path.equals(""))
      	chooser.setCurrentDirectory(new File(path));
      
      int retval = chooser.showDialog(null, I18N.get("COMMON.BUTTON.SAVE"));
      if (retval == JFileChooser.APPROVE_OPTION) 
      {
          File theFile = chooser.getSelectedFile();
          if (theFile != null) 
          {
            if (theFile.isDirectory()) 
              JOptionPane.showMessageDialog(null, "You chose this directory: " +theFile.getPath());
            else 
            {  
              String filename = theFile.getAbsolutePath();
              if(!filename.endsWith(".png"))
                filename = filename +".png";
              InputStream  tmpImage = new FileInputStream(new File(pngImage));
              OutputStream newImage = new FileOutputStream(new File(filename));
              Stream.copyStream(tmpImage,newImage);
              tmpImage.close();
              newImage.close();
              // Save the lat directory. The dialog (and others) can switch to this
              // directory if the view a file chooser....
              //
              Configuration.setString("WorkingDirectory",theFile.getParent());
              //JOptionPane.showMessageDialog(null, "You chose this file: " + theFile.getPath());
            }
          }
      } 
    }
    catch (Exception e)
    {
      Trace.error(e);
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
      return "MENU.ENTRY.EXPORT.PNGIMAGE";
   }

  public String getDescription()
   {
      return "EXPORT.PNGIMAGE.DESCRIPTION" ;
   }
  
  /**
   * only to test this class
   */
  public static void main(String[] args)
  {
    Export export = new Export();
    export.run(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"+
        "<circuit name=\"Komparator.dsim\">"+
        "<circuitPath>D:\\FreeGroup\\DigitalSimulator\\bin\\examples\\Komparator.dsim</circuitPath>"+
        "<tmpCircuitPath>D:\\FreeGroup\\DigitalSimulator\\bin\\temp\\Komparator_12.dsim</tmpCircuitPath>"+
        "<imagePath>D:\\FreeGroup\\DigitalSimulator\\bin\\temp\\ShiftRegister, loadable_7.png</imagePath>"+
        "</circuit>"
    );
  }
  }

