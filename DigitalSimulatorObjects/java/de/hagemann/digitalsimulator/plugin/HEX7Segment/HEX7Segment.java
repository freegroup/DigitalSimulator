package de.hagemann.digitalsimulator.plugin.HEX7Segment;

import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Painter;
import de.freegroup.digitalsimulator.plugin.object.ObjectPlugin;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;

/*
 * Title:        DigitalSimulator java Plugin
 * Description:  Konvertiert 4-Bit-Binär nach 7-Segment-Anzeige
 * Copyright:    Copyright (c) 2002
 * Author:       Norbert Hagemann
 * Version:      1.1 05.10.2002
 */

public class HEX7Segment extends ObjectPlugin implements ILiveUpdateObject
{  
   static final int    Height       = 243;
   static final int    Width        = 167;
   static final int    PinOutOffset = -30;
   static final int    PinInOffset  = -48;
   static final String DescName     = "OBJ_HEX_7Segment_Konverter_Description";
   static final String Description  = "Kodekonverter von HEX nach 7-Segment.";
   static final byte[] SegmentBits  = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
                                       0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

   public String getKey()            { return "HEX / 7Segment Konverter"; }   
   public String getName()           { return "OBJECT.CONVETER.HEX.TO.7SEGMENT"; }
   public int    getVersion()        { return 1; }
   public String getGroup()          { return "OBJECTGROUP.CONVERTER"; }
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
      result[0] = 4;
      result[1] = 4;
      return result;
   }

   // Returns the DigitalSimulator the possible count of output pins
   public int[] getOutputCountRange()
   {
      int[] result = new int[2];
      result[0] = 7;
      result[1] = 7;
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
      byte OutWert = SegmentBits[input[0] +(input[1] << 1) +(input[2] << 2) +(input[3] << 3)];
      for (int i=0; i<output.length; i++) output[i] = (OutWert >> i) & 1;
      return false;
   }

   public void paint(int xPos, int yPos, byte[] param)
   {
      Painter.drawRect(xPos, yPos, xPos+Width, yPos-Height);
      Painter.drawText("HEX", 60, xPos+10, yPos);
      Painter.drawText("7-Seg", 60, xPos+40, yPos-85);
      Painter.drawLine(xPos+Width-10, yPos-30, xPos+10, yPos-100);
   }

   // layout the output pins. The origin (0/0) are at the top left corner
   // x INCREASED to the right and y DECREASE to the bottom.
   public int[] layoutOutput( int inputCount,  int outputCount, byte[] param )
   {
      int[] result = new int[2*outputCount];
      for (int i=0; i<2*outputCount; i=i+2)
      {
      	 result[i] = Width;
      	 result[i+1] = PinOutOffset*(i/2+1);
      }
      return result;
   }

   // layout the input pins. The origin (0/0) are at the top left corner
   // x increased to the right and y decreased to the bottom.
   public int[] layoutInput(int inputCount, int outputCount, byte[] param)
   {
      int[] result = new int[2*inputCount];
      for (int i=0; i<2*inputCount; i=i+2)
      {
      	 result[i] = 0;
      	 result[i+1] = PinInOffset*(i/2+1);
      }
      return result;
   }
}

