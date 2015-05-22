package de.freegroup.digitalsimulator.plugin.volladdierer1bit;

/**
 * Title:        DigitalSimulator java Pugins
 * Description:  1 bit full adder
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import java.util.*;
import de.freegroup.digitalsimulator.Painter;
import de.freegroup.digitalsimulator.plugin.object.ObjectPlugin;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;

import java.awt.Color;

public class Volladdierer1Bit extends ObjectPlugin implements ILiveUpdateObject
{
    static final int BREITE = 100;
    static final int HOEHE  = 200;

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
    return "1-Bit Volladdierer";
   }

   // ....
   public String  getName()
   {
      return "OBJECT.FULLADDER.1.BIT";
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
      return 0;
   }


   // Returns the DigitalSimulator the possible count of
   // input pins
   //
   public int[] getInputCountRange()
   {
      int[] result = new int[2];
      result[0] = 3;
      result[1] = 3;

      return result;
   }

   // ......
   //
   public int[] getOutputCountRange()
   {
      int[] result = new int[2];
      result[0] = 2;
      result[1] = 2;

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
      return "1-Bit Volladdierer. A und B werden addiert. Der Ausgang S gibt die Summe an."+
             "C (carry) zeigt den eventuell entstehenden Uebertrag an.";
   }


   // returns the name of the object group (e.g. Gatter, FlipFlop).
   // The object will be stored in the extenden dialog in this sub-tree of
   // the group name. Is the group does not exist it will be created.
   //
   public String  getGroup()
   {
      return "OBJECTGROUP.ALU";
   }

   // calculate the values of the output pins
   // return 0 for NO redraw neccessary
   // return 1 for redraw neccessary
   //
    public boolean calculate(int[] input ,int[] lastInput, int[] output, byte[] param)
    {
       // no carry
        if(input[2]==0)
        {
            // 0+0
            if(input[0]==0 && input[1]==0)
            {
                output[0]=0;
                output[1]=0;
            }
            // 1+1
            else if(input[0]==1 && input[1]==1)
            {
                output[0]=0;
                output[1]=1;
            }
            // 1+0
            else
            {
                output[0]=1;
                output[1]=0;
            }
        }
        else
        {
            // 1+0+0
            if(input[0]==0 && input[1]==0)
            {
                output[0]=1;
                output[1]=0;
            }
            // 1+1+1
            else if(input[0]==1 && input[1]==1)
            {
                output[0]=1;
                output[1]=1;
            }
            // 1+1+0
            else
            {
                output[0]=0;
                output[1]=1;
            }
        }
        return false;
   }

   //
   //
   public void paint(int xPos, int yPos, byte[] param)
   {
      Painter.drawRect(xPos, yPos, xPos+BREITE,yPos -HOEHE);
      Painter.drawText( "VA",50, xPos+(int)(BREITE/2-25), yPos-(HOEHE/2-30));

      Painter.drawText( "A"  ,35, xPos+7                 , yPos-((HOEHE/4)  -35));
      Painter.drawText( "B"  ,35, xPos+7                 , yPos-((HOEHE/4*2)-35));
      Painter.drawText( "Ce" ,35, xPos+7                 , yPos-((HOEHE/4*3)-35));
      Painter.drawText( "S"  ,35, xPos+BREITE-30         , yPos-((HOEHE/3)  -35));
      Painter.drawText( "C"  ,35, xPos+BREITE-30         , yPos-((HOEHE/3*2)   ));
   }

   // layout the output pins. The origin (0/0) are at the top left corner
   // x INCREASED to the right and y DECREASE to the bottom.
   //
   public int[] layoutOutput( int inputCount,  int outputCount, byte[] param )
   {
      int[] result = new int[2*outputCount];
      result[0] =  BREITE;
      result[1] = -HOEHE/3*1;
      result[2] =  BREITE;
      result[3] = -HOEHE/3*2;

      return result;
   }


   // layout the input pins. The origin (0/0) are at the top left corner
   // x increased to the right and y decreased to the bottom.
   //
   public int[] layoutInput(int inputCount, int outputCount, byte[] param)
   {
      int[] result = new int[2*inputCount];
      result[0] =  0;
      result[1] = -HOEHE/4*1;
      result[2] =  0;
      result[3] = -HOEHE/4*2;
      result[4] =  0;
      result[5] = -HOEHE/4*3;

      return result;
   }
}

