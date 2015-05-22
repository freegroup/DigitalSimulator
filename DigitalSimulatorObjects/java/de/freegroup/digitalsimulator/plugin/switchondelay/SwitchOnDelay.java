package de.freegroup.digitalsimulator.plugin.switchondelay;

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
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.plugin.object.ObjectPlugin;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;

public class SwitchOnDelay extends ObjectPlugin implements ILiveUpdateObject
{
    static final int DELAY_CURRENT    = 0;
    static final int DELAY_CONFIGURED = 1;

    static final byte DEFAULT_DELAY  = 10;

    static final int  BREITE   = 100;
    static final int  HOEHE    = 100;

    static
    {
      try
      {
        // Preload the dialog. If I don't preload them, it is possible that
        // the the dialog is not the top most window. This depends due the
        // JNI Interface I have implemented.
        //
        Class.forName(DelayDialog.class.getName());
      }
      catch (ClassNotFoundException e)
      {
      } 
    }

    // You can popup our own Dialog to configure
    // the object. Store your configuration data in the
    // `param' data block.
    //
    public boolean doConfigure(byte[] param)
    {
        DelayDialog dlg= new DelayDialog(param[DELAY_CONFIGURED]);
        if(dlg.isOk())
        {
            param[DELAY_CONFIGURED]=(byte)dlg.getDelay();
            return true;
        }
        return false;
    }

    // unique hash key for the DigitalSimulator.....this string
    // will be display in the 'extended Option' dialog
    //
    public String  getKey()
    {
      return "Switch on delay";
    }

   // ....
   public String  getName()
   {
      return "OBJECT.SWITCHONDELAY";
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
      return 2;
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
      // test trace statement
      //
      int[] result = new int[2];
      result[0] = BREITE;
      result[1] = HOEHE;

      return result;
   }

   // short discription what the object do. Will be display in the
   // extenden configuration dialog
   //
   public String  getDescription()
   {
      return "no desc";
   }


   // returns the name of the object group (e.g. Gatter, FlipFlop).
   // The object will be stored in the extenden dialog in this sub-tree of
   // the group name. Is the group does not exist it will be created.
   //
   public String  getGroup()
   {
      return "OBJECTGROUP.TIMEELEMENT";
   }

    // calculate the values of the output pins
    // return 0 for NO redraw neccessary
    // return 1 for redraw neccessary
    //
    public boolean calculate(int[] input ,int[] lastInput, int[] output, byte[] param)
    {
        // if the input is low the ouput is low too
        //
        if( input[0]==0 )
        {
            output[0]            = 0; // reset the input
            param[DELAY_CURRENT] = 0; // reset the timer
        }
        // timer delay reached.....switch on the output
        else if(param[DELAY_CURRENT] >= param[DELAY_CONFIGURED] )
        {
            output[0]=1;
        }
        else
        {
            param[DELAY_CURRENT]++;
        }

        return false;
    }

   //
   //
   public void paint(int xPos, int yPos, byte[] param)
   {
      // draw the outline
      //
      Painter.drawRect(xPos, yPos, xPos+BREITE,yPos -HOEHE);

      // draw the inner label
      //
      Painter.drawText("0 - t",40,xPos+25,yPos-50);

      // draw the timeline
      //
      Painter.drawLine(xPos+10        , yPos-(HOEHE/2-10) ,xPos+10, yPos-(HOEHE/2+10) );
      Painter.drawLine(xPos+10        , yPos-(HOEHE/2)    , xPos+BREITE-10, yPos-(HOEHE/2) );
      Painter.drawLine(xPos+BREITE-10 , yPos-(HOEHE/2-10) , xPos+BREITE-10, yPos-(HOEHE/2+10) );
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


   // before the simulator start the calculation of the circuit
   // all objects will be received a message. You can open
   // a file (e.g. report objects) or open a hardware interface
   // (e.g. parallel port)
   //
   public void onStartCalculate( byte[] param)
   {
        // reset the current delay time
        //
        param[DELAY_CURRENT]    = 0;
   }


   // layout the output pins. The origin (0/0) are at the top left corner
   // x INCREASED to the right and y DECREASE to the bottom.
   //
   public int[] layoutOutput( int inputCount,  int outputCount, byte[] param )
   {
      int[] result = new int[2*outputCount];
      result[0] =  BREITE;
      result[1] = -HOEHE/2;

      return result;
   }


   // layout the input pins. The origin (0/0) are at the top left corner
   // x increased to the right and y decreased to the bottom.
   //
   public int[] layoutInput(int inputCount, int outputCount, byte[] param)
   {
      int[] result = new int[2*inputCount];
      result[0] =  0;
      result[1] = -HOEHE/2;

      return result;
   }
}

