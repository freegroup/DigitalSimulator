/*
 * Created on Dec 1, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.plugin.tool.PluginWizard;

import de.freegroup.digitalsimulator.plugin.object.ObjectPlugin;



/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public abstract class MutableObjectPlugin extends ObjectPlugin
{
  public abstract void setProgrammerName(String name);
  public abstract void setProgrammerMail(String name);
  public abstract void setProgrammerURL(String name);

  public abstract void setVersion(int name);
  public abstract void setGroup(String name);
  public abstract void setDescription(String name);
  public abstract void setName(String name);
  
  public abstract void setInputCount(int i);
  public abstract void setOutputCount(int i);
  public abstract void setParamCount(int i);
  
  public abstract void setWidth(int w);
  public abstract void setHeight(int h);
  
  public abstract String  getData(String fileInArchive);
  public abstract void    setData(String fileInArchive, String data);
  
  public abstract boolean hasChanged();
  public abstract void    setChanged(boolean flag);
}
