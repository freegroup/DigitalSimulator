package de.hagemann.digitalsimulator.plugin.Komparator;

import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Painter;
import de.freegroup.digitalsimulator.plugin.object.ObjectPlugin;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;

/*
 * Title:        DigitalSimulator java Plugin
 * Description:  Vergleicht zwei 4-Bit Eingangswerte
 * Copyright:    Copyright (c) 2002
 * Author:       Norbert Hagemann
 * Version:      1.0 05.10.2002
 */

public class Komparator extends ObjectPlugin implements ILiveUpdateObject
{
   static final int Width     = 195;
   static final int Height    = 385;
   static final int PinOffset = -40;
   static final String DescName    = "OBJ_Komparator_Description";
   static final String Description = "Vergleicht zwei 4-Bit Eingangswerte.";

   public String getKey()            { return "4-Bit Komparator"; }
   public String getName()           { return "OBJECT.COMPARATOR.4.BIT"; }
   public int    getVersion()        { return 1; }
   public String getGroup()          { return "OBJECTGROUP.ALU"; }
   public String getProgrammerName() { return "Norbert Hagemann"; }
   public String getProgrammerMail() { return "norbert.hagemann@gmx.de"; }
   public String getProgrammerURL()  { return ""; }
   public String getDescription()
   {
     String Text = I18N.get(DescName);
     if ((Text.equals(DescName)) || (Text.length() == 0)) Text = Description;
     return Text;
   }
    
   public int getParamCount() { return 0; }

  public boolean doConfigure(byte[] param) { return false; }

   // Returns the DigitalSimulator the possible count of input pins
   public int[] getInputCountRange()
   {
      int[] result = new int[2];
      result[0] = 8;
      result[1] = 8;
      return result;
   }

   // Returns the DigitalSimulator the possible count of output pins
   public int[] getOutputCountRange()
   {
      int[] result = new int[2];
      result[0] = 6;
      result[1] = 6;
      return result;
   }

   // Return the size in Pixel wich the object needs
   // Required for the DragDrop operation of the framework
   public int[] getSize(long inputCount, long outputCount)
   {
      int[] result = new int[2];
      result[0] = Width;
      result[1] = Height;
      return result;
   }

   // calculate the values of the output pins
   // return 0 for NO redraw neccessary
   // return 1 for redraw neccessary
   public boolean calculate(int[] input ,int[] lastInput, int[] output, byte[] param)
   {
      int AValue = input[0] +(input[1] << 1) +(input[2] << 2) +(input[3] << 3);
      int BValue = input[4] +(input[5] << 1) +(input[6] << 2) +(input[7] << 3);
      
      output[0] = (AValue == BValue)?1:0;
      output[1] = (AValue > BValue)?1:0;
      output[2] = (AValue < BValue)?1:0;
      output[3] = output[0] ^1;
      output[4] = output[0] | output[1];
      output[5] = output[0] | output[2];
      
      return false;
   }

   public void paint(int xPos, int yPos, byte[] param)
   {
      Painter.drawRect(xPos, yPos, xPos+Width, yPos-Height);
      Painter.drawText("A0", 45, xPos+10, yPos-10);
      Painter.drawText("A1", 45, xPos+10, yPos-50);
      Painter.drawText("A2", 45, xPos+10, yPos-90);
      Painter.drawText("A3", 45, xPos+10, yPos-130);
      Painter.drawText("B0", 45, xPos+10, yPos-210);
      Painter.drawText("B1", 45, xPos+10, yPos-250);
      Painter.drawText("B2", 45, xPos+10, yPos-290);
      Painter.drawText("B3", 45, xPos+10, yPos-330);
      Painter.drawText("A=B", 45, xPos+115, yPos-50);
      Painter.drawText("A>B", 45, xPos+115, yPos-90);
      Painter.drawText("A<B", 45, xPos+115, yPos-130);
      Painter.drawText("A<>B", 45, xPos+98, yPos-210);
      Painter.drawText("A>=B", 45, xPos+98, yPos-250);
      Painter.drawText("A<=B", 45, xPos+98, yPos-290);
   }

   // layout the output pins. The origin (0/0) are at the top left corner
   // x INCREASED to the right and y DECREASE to the bottom.
   public int[] layoutOutput( int inputCount,  int outputCount, byte[] param )
   {
      int[] result = new int[2* outputCount];
      result[0] = Width;
      result[1] = PinOffset*2+10;
      result[2] = Width;
      result[3] = PinOffset*3+10;
      result[4] = Width;
      result[5] = PinOffset*4+10;
      
      result[6] = Width;
      result[7] = PinOffset*6+10;
      result[8] = Width;
      result[9] = PinOffset*7+10;
      result[10] = Width;
      result[11] = PinOffset*8+10;
      return result;
   }

   // layout the input pins. The origin (0/0) are at the top left corner
   // x increased to the right and y decreased to the bottom.
   public int[] layoutInput(int inputCount, int outputCount, byte[] param)
   {
      int[] result = new int[2*inputCount];
      result[0] = 0;
      result[1] = PinOffset*1+10;
      result[2] = 0;
      result[3] = PinOffset*2+10;
      result[4] = 0;
      result[5] = PinOffset*3+10;
      result[6] = 0;
      result[7] = PinOffset*4+10;
      
      result[8] = 0;
      result[9] = PinOffset*6+10;
      result[10] = 0;
      result[11] = PinOffset*7+10;
      result[12] = 0;
      result[13] = PinOffset*8+10;
      result[14] = 0;
      result[15] = PinOffset*9+10;
      return result;
   }
}
