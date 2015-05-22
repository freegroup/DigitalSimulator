package de.freegroup.digitalsimulator.webstore;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import java.util.*;
import com.meterware.httpunit.*;


import de.freegroup.digitalsimulator.webstore.dialogs.GenericFileSelector;

import java.io.*;
import HTTPClient.*;
import de.freegroup.digitalsimulator.dialogs.UserPasswordDialog;


public class UploadManager
{
   private static String  user;
   private static String  passwd;
   private static boolean identOk=false;

   public static void upload(String simFile, String screenshoot)
   {
      try
      {
          WebConversation conversation = new WebConversation();

        String warningString = "";
        while(!identOk)
        {
          UserPasswordDialog userDlg = new UserPasswordDialog("Password dialog",warningString, user);
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
            warningString = "User or password invalid";
          }
          else
          {
            return;
          }
        }


         // create the FileList from the webserver
         //
         WebRequest  request  = new GetMethodWebRequest("http://www.DigitalSimulator.de/webstore/filelist.php3");
         request.setParameter("user"    , user    );
         request.setParameter("password", passwd);
         WebResponse response = conversation.getResponse(request);

         StringTokenizer token = new StringTokenizer(response.getText(),"\n\r");
         Vector filelist = new Vector();
         while(token.hasMoreTokens())
         {
            String filename = token.nextToken();
            filename = filename.substring(0,filename.length()-5);
            filelist.add(filename);
         }

         GenericFileSelector fs= new GenericFileSelector(filelist,"Upload your file");


         HTTPConnection con = new HTTPConnection("www.DigitalSimulator.de");
         NVPair[] opts = { new NVPair("user"       , user),
                           new NVPair("password"   , passwd),
                           new NVPair("targetName" , fs.getFilename())
                         };
         NVPair[] file = { new NVPair("simFile"    , simFile),
                           new NVPair("screenshoot", screenshoot)
                         };
         NVPair[] hdrs = new NVPair[1];
         byte[]   data = Codecs.mpFormDataEncode(opts, file, hdrs);
         HTTPResponse res = con.Post("webstore/upload.php3", data, hdrs);
         System.out.println(new String(res.getData()));
         System.out.println("done");
      }
      catch (Exception ex)
      {
         System.out.println(ex);
      }
   }


   /**
    *
    */
   public static void main(String[] args)
   {
      upload("D:\\projects\\DigitalSimulator\\bin\\temp\\Arbeitsblatt1.dsim","D:\\projects\\DigitalSimulator\\bin\\temp\\Arbeitsblatt1.png");
   }
}