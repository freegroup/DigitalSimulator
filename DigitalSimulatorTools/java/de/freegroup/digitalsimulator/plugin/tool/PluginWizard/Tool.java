/*
 * Created on Nov 24, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.plugin.tool.PluginWizard;

import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.dialogs.MsgBox;
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
  static
  {
    try
		{
      Class.forName(WizardObjectErrorDialog.class.getName());
      Class.forName(WizardObjectCreate.class.getName());
      Class.forName(WizardObjectCustomize.class.getName());
		}
		catch (Exception e)
		{
			// ignore
		}
  }
  public String getMenuEntry()
  {
    return "MENU.TOOL.OBJECTWIZARD";
  }
  
  public String getId()
  {
    return ""+hashCode();
  }
  
  public void run()
  {
    try
    {    
      //new MsgBox("Sie müssen die Anwendung neu starten um das neu erzeugte Objekt zu laden.");
      WizardObjectCreate dialog = new WizardObjectCreate();
      if(dialog.isOk()==true)
        new MsgBox(I18N.get("OBJECTWIZARD.MESSAGE.RESTARTAPPLICATION"));
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
