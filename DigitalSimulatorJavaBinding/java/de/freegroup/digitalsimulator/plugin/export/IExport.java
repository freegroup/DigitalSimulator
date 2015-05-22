/*
 * Created on Jan 16, 2004
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.plugin.export;

import javax.swing.ImageIcon;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public interface IExport
{
	public abstract void      run(String xmlData);
	public abstract String    getMenyEntry();
  public abstract ImageIcon getIcon();
	public abstract String    getDescription();
}