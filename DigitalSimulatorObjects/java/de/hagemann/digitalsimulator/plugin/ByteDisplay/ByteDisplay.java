package de.hagemann.digitalsimulator.plugin.ByteDisplay;

import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Painter;
import de.freegroup.digitalsimulator.plugin.object.ObjectPlugin;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;

/*
 * Title:        DigitalSimulator java Plugin
 * Description:  Ziffernanzeige incl. Decoder
 * Copyright:    Copyright (c) 2002
 * Author:       Norbert Hagemann
 * Version:      1.0 06.10.2002
 */

public class ByteDisplay extends ObjectPlugin implements ILiveUpdateObject
{
   static final int    Value       = 0;
   static final int    OldValue    = 1;

   static final byte   PointWidth  = 20;
   static final byte   PointOffset = 6;
   static final int    Height      = 6*PointOffset +7*PointWidth +20;
   static final int    Width       = 6*PointOffset +8*PointWidth +35;
   static final int    PinOffset   = -Height/9;
   static final String DescName    = "OBJ_ByteDisplay_Description";
   static final String Description = "Ziffernanzeige (00..FF) incl. Decoder";
   static final byte[][] HEXBitmuster ={
        {0x06, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06}, // HEX 0
    	{0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}, // HEX 1
    	{0x0E, 0x01, 0x01, 0x06, 0x08, 0x08, 0x0E}, // HEX 2
    	{0x0E, 0x01, 0x01, 0x06, 0x01, 0x01, 0x0E}, // HEX 3
    	{0x08, 0x09, 0x09, 0x0F, 0x01, 0x01, 0x01}, // HEX 4
    	{0x0F, 0x08, 0x08, 0x0E, 0x01, 0x01, 0x0E}, // HEX 5
    	{0x06, 0x08, 0x08, 0x0E, 0x09, 0x09, 0x06}, // HEX 6
    	{0x0F, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}, // HEX 7
    	{0x06, 0x09, 0x09, 0x06, 0x09, 0x09, 0x06}, // HEX 8
    	{0x06, 0x09, 0x09, 0x07, 0x01, 0x01, 0x06}, // HEX 9
    	{0x06, 0x09, 0x09, 0x0F, 0x09, 0x09, 0x09}, // HEX A
    	{0x0E, 0x09, 0x09, 0x0E, 0x09, 0x09, 0x0E}, // HEX B
    	{0x07, 0x08, 0x08, 0x08, 0x08, 0x08, 0x07}, // HEX C
    	{0x0E, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0E}, // HEX D
    	{0x0F, 0x08, 0x08, 0x0E, 0x08, 0x08, 0x0F}, // HEX E
    	{0x0F, 0x08, 0x08, 0x0E, 0x08, 0x08, 0x08}};// HEX F

   public String getKey()            { return "Byte-Display"; }
   public String getName()           { return "OBJECT.BYTEDISPLAY"; }
   public int    getVersion()        { return 1; }
   public String getGroup()          { return "OBJECTGROUP.DISPLAY"; }
   public String getProgrammerName() { return "Norbert Hagemann"; }
   public String getProgrammerMail() { return "norbert.hagemann@gmx.de"; }
   public String getProgrammerURL()  { return ""; }
   public String getDescription()
   {
     String Text = I18N.get(DescName);
     if ((Text.equals(DescName)) || (Text.length() == 0)) Text = Description;
     return Text;
   }

   public int getParamCount() { return 2; }
   public void init(byte[] param)
   {
     param[Value] = 0x00;
     param[OldValue] = 0x00;
   }

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
      result[0] = 0;
      result[1] = 0;
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
      int NewValue = 0;
      for (int i=0; i<8; i++) NewValue = NewValue | (input[i] << i);
      param[Value] = (byte) NewValue;
      return (param[OldValue] != param[Value]);
   }

   public void paint(int xPos, int yPos, byte[] param)
   {
      Painter.fillRect(xPos, yPos, xPos+Width, yPos-Height, 0xf7, 0xf7, 0xf7, 1, 0, 0, 0);
      // linke Ziffer
      drawDigit(xPos+10, yPos-10, param[Value] >>4);
      // rechte Ziffer
      drawDigit(xPos+25+4*PointWidth+3*PointOffset, yPos-10, param[Value]);
      param[OldValue] = param[Value];
   }

   void drawDigit(int xStart, int yStart, int Value)
   {
      int y = yStart;
      for (int i=0; i<7; i++)
      { 
         int x = xStart;
         byte Wert = HEXBitmuster[Value & 0x0F][i];
         for (int j=3; j>-1; j--)
         {
            if (((Wert >> j) & 1) == 1) Painter.fillOval(x, y, x+PointWidth, y-PointWidth, 0xFF, 0, 0);
  	    x = x+PointWidth+PointOffset;
         }        
         y = y-PointWidth-PointOffset;
      }
   }

   // layout the output pins. The origin (0/0) are at the top left corner
   // x INCREASED to the right and y DECREASE to the bottom.
   public int[] layoutOutput( int inputCount,  int outputCount, byte[] param )
   {
      int[] result = new int[2*outputCount];
      return result;
   }

   // layout the input pins. The origin (0/0) are at the top left corner
   // x increased to the right and y decreased to the bottom.
   public int[] layoutInput(int inputCount, int outputCount, byte[] param)
   {
      int[] result = new int[2*inputCount];
      for (int i=0; i<result.length; i=i+2)
      {
         result[i] = 0;
         result[i+1] = PinOffset*(i/2+1);
      }
      return result;
   }
}

