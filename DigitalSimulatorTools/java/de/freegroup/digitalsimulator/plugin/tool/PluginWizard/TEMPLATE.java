package de.freegroup.digitalsimulator.plugin.tool.PluginWizard;

/**
 * Title:        DigitalSimulator java Pugins
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.*;
import java.util.zip.ZipException;

import com.holub.tools.Archive;

import bsh.EvalError;
import bsh.Interpreter;
import de.freegroup.digitalsimulator.Painter;
import de.freegroup.digitalsimulator.plugin.object.*;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.dialogs.*;
import de.freegroup.digitalsimulator.plugin.PluginManager;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;
import de.freegroup.digitalsimulator.update.LiveUpdateObject;
import de.freegroup.digitalsimulator.plugin.tool.PluginWizard.*;

public class TEMPLATE extends MutableObjectPlugin implements ILiveUpdateObject
{
    private static Interpreter interpreter = new Interpreter();
    
    private static String programmerName = null;
    private static String programmerURL  = null;
    private static String programmerMail = null;
    
    private static int    version        = -1;
    private static String description    = null;
    private static String group          = null;
    private static String name           = null;
    
    private static int    inputCount  =-1;
    private static int    outputCount =-1;
    private static int    paramCount  =-1;
    
    private static int    width       = -1;
    private static int    height      = -1;
    
    private static String calculate        = null;
    private static String layoutInput      = null;
    private static String layoutOutput     = null;
    private static String onButtonClick    = null;
    private static String paint            = null;
    private static String onButtonDown     = null;
    private static String onButtonUp       = null;
    private static String onStartCalculate = null;
    private static String onStopCalculate  = null;
    private static String onMouseOverEnd   = null;
    private static String onMouseOver      = null;
    private static String onMouseOverStart = null;
    private static String jarPlugin = null;
    
    private static boolean changed=false;
    
   // You can popup our own Dialog to configure
   // the object. Store your configuration data in the
   // `param' data block.
   //
   
   public boolean doConfigure(byte[] param)
   {
    try
    {
      WizardObjectCustomize dialog = new WizardObjectCustomize(this);
      return dialog.isOk();
     }
     catch(Throwable th)
     {
      Trace.error(th);
     }
     return false;
   }
   
   
  public String getData(String fileInArchive)
  {
    try
    {
      if(jarPlugin==null)
      {
        jarPlugin = PluginManager.getJarFileFromPluginClass(this.getClass().getName());
        int index = jarPlugin.indexOf(".jar");
        jarPlugin = jarPlugin.substring(0,index)+".object";
        Trace.info(jarPlugin);
      }
      Archive arch = new Archive(jarPlugin);
      InputStream in = arch.input_stream_for(fileInArchive);
      BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(in));
      StringBuffer line = new StringBuffer();
      int count = 0;
      char[] c = new char[1];
      while ((count = bufferedReader.read(c)) != -1)
      {
        line.append(c);
      }
      return line.toString();
    }
    catch (ZipException e)
    {
      Trace.error(e);
      return e.getMessage();
    }
    catch (Exception e)
    {
      Trace.error(e);
      return e.getMessage();
    }
  }

  public void setData(String fileInArchive, String data)
  {
    try
    {
      if(jarPlugin==null)
      {
        jarPlugin = PluginManager.getJarFileFromPluginClass(this.getClass().getName());
        int index = jarPlugin.indexOf(".jar");
        jarPlugin = jarPlugin.substring(0,index)+".object";
        Trace.info(jarPlugin);
      }
      Archive arch = new Archive(jarPlugin);
      OutputStream out = arch.output_stream_for(fileInArchive);
      out.write(data.getBytes("ISO-8859-1"));
      Trace.info("FILE DATA:\n"+data);
      out.close();
      arch.close();
      
      if(fileInArchive.equals("programmerName"))
          programmerName=data;
      else if(fileInArchive.equals("programmerURL"))
          programmerURL=data;
      else if(fileInArchive.equals("programmerMail"))
          programmerMail=data;
      else if(fileInArchive.equals("description"))
          description=data;
      else if(fileInArchive.equals("group"))
          group=data;
      else if(fileInArchive.equals("name"))
          name=data;
      else if(fileInArchive.equals("calculate"))
          calculate=data;
      else if(fileInArchive.equals("layoutInput"))
          layoutInput=data;
      else if(fileInArchive.equals("layoutOutput"))
          layoutOutput=data;
      else if(fileInArchive.equals("onButtonClick"))
          onButtonClick=data;
      else if(fileInArchive.equals("paint"))
          paint=data;
      else if(fileInArchive.equals("onButtonDown"))
          onButtonDown=data;
      else if(fileInArchive.equals("onButtonUp"))
          onButtonUp=data;
      else if(fileInArchive.equals("onStartCalculate"))
          onStartCalculate=data;
      else if(fileInArchive.equals("onStopCalculate"))
          onStopCalculate=data;
      else if(fileInArchive.equals("onMouseOverEnd"))
          onMouseOverEnd=data;
      else if(fileInArchive.equals("onMouseOver"))
          onMouseOver=data;
      else if(fileInArchive.equals("onMouseOverStart"))
        onMouseOverStart=data;
    }
    catch (ZipException e)
    {
      Trace.error(e);
    }
    catch (Exception e)
    {
      Trace.error(e);
    }
  }
  
   // unique hash key for the DigitalSimulator.....this string
   // will be display in the 'extended Option' dialog
   //
   public String  getKey()
   {
      return "@TEMPLATE@";
   }

  // ....
  public String getName()
  {
    if(name==null)
      name = getData("name").trim();
    return name; 
  }

  // Return the name of the developer of this plugIn.
  // This name will be display in the generic option dialog
  //
  public void  setName(String _name)
  {
    if(_name.equals(name))
      return;
    changed = true;
    name = _name;
    setData("name", name);
  }
  
  // Return the name of the developer of this plugIn.
  // This name will be display in the generic option dialog
  //
  public String  getProgrammerName()
  {
    if(programmerName==null)
      programmerName = getData("programmerName");
    return programmerName; 
  }
  
  // Return the name of the developer of this plugIn.
  // This name will be display in the generic option dialog
  //
  public void  setProgrammerName(String name)
  {
    if(name.equals(programmerName))
      return;
    changed = true;
    programmerName = name;
    setData("programmerName", programmerName);
  }
 
   // Return your homepage
   public String  getProgrammerURL()
   {
     if(programmerURL==null)
       programmerURL = getData("programmerURL");
     return programmerURL; 
   }


  /**
   * 
   * @param url
   */
  public void  setProgrammerURL(String url)
  {
    if(url.equals(programmerURL))
      return;
    changed = true;
    programmerURL = url;
    setData("programmerURL", programmerURL);
  }

   // Return your the Developer Address. In the generic configuration
   // dialog is a mail-link.
   //
   public String  getProgrammerMail()
   {
     if(programmerMail==null)
       programmerMail = getData("programmerMail");
     return programmerMail; 
   }

  /**
   * 
   * @param url
   */
  public void  setProgrammerMail(String mailAdress)
  {
    if(mailAdress.equals(programmerMail))
      return;
    changed = true;
    programmerMail = mailAdress;
    setData("programmerMail", programmerMail);
  }

   // Return the PlugInVersion
   // At the Moment will not be checked againts
   // saved objects.....planed for the future
   // The Version will be display in the generic configuration
   // dialog
   //
   public int  getVersion()
   {
    try
    {
      if (version == -1)
        version = Integer.parseInt(getData("version"));
    }
    catch (NumberFormatException e)
    {
      version = 0;
    }
    return version; 
   }

  /**
   * 
   * @param url
   */
  public void  setVersion(int v)
  {
    if(v==version)
      return;
    changed = true;
    version = v;
    setData("version", ""+version);
  }


   // ......
   //
   public int getParamCount()
   {
     try
     {
       if (paramCount == -1)
        paramCount = Integer.parseInt(getData("paramCount"));
     }
     catch (NumberFormatException e)
     {
       paramCount = 1;
     }
     return paramCount;
   }

  public void setParamCount(int p)
  {
    if(p==paramCount)
      return;
    changed = true;
    paramCount = p;
    setData("paramCount", ""+paramCount);
  }


	// Returns the DigitalSimulator the possible count of
	// input pins
	//
	public int[] getInputCountRange()
	{
    try
    {
      if (inputCount == -1)
        inputCount = Integer.parseInt(getData("inputCount"));
    }
    catch (NumberFormatException e)
    {
      inputCount = 1;
    }
		int[] result = new int[2];
		result[0] = inputCount;
		result[1] = inputCount;
		return result;
	}

  public void setInputCount(int in)
  {
    if(in==inputCount)
      return;
    changed = true;
    inputCount = in;
    setData("inputCount", ""+inputCount);
  }

	// ......
	//
	public int[] getOutputCountRange()
	{
		try
		{
			if (outputCount == -1)
				outputCount = Integer.parseInt(getData("outputCount"));
		}
		catch (NumberFormatException e)
		{
			outputCount = 1;
		}
		int[] result = new int[2];
		result[0] = outputCount;
		result[1] = outputCount;
		return result;
	}

   public void setOutputCount(int out)
   {
    if(out==outputCount)
      return;
    changed = true;
    outputCount = out;
     setData("outputCount", ""+outputCount);

   }

   // Return the size in Pixel wich the object needs
   // Required for the DragDrop operation of the framework
   //
   public int[] getSize(long inputCount, long outputCount)
   {
     try
     {
       if (width == -1)
        width = Integer.parseInt(getData("width"));
       if (height == -1)
        height = Integer.parseInt(getData("height"));
     }
     catch (NumberFormatException e)
     {
       width  = 100;
       height = 100;
     }
        
      int[] result = new int[2];
      result[0] = width;
      result[1] = height;

      return result;
   }

  public void setWidth(int w)
  {
    if(w==width)
      return;
    changed = true;
    width = w;
    setData("width", ""+width);
  }
  
  public void setHeight(int h)
  {
    if(h==height)
      return;
    changed = true;
    height = h;
    setData("height", ""+height);
  }

   // short discription what the object do. Will be display in the
   // extenden configuration dialog
   //
   public String  getDescription()
   {
     if(description==null)
      description = getData("description");
     return description; 
   }

  /**
   * 
   * @param url
   */
  public void  setDescription(String desc)
  {
  	if(desc.equals(description))
      return;
    changed = true;
    description = desc;
    setData("description", description);
  }

   // returns the name of the object group (e.g. Gatter, FlipFlop).
   // The object will be stored in the extenden dialog in this sub-tree of
   // the group name. Is the group does not exist it will be created.
   //
   public String  getGroup()
   {
     if(group==null)
      group = getData("group");
     return group; 
   }

  /**
   * 
   * @param url
   */
  public void  setGroup(String g)
  {
    if(g.equals(group))
      return;
    changed = true;
    group = g;
    setData("group", group);
  }

   // calculate the values of the output pins
   // return 0 for NO redraw neccessary
   // return 1 for redraw neccessary
   //
   public boolean calculate(int[] input ,int[] lastInput, int[] output, byte[] param)
   {
      try
      {
        if (calculate == null)
          calculate = getData("calculate");
        interpreter.set("param"  ,param);
        interpreter.set("input"  ,input);
        interpreter.set("lastInput"  ,lastInput);
        interpreter.set("output"  ,output);
        Object obj=exec(interpreter,calculate,"calculate");
        if(obj!=null)
          return ((Boolean)obj).booleanValue();
        }
      catch (EvalError e)
      {
        Trace.error(e);
      }
     catch(Throwable th)
     {
      Trace.error(th);
     }
     return false;
   }

   //
   //
   public void paint(int xPos, int yPos, byte[] param)
   {
      try
      {
        if (paint == null)
          paint = getData("paint");
        interpreter.set("param"  ,param);
        interpreter.set("xPos"   ,xPos);
        interpreter.set("yPos"   ,yPos);
        exec(interpreter,paint,"paint");
      }
      catch (EvalError e)
      {
        Trace.error(e);
      }
     catch(Throwable th)
     {
      Trace.error(th);
     }
   }

   // This method will be called if the user clicks the object with
   // the left mouse button
   //
   // return true if a repaint required.
   // return false if no repaint required.
   //
   public boolean onButtonClick(byte[] param)
   {
      try
      {
        if (onButtonClick == null)
          onButtonClick = getData("onButtonClick");
        interpreter.set("param"  ,param);
        Object obj=exec(interpreter,onButtonClick,"onButtonClick");
        if(obj!=null)
          return ((Boolean)obj).booleanValue();
      }
      catch (EvalError e)
      {
        Trace.error(e);
      }
     catch(Throwable th)
     {
      Trace.error(th);
     }

      return false;
   }

   // This method will be called if the user double clicks the object with
   // the left mouse button
   //
   // return true if a repaint required.
   // return false if no repaint required.
    //
   public boolean onButtonDblClick(int x, int y, byte[] param)
   {
     return doConfigure(param);
   }

   // This method will be called if the user pressed the left
   // mouse button over the object.
   //
   // return true if a repaint required.
   // return false if no repaint required.
   //
   public boolean onButtonDown(byte[] param)
   {
      try
      {
        if (onButtonDown == null)
          onButtonDown = getData("onButtonDown");
        interpreter.set("param"  ,param);
        Object obj=exec(interpreter,onButtonDown,"onButtonDown");
        if(obj!=null)
          return ((Boolean)obj).booleanValue();
      }
     catch(Throwable th)
     {
      Trace.error(th);
     }
      return false;
   }

   // This method will be called if the user leaved the left
   // mouse button over the object.
   //
   // return true if a repaint required.
   // return false if no repaint required.
   //
   public boolean onButtonUp(byte[] param)
   {
      try
      {
        if (onButtonUp == null)
          onButtonUp = getData("onButtonUp");
        interpreter.set("param"  ,param);
        Object obj=exec(interpreter,onButtonUp,"onButtonUp");
        if(obj!=null)
          return ((Boolean)obj).booleanValue();
      }
     catch(Throwable th)
     {
      Trace.error(th);
     }
      return false;
   }

    // will be called if the mouse cursor 'enters' an object
    // (hover)
    //return true if an redraw of the object is required
    //
    public  boolean onMouseOverStart(int x, int y, byte[] param)
    {
      try
      {
        if (onMouseOverStart == null)
          onMouseOverStart = getData("onMouseOverStart");
        interpreter.set("param"  ,param);
        interpreter.set("x"      ,x);
        interpreter.set("y"      ,y);
        Object obj=exec(interpreter,onMouseOverStart,"onMouseOverStart");
        if(obj!=null)
          return ((Boolean)obj).booleanValue();
      }
     catch(Throwable th)
     {
      Trace.error(th);
     }

      return false;
    }
    
    // will be called if the mouse cursor 'moves' over an object
    // (hover)
    //return true if an redraw of the object is required
    public  boolean onMouseOver(int x, int y, byte[] param)
    {
      try
      {
        if (onMouseOver == null)
          onMouseOver = getData("onMouseOver");
        interpreter.set("param"  ,param);
        interpreter.set("x"      ,x);
        interpreter.set("y"      ,y);
        Object obj=exec(interpreter,onMouseOver,"onMouseOver");
        if(obj!=null)
          return ((Boolean)obj).booleanValue();
      }
     catch(Throwable th)
     {
      Trace.error(th);
     }
     return false;
    }
    
    // will be called if the mouse cursor 'leafes' an object
    // (hover)
    //return true if an redraw of the object is required
    public  boolean onMouseOverEnd(int x, int y, byte[] param)
    {
      try
      {
        if (onMouseOverEnd == null)
          onMouseOverEnd = getData("onMouseOverEnd");
        interpreter.set("param"  ,param);
        interpreter.set("x"      ,x);
        interpreter.set("y"      ,y);
        Object obj=exec(interpreter,onMouseOverEnd,"onMouseOverEnd");
        if(obj!=null)
          return ((Boolean)obj).booleanValue();
      }
     catch(Throwable th)
     {
      Trace.error(th);
     }

      return false;
    }

   // before the simulator start the calculation of the circuit
   // all objects will be received a message. You can open
   // a file (e.g. report objects) or open a hardware interface
   // (e.g. parallel port)
   //
   public void onStartCalculate( byte[] param)
   {
      try
      {
        if (onStartCalculate == null)
          onStartCalculate = getData("onStartCalculate");
        interpreter.set("param"  ,param);
        exec(interpreter,onStartCalculate,"onStartCalculate");
      }
     catch(Throwable th)
     {
      Trace.error(th);
     }
   }


   // After the calculation is done all objects will received a
   // message. You can close all handles or free some temp memory
   //
   public void onStopCalculate( byte[] param)
   {
      try
      {
        if (onStopCalculate == null)
          onStopCalculate = getData("onStopCalculate");
        interpreter.set("param"  ,param);
        exec(interpreter,onStopCalculate,"onStopCalculate");
      }
     catch(Throwable th)
     {
      Trace.error(th);
     }
   }


   // layout the output pins. The origin (0/0) are at the top left corner
   // x INCREASED to the right and y DECREASE to the bottom.
   //
   public int[] layoutOutput( int inputCount,  int outputCount, byte[] param )
   {
      try
      {
        if (layoutOutput == null)
          layoutOutput = getData("layoutOutput");
        interpreter.set("param"  ,param);
        Object obj=exec(interpreter,layoutOutput,"layoutOutput");
        if(obj!=null)
          return (int[])obj;
      }
     catch(Throwable th)
     {
      Trace.error(th);
     }

      int[] result = new int[2*outputCount];
      result[0] = 100;
      result[1] = -height/2;

      return result;
   }


   // layout the input pins. The origin (0/0) are at the top left corner
   // x increased to the right and y decreased to the bottom.
   //
   public int[] layoutInput(int inputCount, int outputCount, byte[] param)
   {
      try
      {
        if (layoutInput == null)
          layoutInput = getData("layoutInput");
        interpreter.set("param"  ,param);
        Object obj= exec(interpreter,layoutInput,"layoutInput");
        if(obj!=null)
          return (int[])obj;
      }
     catch(Throwable th)
     {
      Trace.error(th);
     }
     return new int[2*inputCount];
   }
   
   private Object exec(Interpreter i, String code, String function) throws EvalError
   {
     try
		{
			if(code==null || code.length()<1)
			   return null;
			 i.set("width"       ,width);
			 i.set("height"      ,height);
			 i.set("inputCount"  ,inputCount);
			 i.set("outputCount" ,outputCount);
			 i.set("version"     ,version);
			 i.set("paramCount"  ,paramCount);
			 return interpreter.eval(code);
		}
		catch (EvalError e)
		{
      WizardObjectErrorDialog.show(e,code, function, this);
      interpreter = new Interpreter();
      throw e;
		}
  }
  
  public void init()
  {
    interpreter.setStrictJava(false);
  }
  
  public void setChanged(boolean flag)
  {
    changed = flag;
  }

  public boolean hasChanged()
  {
  	return changed;
  }
  
}

