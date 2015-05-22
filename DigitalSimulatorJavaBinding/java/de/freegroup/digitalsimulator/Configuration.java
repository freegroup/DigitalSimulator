/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
package de.freegroup.digitalsimulator;
import java.util.*;


public class Configuration
{
	public interface Notifyee
	{
		public Set getNotifyKeys();
		public void onAfterChange(String key, String value);
		public void onDuringChange(String key, String value);
		public void onBeforeChange(String key, String value);
	};
  
	public static final String WMF_PATH         = "WMFPath";
	public static final String BMP_PATH         = "BMPPath";
	public static final String PALETTE_PATH     = "PalettePath";
  public static final String PLUGIN_PATH      = "PluginPath";
  public static final String THEMES_PATH      = "ThemesPath";
  public static final String BASIC_PATH       = "BasicPath";
	public static final String SCRIPT_PATH      = "ScriptPath";
	public static final String LANGUAGE_PATH    = "LanguagePath";
	public static final String APPLICATION_PATH = "ApplicationPath";
	public static final String LOGGING_PATH     = "LoggingPath";
	public static final String TEMP_PATH        = "TempPath";
	public static final String JAVA_HOME        = "JAVA_HOME";
	public static final String CURRENT_LANGUAGE = "Language";
  
	private static Vector notifyees = new Vector();
  
  private static native String n_getString(String key);
	private static native void n_setString(String key, String value);
  
	public static String getString(String key)
	{
		if (Application.isRunningInDigiSim())
			return n_getString(key);
		return (String)(conf.get(key)==null?"":conf.get(key));
	}
  
	public static void setString(String key, String value)
	{
		if (Application.isRunningInDigiSim())
			n_setString(key, value);
		else
			conf.put(key, value);
	}
	public static int getInt(String key, int _default)
	{
		if (Application.isRunningInDigiSim())
		{
			try
			{
				String value = n_getString(key);
				return Integer.parseInt(value);
			}
			catch (NumberFormatException e)
			{
				// ignore
			}
		}
		return _default;
	}
  
  public static void register(Notifyee notifyee)
  {
  	notifyees.add(notifyee);
  }
  
	/**
	 * This event-Handler will be called from the C++ Applikation if an Parameter
	 * has been/will be changed.
	 */
	public static void onBeforeChange(String key, String value)
	{
		Trace.info("onBeforeChange");
    Iterator iter = notifyees.iterator();
    while(iter.hasNext())
    {
    	Notifyee notifyee = (Notifyee)iter.next();
    	if(notifyee.getNotifyKeys().contains(key))
        notifyee.onAfterChange(key, value);
    }
	}
  
	public static void onDuringChange(String key, String value)
	{
		Trace.info("onDuringChange");
    Iterator iter = notifyees.iterator();
    while(iter.hasNext())
    {
      Notifyee notifyee = (Notifyee)iter.next();
      if(notifyee.getNotifyKeys().contains(key))
        notifyee.onDuringChange(key, value);
    }
  }
  
	public static void onAfterChange(String key, String value)
	{
		Trace.info("onAfterChange");
    Iterator iter = notifyees.iterator();
    while(iter.hasNext())
    {
      Notifyee notifyee = (Notifyee)iter.next();
      if(notifyee.getNotifyKeys().contains(key))
        notifyee.onAfterChange(key, value);
    }
  }
  
	/**
	 * This part is only for the test (if the java part doesn't run in the C++
	 * Application
	 */
	static HashMap conf = new HashMap();
	static {
		conf.put(PLUGIN_PATH, "D:/FreeGroup/DigitalSimulator/bin/Plugins/");
		conf.put(WMF_PATH, "D:/FreeGroup/DigitalSimulator/bin/WMF/");
		conf.put(BMP_PATH, "D:/FreeGroup/DigitalSimulator/bin/bmp/");
		conf.put(APPLICATION_PATH, "D:/FreeGroup/DigitalSimulator/bin/");
		conf.put(LANGUAGE_PATH, "D:/FreeGroup/DigitalSimulator/bin/langCatalog/");
		conf.put(TEMP_PATH, "D:/FreeGroup/DigitalSimulator/bin/temp/");
		conf.put("ApplicationVersion","5.56");
		conf.put("debug", "false");
		conf.put("GridStyle", "c");
		conf.put("Language", "de");
	}
}
