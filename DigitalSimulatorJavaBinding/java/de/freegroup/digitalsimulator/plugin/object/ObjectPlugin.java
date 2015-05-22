package de.freegroup.digitalsimulator.plugin.object;

import de.freegroup.digitalsimulator.Application;

public abstract class ObjectPlugin
{
   // You can popup our own Dialog to configure
   // the object. Store your configuration data in the
   // `param' data block.
   //
   // return 0
   public abstract boolean doConfigure(byte[] param);

   // unique hash key for the DigitalSimulator.....this string
   // will be display in the 'extended Option' dialog
   //
   public abstract String getKey();

   // ....
   public abstract String getName();

   // Return the name of the developer of this PlugIn.
   // This name will be display in the generic option dialog
   //
   public abstract String getProgrammerName();

   // Return your homepage
   //
   public abstract String getProgrammerURL();

   // Return the Developer MailAddress. In the generic configuration
   // dialog is a mail-link.
   //
   public abstract String getProgrammerMail();

   // Return the PlugInVersion
   // At the Moment will not be checked againts
   // saved objects.....planed for the future
   // The Version will be display in the generic configuration
   // dialog
   //
   public abstract int getVersion();

   // return the text label which is displayed under the object
   // (NOT SUPPORTED AT THE MOMENT)
   //
   public final String  getLabel(){return "";}


   // return the byte count of required extra data. this data
   // will be saved witch the document.
   // The allocated data will be hand over each funktion in this
   // class
   //
   public abstract int getParamCount();

   // Returns the DigitalSimulator the possible count of
   // input pins
   //
   public abstract int[] getInputCountRange();

   // ......
   //
   public abstract int[] getOutputCountRange();

   // Return the size in Pixel which the object needs
   // Required for the DragDrop operation of the framework
   //
   public abstract int[] getSize(long inputCount, long outputCount);

   // short discription what the object do. Will be display in the
   // extenden configuration dialog
   //
   public abstract String  getDescription();

   // returns the name of the object group (e.g. Gatter, FlipFlop).
   // The object will be stored in the extenden dialog in this sub-tree of
   // the group name. Is the group does not exist it will be created.
   //
   public abstract String  getGroup();


   // calculate the values of the output pins
   // return 0 for NO redraw neccessary
   // return 1 for redraw neccessary
   //
   public abstract boolean calculate(int[] input ,int[] lastInput, int[] output, byte[] param);

   // paints the object. use the Painter class with his static function
   // for painting in the device context.
   // The origin (xPos/yPos) are at the top left corner.
   // x INCREASED to the right and y DECREASE to the bottom.
   //
   // Example:
   //   Painter.drawRect(xPos, yPos, xPos+100,yPos -200);
   //   Painter.drawLine(xPos, yPos, xPos+100,yPos -200);
   //
   public abstract void paint(int xPos, int yPos, byte[] param);


   // Before the simulator start the calculation of the circuit
   // all objects will be received a message. You can open
   // a file (e.g. report objects) or open a hardware interface
   // (e.g. parallel port)
   //
   public void onStartCalculate(byte[] param){}


   // After the calculation is done all objects will received a
   // message. You can close all handles or free some temp memory
   //
   public void onStopCalculate(byte[] param){}

   // This method will be called if the user clicks the object with
   // the left mouse button
   //
   // return true if a repaint required.
   // return false if no repaint required.
   //
   public boolean onButtonClick(int x, int y, byte[] param){return false;}


   // This method will be called if the user double clicks the object with
   // the left mouse button
   //
   // return true if a repaint required.
   // return false if no repaint required.
    //
   public boolean onButtonDblClick(int x, int y, byte[] param){return false;}

   // This method will be called if the user pressed the left
   // mouse button over the object.
   //
   // return true if a repaint required.
   // return false if no repaint required.
   //
   public boolean onButtonDown(int x, int y, byte[] param){return false;}

   // This method will be called if the user leaved the left
   // mouse button over the object.
   //
   // return true if a repaint required.
   // return false if no repaint required.
    //
   public boolean onButtonUp(int x, int y, byte[] param){return false;}

  // will be called if the mouse cursor 'enters' an object
  // (hover)
  //return true if an redraw of the object is required
  //
  public  boolean onMouseOverStart(int x, int y, byte[] param){return false;}
  
  // will be called if the mouse cursor 'moves' over an object
  // (hover)
  //return true if an redraw of the object is required
  public  boolean onMouseOver(int x, int y, byte[] param){return false;}
  
  // will be called if the mouse cursor 'leafes' an object
  // (hover)
  //return true if an redraw of the object is required
  public  boolean onMouseOverEnd(int x, int y, byte[] param){return false;}
   
   // layout the output pins. The origin (0/0) are at the top left corner
   // x INCREASED to the right and y DECREASE to the bottom.
   //
   public abstract int[] layoutOutput( int inputCount,  int outputCount, byte[] param );


   // layout the input pins. The origin (0/0) are at the top left corner
   // x increased to the right and y decreased to the bottom.
   //
   public abstract int[] layoutInput(int inputCount, int outputCount, byte[] param);


   // This method will be called after the object class has been
   // successfull loaded by the DigitalSimulator. Insert in this funktion
   // your additional init-codeing. DON'T use the static{}-method or the Constructor to init your
   // object!!!!!
   //
   // Note: This method will be called once
   //
   public void init()
   {
   }


   // After the main initialisation of the ports and graphics this
   // post initilizer will be called from the framework.
   //
   public void init(byte[] param)
   {
   }

   // call this funktions to set the input or an out as an inverter
   // All incomming or outgoing signals will be inverted automaticly
   //
   public void invertInput(int index, boolean invert)
   {
     if(Application.isRunningInDigiSim())
       n_invertInput(index, invert);
   }
   public void invertOutput(int index, boolean invert)
   {
     if(Application.isRunningInDigiSim())
      n_invertOutput(index, invert);     
   }
   public static boolean isObjectNameFree(String name)
   {
     if(Application.isRunningInDigiSim())
        return n_isObjectNameFree(name);
     return false;     
   }
   public native void    n_invertInput(int index, boolean invert);
   public native void    n_invertOutput(int index, boolean invert);
   public static native boolean n_isObjectNameFree(String name);
}

