package de.freegroup.digitalsimulator.plugin.loadablebinarycounter;

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

public class LoadableBinaryCounter extends ObjectPlugin implements ILiveUpdateObject
{
   static final int INPUT_COUNT  = 11; // Clock, Reset, Load and 8 load inputs
   static final int OUTPUT_COUNT = 8;

   static final int LOAD    = 0;
   static final int CLOCK   = 1;
   static final int RESET   = 2;

   // You can popup our own Dialog to configure
   // the object. Store your configuration data in the
   // 'param' data block.
   //
  public boolean doConfigure(byte[] param) { return false; }

   // unique hash key for the DigitalSimulator.....this string
   // will be display in the 'extended Option' dialog
   //
   public String  getKey()
   {
    return "Loadable 8-bit binary counter";
   }

   // ....
   public String  getName()
   {
      return "OBJECT.LOADABLECOUNTER.8.BIT";
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
      // to store the current value of the counter
      //
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

      result[0] = 200;
      result[1] = (int)(70+20+70*outputCount);

      return result;
   }

   // short discription what the object do. Will be display in the
   // extenden configuration dialog
   //
   public String  getDescription()
   {
   return "Loadable binary counter\r\n\r\n"+
          "Counts from 0-255 and sets the corresponding outputs\r\n"+
          "to HIGH.\r\n\r\n"+
          "The counter can be loaded with the high->low flank at the\r\n"+
          "L-input.\r\n"+
          "This value is the base for the next increment of the counter.\r\n";
   }


   // returns the name of the object group (e.g. Gatter, FlipFlop).
   // The object will be stored in the extenden dialog in this sub-tree of
   // the group name. Is the group does not exist it will be created.
   //
   public String  getGroup()
   {
      return "OBJECTGROUP.COUNTER";
   }

   // calculate the values of the output pins
   // return 0 for NO redraw neccessary
   // return 1 for redraw neccessary
   //
   public boolean calculate(int[] input ,int[] lastInput, int[] output, byte[] param)
   {
        int outputCount = output.length;

        if(input[RESET]==0)
        {
            // bei abfallender takflanke am load-Eingang Werte
            // vom Eingang uebernehmen und diese auf den Ausgang
            // durchreichen
            //
            if(input[LOAD]==0 && input[LOAD]!=lastInput[LOAD])
            {
                for(int i = 0 ;i<output.length ; i++)
                    output[i] = input[i+3];
            }
            else
            {
                // Nur den Wert erhoehen, falls der Eingang eine positive Flanke hat
                //
                if(input[CLOCK]==1 && input[CLOCK]!=lastInput[CLOCK])
                {
                    boolean carry;

                    // zu dem ersten Bit des Zaehlers 1 addieren (=toggle ..1+1=0 )
                    //
                    output[0]=output[0]==1?0:1;
                    // Falls der Wert jetzt auf 0 steht, hat es einen
                    // Ueberlauf bei diesem bit gegeben
                    //
                    carry = output[0]==0;
                    for(int loop=1 ;loop <output.length  ; loop++)
                    {
                        // falls es keinen Uberlauf bei der 'addition'
                        // zuvor gegeben hat kann die schleife verlassen werden.
                        //
                        if(!carry)
                            break;

                        // den Uberlauf zu dem naechsten bit 'addieren'
                        //
                        output[loop]=output[loop]==1?0:1;
                        // ... und feststellen ob es wieder ein ueberlauf
                        // gegeben hat
                        //
                        carry = output[loop]==0;
                    }
               }
            }
        }
        else
        {
            for(int i=0; i<output.length ; i++)
               output[i]=0;
        }
        return false;
   }

    //
    //
    public void paint(int xPos, int yPos, byte[] param)
    {
        int yOffset=0;
        int xSize  =getSize(INPUT_COUNT,OUTPUT_COUNT)[0];
        int ySize  =getSize(INPUT_COUNT,OUTPUT_COUNT)[1];

        // Steuereinheit zeichnen
        //
        Painter.drawRect(xPos      , yPos-yOffset , xPos+ xSize  , yPos- yOffset-72);
        yOffset+=70;

        // Abstandsblock zeichnen
        //
        Painter.drawRect(xPos + 10 , yPos-yOffset, xPos+ xSize-10, yPos- yOffset-20);
        yOffset+=20;

        // für jeden Ausgang ein eigenes Feld zeichnen
        //
        for(int loop=0; loop<OUTPUT_COUNT; loop++)
        {
          Painter.drawRect(xPos,yPos-yOffset,xPos+ xSize,yPos-yOffset-70);
          yOffset+=70;
        }

        Painter.drawText("L" ,35, xPos + 8, yPos    );
        Painter.drawText("C" ,35, xPos + 8, yPos-22 );
        Painter.drawText("R" ,35, xPos + 8, yPos-44 );
        Painter.drawText("loadable" ,40, xPos + 48, yPos );
        Painter.drawText("Binary" ,50, xPos + 40, yPos-25 );
    }

   // layout the output pins. The origin (0/0) are at the top left corner
   // x INCREASED to the right and y DECREASE to the bottom.
   //
   public int[] layoutOutput( int inputCount,  int outputCount, byte[] param )
   {
      int[] result = new int[2*outputCount];
      int  yOffset = 70;
      int  width   = getSize(inputCount, outputCount)[0];

       for(int loop=0 ;loop <(2*outputCount) ; loop=loop+2)
       {
          result[loop]   = width;                          // x
          result[loop+1] = -(70+20+35) -yOffset*(loop/2);  // y
       }

       return result;
   }


   // layout the input pins. The origin (0/0) are at the top left corner
   // x increased to the right and y decreased to the bottom.
   //
    public int[] layoutInput(int inputCount, int outputCount, byte[] param)
    {
        int[] result = new int[2*inputCount];

        result[0] = 0;
        result[1] = -15;

        result[2] = 0;
        result[3] = -35;

        result[4] = 0;
        result[5] = -55;

        int  yOffset = 70;
        for(int loop=6 ;loop <(2*inputCount) ; loop=loop+2)
        {
          result[loop] = 0;
          result[loop+1] = -(70+20+35) -yOffset*((loop-6)/2);
        }

        return result;
    }
}

