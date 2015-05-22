package de.hagemann.digitalsimulator.plugin.LoadableShiftRegister;

import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Painter;
import de.freegroup.digitalsimulator.plugin.object.ObjectPlugin;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;

/*
 * Title:        DigitalSimulator java Plugin
 * Description:  Verschiebt das Bitmuster um 1 Position, das Startmuster kann eingestellt werden
 * Copyright:    Copyright (c) 2002
 * Author:       Norbert Hagemann
 * Version:      1.0 05.10.2002
 */

public class LoadableShiftRegister extends ObjectPlugin implements ILiveUpdateObject
{
   static final int In_Data   = 0;
   static final int In_Clock  = 1;
   static final int In_Clear  = 2;
   static final int In_Load   = 3;

   static final int Width     = 167;
   static final int Height    = 468;
   static final int PinOffset = -32;
   static final String DescName    = "OBJ_8-Bit_ShiftRegister_loadable_Description";
   static final String Description = "Verschiebt das Bitmuster um 1 Position.\r\n"
                                    +"Das Eingangssignal 'In' wird in den Ausgang '0' geschoben.\r\n"
                                    +"Das Startmuster kann eingestellt werden.";

   public String getKey()            { return "8-Bit ShiftRegister, loadable"; }
   public String getName()           { return "OBJECT.LOADABLESHIFTREGISTER.8.BIT"; }
   public int    getVersion()        { return 1; }
   public String getGroup()          { return "OBJECTGROUP.REGISTER"; }
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
      result[0] = 12;
      result[1] = 12;
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
      if (input[In_Clear] == 1) for(int i=0; i<output.length ; i++) output[i]=0;
      else
      {
      	 if (input[In_Load] == 1) for (int i=0; i<output.length; i++) output[i] = input[i+4];
         else if (input[In_Clock] == 1 && input[In_Clock]!=lastInput[In_Clock])
         {          
            for (int i=output.length-1; i>0; i--) output[i] = output[i-1];
            output[0] = input[In_Data];
         }
      }
      return false;
   }

   public void paint(int xPos, int yPos, byte[] param)
   {
      Painter.drawRect(xPos, yPos, xPos+Width, yPos-Height);
      Painter.drawText("In", 45, xPos+10, yPos-10);
      Painter.drawLine(xPos, yPos-60, xPos+20, yPos-70);
      Painter.drawLine(xPos+20, yPos-70, xPos, yPos-80);
      Painter.drawText("Clock", 45, xPos+30, yPos-50);
      Painter.drawText("Clear", 45, xPos+10, yPos-90);
      Painter.drawText("Load", 45, xPos+10, yPos-130);
      Painter.drawLine(xPos, yPos-180, xPos+Width, yPos-180);
      Painter.drawLine(xPos+Width-30, yPos +PinOffset-180, xPos+Width-30, yPos +PinOffset*8-180);
      Painter.drawLine(xPos+Width-30, yPos +PinOffset*8-180, xPos+Width-15, yPos +PinOffset*8-150);
      Painter.drawLine(xPos+Width-30, yPos +PinOffset*8-180, xPos+Width-45, yPos +PinOffset*8-150);
   }

   // layout the output pins. The origin (0/0) are at the top left corner
   // x INCREASED to the right and y DECREASE to the bottom.
   public int[] layoutOutput( int inputCount,  int outputCount, byte[] param )
   {
      int[] result = new int[2* outputCount];
      for(int i=0; i<(result.length); i=i+2)
      {
      	 result[i] = Width;
         result[i+1] = PinOffset*(i/2+1)-180;
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
      result[2] = 0;
      result[3] = -70;
      result[4] = 0;
      result[5] = -110;
      result[6] = 0;
      result[7] = -150;
      for (int i=8; i<result.length; i=i+2)
      {
      	 result[i] = 0;
      	 result[i+1] = PinOffset*((i-8)/2+1)-180;
      }
      return result;
   }
}
