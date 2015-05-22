package de.freegroup.digitalsimulator.plugin.identity;

/**
 * Title:        DigitalSimulator java Pugins
 * Description:  Simple example for the java plugin development
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */

import java.util.*;
import de.freegroup.digitalsimulator.Painter;
import de.freegroup.digitalsimulator.dialogs.MsgBox;
import de.freegroup.digitalsimulator.plugin.object.ObjectPlugin;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;
import de.freegroup.digitalsimulator.Trace;
import java.awt.Color;

public class Identity extends ObjectPlugin implements ILiveUpdateObject
{
   // You can popup our own Dialog to configure
   // the object. Store your configuration data in the
   // `param' data block.
   //
  public boolean doConfigure(byte[] param) { return false; }

   // unique hash key for the DigitalSimulator.....this string
   // will be display in the 'extended Option' dialog
   //
   public String  getKey()
   {
    return "Identity";
   }

   // ....
   public String  getName()
   {
      return "OBJECT.IDENTITY";
   }

   // Return the name of the developer of this plugIn.
   // This name will be display in the generic option dialog
   //
   public String  getProgrammerName()
   {
      return "Andreas Herz";
   }

   // Return your homepage
   public String  getProgrammerURL()

   {
      return "http://www.FreeGroup.de";
   }


   // Return your the Developer Address. In the generic configuration
   // dialog is a mail-link.
   //
   public String  getProgrammerMail()
   {
      return "A.Herz@FreeGroup.de";
   }


   // Return the PlugInVersion
   // At the Moment will not be checked againts
   // saved objects.....planed for the future
   // The Version will be display in the generic configuration
   // dialog
   //
   public int  getVersion()
   {
    return 1;
   }
   
   // ......
   //
   public int getParamCount()
   {
      return 1;
   }


   // Returns the DigitalSimulator the possible count of
   // input pins
   //
   public int[] getInputCountRange()
   {
      int[] result = new int[2];
      result[0] = 1;
      result[1] = 1;

      return result;
   }

   // ......
   //
   public int[] getOutputCountRange()
   {

      int[] result = new int[2];
      result[0] = 1;
      result[1] = 1;

      return result;
   }


   // Return the size in Pixel wich the object needs
   // Required for the DragDrop operation of the framework
   //
   public int[] getSize(long inputCount, long outputCount)
   {
      int[] result = new int[2];
      result[0] = 100;
      result[1] = 200;

      return result;
   }

   // short discription what the object do. Will be display in the
   // extenden configuration dialog
   //
   public String  getDescription()
   {
      return "Simple example object for the java pluginin interface";
   }


   // returns the name of the object group (e.g. Gatter, FlipFlop).
   // The object will be stored in the extenden dialog in this sub-tree of
   // the group name. Is the group does not exist it will be created.
   //
   public String  getGroup()
   {
      return "OBJECTGROUP.GATE";
   }

   // calculate the values of the output pins
   // return 0 for NO redraw neccessary
   // return 1 for redraw neccessary
   //
   public boolean calculate(int[] input ,int[] lastInput, int[] output, byte[] param)
   {
      output[0] = input[0];
      return false;
   }

   //
   //
   public void paint(int xPos, int yPos, byte[] param)
   {
          Painter.drawRect(xPos, yPos, xPos+100,yPos -200, Color.black);
   }

   // layout the output pins. The origin (0/0) are at the top left corner
   // x INCREASED to the right and y DECREASE to the bottom.
   //
   public int[] layoutOutput( int inputCount,  int outputCount, byte[] param )
   {
      int[] result = new int[2*outputCount];
      result[0] = 100;
      result[1] = -100;

      return result;
   }


   // layout the input pins. The origin (0/0) are at the top left corner
   // x increased to the right and y decreased to the bottom.
   //
   public int[] layoutInput(int inputCount, int outputCount, byte[] param)
   {
      int[] result = new int[2*inputCount];
      result[0] =    0;
      result[1] = -100;

      return result;
   }

   // will be called if the mouse 'enters' an object
   // (hover)
   public  boolean onMouseOverStart(int x, int y, byte[] param)
   {
        param[0]=1; // mark for the paint method
        return true; // return true if an redraw of the object is required
   }

   // will be called if the mouse cursor 'leafes' an object
   // (hover)
   public  boolean onMouseOverEnd(int x, int y, byte[] param)
   {
        param[0]=0; // remove the mark for the paint method
        return true; // return true if an redraw of the object is required
   }
}

