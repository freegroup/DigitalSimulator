/*
 * Created on Dec 28, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.plugin.tool.ResistorCoder;

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
    return "MENU.TOOL.RESISTORCOLORCODER";
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
      Dialog dialog = new Dialog();
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
    return 2; 
  }
  
}
