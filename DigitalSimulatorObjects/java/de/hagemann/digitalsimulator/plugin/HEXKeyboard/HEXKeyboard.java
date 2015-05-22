package de.hagemann.digitalsimulator.plugin.HEXKeyboard;

import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Painter;
import de.freegroup.digitalsimulator.plugin.object.ObjectPlugin;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;

/*
 * Title:        DigitalSimulator java Plugin
 * Description:  Tastenfeld zur Eingabe von Ziffern
 * Copyright:    Copyright (c) 2002
 * Author:       Norbert Hagemann
 * Version:      1.0 05.10.2002
 */

public class HEXKeyboard extends ObjectPlugin implements ILiveUpdateObject
{
   static final int    KeyValue  = 0;
   static final int    KeyDown   = 1;
   static final int    KeyMouse  = 2;
   static final int    Running   = 3;

   static final int    Height    = 265;
   static final int    Width     = 200;
   static final int    PinOffset = -32;
   static final String KeyText   = "0123456789ABCDEF";
   static final int[]  xKeyPos   = {10, 60, 110, 160};
   static final int[]  yKeyPos   = {5, 70, 135, 200};
   static final String DescName    = "OBJ_HEXKeyboard_Description";
   static final String Description = "Tastenfeld zur Eingabe von Ziffern.";
   
   public String getKey()            { return "HEXKeyboard"; }
   public String getName()           { return "OBJECT.HEXKEYBOARD"; }
   public int    getVersion()        { return 1; }
   public String getGroup()          { return "OBJECTGROUP.SWITCH"; }
   public String getProgrammerName() { return "Norbert Hagemann"; }
   public String getProgrammerMail() { return "norbert.hagemann@gmx.de"; }
   public String getProgrammerURL()  { return ""; }
   public String getDescription()
   {
     String Text = I18N.get(DescName);
     if ((Text.equals(DescName)) || (Text.length() == 0)) Text = Description;
     return Text;
   }
    
   public int getParamCount() { return 4; }

   public void init(byte[] param)
   {
     param[KeyValue] = 0;
     param[KeyDown] = 0;
     param[KeyMouse] = -1;
     param[Running] = 0;
   }

   public boolean doConfigure(byte[] param) { return false; }

   // Returns the DigitalSimulator the possible count of input pins
   public int[] getInputCountRange()
   {
      int[] result = new int[2];
      result[0] = 0;
      result[1] = 0;
      return result;
   }

   // Returns the DigitalSimulator the possible count of output pins
   public int[] getOutputCountRange()
   {
      int[] result = new int[2];
      result[0] = 5;
      result[1] = 5;
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
      for (int i=0; i<4; i++) output[i] = (param[KeyValue] >> i) & 1;
      output[4] = param[KeyDown];
      return false;
   }

   public void paint(int xPos, int yPos, byte[] param)
   {
      if ((param[Running] == 1) && (param[KeyMouse] > -1))
        Painter.fillRect(xPos, yPos, xPos+Width, yPos-Height, 0xF0, 0xF0, 0xF0, 1, 0, 0, 0);
      else Painter.drawRect(xPos, yPos, xPos+Width, yPos-Height);
      for (int i=1; i<4; i++)
      {
        Painter.drawLine(xPos+xKeyPos[i]-10, yPos, xPos+xKeyPos[i]-10, yPos-Height);
        Painter.drawLine(xPos, yPos-yKeyPos[i]+5, xPos+Width, yPos-yKeyPos[i]+5);
      }
      for (int i=0; i<KeyText.length(); i++)
        Painter.drawText(KeyText.substring(i, i+1), 60, xPos+xKeyPos[i & 3], yPos-yKeyPos[i >> 2], (((param[Running] == 1) && (i == param[KeyMouse]))?0xFF:0x00), 0x00, 0x00);
   }

   // layout the output pins. The origin (0/0) are at the top left corner
   // x INCREASED to the right and y DECREASE to the bottom.
   public int[] layoutOutput( int inputCount,  int outputCount, byte[] param )
   {
      int[] result = new int[2*outputCount];
      result[0] = Width;
      result[1] = PinOffset*1;
      result[2] = Width;
      result[3] = PinOffset*2;
      result[4] = Width;
      result[5] = PinOffset*3;
      result[6] = Width;
      result[7] = PinOffset*4;
      result[8] = Width;
      result[9] = -Height-PinOffset;

      return result;
   }

   // layout the input pins. The origin (0/0) are at the top left corner
   // x increased to the right and y decreased to the bottom.
   public int[] layoutInput(int inputCount, int outputCount, byte[] param)
   {
      int[] result = new int[0];
      return result;
   }

  
   public boolean onButtonDown(int x, int y, byte[] param)   
   { 
      int col = x/50;
      int row = ~y/65;
      if ((col <4) && (row <4))
      {
        param[KeyValue] = (byte)(row*4+col);
        param[KeyDown] = 1;   
      }
      return false;
   }

   // This method will be called if the user leaved the left
   // mouse button over the object.
   //
   // return true if a repaint required.
   // return false if no repaint required.
   public boolean onButtonUp(int x, int y, byte[] param)
   { 
      param[KeyDown] = 0;
      return false;
   }
   
   // Die Maus betritt das Keyboard 
   public  boolean onMouseOverStart(int x, int y, byte[] param)
   { return onMouseOver(x, y, param); }
      
   // Die Maus wird im Keyboard bewegt
   public  boolean onMouseOver(int x, int y, byte[] param)
   {
      boolean NewValue;
      int col = x/50;
      int row = ~y/65;
      if ((col <4) && (row <4))
      {
      	 NewValue = param[KeyMouse] != (byte)(row*4+col);
      	 param[KeyMouse] = (byte)(row*4+col);
      }
      else
      {
         NewValue = true;
         param[KeyMouse] = -1;
      }
      return (param[Running] == 1) && NewValue;
   }

   // Die Maus verlässt das Keyboard 
   public  boolean onMouseOverEnd(int x, int y, byte[] param) 
   {
     param[KeyMouse] = -1;
     return (param[Running] == 1);
   }
   
   // before the simulator start the calculation of the circuit
   // all objects will be received a message. You can open
   // a file (e.g. report objects) or open a hardware interface
   // (e.g. parallel port)
   public void onStartCalculate(byte[] param)
   {
     init(param);
     param[Running] = 1;
   }

   // After the calculation is done all objects will received a
   // message. You can close all handles or free some temp memory
   public void onStopCalculate(byte[] param)
   {
     param[Running] = 0;
   }
}

