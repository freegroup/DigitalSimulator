package de.hagemann.digitalsimulator.plugin.ASCIIDisplay;

import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Painter;
import de.freegroup.digitalsimulator.plugin.object.ObjectPlugin;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;

/*
 * Title:        DigitalSimulator java Plugin
 * Description:  Alphanummerische Anzeige incl. Decoder (7Bit-ASCII)
 * Copyright:    Copyright (c) 2002
 * Author:       Norbert Hagemann
 * Version:      1.0 06.10.2002
 */

public class ASCIIDisplay extends ObjectPlugin implements ILiveUpdateObject
{
   static final int    Value       = 0;
   static final int    OldValue    = 1;

   static final byte   PointWidth  = 20;
   static final byte   PointOffset = 6;
   static final int    Height      = 6*PointOffset +7*PointWidth +20;
   static final int    Width       = 4*PointOffset +5*PointWidth +20;
   static final int    PinOffset   = -Height/8;
   static final String DescName    = "OBJ_ASCIIDisplay_Description";
   static final String Description = "Alphanummerische Anzeige incl. 7Bit-ASCII-Decoder";
   static final byte[][] ASCIIBitmuster ={
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x00
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x01
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x02
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x03
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x04
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x05
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x06
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x07
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x08
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x09
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x0A
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x0B
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x0C
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x0D
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x0E
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x0F
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x10
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x11
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x12
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x13
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x14
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x15
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x16
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x17
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x18
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x19
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x1A
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x1B
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x1C
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x1D
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x1E
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x1F
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0x20
     {0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x04}, // 0x21
     {0x0A, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00}, // 0x22
     {0x0A, 0x0A, 0x1F, 0x0A, 0x1F, 0x0A, 0x0A}, // 0x23
     {0x04, 0x0F, 0x14, 0x0E, 0x06, 0x1E, 0x04}, // 0x24
     {0x1C, 0x15, 0x1A, 0x04, 0x0B, 0x15, 0x07}, // 0x25
     {0x08, 0x14, 0x14, 0x08, 0x15, 0x12, 0x0D}, // 0x26
     {0x06, 0x06, 0x02, 0x04, 0x00, 0x00, 0x00}, // 0x27
     {0x02, 0x04, 0x08, 0x08, 0x08, 0x04, 0x02}, // 0x28
     {0x08, 0x04, 0x02, 0x02, 0x02, 0x04, 0x08}, // 0x29
     {0x04, 0x15, 0x0E, 0x1F, 0x0E, 0x15, 0x04}, // 0x2A
     {0x00, 0x04, 0x04, 0x1F, 0x04, 0x04, 0x00}, // 0x2B
     {0x00, 0x00, 0x00, 0x0C, 0x0C, 0x04, 0x08}, // 0x2C
     {0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00}, // 0x2D
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C}, // 0x2E
     {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x00}, // 0x2F
     {0x0E, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0E}, // 0x30
     {0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E}, // 0x31
     {0x0E, 0x11, 0x01, 0x0E, 0x10, 0x10, 0x1F}, // 0x32
     {0x0E, 0x11, 0x01, 0x06, 0x01, 0x11, 0x0E}, // 0x33
     {0x02, 0x06, 0x0A, 0x12, 0x1F, 0x02, 0x02}, // 0x34
     {0x1F, 0x10, 0x1E, 0x01, 0x01, 0x11, 0x0E}, // 0x35
     {0x06, 0x08, 0x10, 0x1E, 0x11, 0x11, 0x0E}, // 0x36
     {0x1F, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08}, // 0x37
     {0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E}, // 0x38
     {0x0E, 0x11, 0x11, 0x0F, 0x01, 0x02, 0x0C}, // 0x39
     {0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x00}, // 0x3A
     {0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x04, 0x08}, // 0x3B
     {0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02}, // 0x3C
     {0x00, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x00}, // 0x3D
     {0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08}, // 0x3E
     {0x0E, 0x11, 0x01, 0x02, 0x04, 0x00, 0x04}, // 0x3F
     {0x0E, 0x11, 0x01, 0x0D, 0x15, 0x15, 0x0E}, // 0x40
     {0x04, 0x0A, 0x11, 0x11, 0x1F, 0x11, 0x11}, // 0x41
     {0x1E, 0x09, 0x09, 0x0E, 0x09, 0x09, 0x1E}, // 0x42
     {0x0E, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0E}, // 0x43
     {0x1E, 0x09, 0x09, 0x09, 0x09, 0x09, 0x1E}, // 0x44
     {0x1F, 0x10, 0x10, 0x1C, 0x10, 0x10, 0x1F}, // 0x45
     {0x1F, 0x10, 0x10, 0x1C, 0x10, 0x10, 0x10}, // 0x46
     {0x0E, 0x11, 0x10, 0x17, 0x11, 0x11, 0x0E}, // 0x47
     {0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11}, // 0x48
     {0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E}, // 0x49
     {0x07, 0x02, 0x02, 0x02, 0x02, 0x12, 0x0C}, // 0x4A
     {0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11}, // 0x4B
     {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F}, // 0x4C
     {0x11, 0x1B, 0x15, 0x15, 0x11, 0x11, 0x11}, // 0x4D
     {0x11, 0x19, 0x15, 0x13, 0x11, 0x11, 0x11}, // 0x4E
     {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, // 0x4F
     {0x1E, 0x11, 0x11, 0x1E, 0x10, 0x10, 0x10}, // 0x50
     {0x0E, 0x11, 0x11, 0x11, 0x15, 0x12, 0x0D}, // 0x51
     {0x1E, 0x11, 0x11, 0x1E, 0x14, 0x12, 0x11}, // 0x52
     {0x0E, 0x11, 0x10, 0x0E, 0x01, 0x11, 0x0E}, // 0x53
     {0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}, // 0x54
     {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, // 0x55
     {0x11, 0x11, 0x11, 0x0A, 0x0A, 0x04, 0x04}, // 0x56
     {0x11, 0x11, 0x11, 0x15, 0x15, 0x1B, 0x11}, // 0x57
     {0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11}, // 0x58
     {0x11, 0x11, 0x0A, 0x04, 0x04, 0x04, 0x04}, // 0x59
     {0x1F, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1F}, // 0x5A
     {0x0E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0E}, // 0x5B
     {0x00, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00}, // 0x5C
     {0x0E, 0x02, 0x02, 0x02, 0x02, 0x02, 0x0E}, // 0x5D
     {0x04, 0x0A, 0x11, 0x00, 0x00, 0x00, 0x00}, // 0x5E
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F}, // 0x5F
     {0x06, 0x06, 0x04, 0x02, 0x00, 0x00, 0x00}, // 0x60
     {0x00, 0x00, 0x0E, 0x01, 0x0F, 0x11, 0x0E}, // 0x61
     {0x10, 0x10, 0x16, 0x19, 0x11, 0x19, 0x16}, // 0x62
     {0x00, 0x00, 0x07, 0x08, 0x08, 0x08, 0x07}, // 0x63
     {0x01, 0x01, 0x0D, 0x13, 0x11, 0x13, 0x0D}, // 0x64
     {0x00, 0x00, 0x0E, 0x11, 0x1F, 0x10, 0x0E}, // 0x65
     {0x06, 0x09, 0x08, 0x1E, 0x08, 0x08, 0x08}, // 0x66
     {0x00, 0x00, 0x0F, 0x11, 0x0F, 0x01, 0x0E}, // 0x67
     {0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x11}, // 0x68
     {0x04, 0x00, 0x0C, 0x04, 0x04, 0x04, 0x0E}, // 0x69
     {0x02, 0x00, 0x06, 0x02, 0x02, 0x12, 0x0C}, // 0x6A
     {0x08, 0x08, 0x09, 0x0A, 0x0C, 0x0A, 0x09}, // 0x6B
     {0x0C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E}, // 0x6C
     {0x00, 0x00, 0x1A, 0x15, 0x15, 0x15, 0x15}, // 0x6D
     {0x00, 0x00, 0x16, 0x19, 0x11, 0x11, 0x11}, // 0x6E
     {0x00, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E}, // 0x6F
     {0x00, 0x00, 0x1E, 0x11, 0x1E, 0x10, 0x10}, // 0x70
     {0x00, 0x00, 0x0F, 0x11, 0x0F, 0x01, 0x01}, // 0x71
     {0x00, 0x00, 0x16, 0x19, 0x10, 0x10, 0x10}, // 0x72
     {0x00, 0x00, 0x0F, 0x10, 0x0E, 0x01, 0x1E}, // 0x73
     {0x04, 0x04, 0x0F, 0x04, 0x04, 0x04, 0x03}, // 0x74
     {0x00, 0x00, 0x11, 0x11, 0x11, 0x13, 0x0D}, // 0x75
     {0x00, 0x00, 0x11, 0x11, 0x11, 0x0A, 0x04}, // 0x76
     {0x00, 0x00, 0x11, 0x11, 0x15, 0x15, 0x0A}, // 0x77
     {0x00, 0x00, 0x11, 0x0A, 0x04, 0x0A, 0x11}, // 0x78
     {0x00, 0x00, 0x11, 0x11, 0x0F, 0x01, 0x0E}, // 0x79
     {0x00, 0x00, 0x1F, 0x02, 0x04, 0x08, 0x1F}, // 0x7A
     {0x02, 0x04, 0x04, 0x08, 0x04, 0x04, 0x02}, // 0x7B
     {0x04, 0x04, 0x04, 0x00, 0x04, 0x04, 0x04}, // 0x7C
     {0x08, 0x04, 0x04, 0x02, 0x04, 0x04, 0x08}, // 0x7D
     {0x08, 0x15, 0x02, 0x00, 0x00, 0x00, 0x00}, // 0x7E
     {0x0A, 0x15, 0x0A, 0x15, 0x0A, 0x15, 0x0A}  // 0x7F
     };

   public String getKey()            { return "ASCII-Display"; }
   public String getName()           { return "OBJECT.ASCIIDISPLAY"; }
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
      param[Value] = 0x41;
      param[OldValue] = 0x41;
   }
   
   public boolean doConfigure(byte[] param) { return false; }
  
   // Returns the DigitalSimulator the possible count of input pins
   public int[] getInputCountRange()
   {
      int[] result = new int[2];
      result[0] = 7;
      result[1] = 7;
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
      for (int i=0; i<input.length; i++) NewValue = NewValue | (input[i] << i);
      param[Value] = (byte) NewValue;
      return (param[OldValue] != param[Value]);
   }

   public void paint(int xPos, int yPos, byte[] param)
   {
      Painter.fillRect(xPos, yPos, xPos+Width, yPos-Height, 0xf7, 0xf7, 0xf7, 1, 0, 0, 0);
      int y = yPos-10;
      for (int i=0; i<7; i++)
      { 
         int x = xPos+10;
         byte Wert = ASCIIBitmuster[param[Value]][i];
         for (int j=4; j>-1; j--)
         {
    	    if (((Wert >> j) & 1) == 1) Painter.fillOval(x, y, x+PointWidth, y-PointWidth, 0xFF, 0, 0);
      	    x = x+PointWidth+PointOffset;
      	 }        
         y = y-PointWidth-PointOffset;
      }
      param[OldValue] = param[Value];
   }

   // layout the output pins. The origin (0/0) are at the top left corner
   // x INCREASED to the right and y DECREASE to the bottom.
   public int[] layoutOutput( int inputCount,  int outputCount, byte[] param )
   {
      int[] result = new int[0];
      return result;
   }

   // layout the input pins. The origin (0/0) are at the top left corner
   // x increased to the right and y decreased to the bottom.
   public int[] layoutInput(int inputCount, int outputCount, byte[] param)
   {
      int[] result = new int[2*inputCount];
      for (int i=0; i<2*inputCount; i=i+2)
      {
        result[i]   = 0;
        result[i+1] = PinOffset*(i/2+1);
      }
      return result;
   }
  
}
