package de.freegroup.digitalsimulator.plugin.bus;

/**
 * Title:        DigitalSimulator java Pugins
 * Description:
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

public class OutputBus extends ObjectPlugin implements ILiveUpdateObject
{
    final static int INPUT_COUNT  = 0;
    final static int OUTPUT_COUNT = 8;

    final static int WIDTH  = 100;
    final static int HEIGHT = 300;

   // You can popup our own Dialog to configure
   // the object. Store your configuration data in the
   // `param' data block.
   //
   public boolean doConfigure(byte[] param)
   {
      BusDialog dlg= new BusDialog((int)param[0]);
      if(dlg.isOk())
      {
        param[0]=(byte)dlg.getBusId();
        return true;
      }
      return false;
   }

   // unique hash key for the DigitalSimulator.....this string
   // will be display in the 'extended Option' dialog
   //
   public String  getKey()
   {
    return "8-bit Bus (output)";
   }

   // ....
   public String  getName()
   {
      return "OBJECT.OUTPUTBUS.8.BIT";
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
      result[0] = INPUT_COUNT;
      result[1] = INPUT_COUNT;

      return result;
   }

   // ......
   //
   public int[] getOutputCountRange()
   {

      int[] result = new int[2];
      result[0] = OUTPUT_COUNT;
      result[1] = OUTPUT_COUNT;

      return result;
   }


   // Return the size in Pixel wich the object needs
   // Required for the DragDrop operation of the framework
   //
   public int[] getSize(long inputCount, long outputCount)
   {
      int[] result = new int[2];
      result[0] = WIDTH;
      result[1] = HEIGHT;

      return result;
   }

   // short discription what the object do. Will be display in the
   // extenden configuration dialog
   //
   public String  getDescription()
   {
      return "8-bit data bus\r\n"+
             "select the number of the bus to with you want connect\r\n"+
             "The information from the corresponding bus will be display\r\n"+
             "at this output element.\r\n"+
             "With this object it is possible to avoid the wide range\r\n"+
             "connector over the circuit.";
   }


   // returns the name of the object group (e.g. Gatter, FlipFlop).
   // The object will be stored in the extenden dialog in this sub-tree of
   // the group name. Is the group does not exist it will be created.
   //
   public String  getGroup()
   {
      return "OBJECTGROUP.BUS";
   }

   // calculate the values of the output pins
   // return 0 for NO redraw neccessary
   // return 1 for redraw neccessary
   //
   public boolean calculate(int[] input ,int[] lastInput, int[] output, byte[] param)
   {
      System.arraycopy(BusManager.getData(new Integer(param[0])),0,output,0,output.length);
      return false;
   }

   //
   //
   public void paint(int xPos, int yPos, byte[] param)
   {
      Painter.drawRect(xPos, yPos, xPos+WIDTH,yPos -HEIGHT);
      Painter.drawText("BUS",55, xPos+5,yPos -100);
      Painter.drawText("("+param[0]+")",45, xPos+8,yPos -150);
   }


   // This method will be called if the user double clicks the object with
   // the left mouse button
   //
   // return true if a repaint required.
   // return false if no repaint required.
    //
   public boolean onButtonDblClick(int x, int y, byte[] param)
   {
      return doConfigure(param);
   }

   // layout the output pins. The origin (0/0) are at the top left corner
   // x INCREASED to the right and y DECREASE to the bottom.
   //
   public int[] layoutOutput( int inputCount,  int outputCount, byte[] param )
   {
      int[] result = new int[2*outputCount];
      float offset = (float)HEIGHT/(outputCount+1);

      for(int i=0; i<(outputCount*2); i=i+2)
      {
          result[i] = WIDTH;
          result[i+1] = -(int)(offset+offset*(i/2));
      }

      return result;
   }


   // layout the input pins. The origin (0/0) are at the top left corner
   // x increased to the right and y decreased to the bottom.
   //
   public int[] layoutInput(int inputCount, int outputCount, byte[] param)
   {
      int[] result = new int[2*inputCount];
      float offset = (float)HEIGHT/(inputCount+1);

      for(int i=0; i<(inputCount*2); i=i+2)
      {
          result[i] = 0;
          result[i+1] = -(int)(offset+offset*(i/2));
      }

      return result;
   }
}
