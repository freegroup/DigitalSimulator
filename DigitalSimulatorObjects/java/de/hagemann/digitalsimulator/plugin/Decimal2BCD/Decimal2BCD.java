package de.hagemann.digitalsimulator.plugin.Decimal2BCD;

import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Painter;
import de.freegroup.digitalsimulator.plugin.object.ObjectPlugin;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;

/*
 * Title:        DigitalSimulator java Plugin
 * Description:  Kodekonverter von Decimal nach BCD
 * Copyright:    Copyright (c) 2002
 * Author:       Norbert Hagemann
 * Version:      1.0 06.10.2002
 */ 

public class Decimal2BCD extends ObjectPlugin implements ILiveUpdateObject
{
   static final int    Width       = 150;
   static final int    Height      = 340;
   static final int    PinOffset   = -40;
   static final String DescName    = "OBJ_Decimal_BCD_Konverter_Description";
   static final String Description = "Kodekonverter von Decimal nach BCD";

   public String getKey()            { return "Decimal / BCD Konverter"; }
   public String getName()           { return "OBJECT.CONVERTER.DECIMAL.TO.BCD"; }
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

   public void init(byte[] param)
   {
     for (int i=0; i<8; i++) invertInput(i, true);
     for (int i=0; i<3; i++) invertOutput(i, true);
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
      result[0] = 4;
      result[1] = 4;
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
      int Value = 0xFF;
      for (int i=0; i<8; i++) if (input[i] == 1) Value = i;
      output[3] = Value == 0xFF?0:1;
      if (Value == 0xFF) Value = 0;
      for (int i=0; i<3; i++) output[i] = (Value >> i) &1;
      return false;
   }

   public void paint(int xPos, int yPos, byte[] param)
   {
      Painter.drawRect(xPos, yPos, xPos+Width, yPos-Height);
      for (int i=0; i<8; i++) Painter.drawText(""+i, 45, xPos+10, yPos-10+i*PinOffset);
      Painter.drawText("Q0", 45, xPos+90, yPos-10);      
      Painter.drawText("Q1", 45, xPos+90, yPos-50);      
      Painter.drawText("Q2", 45, xPos+90, yPos-90);      
      Painter.drawText("EO", 45, xPos+90, yPos-170);      
   }

   // layout the output pins. The origin (0/0) are at the top left corner
   // x INCREASED to the right and y DECREASE to the bottom.
   public int[] layoutOutput( int inputCount,  int outputCount, byte[] param )
   {
      int[] result = new int[2*outputCount];
      result[0] = Width;
      result[1] = -30;
      result[2] = Width;
      result[3] = -70;
      result[4] = Width;
      result[5] = -110;
      result[6] = Width;
      result[7] = -190;
      return result;
   }

   // layout the input pins. The origin (0/0) are at the top left corner
   // x increased to the right and y decreased to the bottom.
   public int[] layoutInput(int inputCount, int outputCount, byte[] param)
   {
      int[] result = new int[2*inputCount];
      for (int i=0; i<inputCount*2; i=i+2)
      {
         result[i] = 0;
         result[i+1] = -30+i/2*PinOffset;
      }
      return result;
   }
}

