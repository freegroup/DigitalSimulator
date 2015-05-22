package de.freegroup.digitalsimulator.plugin.tool.ResistorCoder;
/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */


import java.awt.*;

import javax.swing.*;
import java.awt.event.*;
import java.util.HashMap;

import javax.swing.event.*;

import de.freegroup.digitalsimulator.Configuration;
import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.ui.*;
import javax.swing.border.*;

import com.jgoodies.clearlook.ClearLookManager;
import com.jgoodies.clearlook.ClearLookMode;
import com.jgoodies.forms.builder.PanelBuilder;
import com.jgoodies.forms.debug.FormDebugPanel;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;
import com.jgoodies.plaf.FontSizeHints;
import com.jgoodies.plaf.Options;
import com.jgoodies.plaf.plastic.Plastic3DLookAndFeel;

import de.freegroup.digitalsimulator.dialogs.GenericDialog;
import de.freegroup.digitalsimulator.dialogs.MsgBox;
import de.freegroup.digitalsimulator.ui.HGradient;

public class Dialog extends GenericDialog 
{
  private final class Band01ColorAction implements MouseListener
  {
    public void mouseClicked(MouseEvent e)
    {
      ImageIcon icon= (ImageIcon)label2Color.get(e.getComponent());
      band01Value = (String)label2Factor.get(e.getComponent());
      if(icon!=null)
        resistorBand01.setIcon(icon);
      calculate();
    }
    public void mousePressed(MouseEvent e){}
    public void mouseReleased(MouseEvent e){}
    public void mouseEntered(MouseEvent e)
    {
      bandMouseOverLabel.setText(I18N.get("RESISTORCOLORCODER.LABEL.FIRSTDIGIT")+label2Factor.get(e.getComponent()));
    }
    public void mouseExited(MouseEvent e)
    {
      bandMouseOverLabel.setText("");
    }
  }
  
  private final class Band02ColorAction implements MouseListener
  {
    public void mouseClicked(MouseEvent e)
    {
      ImageIcon icon= (ImageIcon)label2Color.get(e.getComponent());
      band02Value = (String)label2Factor.get(e.getComponent());
      if(icon!=null)
        resistorBand02.setIcon(icon);
      calculate();
    }
    public void mousePressed(MouseEvent e){}
    public void mouseReleased(MouseEvent e){}
    public void mouseEntered(MouseEvent e)
    {
      bandMouseOverLabel.setText(I18N.get("RESISTORCOLORCODER.LABEL.SECONDDIGIT")+label2Factor.get(e.getComponent()));
    }
    public void mouseExited(MouseEvent e)
    {
      bandMouseOverLabel.setText("");
    }
  }
  private final class Band03ColorAction implements MouseListener
  {
    public void mouseClicked(MouseEvent e)
    {
      ImageIcon icon= (ImageIcon)label2Color.get(e.getComponent());
      band03Value = (String)label2Factor.get(e.getComponent());
      if(icon!=null)
        resistorBand03.setIcon(icon);
      calculate();
    }
    public void mousePressed(MouseEvent e){}
    public void mouseReleased(MouseEvent e){}
    public void mouseEntered(MouseEvent e)
    {
      bandMouseOverLabel.setText(I18N.get("RESISTORCOLORCODER.LABEL.FACTOR")+label2Factor.get(e.getComponent()));
    }
    public void mouseExited(MouseEvent e)
    {
      bandMouseOverLabel.setText("");
    }
  }

  private final class Band04ColorAction implements MouseListener
  {
    public void mouseClicked(MouseEvent e)
    {
      ImageIcon icon= (ImageIcon)label2Color.get(e.getComponent());
      band04Value = (String)label2Factor.get(e.getComponent());
      if(icon!=null)
        resistorBand04.setIcon(icon);
      calculate();
    }
    public void mousePressed(MouseEvent e){}
    public void mouseReleased(MouseEvent e){}
    public void mouseEntered(MouseEvent e)
    {
      bandMouseOverLabel.setText(I18N.get("RESISTORCOLORCODER.LABEL.TOLERANZ")+label2Factor.get(e.getComponent()));
    }
    public void mouseExited(MouseEvent e)
    {
      bandMouseOverLabel.setText("");
    }
  }
  MouseListener band01Listener = null;
  MouseListener band02Listener = null;
  MouseListener band03Listener = null;
  MouseListener band04Listener = null;

  String    band01Value ="";
  String    band02Value ="";
  String    band03Value ="";
  String    band04Value ="";

  JLabel    bandMouseOverLabel = null;
  
  JLabel   calculatedValue   = null;
  JLabel   resistorLeft      = null;
  JLabel   resistorBand01    = null;
  JLabel   resistorBand02    = null;
  JLabel   resistorBand03    = null;
  JLabel   resistorBand04    = null;
  JLabel   resistorRight     = null;
  
  ImageIcon  blackImage  = null;
  ImageIcon  blueImage  = null;
  ImageIcon  brownImage  = null;
  ImageIcon  goldImage  = null;
  ImageIcon  grayImage  = null;
  ImageIcon  greenImage  = null;
  ImageIcon  silverImage  = null;
  ImageIcon  orangeImage  = null;
  ImageIcon  redImage  = null;
  ImageIcon  violetImage  = null;
  ImageIcon  whiteImage  = null;
  ImageIcon  yellowImage  = null;
  ImageIcon  resleftImage  = null;
  ImageIcon  resrightImage  = null;

  JLabel  blackLabel_01  = null;
  JLabel  blueLabel_01   = null;
  JLabel  brownLabel_01  = null;
  JLabel  goldLabel_01   = null;
  JLabel  grayLabel_01   = null;
  JLabel  greenLabel_01  = null;
  JLabel  silverLabel_01   = null;
  JLabel  orangeLabel_01 = null;
  JLabel  redLabel_01    = null;
  JLabel  violetLabel_01 = null;
  JLabel  whiteLabel_01  = null;
  JLabel  yellowLabel_01 = null;
  

  JLabel  blackLabel_02  = null;
  JLabel  blueLabel_02   = null;
  JLabel  brownLabel_02  = null;
  JLabel  goldLabel_02   = null;
  JLabel  grayLabel_02   = null;
  JLabel  greenLabel_02  = null;
  JLabel  silverLabel_02   = null;
  JLabel  orangeLabel_02 = null;
  JLabel  redLabel_02    = null;
  JLabel  violetLabel_02 = null;
  JLabel  whiteLabel_02  = null;
  JLabel  yellowLabel_02 = null;

  JLabel  blackLabel_03  = null;
  JLabel  blueLabel_03   = null;
  JLabel  brownLabel_03  = null;
  JLabel  goldLabel_03   = null;
  JLabel  grayLabel_03   = null;
  JLabel  greenLabel_03  = null;
  JLabel  silverLabel_03   = null;
  JLabel  orangeLabel_03 = null;
  JLabel  redLabel_03    = null;
  JLabel  violetLabel_03 = null;
  JLabel  whiteLabel_03  = null;
  JLabel  yellowLabel_03 = null;

  JLabel  blackLabel_04  = null;
  JLabel  blueLabel_04   = null;
  JLabel  brownLabel_04  = null;
  JLabel  goldLabel_04   = null;
  JLabel  grayLabel_04   = null;
  JLabel  greenLabel_04  = null;
  JLabel  silverLabel_04   = null;
  JLabel  orangeLabel_04 = null;
  JLabel  redLabel_04    = null;
  JLabel  violetLabel_04 = null;
  JLabel  whiteLabel_04  = null;
  JLabel  yellowLabel_04 = null;
  
  HashMap label2Color = null;
  HashMap label2Factor = null;

  /**
     * only to test this class
     * 
     * @param args
     */
    public static void main(String[] args)
		{
      UIManager.put("Application.useSystemFontSettings", Boolean.TRUE);
      Options.setGlobalFontSizeHints(FontSizeHints.MIXED);
      ClearLookManager.setMode(ClearLookMode.ON);
      try
      {
        UIManager.setLookAndFeel("com.jgoodies.plaf.plastic.PlasticXPLookAndFeel");
      }
      catch (Exception e)
      {
        // Likely PlasticXP is not in the class path; ignore.
      }
      Plastic3DLookAndFeel.setHighContrastFocusColorsEnabled(true);
      UIManager.put("Application.useSystemFontSettings", Boolean.TRUE);
      UIManager.put(Options.USE_SYSTEM_FONTS_APP_KEY, Boolean.TRUE);
      UIManager.put("ScrollBar.is3DEnabled", Boolean.FALSE);
      Options.setGlobalFontSizeHints(FontSizeHints.MIXED);
      Plastic3DLookAndFeel.setFontSizeHints(FontSizeHints.SYSTEM);
			new Dialog();
		}
  
    public Dialog() 
    {
      super(I18N.get("COMMON.DIALOGHEADER.RESISTORCOLORCODER"),
            I18N.get("RESISTORCOLORCODER.LABEL.HELPHEADER"),
            I18N.get("RESISTORCOLORCODER.LABEL.HELPLINE01"),
            I18N.get("RESISTORCOLORCODER.LABEL.HELPLINE02"));
      
       this.withCancelButton = false; 
       show(680,550);
    }


    
      /* (non-Javadoc)
   * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#initComponents()
   */
  public void initComponents()
  {
    label2Color = new HashMap();
    label2Factor= new HashMap();

    band01Listener = new Band01ColorAction();
    band02Listener = new Band02ColorAction();
    band03Listener = new Band03ColorAction();
    band04Listener = new Band04ColorAction();

    calculatedValue   = new JLabel("");
    calculatedValue.setFont( new Font("",Font.PLAIN,15));

    bandMouseOverLabel = new JLabel();

    resistorLeft      = new JLabel("");
    resistorBand01    = new JLabel("");
    resistorBand02    = new JLabel("");
    resistorBand03    = new JLabel("");
    resistorBand04    = new JLabel("");
    resistorRight     = new JLabel("");
 
    blackImage    = new ImageIcon(getClass().getResource("Black.png"));
    blueImage     = new ImageIcon(getClass().getResource("Blue.png"));
    brownImage    = new ImageIcon(getClass().getResource("Brown.png"));
    goldImage     = new ImageIcon(getClass().getResource("Gold.png"));
    grayImage     = new ImageIcon(getClass().getResource("Gray.png"));
    greenImage    = new ImageIcon(getClass().getResource("Green.png"));
    silverImage   = new ImageIcon(getClass().getResource("Silver.png"));
    orangeImage   = new ImageIcon(getClass().getResource("Orange.png"));
    redImage      = new ImageIcon(getClass().getResource("Red.png"));
    violetImage   = new ImageIcon(getClass().getResource("Violet.png"));
    whiteImage    = new ImageIcon(getClass().getResource("White.png"));
    yellowImage   = new ImageIcon(getClass().getResource("Yellow.png"));
    resleftImage  = new ImageIcon(getClass().getResource("resleft.png"));
    resrightImage = new ImageIcon(getClass().getResource("resright.png"));
    
    blackLabel_01  = new JLabel(" ");
    blueLabel_01   = new JLabel(" ");
    brownLabel_01  = new JLabel(" ");
    goldLabel_01   = new JLabel(" ");
    grayLabel_01   = new JLabel(" ");
    greenLabel_01  = new JLabel(" ");
    silverLabel_01 = new JLabel(" ");
    orangeLabel_01 = new JLabel(" ");
    redLabel_01    = new JLabel(" ");
    violetLabel_01 = new JLabel(" ");
    whiteLabel_01  = new JLabel(" ");
    yellowLabel_01 = new JLabel(" ");

    blackLabel_02  = new JLabel(" ");
    blueLabel_02   = new JLabel(" ");
    brownLabel_02  = new JLabel(" ");
    goldLabel_02   = new JLabel(" ");
    grayLabel_02   = new JLabel(" ");
    greenLabel_02  = new JLabel(" ");
    silverLabel_02 = new JLabel(" ");
    orangeLabel_02 = new JLabel(" ");
    redLabel_02    = new JLabel(" ");
    violetLabel_02 = new JLabel(" ");
    whiteLabel_02  = new JLabel(" ");
    yellowLabel_02 = new JLabel(" ");

    blackLabel_03  = new JLabel(" ");
    blueLabel_03   = new JLabel(" ");
    brownLabel_03  = new JLabel(" ");
    goldLabel_03   = new JLabel(" ");
    grayLabel_03   = new JLabel(" ");
    greenLabel_03  = new JLabel(" ");
    silverLabel_03 = new JLabel(" ");
    orangeLabel_03 = new JLabel(" ");
    redLabel_03    = new JLabel(" ");
    violetLabel_03 = new JLabel(" ");
    whiteLabel_03  = new JLabel(" ");
    yellowLabel_03 = new JLabel(" ");

    blackLabel_04  = new JLabel(" ");
    blueLabel_04   = new JLabel(" ");
    brownLabel_04  = new JLabel(" ");
    goldLabel_04   = new JLabel(" ");
    grayLabel_04   = new JLabel(" ");
    greenLabel_04  = new JLabel(" ");
    silverLabel_04 = new JLabel(" ");
    orangeLabel_04 = new JLabel(" ");
    redLabel_04    = new JLabel(" ");
    violetLabel_04 = new JLabel(" ");
    whiteLabel_04  = new JLabel(" ");
    yellowLabel_04 = new JLabel(" ");
    
    // set the opaque=true to see the background color
    //
    blackLabel_01.setOpaque(true);
    blueLabel_01.setOpaque(true);
    brownLabel_01.setOpaque(true);
    goldLabel_01.setOpaque(true);
    grayLabel_01.setOpaque(true);
    greenLabel_01.setOpaque(true);
    silverLabel_01.setOpaque(true);
    orangeLabel_01.setOpaque(true);
    redLabel_01.setOpaque(true);
    violetLabel_01.setOpaque(true);
    whiteLabel_01.setOpaque(true);
    yellowLabel_01.setOpaque(true);
    
    
    blackLabel_02.setOpaque(true);
    blueLabel_02.setOpaque(true);
    brownLabel_02.setOpaque(true);
    goldLabel_02.setOpaque(true);
    grayLabel_02.setOpaque(true);
    greenLabel_02.setOpaque(true);
    silverLabel_02.setOpaque(true);
    orangeLabel_02.setOpaque(true);
    redLabel_02.setOpaque(true);
    violetLabel_02.setOpaque(true);
    whiteLabel_02.setOpaque(true);
    yellowLabel_02.setOpaque(true);
    
    blackLabel_03.setOpaque(true);
    blueLabel_03.setOpaque(true);
    brownLabel_03.setOpaque(true);
    goldLabel_03.setOpaque(true);
    grayLabel_03.setOpaque(true);
    greenLabel_03.setOpaque(true);
    silverLabel_03.setOpaque(true);
    orangeLabel_03.setOpaque(true);
    redLabel_03.setOpaque(true);
    violetLabel_03.setOpaque(true);
    whiteLabel_03.setOpaque(true);
    yellowLabel_03.setOpaque(true);
    
    blackLabel_04.setOpaque(true);
    blueLabel_04.setOpaque(true);
    brownLabel_04.setOpaque(true);
    goldLabel_04.setOpaque(true);
    grayLabel_04.setOpaque(true);
    greenLabel_04.setOpaque(true);
    silverLabel_04.setOpaque(true);
    orangeLabel_04.setOpaque(true);
    redLabel_04.setOpaque(true);
    violetLabel_04.setOpaque(true);
    whiteLabel_04.setOpaque(true);
    yellowLabel_04.setOpaque(true);
    
    blackLabel_01.addMouseListener(band01Listener);
    blueLabel_01.addMouseListener(band01Listener);
    brownLabel_01.addMouseListener(band01Listener);
    goldLabel_01.addMouseListener(band01Listener);
    grayLabel_01.addMouseListener(band01Listener);
    greenLabel_01.addMouseListener(band01Listener);
    silverLabel_01.addMouseListener(band01Listener);
    orangeLabel_01.addMouseListener(band01Listener);
    redLabel_01.addMouseListener(band01Listener);
    violetLabel_01.addMouseListener(band01Listener);
    whiteLabel_01.addMouseListener(band01Listener);
    yellowLabel_01.addMouseListener(band01Listener);
    blackLabel_02.addMouseListener(band02Listener);
    blueLabel_02.addMouseListener(band02Listener);
    brownLabel_02.addMouseListener(band02Listener);
    goldLabel_02.addMouseListener(band02Listener);
    grayLabel_02.addMouseListener(band02Listener);
    greenLabel_02.addMouseListener(band02Listener);
    silverLabel_02.addMouseListener(band02Listener);
    orangeLabel_02.addMouseListener(band02Listener);
    redLabel_02.addMouseListener(band02Listener);
    violetLabel_02.addMouseListener(band02Listener);
    whiteLabel_02.addMouseListener(band02Listener);
    yellowLabel_02.addMouseListener(band02Listener);
    blackLabel_03.addMouseListener(band03Listener);
    blueLabel_03.addMouseListener(band03Listener);
    brownLabel_03.addMouseListener(band03Listener);
    goldLabel_03.addMouseListener(band03Listener);
    grayLabel_03.addMouseListener(band03Listener);
    greenLabel_03.addMouseListener(band03Listener);
    silverLabel_03.addMouseListener(band03Listener);
    orangeLabel_03.addMouseListener(band03Listener);
    redLabel_03.addMouseListener(band03Listener);
    violetLabel_03.addMouseListener(band03Listener);
    whiteLabel_03.addMouseListener(band03Listener);
    yellowLabel_03.addMouseListener(band03Listener);
    blackLabel_04.addMouseListener(band04Listener);
    blueLabel_04.addMouseListener(band04Listener);
    brownLabel_04.addMouseListener(band04Listener);
    goldLabel_04.addMouseListener(band04Listener);
    grayLabel_04.addMouseListener(band04Listener);
    greenLabel_04.addMouseListener(band04Listener);
    silverLabel_04.addMouseListener(band04Listener);
    orangeLabel_04.addMouseListener(band04Listener);
    redLabel_04.addMouseListener(band04Listener);
    violetLabel_04.addMouseListener(band04Listener);
    whiteLabel_04.addMouseListener(band04Listener);
    yellowLabel_04.addMouseListener(band04Listener);

    blackLabel_01.setBorder(LineBorder.createGrayLineBorder());
    blueLabel_01.setBorder(LineBorder.createGrayLineBorder());
    brownLabel_01.setBorder(LineBorder.createGrayLineBorder());
    goldLabel_01.setBorder(LineBorder.createGrayLineBorder());
    grayLabel_01.setBorder(LineBorder.createGrayLineBorder());
    greenLabel_01.setBorder(LineBorder.createGrayLineBorder());
    silverLabel_01.setBorder(LineBorder.createGrayLineBorder());
    orangeLabel_01.setBorder(LineBorder.createGrayLineBorder());
    redLabel_01.setBorder(LineBorder.createGrayLineBorder());
    violetLabel_01.setBorder(LineBorder.createGrayLineBorder());
    whiteLabel_01.setBorder(LineBorder.createGrayLineBorder());
    yellowLabel_01.setBorder(LineBorder.createGrayLineBorder());
    blackLabel_02.setBorder(LineBorder.createGrayLineBorder());
    blueLabel_02.setBorder(LineBorder.createGrayLineBorder());
    brownLabel_02.setBorder(LineBorder.createGrayLineBorder());
    goldLabel_02.setBorder(LineBorder.createGrayLineBorder());
    grayLabel_02.setBorder(LineBorder.createGrayLineBorder());
    greenLabel_02.setBorder(LineBorder.createGrayLineBorder());
    silverLabel_02.setBorder(LineBorder.createGrayLineBorder());
    orangeLabel_02.setBorder(LineBorder.createGrayLineBorder());
    redLabel_02.setBorder(LineBorder.createGrayLineBorder());
    violetLabel_02.setBorder(LineBorder.createGrayLineBorder());
    whiteLabel_02.setBorder(LineBorder.createGrayLineBorder());
    yellowLabel_02.setBorder(LineBorder.createGrayLineBorder());
    blackLabel_03.setBorder(LineBorder.createGrayLineBorder());
    blueLabel_03.setBorder(LineBorder.createGrayLineBorder());
    brownLabel_03.setBorder(LineBorder.createGrayLineBorder());
    goldLabel_03.setBorder(LineBorder.createGrayLineBorder());
    grayLabel_03.setBorder(LineBorder.createGrayLineBorder());
    greenLabel_03.setBorder(LineBorder.createGrayLineBorder());
    silverLabel_03.setBorder(LineBorder.createGrayLineBorder());
    orangeLabel_03.setBorder(LineBorder.createGrayLineBorder());
    redLabel_03.setBorder(LineBorder.createGrayLineBorder());
    violetLabel_03.setBorder(LineBorder.createGrayLineBorder());
    whiteLabel_03.setBorder(LineBorder.createGrayLineBorder());
    yellowLabel_03.setBorder(LineBorder.createGrayLineBorder());
    blackLabel_04.setBorder(LineBorder.createGrayLineBorder());
    blueLabel_04.setBorder(LineBorder.createGrayLineBorder());
    brownLabel_04.setBorder(LineBorder.createGrayLineBorder());
    goldLabel_04.setBorder(LineBorder.createGrayLineBorder());
    grayLabel_04.setBorder(LineBorder.createGrayLineBorder());
    greenLabel_04.setBorder(LineBorder.createGrayLineBorder());
    silverLabel_04.setBorder(LineBorder.createGrayLineBorder());
    orangeLabel_04.setBorder(LineBorder.createGrayLineBorder());
    redLabel_04.setBorder(LineBorder.createGrayLineBorder());
    violetLabel_04.setBorder(LineBorder.createGrayLineBorder());
    whiteLabel_04.setBorder(LineBorder.createGrayLineBorder());
    yellowLabel_04.setBorder(LineBorder.createGrayLineBorder());



    blackLabel_01.setBackground(new Color(0,0,0));
    blueLabel_01.setBackground(new Color(0,51,153));
    brownLabel_01.setBackground(new Color(153,102,0));
    goldLabel_01.setBackground(new Color(204,153,0));
    grayLabel_01.setBackground(new Color(100,100,100));
    greenLabel_01.setBackground(new Color(0,102,0));
    silverLabel_01.setBackground(Color.lightGray);
    orangeLabel_01.setBackground(new Color(255,51,0));
    redLabel_01.setBackground(new Color(153,0,0));
    violetLabel_01.setBackground(new Color(102,102,152));
    whiteLabel_01.setBackground(new Color(255,255,255));
    yellowLabel_01.setBackground(new Color(255,255,0));
    
    blackLabel_02.setBackground(new Color(0,0,0));
    blueLabel_02.setBackground(new Color(0,51,153));
    brownLabel_02.setBackground(new Color(153,102,0));
    goldLabel_02.setBackground(new Color(204,153,0));
    grayLabel_02.setBackground(new Color(100,100,100));
    greenLabel_02.setBackground(new Color(0,102,0));
    silverLabel_02.setBackground(Color.lightGray);
    orangeLabel_02.setBackground(new Color(255,51,0));
    redLabel_02.setBackground(new Color(153,0,0));
    violetLabel_02.setBackground(new Color(102,102,152));
    whiteLabel_02.setBackground(new Color(255,255,255));
    yellowLabel_02.setBackground(new Color(255,255,0));
    
    blackLabel_03.setBackground(new Color(0,0,0));
    blueLabel_03.setBackground(new Color(0,51,153));
    brownLabel_03.setBackground(new Color(153,102,0));
    goldLabel_03.setBackground(new Color(204,153,0));
    grayLabel_03.setBackground(new Color(100,100,100));
    greenLabel_03.setBackground(new Color(0,102,0));
    silverLabel_03.setBackground(Color.lightGray);
    orangeLabel_03.setBackground(new Color(255,51,0));
    redLabel_03.setBackground(new Color(153,0,0));
    violetLabel_03.setBackground(new Color(102,102,152));
    whiteLabel_03.setBackground(new Color(255,255,255));
    yellowLabel_03.setBackground(new Color(255,255,0));
    
    blackLabel_04.setBackground(new Color(0,0,0));
    blueLabel_04.setBackground(new Color(0,51,153));
    brownLabel_04.setBackground(new Color(153,102,0));
    goldLabel_04.setBackground(new Color(204,153,0));
    grayLabel_04.setBackground(new Color(100,100,100));
    greenLabel_04.setBackground(new Color(0,102,0));
    silverLabel_04.setBackground(Color.lightGray);
    orangeLabel_04.setBackground(new Color(255,51,0));
    redLabel_04.setBackground(new Color(153,0,0));
    violetLabel_04.setBackground(new Color(102,102,152));
    whiteLabel_04.setBackground(new Color(255,255,255));
    yellowLabel_04.setBackground(new Color(255,255,0));
    
    label2Color.put(blackLabel_01  ,blackImage);
    label2Color.put(blueLabel_01   ,blueImage);
    label2Color.put(brownLabel_01  ,brownImage);
    label2Color.put(goldLabel_01   ,goldImage);
    label2Color.put(grayLabel_01   ,grayImage);
    label2Color.put(greenLabel_01  ,greenImage);
    label2Color.put(silverLabel_01 ,silverImage);
    label2Color.put(orangeLabel_01 ,orangeImage);
    label2Color.put(redLabel_01    ,redImage);
    label2Color.put(violetLabel_01 ,violetImage);
    label2Color.put(whiteLabel_01  ,whiteImage);
    label2Color.put(yellowLabel_01 ,yellowImage);
        
    label2Color.put(blackLabel_02  ,blackImage);
    label2Color.put(blueLabel_02   ,blueImage);
    label2Color.put(brownLabel_02  ,brownImage);
    label2Color.put(goldLabel_02   ,goldImage);
    label2Color.put(grayLabel_02   ,grayImage);
    label2Color.put(greenLabel_02  ,greenImage);
    label2Color.put(silverLabel_02 ,silverImage);
    label2Color.put(orangeLabel_02 ,orangeImage);
    label2Color.put(redLabel_02    ,redImage);
    label2Color.put(violetLabel_02 ,violetImage);
    label2Color.put(whiteLabel_02  ,whiteImage);
    label2Color.put(yellowLabel_02 ,yellowImage);

    label2Color.put(blackLabel_03  ,blackImage);
    label2Color.put(blueLabel_03   ,blueImage);
    label2Color.put(brownLabel_03  ,brownImage);
    label2Color.put(goldLabel_03   ,goldImage);
    label2Color.put(grayLabel_03   ,grayImage);
    label2Color.put(greenLabel_03  ,greenImage);
    label2Color.put(silverLabel_03 ,silverImage);
    label2Color.put(orangeLabel_03 ,orangeImage);
    label2Color.put(redLabel_03    ,redImage);
    label2Color.put(violetLabel_03 ,violetImage);
    label2Color.put(whiteLabel_03  ,whiteImage);
    label2Color.put(yellowLabel_03 ,yellowImage);

    label2Color.put(blackLabel_04  ,blackImage);
    label2Color.put(blueLabel_04   ,blueImage);
    label2Color.put(brownLabel_04  ,brownImage);
    label2Color.put(goldLabel_04   ,goldImage);
    label2Color.put(grayLabel_04   ,grayImage);
    label2Color.put(greenLabel_04  ,greenImage);
    label2Color.put(silverLabel_04 ,silverImage);
    label2Color.put(orangeLabel_04 ,orangeImage);
    label2Color.put(redLabel_04    ,redImage);
    label2Color.put(violetLabel_04 ,violetImage);
    label2Color.put(whiteLabel_04  ,whiteImage);
    label2Color.put(yellowLabel_04 ,yellowImage);

    label2Factor.put(brownLabel_01  ,"1");
    label2Factor.put(redLabel_01    ,"2");
    label2Factor.put(orangeLabel_01 ,"3");
    label2Factor.put(yellowLabel_01 ,"4");
    label2Factor.put(greenLabel_01  ,"5");
    label2Factor.put(blueLabel_01   ,"6");
    label2Factor.put(violetLabel_01 ,"7");
    label2Factor.put(grayLabel_01   ,"8");
    label2Factor.put(whiteLabel_01  ,"9");
        
    label2Factor.put(blackLabel_02  ,"0");
    label2Factor.put(brownLabel_02  ,"1");
    label2Factor.put(redLabel_02    ,"2");
    label2Factor.put(orangeLabel_02 ,"3");
    label2Factor.put(yellowLabel_02 ,"4");
    label2Factor.put(greenLabel_02  ,"4");
    label2Factor.put(blueLabel_02   ,"6");
    label2Factor.put(violetLabel_02 ,"7");
    label2Factor.put(grayLabel_02   ,"8");
    label2Factor.put(whiteLabel_02  ,"9");

    label2Factor.put(blackLabel_03  ,"1");
    label2Factor.put(brownLabel_03  ,"10");
    label2Factor.put(redLabel_03    ,"100");
    label2Factor.put(orangeLabel_03 ,"1000");
    label2Factor.put(yellowLabel_03 ,"10000");
    label2Factor.put(greenLabel_03  ,"100000");
    label2Factor.put(blueLabel_03   ,"1000000");
    label2Factor.put(goldLabel_03   ,"0.1");
    label2Factor.put(silverLabel_03   ,"0.01");

    label2Factor.put(redLabel_04    ,"+/- 2%");
    label2Factor.put(goldLabel_04   ,"+/- 5%");
    label2Factor.put(silverLabel_04   ,"+/- 10%");

    // image panel
    //
   
    resistorLeft.setIcon(resleftImage);
    resistorBand01.setIcon(brownImage);
    resistorBand02.setIcon(blackImage);
    resistorBand03.setIcon(brownImage);
    resistorBand04.setIcon(goldImage);
    resistorRight.setIcon(resrightImage);
    
    band01Value = (String)label2Factor.get(brownLabel_01);
    band02Value = (String)label2Factor.get(blackLabel_02);
    band03Value = (String)label2Factor.get(brownLabel_03);
    band04Value = (String)label2Factor.get(goldLabel_04);
    
    calculate();
  }

/* (non-Javadoc)
	 * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#buildInputPanel()
	 */
	public Component buildInputPanel()
	{
    FormLayout layout = new FormLayout(
        "5dlu:grow,right:p,p,p,p,p,p,p,p,5dlu:grow",      // cols
        "10dlu:grow, p,fill:p,fill:p,fill:p,fill:p,fill:p,fill:p,fill:p,fill:p,fill:p,fill:p,fill:p,fill:p,fill:p,fill:p:grow,");  // rows
    
    PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
    if(debug)
      builder = new PanelBuilder(new FormDebugPanel(),layout);
    builder.setDefaultDialogBorder();

    CellConstraints cc = new CellConstraints();

    builder.add(bandMouseOverLabel     , cc.xywh(3,  1,5,1));

    builder.add(resistorLeft       , cc.xy(2,  2));
    builder.add(resistorBand01     , cc.xy(3,  2));
    builder.add(resistorBand02     , cc.xy(4,  2));
    builder.add(resistorBand03     , cc.xy(5,  2));
    builder.add(resistorBand04     , cc.xy(6,  2));
    builder.add(resistorRight      , cc.xy(7,  2));
    
    builder.addLabel(I18N.get("RESISTORCOLORCALC.LABEL.BLACK") ,cc.xy(2,  3));
    builder.addLabel(I18N.get("RESISTORCOLORCALC.LABEL.BROWN")  ,cc.xy(2,  4));
    builder.addLabel(I18N.get("RESISTORCOLORCALC.LABEL.RED")    ,cc.xy(2,  5));
    builder.addLabel(I18N.get("RESISTORCOLORCALC.LABEL.ORANGE") ,cc.xy(2,  6));
    builder.addLabel(I18N.get("RESISTORCOLORCALC.LABEL.YELLOW") ,cc.xy(2,  7));
    builder.addLabel(I18N.get("RESISTORCOLORCALC.LABEL.GREEN")  ,cc.xy(2,  8));
    builder.addLabel(I18N.get("RESISTORCOLORCALC.LABEL.BLUE")   ,cc.xy(2,  9));
    builder.addLabel(I18N.get("RESISTORCOLORCALC.LABEL.VIOLET") ,cc.xy(2,  10));
    builder.addLabel(I18N.get("RESISTORCOLORCALC.LABEL.GRAY")   ,cc.xy(2,  11));
    builder.addLabel(I18N.get("RESISTORCOLORCALC.LABEL.WHITE")  ,cc.xy(2,  12));
    builder.addLabel(I18N.get("RESISTORCOLORCALC.LABEL.SILVER")   ,cc.xy(2,  13));
    builder.addLabel(I18N.get("RESISTORCOLORCALC.LABEL.GOLD")   ,cc.xy(2,  14));
    
    builder.add(calculatedValue, cc.xy(9,2));
  
//    builder.add(blackLabel_01  ,cc.xy(3,  3));
    builder.add(brownLabel_01  ,cc.xy(3,  4));
    builder.add(redLabel_01    ,cc.xy(3,  5));
    builder.add(orangeLabel_01 ,cc.xy(3,  6));
    builder.add(yellowLabel_01 ,cc.xy(3,  7));
    builder.add(greenLabel_01  ,cc.xy(3,  8));
    builder.add(blueLabel_01   ,cc.xy(3,  9));
    builder.add(violetLabel_01 ,cc.xy(3,  10));
    builder.add(grayLabel_01   ,cc.xy(3,  11));
    builder.add(whiteLabel_01  ,cc.xy(3,  12));
//    builder.add(noneLabel_01   ,cc.xy(3,  13));
//    builder.add(goldLabel_01   ,cc.xy(3,  14));
    
    builder.add(blackLabel_02  ,cc.xy(4,  3));
    builder.add(brownLabel_02  ,cc.xy(4,  4));
    builder.add(redLabel_02    ,cc.xy(4,  5));
    builder.add(orangeLabel_02 ,cc.xy(4,  6));
    builder.add(yellowLabel_02 ,cc.xy(4,  7));
    builder.add(greenLabel_02  ,cc.xy(4,  8));
    builder.add(blueLabel_02   ,cc.xy(4,  9));
    builder.add(violetLabel_02 ,cc.xy(4,  10));
    builder.add(grayLabel_02   ,cc.xy(4,  11));
    builder.add(whiteLabel_02  ,cc.xy(4,  12));
//    builder.add(noneLabel_02   ,cc.xy(4,  13));
//    builder.add(goldLabel_02   ,cc.xy(4,  14));

    builder.add(blackLabel_03  ,cc.xy(5,  3));
    builder.add(brownLabel_03  ,cc.xy(5,  4));
    builder.add(redLabel_03    ,cc.xy(5,  5));
    builder.add(orangeLabel_03 ,cc.xy(5,  6));
    builder.add(yellowLabel_03 ,cc.xy(5,  7));
    builder.add(greenLabel_03  ,cc.xy(5,  8));
    builder.add(blueLabel_03   ,cc.xy(5,  9));
//    builder.add(violetLabel_03 ,cc.xy(5,  10));
//    builder.add(grayLabel_03   ,cc.xy(5,  11));
//    builder.add(whiteLabel_03  ,cc.xy(5,  12));
    builder.add(silverLabel_03   ,cc.xy(5,  13));
    builder.add(goldLabel_03   ,cc.xy(5,  14));

//    builder.add(blackLabel_04  ,cc.xy(6,  3));
//    builder.add(brownLabel_04  ,cc.xy(6,  4));
    builder.add(redLabel_04    ,cc.xy(6,  5));
//    builder.add(orangeLabel_04 ,cc.xy(6,  6));
//    builder.add(yellowLabel_04 ,cc.xy(6,  7));
//    builder.add(greenLabel_04  ,cc.xy(6,  8));
//    builder.add(blueLabel_04   ,cc.xy(6,  9));
//    builder.add(violetLabel_04 ,cc.xy(6,  10));
//    builder.add(grayLabel_04   ,cc.xy(6,  11));
//    builder.add(whiteLabel_04  ,cc.xy(6,  12));
    builder.add(silverLabel_04   ,cc.xy(6,  13));
    builder.add(goldLabel_04   ,cc.xy(6,  14));
    
    
    return builder.getPanel();
  }


	/* (non-Javadoc)
	 * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#onCancel()
	 */
	public void onCancel()
	{
	}

	/* (non-Javadoc)
	 * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#onOk()
	 */
	public void onOk()
	{
 	}

  private void calculate()
  {
//    System.out.println(band01Value+" "+band02Value+ " x "+ band03Value + " "+band04Value);
    try
		{ 
      double base   = Double.parseDouble(band01Value+band02Value); 
      double factor = Double.parseDouble(band03Value);
      double value  = base*factor;
      
      // bei dem Teilen treten rundungsfehler auf. Dies muss duch
      // ein 'manuelles' teilen der bereingt werden.
      if(band03Value.equals("0.1"))
        value = Double.parseDouble(band01Value+"."+band02Value);
      else if(band03Value.equals("0.01"))
        value = Double.parseDouble("0."+band01Value+band02Value);

      String valueString ="";
//      System.out.println("Wert:"+value);
      if(value<1000) // less than 1K Ohm
      {  
        valueString = ""+value+" Ohm "+band04Value;
      }
      else if(value<1000000)
      {
        valueString = ""+(value/1000.0d)+"K Ohm "+band04Value;
      }
      else if(value<1000000000)
        valueString = ""+(value/1000000.0d)+"M Ohm "+band04Value;
//      System.out.println(valueString);
      calculatedValue.setText(valueString);
		}
		catch (Exception e)
		{
      calculatedValue.setText("-Error-");
		}
  }
}