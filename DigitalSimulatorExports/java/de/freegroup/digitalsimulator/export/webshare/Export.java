package de.freegroup.digitalsimulator.export.webshare;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import java.io.StringBufferInputStream;

import javax.swing.ImageIcon;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

import HTTPClient.Codecs;
import HTTPClient.HTTPConnection;
import HTTPClient.HTTPResponse;
import HTTPClient.NVPair;

import com.meterware.httpunit.GetMethodWebRequest;
import com.meterware.httpunit.WebConversation;
import com.meterware.httpunit.WebRequest;
import com.meterware.httpunit.WebResponse;

import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.dialogs.MsgBox;
import de.freegroup.digitalsimulator.export.webshare.dialogs.UserPasswordDialog;
import de.freegroup.digitalsimulator.export.webshare.dialogs.WebFileManager;
import de.freegroup.digitalsimulator.plugin.export.IExport;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;


public class Export implements IExport, ILiveUpdateObject
{
   private static String  user;
   private static String  passwd;
   private static boolean identOk=false;

   /**
    * Interface implementation for ILiveUpdateObject
    */
   public int getVersion()
   {
    return 3;
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
        upload(dsimFile, pngImage);
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

   public String getMenyEntry()
   {
    return "MENU.ENTRY.EXPORT.WEBSHARE";
   }

   public String getDescription()
   {
    return "EXPORT.WEBSHARE.DESCRIPTION";
   }
   
   private static void upload(String simFile, String screenshoot)
   {
      try
      {
        WebConversation conversation = new WebConversation();

        String warningString = "";
        while(!identOk)
        {
          UserPasswordDialog userDlg = new UserPasswordDialog(warningString, user);
          if(userDlg.isOk())
          {
            // test the password
            // if ok => break
            WebRequest  request  = new GetMethodWebRequest("http://www.DigitalSimulator.de/webstore/checkPasswd.php3");
            user   = userDlg.getUser() ;
            passwd = userDlg.getPassword();
            request.setParameter("user"  , user );
            request.setParameter("passwd", passwd);
            WebResponse response = conversation.getResponse(request);
            if(response.getText().trim().equalsIgnoreCase("true"))
            {
                identOk=true;
                break;
            }
            warningString = I18N.get("COMMON.MESSAGE.INVALIDPASSWORD");
          }
          else
          {
            return;
          }
        }

        WebFileManager fs= new WebFileManager(user,passwd,simFile, screenshoot);
      }
      catch (Exception ex)
      {
         new MsgBox(I18N.get("COMMON.MESSAGE.UNABLETOCONNECTWEBSITE"));
      }
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