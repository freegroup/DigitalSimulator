package de.freegroup.digitalsimulator.export.wired.test;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import de.freegroup.digitalsimulator.export.wired.db.*;
import de.freegroup.digitalsimulator.export.wired.*;
import Application;
import java.util.ArrayList;
import java.util.Iterator;

import org.w3c.dom.*;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.xml.sax.*;
import java.io.*;
import java.util.*;

public class TestCase02
{
   private static HashMap pinMap    = new HashMap();
   private static HashMap objectMap = new HashMap();

    public static void main(String[] args)
    {
      Application.onExport(testXML);
    }


    public static String testXML ="<circuit name=\"testCircuit\" >\n"+
                    "    <objects>\n"+
                    "       <object id=\"07BEEDD8\" group=\"Gatter\" type=\"OBJ_NAND\">\n"+
                    "          <input>\n"+
                    "             <port id=\"07BEEC98\"/>\n"+
                    "             <port id=\"07BEEF68\"/>\n"+
                    "          </input>\n"+
                    "          <output>\n"+
                    "             <port id=\"052A4BB0\"/>\n"+
                    "          </output>\n"+
                    "       </object>\n"+
                    "       <object id=\"052A4DE8\" group=\"Gatter\" type=\"OBJ_NAND\">\n"+
                    "          <input>\n"+
                    "             <port id=\"052A4CC0\"/>\n"+
                    "             <port id=\"052A4F78\"/>\n"+
                    "          </input>\n"+
                    "          <output>\n"+
                    "             <port id=\"052A5000\"/>\n"+
                    "          </output>\n"+
                    "       </object>\n"+
                    "       <object id=\"07C304A0\" group=\"Anzeige\" type=\"OBJ_SWITCH_AUS\">\n"+
                    "          <input>\n"+
                    "             <port id=\"07C30378\"/>\n"+
                    "          </input>\n"+
                    "          <output>\n"+
                    "             <port id=\"052A5000fake\"/>\n"+
                    "          </output>\n"+
                    "       </object>\n"+
                    "    </objects>\n"+
                    "    <links>\n"+
                    "       <link id=\"052A5128\" port1=\"052A4CC0\" port2=\"052A4BB0\"/>\n"+
                    "       <link id=\"07C306A0\" port1=\"07C30378\" port2=\"052A5000\"/>\n"+
                    "    </links>\n"+
                    " </circuit>\n";
}