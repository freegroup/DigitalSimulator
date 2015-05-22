

package de.freegroup.digitalsimulator;

import java.io.File;
import java.io.FileFilter;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.util.StringTokenizer;
import java.util.TreeSet;
import java.util.Vector;

import de.freegroup.digitalsimulator.update.LiveUpdateObject;
import de.freegroup.digitalsimulator.update.UpdateManager;
import de.freegroup.util.i18n.StringHelper;
import de.freegroup.util.i18n.UberProperties;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */

public class I18N implements Configuration.Notifyee
{
  static HashMap        langCatalog = new HashMap();
  static UberProperties initProps   = null;
  
  public static void main(String[] args)
	{
		
	}
  
  static
	{
    try
		{
      load();
      Configuration.register(new I18N());
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
  
  /**
   * 
   * @param key
   * @return
   */
  public static String get(String key)
  {
    String currentLocale = Configuration.getString(Configuration.CURRENT_LANGUAGE);
    UberProperties props =(UberProperties) langCatalog.get(currentLocale);
    if(props==null)
      return key;
    String trans =  props.getProperty(key);
    return trans==null?key:trans;
  }
 
  public static Enumeration getKeys()
  {
    return initProps.getKeys();
  }
  
  public static Set getInstalledLaguages()
  {
    return langCatalog.keySet();
  }
  
 
  /**
   * 
   * @param args
   * @throws IOException
   */
  private static void load() throws IOException
  {
    String file = Configuration.getString(Configuration.LANGUAGE_PATH)+"DigitalSimulator.properties";
    File f = new File(file);
    
    if (f == null)
      throw new IOException();
    File parent = f.getCanonicalFile().getParentFile();
    if (parent == null)
      throw new IOException();
    String baseName = f.getName();
    if (baseName.endsWith(".properties"))
    {
      baseName = baseName.substring(0, baseName.length() - 11);
    }
    final String finalBaseName = baseName;
    initProps = new UberProperties();
    initProps.load(new FileInputStream(f));
    String absolutePath = Configuration.getString(Configuration.LANGUAGE_PATH)+"DigitalSimulator.properties";
    String relativePath = Configuration.getString(Configuration.LANGUAGE_PATH)+"DigitalSimulator.properties";
    String applicationPath = Configuration.getString(Configuration.APPLICATION_PATH);
    int version = 0;
    try
    {
      version = Integer.parseInt(initProps.getProperty("__VERSION"));
    }
    catch (NumberFormatException e)
    {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
    relativePath = "./"+relativePath.substring(applicationPath.length());
    UpdateManager.register(new LiveUpdateObject(relativePath, absolutePath, version));
    
    File[] transFiles = parent.listFiles(new FileFilter()
        {
      public boolean accept(File pathname)
      {
        String s = pathname.getName();
        if (!s.startsWith(finalBaseName + "_"))
          return false;
        if (!s.endsWith(".properties"))
          return false;
        String locale = s.substring(finalBaseName.length() + 1, s.length() - 11);
        String[] localeData = StringHelper.split(locale, "_");
        if (localeData.length < 1)
          return false;
        if (localeData.length > 3)
          return false;
        if (localeData[0].length() != 2)
          return false;
        if (!isLower(localeData[0]))
          return false;
        if (localeData.length > 1)
        {
          if (localeData[1].length() != 2)
            return false;
          if (!isUpper(localeData[1]))
            return false;
        }
        if (localeData.length > 2)
        {
          if (localeData[2].length() == 0)
            return false;
          if (!isUpper(localeData[2]))
            return false;
        }
        return true;
      }
    });
    
    Arrays.sort(transFiles);
    for (int i = 0; i < transFiles.length; i++)
    {
      String s = transFiles[i].getName();
      s = s.substring(finalBaseName.length() + 1, s.length() - 11);
      String language = null;
      String country  = null;
      String variant  = null;
      StringTokenizer st = new StringTokenizer(s, "_");
      if (st.hasMoreTokens())
        language = st.nextToken();
      if (st.hasMoreTokens())
        country = st.nextToken();
      if (st.hasMoreTokens())
        variant = st.nextToken();
      loadLangCatalog(language, country, variant, new FileInputStream(transFiles[i]));
    }
  }

  /**
   * Load the language catalog and store the file in an internal HashMap with
   * the language/country/variant as key.
   * 
   * @param language
   * @param country
   * @param variant
   * @param in
   * @throws IOException
   */
  private static void loadLangCatalog(String language, String country, String variant, InputStream in) throws IOException
  {
    String locale = language;
    UberProperties props = new UberProperties(initProps);

    if (in != null)
      props.load(in);

    if(country!=null)
    	locale = language + "_" + country;
    
    if (variant != null)
      locale = language +"_"+country +"_"+variant;
    langCatalog.put(locale, props);
    
    // register the corespondig file for updateable.
    //
    String absolutePath = Configuration.getString(Configuration.LANGUAGE_PATH)+"DigitalSimulator_"+locale+".properties";
    String relativePath = Configuration.getString(Configuration.LANGUAGE_PATH)+"DigitalSimulator_"+locale+".properties";
    String applicationPath = Configuration.getString(Configuration.APPLICATION_PATH);
    int version = 0;
    try
		{
			version = Integer.parseInt(props.getProperty("__VERSION"));
		}
		catch (NumberFormatException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    relativePath = "./"+relativePath.substring(applicationPath.length());
    UpdateManager.register(new LiveUpdateObject(relativePath, absolutePath, version));
    }
  
  /**
   * 
   * @param s
   * @return
   */
  private static boolean isUpper(String s)
  {
    for (int i = 0; i < s.length(); i++)
    {
      char c = s.charAt(i);
      if (c < 'A' || c > 'Z')
        return false;
    }
    return true;
  }
  
  /**
   * 
   * @param s
   * @return
   */
  private static boolean isLower(String s)
  {
    for (int i = 0; i < s.length(); i++)
    {
      char c = s.charAt(i);
      if (c < 'a' || c > 'z')
        return false;
    }
    return true;
  }
  
  /**
   * for the interface Configuration.Notifyee
   */
  public Set getNotifyKeys()
  {
    Set keys = new TreeSet();
    keys.add("Language");
    return keys;  
  }
  
  public void onAfterChange(String key, String value)
  {
  	try
		{
			I18N.load();
		}
		catch (IOException e)
		{
			Trace.error(e);
		}
  }
  
  public void onDuringChange(String key, String value)
  {
    
  }
  public void onBeforeChange(String key, String value)
  {
    
  }
}