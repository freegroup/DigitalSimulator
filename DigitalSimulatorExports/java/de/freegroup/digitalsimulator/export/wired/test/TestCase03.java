package de.freegroup.digitalsimulator.export.wired.test;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import java.io.IOException;
import java.util.HashMap;

import org.apache.commons.io.IOUtils;

import de.freegroup.digitalsimulator.export.wired.Export;

public class TestCase03
{
   private static HashMap pinMap    = new HashMap();
   private static HashMap objectMap = new HashMap();

    public static void main(String[] args)
    {
      try
      {
        String xmlData= IOUtils.toString(TestCase03.class.getResourceAsStream("Taktgeber.xml"));
        new Export().run(xmlData);
      }
      catch (IOException e)
      {
        // TODO Auto-generated catch block
        e.printStackTrace();
      }
    }
}