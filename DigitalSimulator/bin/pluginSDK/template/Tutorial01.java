package de.freegroup.digitalsimulator.plugin.tutorial01;

/**
 * Title:        DigitalSimulator java Pugin
 * Description:  Simple example to demonstrate how to implement an object plugin (NOT)
 * Copyright:    Copyright (c) 2004
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
 
import java.util.*;
import de.freegroup.digitalsimulator.Painter;
import de.freegroup.digitalsimulator.plugin.object.ObjectPlugin;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;

/**
 *
 * Simple Example to demonstrate how to implement a 'NOT' object for
 * DigitalSimulator.
 *
 */
public class Tutorial01 extends ObjectPlugin implements ILiveUpdateObject
{
    public final static int HEIGHT           = 90;   // the graphical height of the object
    public final static int WIDTH            = 50;   //            .. width of the object


   // You can popup our own Dialog to configure
   // the object. Store your configuration data in the
   // `param' data block.
   //
   // The 'param' will be saved with the correspponding object
   //
  public boolean doConfigure(byte[] param) { return false; }

   // unique hash key for the DigitalSimulator.
   //
   public String  getKey()
   {
    return "tutorial01";
   }

   // This name will be display in the extended dialog of the simulator.
   // You can enter the translation in the menu Tools->Localisation.
   // Enter 'OBJECT.OBJECT01' and the corresponding translation in the 
   // localisation GUI.
   //
   public String  getName()
   {
      return "OBJECT.OBJECT01";
   }



   // short discription what the object do. Will be display in the
   // extenden configuration dialog
   //
   public String  getDescription()
   {
      return "Negater with small representation";
   }


   // Returns the name of the object group (e.g. Gatter, FlipFlop).
   // The object will be stored in the extenden dialog in this sub-tree of
   // the group name. Is the group does not exist it will be created.
   // 
   public String  getGroup()
   {
      return "OBJECTGROUP.TUTORIAL01";
   }


   // Return the name of the developer of this plugIn.
   // This name will be display in the generic option dialog
   //
   public String  getProgrammerName()
   {
      return "Andreas Herz";
   }

   // Return your homepage
   //
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
   // This Version is important for the 'LiveUpdate' functionality.
   // The Version will be display in the generic configuration
   // dialog
   //
   public int  getVersion()
   {
    return 1;
   }
   
   // You many bytes do you need to store in EACH object. The allocated 
   // memory will be hand over on all related functions and is called mostly 'param'
   //
   public int getParamCount()
   {
      return 0;
   }


   // Returns the DigitalSimulator the possible count of
   // input pins
   //
   public int[] getInputCountRange()
   {
      int[] result = new int[2];
      result[0] = 1;  // minimum input pins
      result[1] = 1;  // maximum input pins

      return result;
   }

   // ......
   //
   public int[] getOutputCountRange()
   {
      int[] result = new int[2];
      result[0] = 1; // minimum output pins
      result[1] = 1; // maximum output pins

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

   // We create a small inverter. In this case we can negate the output pin.
   // No additional calculation is neccessaray.
   //
   public void init(byte[] param)
   {
        invertOutput(0,true);
   }

   // calculate the values of the output pins
   // return 0 for NO redraw neccessary
   // return 1 for redraw neccessary
   //
   // You MUST set all allocated output ports.
   //
   public boolean calculate(int[] input ,int[] lastInput, int[] output, byte[] param)
   {
      output[0] = input[0]; // the negated output port will do work
      return false;
   }

   // Paint the object. The origin (0/0) are at the top left corner.
   //
   //0/0
   // +---------> +X
   // |
   // |
   // |
   // |
   // V
   //
   // -Y
   //
   public void paint(int xPos, int yPos, byte[] param)
   {
      // paint the border rect
      //
      Painter.drawRect(xPos, yPos, xPos+WIDTH,yPos - HEIGHT);

      // paint the inner label
      //
      Painter.drawText("T",50,xPos+15,yPos-5);
   }


   // Layout the output pins. The origin (0/0) are at the top left corner.
   //
   //0/0
   // +---------> +X
   // |
   // |
   // |
   // |
   // V
   //
   // -Y
   //
   public int[] layoutOutput( int inputCount,  int outputCount, byte[] param )
   {
      int[] result = new int[2*outputCount];
      result[0] =   WIDTH;
      result[1] = -(HEIGHT/2);

      return result;
   }


   // layout the input pins. The origin (0/0) are at the top left corner
   //
   // [0,0]
   //   +---------> +X
   //   |
   //   |
   //   |
   //   |
   //   V
   //
   //  -Y
   //
   public int[] layoutInput(int inputCount, int outputCount, byte[] param)
   {
      int[] result = new int[2*inputCount];
      result[0] =    0;
      result[1] = - (HEIGHT/2);

      return result;
   }
}

