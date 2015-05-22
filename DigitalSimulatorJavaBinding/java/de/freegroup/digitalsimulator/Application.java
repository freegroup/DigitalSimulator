package de.freegroup.digitalsimulator;

import java.io.File;
import java.util.ArrayList;
import java.util.Iterator;

import javax.swing.UIManager;

import com.jgoodies.clearlook.ClearLookManager;
import com.jgoodies.clearlook.ClearLookMode;
import com.jgoodies.plaf.FontSizeHints;
import com.jgoodies.plaf.Options;
import com.jgoodies.plaf.plastic.Plastic3DLookAndFeel;

import de.freegroup.digitalsimulator.dialogs.HelpAboutDialog;
import de.freegroup.digitalsimulator.plugin.PluginManager;
import de.freegroup.digitalsimulator.plugin.dialog.IDialog;
import de.freegroup.digitalsimulator.plugin.export.ExportManager;
import de.freegroup.digitalsimulator.plugin.export.IExport;
import de.freegroup.digitalsimulator.plugin.object.ObjectPlugin;
import de.freegroup.digitalsimulator.plugin.tool.ITool;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;
import de.freegroup.digitalsimulator.update.LiveUpdateObject;
import de.freegroup.digitalsimulator.update.UpdateManager;
import de.freegroup.util.file.Directory;
/**
 *  Description of the Class
 *
 *@author     c5026971
 *@created    2. Oktober 2001
 */
public class Application
{
	private static final Class[] CALLBACK_SIGNATURE = { String.class };
  private static boolean isRunningInDigiSim = false;
  
  /**
   * only to test this class
   * @param args
   */
  public static void main(String[] args)
	{
		onInit();
	}
  
	/**
	 *  Description of the Method
	 */
	public static void onInit()
	{
    isRunningInDigiSim = true;
    
    Trace.info("Setting up Java Look&Feel");
    Trace.info("------------------------------");
    
		UIManager.put("Application.useSystemFontSettings", Boolean.TRUE);
		Options.setGlobalFontSizeHints(FontSizeHints.MIXED);
		ClearLookManager.setMode(ClearLookMode.ON);
    try
    {
      UIManager.setLookAndFeel("com.jgoodies.plaf.plastic.PlasticXPLookAndFeel");
    }
    catch (Exception e)
    {
      // Likely PlasticXP is not in the class path; ignore.
    }
		Plastic3DLookAndFeel.setHighContrastFocusColorsEnabled(true);
		UIManager.put("Application.useSystemFontSettings", Boolean.TRUE);
		UIManager.put(Options.USE_SYSTEM_FONTS_APP_KEY, Boolean.TRUE);
		UIManager.put("ScrollBar.is3DEnabled", Boolean.FALSE);
		Options.setGlobalFontSizeHints(FontSizeHints.MIXED);
		Plastic3DLookAndFeel.setFontSizeHints(FontSizeHints.SYSTEM);
    
    registerJarsForUpdate();
    
    /* THE IntergerSpinner doesn't work with the different theme packs
     *
    try
    {
        String themepack = Configuration.getString(Configuration.THEMES_PATH)+"whistlerthemepack.zip";
        if (themepack.endsWith(".xml"))
        {
          SkinLookAndFeel.setSkin(SkinLookAndFeel.loadThemePackDefinition(SkinUtils.toURL(new File(themepack))));
        }
        else
        {
          SkinLookAndFeel.setSkin(SkinLookAndFeel.loadThemePack(themepack));
        }
        SkinLookAndFeel.enable();
    }
    catch (Exception ex)
    {
      Trace.error("MESSAGE",ex);
    }
    */
    
    // Register the main executable for the LiveUpdate feature
    //
    registerExeForUpdate();
    
		Trace.info("Loading java extensions");
		Trace.info("------------------------------");
		//Trace.info(System.getProperties().toString());
		try
		{
      String pluginDir = Configuration.getString(Configuration.PLUGIN_PATH);
      String appsDir   = Configuration.getString(Configuration.APPLICATION_PATH);
      ArrayList files = Directory.getAll(new File(pluginDir), false);
			Iterator iter = files.iterator();
			while (iter.hasNext())
			{
				File file = (File) iter.next();
        String origFile = file.getAbsolutePath();
				String className = null;
				// get the class name of the file
				//
				if (file.getName().endsWith(".class"))
				{
					className = file.getName().substring(0, file.getName().length() - 6);
				}
				// get the class name from the manifest entry
				//
				else if (file.getName().endsWith(".jar"))
				{
					try
					{
						java.util.jar.JarFile jarfile = new java.util.jar.JarFile(file);
//						Trace.info(jarfile.getManifest().getMainAttributes().values().toString());
						className = jarfile.getManifest().getMainAttributes().getValue("Main-Class");
					}
					catch (Exception ex)
					{
						Trace.warning("Exception during read of jar file", ex);
					}
				}
				else
				{
					// ignore the class or package
					continue;
				}
        Trace.info("tested file [" + file.getName() + "]");
				Trace.info("Founded plugin class [" + className + "]");
				// check if the class inherited from ObjectPlugin and register
				// this class in the DigitalSimulator
				//
				if (className != null)
				{
					Object obj = Class.forName(className).newInstance();
          if (obj instanceof ObjectPlugin)
					{
						PluginManager.registerPlugin(file.getAbsolutePath(), className);
						// call the object initilizer
						//
						((ObjectPlugin) obj).init();
            int index = file.getAbsolutePath().indexOf(".jar");
            origFile = file.getAbsolutePath().substring(0,index)+".object";
            // test if it is an object from the object wizard
            // Then register the *.object file and not the jar
            //
            File testFile= new File(origFile);
            if(!testFile.exists())
              origFile = file.getAbsolutePath();
          }
					else if (obj instanceof IExport)
					{
						ExportManager.registerExportModul(className);
            int index = file.getAbsolutePath().indexOf(".jar");
            origFile = file.getAbsolutePath().substring(0,index)+".export";
          }
          else if (obj instanceof ITool)
          {
            PluginManager.registerTool((ITool) obj);
            int index = file.getAbsolutePath().indexOf(".jar");
            origFile = file.getAbsolutePath().substring(0,index)+".tool";
          }
          else if (obj instanceof IDialog)
          {
            PluginManager.registerDialog((IDialog) obj);
            int index = file.getAbsolutePath().indexOf(".jar");
            origFile = file.getAbsolutePath().substring(0,index)+".dialog";
          }
          
          if(obj instanceof ILiveUpdateObject)
          {
            ILiveUpdateObject updateObj = (ILiveUpdateObject)obj;
            String relPath = "./"+origFile.substring(appsDir.length());
            UpdateManager.register(new LiveUpdateObject(relPath,origFile,updateObj.getVersion()));
          }
        }
			}
		}
		catch (Throwable exc)
		{
			Trace.error("Unable to load all object plugins", exc);
		}
    
    // start a thread for the garbage collection
    try
    {
      // The Thread is for the second event loop.
      // Is there no Thread the main GUI from the DigitalSimulator
      // will not receive any paint requests.
      //
      Thread thread = new Thread(new Runnable()
          {
        public void run()
        {
          while (true)
					{
            try
						{
              Trace.info("running System.gc()");
							System.gc();
							System.gc();
							System.gc();
							System.gc();
							System.runFinalization();
							Thread.sleep(2000);
              
						}
						catch (InterruptedException e)
						{
              return;
						}
          }
        }
      });
      thread.setDaemon(true);
      thread.start();
    }
    catch (Throwable ex)
    {
      Trace.error("Unable to create Dialog Thread", ex);
    }
    
	}
  /**
   *  Description of the Method
   */
  public static void onExit()
  {
    Trace.info("Application.onExit() called");
  }
  
  /**
   *  Description of the Method
   */
  public static void onHelpAbout()
  {
    try
    {
      // The Thread is for the second event loop.
      // Is there no Thread the main GUI from the DigitalSimulator
      // will not receive any paint requests.
      //
      Thread thread = new Thread(new Runnable()
          {
        public void run()
        {
          new HelpAboutDialog();
        }
      });
      thread.setDaemon(true);
      thread.start();
    }
    catch (Throwable ex)
    {
      Trace.error("Unable to create Dialog Thread", ex);
    }
  }
  
  /**
   *
   */
  public static void onToolCall(String toolId)
  {
    Trace.info("Application.onTool(String toolID) called");
    try
    {
      // The Thread is for the second event loop.
      // Is there no Thread the main GUI from the DigitalSimulator
      // will not receive any paint requests.
      //
      final String x = toolId;
      Thread thread = new Thread(new Runnable()
          {
        public void run()
        {
          PluginManager.onToolCall(x);
        }
      });
      thread.setDaemon(true);
      thread.start();
    }
    catch (Throwable ex)
    {
      Trace.error("Unable to create Dialog Thread", ex);
    }
  }

  /**
   *
   */
  public static void onDialogCall(String dialogId)
  {
    try
    {
      // The Thread is for the second event loop.
      // Is there no Thread the main GUI from the DigitalSimulator
      // will not receive any paint requests.
      //
      final String x = dialogId;
      Thread thread = new Thread(new Runnable()
          {
        public void run()
        {
          PluginManager.onDialogCall(x);
        }
      });
      thread.setDaemon(true);
      thread.start();
    }
    catch (Throwable ex)
    {
      Trace.error("Unable to create Dialog Thread", ex);
    }
  }

	/**
	 *  Description of the Method
	 *
	 *@param  xmlData  Description of Parameter
	 */
	public static void onExport(String xmlData)
	{
		Trace.info("Application.onExport(String xmlData) called");
    try
    {
      // The Thread is for the second event loop.
      // Is there no Thread the main GUI from the DigitalSimulator
      // will not receive any paint requests.
      //
      final String x = xmlData;
      Thread thread = new Thread(new Runnable()
          {
        public void run()
        {
          ExportManager.export(x);
        }
      });
      thread.setDaemon(false);
      thread.start();
    }
    catch (Throwable ex)
    {
      Trace.error("Unable to create Export Thread", ex);
    }
	}

  /**
	 * @return
	 */
	public static boolean isRunningInDigiSim()
	{
		return isRunningInDigiSim;
	}

  /*
   * try to register all jars in the lib directory for the DigitalSimulator
   * UpdateManager
   * 
   */
  private static void registerJarsForUpdate()
  {
    try
    {
      String appsDir   = Configuration.getString(Configuration.APPLICATION_PATH);
      String jarDir = appsDir+"jars\\";
      ArrayList files = Directory.getAll(new File(jarDir), false);
      Iterator iter = files.iterator();
      while (iter.hasNext())
      {
        File file = (File) iter.next();
        String version = null;
        // get the class name of the file
        //
        if (file.getName().endsWith(".jar"))
        {
          try
          {
            java.util.jar.JarFile jarfile = new java.util.jar.JarFile(file);
            version = jarfile.getManifest().getMainAttributes().getValue("Jar-Version");
            if(version!=null)
            {
              String fullPath = jarDir+file.getName();
              String relPath  = ".\\jars\\"+file.getName();
              int    intVersion  = 0;
              try{intVersion = Integer.parseInt(version);}catch (Exception e){/*ignore*/}
              UpdateManager.register(new LiveUpdateObject(relPath, fullPath,intVersion));
            }
          }
          catch (Exception ex)
          {
            /*ignore*/
          }
        }
        else
        {
          // ignore the class or package
          continue;
        }
      }
    }
    catch (Exception exc)
    {
      Trace.error("Unable to load all object plugins", exc);
    }
  }
  
  /**
   * TODO: die EXE ist noch von Windows gelockt. Hier muss noch ein kleines Wunder passieren...
   *
   */
  private static void registerExeForUpdate()
  {
    String buildId = Configuration.getString("ApplicationBuildNumber");
    try
		{
			int appVersion = Integer.parseInt(buildId);
      String relPath = "DigitalSimulator.exe";
      String absPath = Configuration.getString(Configuration.APPLICATION_PATH)+relPath;
      UpdateManager.register(new LiveUpdateObject(relPath, absPath, appVersion));
		}
		catch (Exception e)
		{
			// ignore
		}
  }
}
