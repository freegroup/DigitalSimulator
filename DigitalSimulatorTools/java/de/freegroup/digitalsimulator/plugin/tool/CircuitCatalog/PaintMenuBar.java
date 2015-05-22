package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog;

import javax.swing.*;

import de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.util.*;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

/**
 * A JMenuBar that can do stuff for a PaintPanel based app. 
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class PaintMenuBar extends JMenuBar implements ActionListener, PropertyChangeListener 
{

   private PaintPanel panel;
   private JMenuItem pasteImage;
   private PropertiesGUI props;

   public PaintMenuBar(PaintPanel panel) 
   {
      this.panel = panel;

      this.init();
      this.initProps();
   }

   public void initProps() 
   {
      props = new PropertiesGUI(JImagePaint.frame, "Settings", true);

      PropertiesGUIField width = new PropertiesGUIField(JImagePaint.properties, "width", PropertiesGUIField.TYPE_INT);
      width.getLabel().setText("New Image Width");
      props.addPropertiesGUIField(width);

      PropertiesGUIField height = new PropertiesGUIField(JImagePaint.properties, "height", PropertiesGUIField.TYPE_INT);
      height.getLabel().setText("New Image Height");
      props.addPropertiesGUIField(height);



      PropertiesGUIField bgColor = new PropertiesGUIField(JImagePaint.properties, "bgcolor", PropertiesGUIField.TYPE_COLOR);
      bgColor.getLabel().setText("Background Color");
      bgColor.addPropertyChangeListener(this);
      props.addPropertiesGUIField(bgColor);


      props.buildGUI();

   }

   public void init() {
      JMenu file = new JMenu("File");
      file.setMnemonic(KeyEvent.VK_F);

      this.add(file);

      ImageIcon icon = new ImageIcon(this.getClass().getResource("graphics/new.png"));
      JMenuItem newFile = new JMenuItem("New Image");
      newFile.setMnemonic(KeyEvent.VK_N);
      newFile.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N, ActionEvent.CTRL_MASK));
      newFile.setIcon(icon);
      newFile.setActionCommand("new");
      newFile.addActionListener(this);
      file.add(newFile);

      icon = new ImageIcon(this.getClass().getResource("graphics/open.png"));
      JMenuItem open = new JMenuItem("Open Image");
      open.setMnemonic(KeyEvent.VK_O);
      open.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, ActionEvent.CTRL_MASK));
      open.setIcon(icon);
      open.setActionCommand("open");
      open.addActionListener(this);
      file.add(open);

      icon = new ImageIcon(this.getClass().getResource("graphics/save.png"));
      JMenuItem save = new JMenuItem("Save Image");
      save.setMnemonic(KeyEvent.VK_S);
      save.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, ActionEvent.CTRL_MASK));
      save.setIcon(icon);
      save.setActionCommand("save");
      save.addActionListener(this);
      file.add(save);

      icon = new ImageIcon(this.getClass().getResource("graphics/append.png"));
      JMenuItem append = new JMenuItem("Append Image");
      append.setMnemonic(KeyEvent.VK_A);
      append.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_A, ActionEvent.CTRL_MASK));
      append.setIcon(icon);
      append.setActionCommand("append");
      append.addActionListener(this);
      file.add(append);


      JMenuItem settings = new JMenuItem("Settings");

      settings.setActionCommand("settings");
      settings.addActionListener(this);
      file.add(settings);

      JMenuItem exit = new JMenuItem("Exit");
      exit.setMnemonic(KeyEvent.VK_E);
      exit.setActionCommand("exit");
      exit.addActionListener(this);
      file.add(exit);

      JMenu edit = new JMenu("Edit");
      edit.addActionListener(this);
      edit.setMnemonic(KeyEvent.VK_E);
      edit.addActionListener(this);
      this.add(edit);


      JMenuItem copy = new JMenuItem("Copy Objects");
      copy.addActionListener(this);
      copy.setActionCommand("copy");
      edit.add(copy);

      JMenuItem delete = new JMenuItem("Delete Objects ");
      delete.addActionListener(this);
      delete.setActionCommand("delete");
      edit.add(delete);

      JMenuItem inc = new JMenuItem("Incorporate Objects");
      inc.addActionListener(this);
      inc.setActionCommand("inc");
      edit.add(inc);

      edit.addSeparator();

      JMenuItem selAll = new JMenuItem("Select All Objects");
      selAll.addActionListener(this);
      selAll.setActionCommand("selall");
      edit.add(selAll);

      JMenuItem incAll = new JMenuItem("Incorporate All Objects");
      incAll.addActionListener(this);
      incAll.setActionCommand("incall");
      edit.add(incAll);

      edit.addSeparator();

      JMenuItem copyImage = new JMenuItem("Copy Image To Clipboard");
      copyImage.addActionListener(this);
      copyImage.setActionCommand("copyimage");
      edit.add(copyImage);

      JMenuItem copyImageBG = new JMenuItem("Copy Image with Background");
      copyImageBG.addActionListener(this);
      copyImageBG.setActionCommand("copyimagebg");
      edit.add(copyImageBG);

      pasteImage = new JMenuItem("Paste Image from Clipboard");
      pasteImage.addActionListener(this);
      pasteImage.setActionCommand("pasteimage");
      edit.add(pasteImage);

      JMenu help = new JMenu("Help");
      help.setMnemonic(KeyEvent.VK_H);

      this.add(help);

      JMenuItem readme = new JMenuItem("View Readme");
      readme.addActionListener(this);
      readme.setActionCommand("readme");
      help.add(readme);

      JMenuItem about = new JMenuItem("About");
      about.addActionListener(this);
      about.setActionCommand("about");
      help.add(about);

      JMenuItem website = new JMenuItem("Website");
      website.addActionListener(this);
      website.setActionCommand("website");
      help.add(website);


   }


   public void actionPerformed(ActionEvent e) {
      if (e.getActionCommand().equals("new")) {
         panel.createNewFile();
      }
      if (e.getActionCommand().equals("open")) {
         panel.openImageFile();
      }
      if (e.getActionCommand().equals("save")) {
         panel.saveImageFile();
      }
      if (e.getActionCommand().equals("append")) {
         panel.appendImageFile(0, 0);
      }
      if (e.getActionCommand().equals("settings")) {
         props.setVisible(true);
         panel.repaint();
      }
      if (e.getActionCommand().equals("copy")) {
         panel.copySelected();
      }
      if (e.getActionCommand().equals("delete")) {
         panel.deleteSelected();
      }
      if (e.getActionCommand().equals("inc")) {
         panel.incorporateSelected();
      }

      if (e.getActionCommand().equals("selall")) {
         panel.selectAll();
      }

      if (e.getActionCommand().equals("incall")) {
         panel.selectAll();
         panel.incorporateSelected();
      }
      if (e.getActionCommand().equals("copyimage")) {
         panel.copyImageToClipboard();

      }
      if (e.getActionCommand().equals("copyimagebg")) {
         panel.copyImageToClipboardwBG();
      }

      if (e.getActionCommand().equals("pasteimage")) {
         panel.pasteImageFromClipboard(new Point(0, 0));
      }

      if (e.getActionCommand().equals("edit")) {
         if (!BufferedImageTool.clipboardHasImage()) {
            pasteImage.setEnabled(false);
         }
         else {
            pasteImage.setEnabled(true);
         }
      }
      if(e.getActionCommand().equals("readme")){
         BrowserControl.displayURL("readme.html");
      }

      if (e.getActionCommand().equals("about")) {
         JTextArea text = new JTextArea();
         text.setText("JImagePaint Release 1.0\nCopyright Alistair Dickie 2004\nSee licence.txt for licence information\nSee alistairdickie.com for contact details");
         text.setEditable(false);
         text.setOpaque(false);
         JOptionPane.showMessageDialog(JImagePaint.frame, text, "JImagePaint", JOptionPane.PLAIN_MESSAGE, null);

      }
      if (e.getActionCommand().equals("website")) {
         BrowserControl.displayURL("http://alistairdickie.com");
      }
      if (e.getActionCommand().equals("exit")) {
         JImagePaint.saveProperties();
         System.exit(0);
      }
   }

   public void propertyChange(PropertyChangeEvent evt) {
//    System.out.println("event " + evt.getPropertyName());
      if (evt.getPropertyName().equals("bgcolor")) {

         panel.setBgColor(new Color(((Integer) evt.getNewValue()).intValue()));
         panel.repaint();
      }

   }
}
