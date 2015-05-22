package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog;


import javax.swing.*;

import de.freegroup.digitalsimulator.plugin.tool.ITool;
import de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.util.JavaVersionCheck;

import java.awt.*;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Properties;

/**
 * An example of how to drag together the main jimgpnt components to create an application.
 * <p/>
 * <p/>
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class JImagePaint extends JPanel implements WindowListener , ITool
{

   public static Properties properties;
   public static JFrame frame;

   private PaintPanel panel;
   private ModeToolbar mode;
   private OptionsToolbar options;
   private FileToolbar file;

   public JImagePaint() 
   {
   }
   
   public JImagePaint(File fileToLoad) 
   {
      this.setLayout(new BorderLayout());

      panel = new PaintPanel(properties);
      JScrollPane scroll = new JScrollPane(panel);
      panel.setScroll(scroll);

      new PopupMenu(panel);


      mode = new ModeToolbar(panel);
      mode.setOrientation(JToolBar.VERTICAL);
      panel.addPropertyChangeListener(mode);
      panel.setCurrentMode(PaintPanel.MODE_LINE);


      options = new OptionsToolbar(panel);
      options.addPropertyChangeListener(mode);


      file = new FileToolbar(panel);
      LocationPanel loc = new LocationPanel("");
      panel.setLocationPanel(loc);
      file.add(loc);

      this.add(scroll, BorderLayout.CENTER);
      this.add(mode, BorderLayout.WEST);
      this.add(options, BorderLayout.SOUTH);
      this.add(file, BorderLayout.NORTH);


   }

   public PaintPanel getPanel() 
   {
      return panel;
   }

   public void windowOpened(WindowEvent e) 
   {

   }

   public void windowClosing(WindowEvent e) 
   {
      JImagePaint.saveProperties();
   }

   public void windowClosed(WindowEvent e) 
   {

   }

   public void windowIconified(WindowEvent e) 
   {

   }

   public void windowDeiconified(WindowEvent e) 
   {

   }

   public void windowActivated(WindowEvent e) 
   {

   }

   public void windowDeactivated(WindowEvent e) 
   {

   }


   public static void loadProperties() 
   {
      File file = new File("jimgpnt.properties");
      if (file.exists()) {
         properties = new Properties();
         try {
            properties.load(new FileInputStream(file));
         }
         catch (IOException e) {
            e.printStackTrace();
         }
      }
      else {
         properties = new Properties();
         properties.setProperty("width", "256");
         properties.setProperty("height", "256");
         properties.setProperty("bgcolor", "" + new Color(255, 255, 175).getRGB());
         properties.setProperty("drawcolor", "" + Color.black.getRGB());
         properties.setProperty("alpha", "1.0");
         properties.setProperty("fontname", "Serif");
         properties.setProperty("fonttype", "1");
         properties.setProperty("fontsize", "22");
         properties.setProperty("filled", "false");
         properties.setProperty("antialiased", "true");
         properties.setProperty("arcwidth", "0.0");
         properties.setProperty("archeight", "0.0");
         properties.setProperty("strokewidth", "1.0");
         properties.setProperty("eraserad", "3");
      }
   }

   public static void saveProperties() 
   {
      File file = new File("jimgpnt.properties");
      try 
      {
         FileOutputStream output = new FileOutputStream(file);
         properties.store(output, "JImagePaint Properties version 1.0");
         output.close();
      }
      catch (IOException e) 
      {
         e.printStackTrace();
      }


   }


   public static void main(String[] args) 
   {
      loadProperties();
      frame = new JFrame("JImagePaint");
      if (!JavaVersionCheck.checkMin(1.4)) 
      {
         JOptionPane.showMessageDialog(frame, "You do not seem to have a Java version 1.4 or later\nDownload an updated version from http://java.sun.com", "Java Version Check",             JOptionPane.ERROR_MESSAGE);
         System.exit(-1);
      }

      JImagePaint contents = null;
      if (args.length > 0) {

         File file = new File(args[0]);
         if (file.exists()) {
            contents = new JImagePaint(file);
         }
         else {
            contents = new JImagePaint(null);
         }
      }
      else {
         contents = new JImagePaint(null);
      }
      frame.setContentPane(contents);
      frame.addWindowListener(contents);
      frame.setJMenuBar(new PaintMenuBar(contents.getPanel()));

      frame.pack();
      frame.setLocationRelativeTo(null);
      frame.setVisible(true);
   }
   
  /* 
   * @see de.freegroup.digitalsimulator.plugin.tool.ITool#getId()
   */
  public String getId()
  {
    // TODO Auto-generated method stub
    return "CIRCUITCatalog";
  }

  /* 
   * @see de.freegroup.digitalsimulator.plugin.tool.ITool#getMenuEntry()
   */
  public String getMenuEntry()
  {
    // TODO Auto-generated method stub
    return "CircuitCatalog";
  }

  /* 
   * @see de.freegroup.digitalsimulator.plugin.tool.ITool#run()
   */
  public void run()
  {
    if (!JavaVersionCheck.checkMin(1.4)) 
    {
      JOptionPane.showMessageDialog(frame, "You do not seem to have a Java version 1.4 or later\nDownload an updated version from http://java.sun.com", "Java Version Check", JOptionPane.ERROR_MESSAGE);
      return;
    }
    
    loadProperties();
    frame = new JFrame("JImagePaint");
    
    JImagePaint contents = null;
    contents = new JImagePaint(null);
    frame.setContentPane(contents);
    frame.addWindowListener(contents);
    frame.setJMenuBar(new PaintMenuBar(contents.getPanel()));

    frame.pack();
    frame.setLocationRelativeTo(null);
    frame.setVisible(true);
  }

}
