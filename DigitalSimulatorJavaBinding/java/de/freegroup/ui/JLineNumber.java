/*
 * Created on Feb 19, 2004
 *
 */
package de.freegroup.ui;
/*
 GUI Component JSwing to manage line number display on editors like Editplus, JCreator 

 if (len(newLineNo)==len(CurrentLineNo))
 {
 if (newLineNo > CurrentLineNo)
 {just add on the newLineNo by getting currentlineno}
 if (newLineNo < CurrentLineNo)
 {just - on the newLineNo by substr _xx}

 }obtmise like for range 10 till 99 100-999

 Warning: This bean is not thread safe.
 inital testing and finding results in that creation of new lines 10000 take 640milli sec 
 where as deletation takes 85000milli sec and more

 @author zeroin23@yahoo.com
 @version 0.01 experimental

 */

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.border.*;
import javax.swing.text.Element;
import java.util.*;

public class JLineNumber extends JTextArea
{
  int currentLineno=1;
  StringBuffer stblentemp=new StringBuffer();

  public JLineNumber()
  { 
    super(10,3);
    setBackground(Color.gray);
    setEditable(false);
    setText(" "+currentLineno+" \n");
  }
  
  /**
   * Manages to use quick refresh by subtracting or adding numbers directly to JTextarea
   * or to use refreshWholeLineno() to update entire component.
   * @param clc to show how many lines 
   */
  public void setCurrentLineCount(int clc)
  {
    if(currentLineno==clc)return;
    if(currentLineno!=clc)
    {
      //System.out.println("len(newLineNo)="+lenChar(clc)+"\tnln"+clc);
      //System.out.println("len(CurrentLineNo)="+lenChar(currentLineno)+"\tcln"+currentLineno);
      
      //obtmise like for range 10 till 99 100-999 dont need to resize JTA
      if (lenChar(clc)==lenChar(currentLineno))
      { //System.out.println("TRUE");
        if(clc>currentLineno)
        {//System.out.println("TRUE2");
          StringBuffer stb=new StringBuffer();
          int len=(new String(clc+"")).length();
          for (int x=currentLineno+1;x<=clc;x++)
          {
            stb.append(" ");
            int len2=(new String(x+"")).length();
            int required=len-len2;
            for (int y=0;y<required;y++)
            {
              stb.append(" ");
            }
            stb.append(x+" \n");
          }
          append(stb.toString());
          currentLineno=clc;
          return;
        }
        if(clc<currentLineno)
        {
          int ax=getText().lastIndexOf(" "+(clc+1));
          //long dx=System.currentTimeMillis();
          stblentemp.setLength(0);//$RESULTS$=85110
          stblentemp.append(getText());
          setText(stblentemp.substring(0,ax));
          
          //StringBuffer stb=new StringBuffer(getText());$RESULTS$=85641
          //setText(stb.substring(0,ax));
          
          //setText(getText().substring(0,ax)); $RESULTS$=85406
          
          //if(System.currentTimeMillis()-dx>0)System.out.println(clc+" "+(System.currentTimeMillis()-dx));
          
          currentLineno=clc;
          //System.out.println("clc2="+clc);
          return;
        }
        /*pseudocodes
         if (newLineNo > CurrentLineNo)
         {just add on the newLineNo by getting currentlineno}
         if (newLineNo < CurrentLineNo)
         {just - on the newLineNo by substr _xx}
         */
      }
      
      refreshWholeLineno(clc);
    }
  }
  /**
   * Refresh entire number sequences within JTextArea
   * @param clc refresh JTextArea to this number of lines aka current line count. 
   */
  void refreshWholeLineno(int clc)
  {
    StringBuffer stb=new StringBuffer();//store final text
    /*Calculate space required*/
    int len=(new String(clc+"")).length();
    setText("");
    setColumns(len+2);
    //System.out.println(len+"len");
    for (int x=1;x<=clc;x++)
    {
      stb.append(" ");
      int len2=(new String(x+"")).length();
      int required=len-len2;
      for (int y=0;y<required;y++)
      {
        stb.append(" ");
      }
      stb.append(x+" \n");
      //System.out.println(x+" "+x/10);
    }
    setText(stb.toString());
    currentLineno=clc;
    //System.out.println(stb.toString());
  }
  
  /**
   * getSize of number like lenChar(99)=2 lenChar(120)=3
   * 
   */
  int lenChar(int a)
  {
    stblentemp.setLength(0);
    stblentemp.append(a);
    return stblentemp.length();
  }
  public int getCurrentLineCount()
  {return currentLineno;}

  /**
   * Unit Testing Codes, can be removed wholesale for production.
   *
   */
  public static void main(String[] args) 
  {
    System.out.println("Hello "+"!");//bug
    
    try{
      UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
    }catch (Exception e)
    {
      System.out.println("EXCEPTION:"+e);
    }finally{}
    
    JLineNumber jln=new JLineNumber();

    JFrame jf=new JFrame();
    jf.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
    jf.setSize(new Dimension(750, 500));
    jf.addWindowListener(new WindowAdapter(){
      public void windowClosed(WindowEvent e)
      {
        System.out.println("test1");System.exit(0);
      }
    });

    JScrollPane jsp=new JScrollPane(jln);
    //jf.getContentPane().setLayout(new FlowLayout());
    jf.getContentPane().add(jsp);
    jf.show();

    long start=System.currentTimeMillis();
    for (int x=0;x<10000;x+=10)
    {
      //long dx=System.currentTimeMillis();
      jln.setCurrentLineCount(1+x);
      //if(System.currentTimeMillis()-dx>0)System.out.println(x+" "+(System.currentTimeMillis()-dx));

      if(x%1000==0)
      {long cx=System.currentTimeMillis();
      while(System.currentTimeMillis()-cx<5000);
      }
    }

    long end=System.currentTimeMillis();
    long total=end-start;
    double sec=(((total)/1000/60.0)-((total)/1000/60))*60;
    System.out.println("Time Taken="+((total)/1000/60)+"mins "+sec+"sec");
    System.out.println("st="+start);
    System.out.println("en="+end);
    System.out.println("t="+(end-start));

    jln.refreshWholeLineno(10001);

    for (int y=10000;y>0;y-=10)
    {
      //long dx=System.currentTimeMillis();
      jln.setCurrentLineCount(y);
      //if(System.currentTimeMillis()-dx>0)System.out.println(y+" "+(System.currentTimeMillis()-dx));

      /*if(y%1000==0)
       {long cx=System.currentTimeMillis();
       while(System.currentTimeMillis()-cx<5000);
       }*/
    }

  }
}