/*
 * Created on Dec 28, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.plugin.tool.I18NEditor;

import java.io.File;

import de.freegroup.digitalsimulator.Configuration;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.plugin.tool.ITool;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class Tool implements ITool, ILiveUpdateObject
{
  /**
   * for the interface ITool
   * @return
   */
  public String getMenuEntry()
  {
    return "MENU.TOOL.I18NEDITOR";
  }
  
  /**
   * for the interface ITool
   * @return
   */
  public String getId()
  {
    return ""+hashCode();
  }
  
  /**
   * for the interface ITool
   * @return
   */
  public void run()
  {
    try
    {  
      String languageFile = Configuration.getString(Configuration.LANGUAGE_PATH)+"DigitalSimulator.properties";
      I18NEditor dialog = new I18NEditor(new File(languageFile));
    }
    catch(Exception exc)
    {
      Trace.error(exc);
    }
  }
  
  /**
   * Interface implementation for ILiveUpdateObject
   */
  public int getVersion()
  {
    return 1; 
  }
  
}
