/*
 * Created on Jan 8, 2004
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.update;

import de.freegroup.digitalsimulator.Trace;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class LiveUpdateObject implements ILiveUpdateObject
{
  protected String relativePath = null;
  protected String absolutePath = null;
  protected int    version =0;
  
	/**
	 * @param relativePath
	 * @param absolutePath
	 * @param version
	 */
	public LiveUpdateObject(String relativePath, String absolutePath, int version)
	{
		super();
    relativePath = relativePath.replace('/','\\');
    absolutePath = absolutePath.replace('/','\\');
    this.relativePath = relativePath;
		this.absolutePath = absolutePath;
		this.version = version;
    Trace.info(this.toString());
	}
		/**
	 * toString methode: creates a String representation of the object
	 * @return the String representation
	 * @author info.vancauwenberge.tostring plugin
	
	 */
	public String toString()
	{
		StringBuffer buffer = new StringBuffer();
		buffer.append("LiveUpdateObject[");
		buffer.append("relativePath = ").append(relativePath);
		buffer.append(", absolutePath = ").append(absolutePath);
		buffer.append(", version = ").append(version);
		buffer.append("]");
		return buffer.toString();
	}
  
  public String getRelativePath()
  {
   return relativePath; 
  }
  
  public String getAbsolutePath()
  {
   return absolutePath; 
  }
  
  public int getVersion()
  {
   return version; 
  }
}
