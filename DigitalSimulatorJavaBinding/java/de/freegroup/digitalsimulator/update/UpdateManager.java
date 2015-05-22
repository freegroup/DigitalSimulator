/*
 * Created on Jan 8, 2004
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.update;

import java.util.HashMap;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class UpdateManager
{
  static HashMap updateableObjects = new HashMap();
  
  public static void register(LiveUpdateObject object)
  {
  	updateableObjects.put(object.getRelativePath() ,object);
  }
  
  public static LiveUpdateObject getUpdateableObject(String relativePath)
  {
    relativePath = relativePath.replace('/','\\');
    return (LiveUpdateObject)updateableObjects.get(relativePath);
  }
}
