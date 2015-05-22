/*
 * Created on Jan 5, 2004
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.plugin.tool.LiveUpdate;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.URL;

import javax.swing.JProgressBar;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;

import de.freegroup.digitalsimulator.Configuration;
import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.WinUtil;
import de.freegroup.digitalsimulator.dialogs.MsgBox;
import de.freegroup.digitalsimulator.dialogs.ProgressDialog;
import de.freegroup.digitalsimulator.plugin.PluginManager;
import de.freegroup.digitalsimulator.plugin.tool.ITool;
import de.freegroup.digitalsimulator.plugin.tool.LiveUpdate.castor.Update;
import de.freegroup.digitalsimulator.plugin.tool.LiveUpdate.castor.UpdateFile;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;
import de.freegroup.digitalsimulator.update.LiveUpdateObject;
import de.freegroup.digitalsimulator.update.UpdateManager;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class Tool implements ITool, ILiveUpdateObject
{
  public static StringBuffer downloadMessages = null;
  /**
   * only to test this class
   * 
   * @param args
   */
  public static void main(String[] args)
	{
		new Tool().run();
	}
  /* (non-Javadoc)
	 * @see de.freegroup.digitalsimulator.plugin.tool.ITool#getMenuEntry()
	 */
	public String getMenuEntry()
	{
		return "MENU.TOOL.LIVEUPDATE";
	}
	/* (non-Javadoc)
	 * @see de.freegroup.digitalsimulator.plugin.tool.ITool#getId()
	 */
	public String getId()
	{
		return ""+hashCode();
	}
	/* (non-Javadoc)
	 * @see de.freegroup.digitalsimulator.plugin.tool.ITool#run()
	 */
	public void run()
	{
    boolean restartRequired   = false;
    downloadMessages = new StringBuffer();
    Dialog dlg = new Dialog();

    if(dlg.isOk())
    {
      Trace.info("checking proxy settings");
      if(dlg.useProxy())
      {
        Trace.info("set proxy using");
        appendMessage("using proxy for HTTP connection: <b>["+dlg.getHTTPProxyHost()+":"+dlg.getHTTPProxyPort()+"]</b>");
        System.getProperties().put( "proxySet", "true" );
        System.getProperties().put( "proxyHost", dlg.getHTTPProxyHost() );
        System.getProperties().put( "proxyPort", dlg.getHTTPProxyPort() );
      }
      else
      {
        Trace.info("remove proxy");
        System.getProperties().put( "proxySet", "false" );
      }

     
      // save the dialog settings
      //
      Trace.info("saving configuraion to property file");
      Configuration.setString("proxySet" ,dlg.useProxy()?"true":"false");
      Configuration.setString("proxyHost", dlg.getHTTPProxyHost());
      Configuration.setString("proxyPort", dlg.getHTTPProxyPort());

      // retrieve the plugin.xml from the website
      //
      try
      {
        String version = Configuration.getString("ApplicationVersion");
        version = version.replace('.','_');
        
        URL url = new URL("http://DigitalSimulator.de/LiveUpdate/"+version+"/update.xml?dummy42="+System.currentTimeMillis());
        
        appendMessage("Connecting server <b>["+url+"]</b> to read update information<br>");
        String appPath = Configuration.getString(Configuration.APPLICATION_PATH);
        Update updateObject = Update.unmarshal(new InputStreamReader(url.openStream()));
        appendMessage("Found "+updateObject.getUpdateFileCount()+" files for update check.<br>");
        for(int i =0;i<updateObject.getUpdateFileCount();i++)
        {
          UpdateFile file = updateObject.getUpdateFile(i);
          appendMessage("<ul>Testing file:"+file.getRelativePath());
          try
					{
						LiveUpdateObject luo = UpdateManager.getUpdateableObject(file.getRelativePath());
						if(file.getVersion()>0 && luo==null)
						{
						  appendMessage("<li>Found new File <b>["+file.getRelativePath()+"]</b> for download</li>");
						  download(file.getDownloadUrl(),appPath+ file.getRelativePath(), file.getSize());
              appendMessage("<li><font color=\"00FF00\" >File successfull installed.</font></li>");
              restartRequired = true;
						}
            // no version check if the remote version=0. In this case the file
            // must only exist on the local machine
            else if(file.getVersion()==0)
            {
            	try
							{
            		  File testFile = new File(appPath+file.getRelativePath());
                  if(!testFile.exists())
                  {
                    download(file.getDownloadUrl(), testFile.getAbsolutePath(),file.getSize());
                    appendMessage("<li><font color=\"00FF00\" >File successfull installed.</font></li>");
                    restartRequired = true;
                  }
                  else
                  {
                    appendMessage("<li><font color=\"00FF00\" >File already exists. Download not neccessary.</font></li>");
                  }
							}
							catch (Exception e)
							{
							
							}
            }
						else if (file.getVersion()>luo.getVersion())
						{
						  appendMessage("<li>Remote file has greater version ["+file.getVersion()+">"+luo.getVersion()+"]"+file.getRelativePath()+"</li>");
						  download(file.getDownloadUrl(),appPath+ file.getRelativePath(),file.getSize());
              appendMessage("<li><font color=\"00FF00\" >File successfull updated.</font></li>");
              restartRequired = true;
						}
						else
						{
						 appendMessage("<li>Update not neccessary. File is up to date.</li>"); 
						}
            appendMessage("</ul><br>"); 
          }
					catch (Exception e)
					{
            appendMessage("<li><font color=\"FF0000\" >Unable to install new file!</font></li>");
            appendMessage("</ul><br>"); 
            appendError(e.toString());
					}
        }
        appendMessage("<h2>Update done.</h2>"); 
      }
      catch(java.net.UnknownHostException exc)
      {
        appendError("unable to connect to foreign host<br>"+exc);
        restartRequired = false;
      }
      catch(Exception ex)
      {
        appendError("Unknown error during connect to foreign host<br>"+ex);
        restartRequired = false;
      }
      new StatusReportDialog(downloadMessages.toString(),restartRequired);
    }
    else
    {
      // don't update the plugins
      Trace.info("user don't want update the plugins");
    }
  }
 
  /**
   * 
   * @param from
   * @param to
   */
  private static void download(String from, String to, int bytes) throws Exception
  {
      appendMessage("<li>Download file from ["+from+"] to ["+to+"]</li>");
      ProgressDialog dialog = new ProgressDialog("Download....",I18N.get("COMMON.MESSAGE.DOWNLOADINPROGRESS")+to, bytes);
      InputStream  in  = new URL(from).openStream();
      OutputStream out = new FileOutputStream(to);

      byte [] buffer = new byte[1024];
      int bytes_read;
      int total = 0;
      while((bytes_read = in.read(buffer)) != -1)
      {
        out.write(buffer,0,bytes_read);
        total += bytes_read;
        dialog.setValue(total);
      }
      out.close();
      in.close();
      dialog.dispose();
      dialog = null;
  }

  static protected void appendMessage(String message)
  {
    if(downloadMessages!=null)
      downloadMessages.append(message);
  }
  
  static protected void appendError(String message)
  {
    if(downloadMessages!=null)
      downloadMessages.append("<font color=\"FF0000\" >"+message+"</font>");
  }
  
  /**
   * Interface implementation for ILiveUpdateObject
   */
  public int getVersion()
  {
   return 1; 
  }
}
