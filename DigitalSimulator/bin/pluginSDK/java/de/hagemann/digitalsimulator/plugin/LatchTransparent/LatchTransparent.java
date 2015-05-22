package de.hagemann.digitalsimulator.plugin.LatchTransparent;

import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Painter;
import de.freegroup.digitalsimulator.plugin.object.ObjectPlugin;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;

/*
 * Title:        DigitalSimulator java Plugin
 * Description:  Speicher für 8 Bits, transparent
 * Copyright:    Copyright (c) 2002
 * Author:       Norbert Hagemann
 * Version:      1.0 06.10.2002
 */

public class LatchTransparent extends ObjectPlugin implements ILiveUpdateObject
{
   static final int Width     = 167;
   static final int Height    = 348;
   static final int PinOffset = -32;
   static final String DescName    = "OBJ_Latch_8-Bit_transparent_Description";
   static final String Description = "Speicher fuer 8 Bits\r\n\r\nQ=D solange Enable 1 ist";

   public String getKey()            { return "Latch 8-Bit transparent"; }
   public String getName()           { return "OBJECT.TRANSPARENTLATCH.8.BIT"; }
   public int    getVersion()        { return 1; }
   public String getGroup()          { return "OBJECTGROUP.MEMORY"; }
   public String getProgrammerName() { return "Norbert Hagemann"; }
   public String getProgrammerMail() { return "norbert.hagemann@gmx.de"; }
   public String getProgrammerURL()  { return ""; }
   public String getDescription()
   {
      String Text = I18N.get(DescName);
      return (((Text.equals(DescName)) || (Text.length() == 0))?Description:Text);
   }

   public int getParamCount() { return 0; }

  public boolean doConfigure(byte[] param) { return false; }

   // Returns the DigitalSimulator the possible count of input pins
   public int[] getInputCountRange()
   {
      int[] result = new int[2];
      result[0] = 9;
      result[1] = 9;
      return result;
   }

   // Returns the DigitalSimulator the possible count of output pins
   public int[] getOutputCountRange()
   {
      int[] result = new int[2];
      result[0] = 8;
      result[1] = 8;
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
      if (input[0] == 1) for (int i=1; i<input.length; i++) output[i-1] = input[i];
      return false;
   }

   public void paint(int xPos, int yPos, byte[] param)
   {
      Painter.drawRect(xPos, yPos, xPos+Width, yPos-Height);
      Painter.drawText("Enable", 45, xPos+10, yPos-10);
      Painter.drawLine(xPos, yPos-60, xPos+Width, yPos-60);
   }

   // layout the output pins. The origin (0/0) are at the top left corner
   // x INCREASED to the right and y DECREASE to the bottom.
   public int[] layoutOutput( int inputCount,  int outputCount, byte[] param )
   {
      int[] result = new int[2* outputCount];
      for(int i=0; i<(result.length); i=i+2)
      {
      	 result[i] = Width;
         result[i+1] = PinOffset*(i/2+1)-58;
      }
      return result;
   }

   // layout the input pins. The origin (0/0) are at the top left corner
   // x increased to the right and y decreased to the bottom.
   public int[] layoutInput(int inputCount, int outputCount, byte[] param)
   {
      int[] result = new int[2*inputCount];
      result[0] = 0;
      result[1] = -30;
      for (int i=2; i<result.length; i=i+2)
      {
      	 result[i] = 0;
      	 result[i+1] = PinOffset*((i-1)/2+1)-58;
      }
      return result;
   }
}
