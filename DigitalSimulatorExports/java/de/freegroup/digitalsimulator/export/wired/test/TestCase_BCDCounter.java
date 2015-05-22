/*
 * Created on Feb 2, 2004
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.export.wired.test;

import de.freegroup.digitalsimulator.Application;
import de.freegroup.digitalsimulator.export.partlistpdf.Export;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class TestCase_BCDCounter
{
  public static void main(String[] args)
	{
    new Export().run(testXML);
	}
  
  static final String testXML=
"<circuit name=\"Arbeitsblatt1\">"+
"  <tmpCircuitPath>D:\\FreeGroup\\DigitalSimulator\\bin\\temp\\Arbeitsblatt1_3.dsim</tmpCircuitPath>"+
"  <imagePath>D:\\FreeGroup\\DigitalSimulator\\bin\\temp\\Arbeitsblatt1_2.png</imagePath>"+
"  <objects>"+
"    <object id=\"00C72690\" group=\"OBJECTGROUP.COUNTER\" type=\"OBJ_BCDCOUNTER\" version=\"1.0\" positionX=\"0\" positionY=\"460\" width=\"244\" height=\"375\">"+
"      <input>"+
"        <port id=\"00C72570\"/>"+
"        <port id=\"00C73960\"/>"+
"      </input>"+
"      <output>"+
"        <port id=\"00C73870\" fanOut=\"0\"/>"+
"        <port id=\"00C737C0\" fanOut=\"0\"/>"+
"        <port id=\"00C736D0\" fanOut=\"3\"/>"+
"        <port id=\"00C73620\" fanOut=\"0\"/>"+
"      </output>"+
"    </object>"+
"  </objects>"+
"  <links>"+
"  </links>"+
"</circuit>";

}
