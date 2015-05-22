package de.freegroup.digitalsimulator.plugin.volladdierer4bit;

/**
 * Title:        DigitalSimulator java Pugins
 * Description:  4 bit full adder
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */

import java.util.*;
import de.freegroup.digitalsimulator.Painter;
import de.freegroup.digitalsimulator.plugin.object.ObjectPlugin;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;

public class Volladdierer4Bit extends ObjectPlugin implements ILiveUpdateObject
{
    static final int   INPUTCOUNT   = 9;
    static final int   OUTPUTCOUNT  = 5;
    static final int   BREITE       = 200;
    static final int   HOEHE        = 500;
    static final float OUTPUTOFFSET = HOEHE/(OUTPUTCOUNT+1);
    static final float INPUTOFFSET  = HOEHE/(INPUTCOUNT+1);

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
    return "4-Bit Volladdierer";
   }

   // ....
   public String  getName()
   {
      return "OBJECT.FULLADDER.4.BIT";
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
      result[0] = 9;
      result[1] = 9;

      return result;
   }

   // ......
   //
   public int[] getOutputCountRange()
   {
      int[] result = new int[2];
      result[0] = 5;
      result[1] = 5;

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
      return "4-Bit Volladdierer. A und B werden addiert. Der Ausgang S gibt die Summe an."+
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
        int carry = input[8];

        for (int i=0; i<4 ; i++)
        {
            // calculate with the carry
            if(carry==1)
            {
                if(input[i]==1 && input[i+4]==1)
                {
                    output[i]=1;
                }
                else if(input[i]==1 || input[i+4]==1)
                {
                    output[i]=0;
                }
                else
                {
                    output[i]=1;
                    carry=0;
                }
            }
            else
            {
                if(input[i]==1 && input[i+4]==1)
                {
                    output[i]=0;
                    carry = 1;
                }
                else if(input[i]==1 || input[i+4]==1)
                {
                    output[i]=1;
                }
                else
                {
                    output[i]=0;
                }
            }
        }
        output[4]=carry;
        return false;
    }

   //
   //
   public void paint(int xPos, int yPos, byte[] param)
   {
      Painter.drawRect(xPos, yPos, xPos+BREITE,yPos -HOEHE);
      Painter.drawText( "VA"   ,50, xPos+(int)(BREITE/2-25), yPos-(HOEHE/2-80));
      Painter.drawText( "4-Bit",40, xPos+(int)(BREITE/2-25), yPos-(HOEHE/2-30));

      Painter.drawText( "A1"  ,35, xPos+7                ,(int)( yPos-((INPUTOFFSET*1)-15)));
      Painter.drawText( "B1"  ,35, xPos+7                ,(int)( yPos-((INPUTOFFSET*2)-15)));
      Painter.drawText( "C1"  ,35, xPos+7                ,(int)( yPos-((INPUTOFFSET*3)-15)));
      Painter.drawText( "D1"  ,35, xPos+7                ,(int)( yPos-((INPUTOFFSET*4)-15)));
      Painter.drawText( "A2"  ,35, xPos+7                ,(int)( yPos-((INPUTOFFSET*5)-15)));
      Painter.drawText( "B2"  ,35, xPos+7                ,(int)( yPos-((INPUTOFFSET*6)-15)));
      Painter.drawText( "C2"  ,35, xPos+7                ,(int)( yPos-((INPUTOFFSET*7)-15)));
      Painter.drawText( "D2"  ,35, xPos+7                ,(int)( yPos-((INPUTOFFSET*8)-15)));
      Painter.drawText( "Ce" ,35, xPos+7                 ,(int)( yPos-((INPUTOFFSET*9)-15)));
      Painter.drawText( "As"  ,35, xPos+BREITE-40        ,(int)( yPos-((OUTPUTOFFSET*1) -15)));
      Painter.drawText( "Bs"  ,35, xPos+BREITE-40        ,(int)( yPos-((OUTPUTOFFSET*2) -15)));
      Painter.drawText( "Cs"  ,35, xPos+BREITE-40        ,(int)( yPos-((OUTPUTOFFSET*3) -15)));
      Painter.drawText( "Ds"  ,35, xPos+BREITE-40        ,(int)( yPos-((OUTPUTOFFSET*4) -15)));
      Painter.drawText( "C"  ,35, xPos+BREITE-40         ,(int)( yPos-((OUTPUTOFFSET*5) -15)));
   }

   // layout the output pins. The origin (0/0) are at the top left corner
   // x INCREASED to the right and y DECREASE to the bottom.
   //
   public int[] layoutOutput( int inputCount,  int outputCount, byte[] param )
   {
      int[] result = new int[2*outputCount];
      result[0] =  BREITE;
      result[1] =(int) -OUTPUTOFFSET*1;
      result[2] =  BREITE;
      result[3] =(int) -OUTPUTOFFSET*2;
      result[4] =  BREITE;
      result[5] =(int) -OUTPUTOFFSET*3;
      result[6] =  BREITE;
      result[7] =(int) -OUTPUTOFFSET*4;
      result[8] =  BREITE;
      result[9] =(int) -OUTPUTOFFSET*5;

      return result;
   }


   // layout the input pins. The origin (0/0) are at the top left corner
   // x increased to the right and y decreased to the bottom.
   //
   public int[] layoutInput(int inputCount, int outputCount, byte[] param)
   {
      int[] result = new int[2*inputCount];
      result[0]  =  0;
      result[1]  =(int) -INPUTOFFSET*1;
      result[2]  =  0;
      result[3]  =(int) -INPUTOFFSET*2;
      result[4]  =  0;
      result[5]  =(int) -INPUTOFFSET*3;
      result[6]  =  0;
      result[7]  =(int) -INPUTOFFSET*4;
      result[8]  =  0;
      result[9]  =(int) -INPUTOFFSET*5;
      result[10] =  0;
      result[11] =(int) -INPUTOFFSET*6;
      result[12] =  0;
      result[13] =(int) -INPUTOFFSET*7;
      result[14] =  0;
      result[15] =(int) -INPUTOFFSET*8;
      result[16] =  0;
      result[17] =(int) -INPUTOFFSET*9;

      return result;
   }
}
