package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * A JToolBar to change the main image.
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class FileToolbar extends JToolBar implements ActionListener {
   private JButton newFile;
   private JButton openFile;
   private JButton appendFile;
   private JButton saveFile;

   private PaintPanel panel;

   public FileToolbar(PaintPanel panel) {
      this.panel = panel;

      ImageIcon icon = new ImageIcon(this.getClass().getResource("graphics/new.png"));
      newFile = new JButton(icon);
      newFile.setActionCommand("newfile");
      newFile.addActionListener(this);
      newFile.setToolTipText("New File");
      this.add(newFile);

      icon = new ImageIcon(this.getClass().getResource("graphics/open.png"));
      openFile = new JButton(icon);
      openFile.setActionCommand("openfile");
      openFile.setToolTipText("Open File");
      openFile.addActionListener(this);
      this.add(openFile);

      icon = new ImageIcon(this.getClass().getResource("graphics/save.png"));
      saveFile = new JButton(icon);
      saveFile.setActionCommand("savefile");
      saveFile.setToolTipText("Save File");
      saveFile.addActionListener(this);
      this.add(saveFile);

      icon = new ImageIcon(this.getClass().getResource("graphics/append.png"));
      appendFile = new JButton(icon);
      appendFile.setActionCommand("appendfile");
      appendFile.setToolTipText("Append File");
      appendFile.addActionListener(this);
      this.add(appendFile);


   }

   public void actionPerformed(ActionEvent e) {
      if (e.getActionCommand().equals("newfile")) {
         panel.createNewFile();
      }
      if (e.getActionCommand().equals("openfile")) {
         panel.openImageFile();
      }
      if (e.getActionCommand().equals("appendfile")) {
         panel.appendImageFile(0, 0);
      }
      if (e.getActionCommand().equals("savefile")) {
         panel.saveImageFile();
      }

   }

}
