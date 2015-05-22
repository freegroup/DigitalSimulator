package de.freegroup.digitalsimulator.plugin;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import Configuration;
import Trace;
import JUtil;
import Application;
import I18N;
import java.util.*;
import java.io.*;
import java.net.*;
import org.w3c.dom.Document;
import org.w3c.dom.*;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.xml.sax.*;
import de.freegroup.digitalsimulator.dialogs.*;
import ObjectPlugin;
import de.freegroup.util.file.Directory;


public class PluginManager
{
    public static DownloadReportDialog reportDlg=null;

    /**
     * only to test the class
     *
     */
    public static void main(String[] args)
    {
        upload();
    }

    /**
     *
     */
    public static void upload()
    {
    }

    /**
     *
     */
    public static void download()
    {
        int     newPluginCount    = 0;
        int     allPluginCount    = 0;
        int     updatePluginCount = 0;
        boolean restartRequired   = false;

        String directory = Configuration.getString(Configuration.PLUGIN_PATH);


        PluginUpdateDialog dlg = new PluginUpdateDialog();

        // load the configuration settings
        //
        dlg.setUseProxy((Configuration.getString("proxySet").equalsIgnoreCase("true")));
        dlg.setHTTPProxyHost(Configuration.getString("proxyHost"));
        dlg.setHTTPProxyPort(Configuration.getString("proxyPort"));

        JUtil.setWindowAlwaysOnTop(JUtil.getHwnd(dlg.getTitle()),true);
        dlg.show();
        if(dlg.isOk())
        {
            Trace.info("checking proxy settings");
            if(dlg.useProxy()==true)
            {
                Trace.info("set proxy using");
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
                JUtil.setWindowAlwaysOnTop(JUtil.getHwnd(reportDlg.getTitle()),true);
                reportDlg.show();
                reportDlg.setVisible(true);
                reportDlg.setMessage(I18N.translate("Lese Aktualisierungs-Information...."));

                DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
                DocumentBuilder builder = factory.newDocumentBuilder();
                URL url = new URL("http://www.digital-simulator.de/updates/info.php3?dummy42="+System.currentTimeMillis());

                Document doc = builder.parse(new InputSource(url.openStream()));


                Element  root;
                NodeList rootList;

                // find all Plugins and copy them to the plugin directory
                //
                root = doc.getDocumentElement();

                rootList= root.getElementsByTagName("Plugin");
                for(int nodeIndex=0 ; rootList.getLength() >nodeIndex ;nodeIndex++)
                {
                    String   id          = rootList.item(nodeIndex).getAttributes().getNamedItem("id").getNodeValue();
                    String   name        = rootList.item(nodeIndex).getAttributes().getNamedItem("name").getNodeValue();
                    String   fileName    = rootList.item(nodeIndex).getAttributes().getNamedItem("fileName").getNodeValue();
                    String   className   = rootList.item(nodeIndex).getAttributes().getNamedItem("className").getNodeValue();
                    String   type        = rootList.item(nodeIndex).getAttributes().getNamedItem("type").getNodeValue();
                    String   version     = rootList.item(nodeIndex).getAttributes().getNamedItem("version").getNodeValue();
                    String   urlString   = rootList.item(nodeIndex).getAttributes().getNamedItem("url").getNodeValue();

                    // update statistik
                    allPluginCount++;

                    Trace.info("checking Plugin:["+className+"]");

                    // install new Plugin
                    //
                    if(!isInstalled(className))
                    {
                        newPluginCount++;

                        reportDownload(fileName);
                        // retrieve the file and store them in the plugin directory
                        //
                        InputStream  in  = new URL(urlString).openStream();
                        OutputStream out = new FileOutputStream(directory+fileName);

                        byte [] buffer = new byte[1024];
                        int bytes_read;
                        while((bytes_read = in.read(buffer)) != -1)
                        {
                            out.write(buffer,0,bytes_read);
                        }
                        out.close();
                        in.close();
                        restartRequired = true;
                    }
                    // update installed plugin
                    //
                    else if(isNewVersion(className, version))
                    {
                        updatePluginCount++;

                        reportDownload(fileName);
                        // retrieve the file and store them in the plugin directory
                        //
                        Trace.info("download: "+urlString);
                        InputStream  in  = new URL(urlString).openStream();
                        OutputStream out = new FileOutputStream(directory+fileName);

                        byte [] buffer = new byte[1024];
                        int bytes_read;
                        while((bytes_read = in.read(buffer)) != -1)
                        {
                            out.write(buffer,0,bytes_read);
                        }
                        out.close();
                        in.close();
                        restartRequired = true;
                    }
                }
                reportDlg.setVisible(false);
                reportDlg.hide();

                // display the corresponding update status dialog
                //
                if(allPluginCount==0)
                {
                    new MsgBox(I18N.translate("Es wurden keine neuen Objekt Plugins installiert."));
                }
                else if(newPluginCount!=0)
                {
                    new MsgBox(I18N.translate("Es wurden die neue Objekt-Plugins installiert."));
                }
                else if(updatePluginCount!=0)
                {
                    new MsgBox(I18N.translate("Es wurden die Objekt-Plugins aktualisiert."));
                }
                else
                {
                    new MsgBox(I18N.translate("Ihr DigitalSimulator ist bereits auf dem neusten Stand. Update nicht notwendig."));
                }
            }
            catch(java.net.UnknownHostException exc)
            {
                reportDlg.setVisible(false);
                reportDlg.hide();
                Trace.error("unable to connect to foreign host",exc);
                restartRequired = false;
                new MsgBox(I18N.translate("Konnte keine Verbindung zu 'www.digital-simulator.de' herstellen!"));
             }
            catch(Exception ex)
            {
                reportDlg.setVisible(false);
                reportDlg.hide();
                Trace.error("Unknown error during connect to foreign host",ex);
                new MsgBox(I18N.translate("Unbekannter Fehler wärend des Updates aufgetretten!"));
            }
            if(restartRequired)
                new MsgBox(I18N.translate("DigitalSimulator bitte neu starten um die Programmerweiterungen zu aktivieren."));
        }
        else
        {
            // don't update the plugins
            Trace.info("user don't want update the plugins");
        }
    }

    public native static void registerPlugin(String className);

    /**
     *
     */
    static public boolean isInstalled(String className)
    {
        try
        {
            Object object = Class.forName(className).newInstance();
            if(object instanceof ObjectPlugin)
            {
                return true;
            }
            else
            {
                Trace.warning("Class found but is not an instace of ObjectPlugin");
            }
        }
        catch (Exception ex)
        {
            Trace.info("Plugin not installed :"+className);
        }
        return false;
    }

    /**
     *
     */
    static public boolean isNewVersion(String className, String versionString)
    {
        try
        {
            Object object = Class.forName(className).newInstance();
            if(object instanceof ObjectPlugin)
            {
                ObjectPlugin plugin= (ObjectPlugin)object;
                Trace.info("checking Plugin '"+className+"' installed version='"+plugin.getVersion()+"' WebSite version='"+versionString+"'");
                if(!plugin.getVersion().equals(versionString))
                {
                    return true;
                }
            }
            else
            {
                Trace.warning("Class found but is not an instace of ObjectPlugin");
            }
        }
        catch (Exception ex)
        {
            Trace.info("Plugin not installed :"+className);
        }
        return false;
    }


    /**
     *
     */
    static protected void reportDownload(String fileName)
    {
        Trace.info("Update Plugin: "+fileName);
        reportDlg.setMessage("downloading plugin: "+fileName);
    }


    /**
     *
     */
    static
    {
        reportDlg = new DownloadReportDialog();
        reportDlg.hide();
    }

}