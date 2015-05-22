package de.freegroup.digitalsimulator.plugin;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import java.util.HashMap;
import java.util.Map;

import de.freegroup.digitalsimulator.Application;
import de.freegroup.digitalsimulator.plugin.dialog.IDialog;
import de.freegroup.digitalsimulator.plugin.tool.ITool;


public class PluginManager
{
    private static Map plugin2jar = new HashMap();
    private static Map id2Tool    = new HashMap();
    private static Map id2Dialog  = new HashMap();
    
    // register the class in the DigitalSimulator
    // 
    private native static void n_registerTool(String menuEntry, String objId);
    private native static void n_registerDialog(String menuEntry, String objId);
    private native static void n_registerPlugin(String className);

    /**
     * execute the tool with the hands over toolId
     * 
     * @param toolId
     */
  	public static void onToolCall(String toolId)
  	{
  		ITool tool = (ITool)id2Tool.get(toolId);
      if(tool!=null)
      {
        tool.run();
      }
  	}
 

    /**
     * execute the dialog with the hands over dialogId
     * 
     * @param dialogId
     */
    public static void onDialogCall(String dialogId)
    {
      IDialog dialog = (IDialog)id2Dialog.get(dialogId);
      if(dialog!=null)
      {
        dialog.run();
      }
    }

  /**
   * 
   * @param fileName
   * @param className
   */
  public static void registerPlugin(String fileName, String className)
  {
    // map the de.freegroup.plugins.... class name to the JNI required
    // notation 'de/freegroup/plugins...'
    //
    if(Application.isRunningInDigiSim())
    {
      // store the filename (from the jar-File) of the loaded class
      //
      plugin2jar.put(className, fileName);
      n_registerPlugin(className.replace('.','/'));
    }
  }
  
  /**
   * 
   * @param tool
   */
  public static void registerTool(ITool tool)
  {
    id2Tool.put(tool.getId(),tool);
    if(Application.isRunningInDigiSim())
      n_registerTool(tool.getMenuEntry(),tool.getId());
  }
  
  
  /**
   * 
   * @param tool
   */
  public static void registerDialog(IDialog dialog)
  {
    id2Dialog.put(dialog.getId(),dialog);
    if(Application.isRunningInDigiSim())
      n_registerDialog(dialog.getMenuEntry(),dialog.getId());
  }
  
  
	public static String getJarFileFromPluginClass(String clazz)
	{
    if(!Application.isRunningInDigiSim())
      return "D:/FreeGroup/DigitalSimulator/bin/plugins/SimpleLED.jar";
    return (String) plugin2jar.get(clazz);
	}
  
    /**
     *
     */
/*
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
*/
    
    /**
     *
     */
    /*
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
*/

}