/*
 * Created on Nov 24, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator;

import JUtil;
/**
 * @author Administrator
 *
 * This class is required because in the JDK 1.4 it is not possible to include
 * a class in the 'default package'. So, we create a wrapper class in 'any' package, compile it 
 * with a JDK 1.3 an the other classes (with 1.4) can include this wrapper class
 */
public class WinUtil
{
  public static void setWindowAlwaysOnTop(String title)
  {
    if(Application.isRunningInDigiSim())
      JUtil.setWindowAlwaysOnTop(JUtil.getHwnd(title),true);
  }
}
