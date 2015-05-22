/*
 * Created on Jan 15, 2004
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.plugin.export;

import javax.swing.ImageIcon;

import de.freegroup.util.file.Display;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class TestExportModul implements IExport
{
	/* (non-Javadoc)
	 * @see de.freegroup.digitalsimulator.plugin.export.ExportModul#transformAndDisplay(java.lang.String)
	 */
	public void run(String xmlData)
	{
		Display.displayFile(xmlData,"test.xml");
	}

  public ImageIcon getIcon()
  {
    return new ImageIcon(TestExportModul.class.getResource("icon.png"));
  }

	/* (non-Javadoc)
	 * @see de.freegroup.digitalsimulator.plugin.export.ExportModul#getMenyEntry()
	 */
	public String getMenyEntry()
	{
		// TODO Auto-generated method stub
		return "TestExportModul";
	}
	/* (non-Javadoc)
	 * @see de.freegroup.digitalsimulator.plugin.export.ExportModul#getDescription()
	 */
	public String getDescription()
	{
		return "Leider keine Beschreibung vorhanden";
	}
}
