package de.freegroup.digitalsimulator.webstore.dialogs;

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import javax.swing.event.*;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import java.util.*;
import de.freegroup.ui.SkinButton;
import de.freegroup.digitalsimulator.ui.ImageBackgroundPanel;
import JUtil;

public class GenericFileSelector extends JDialog
{
   ImageIcon pluginImage = null;
   JPanel contentPanel = new ImageBackgroundPanel();//new JPanel();
   BorderLayout borderLayout1 = new BorderLayout();
   JList fileList = null;
   JPanel inputPanel = new JPanel();
   BorderLayout borderLayout2 = new BorderLayout();
   JButton actionButton = new SkinButton();
   JTextField fileNameTextField = new JTextField();
   Vector fileNames = null;
    JLabel imageLabel = new JLabel();
    JLabel fileNameLabel = new JLabel();
    JLabel jLabel1 = new JLabel();

   public GenericFileSelector(Vector fileNameList, String title)
   {
      super((Frame)null, title, true);
      try
      {
         fileNames = (Vector)fileNameList.clone();
         jbInit();
         pack();
         Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
         int w = 500;
         int h = 300;
         int x = (dim.width-w)/2;
         int y = (dim.height-h)/2;

         setBounds(x, y, w, h);
         JUtil.setWindowAlwaysOnTop(JUtil.getHwnd(getTitle()),true);
         show();
      }
      catch(Exception ex)
      {
         ex.printStackTrace();
      }
   }

   void jbInit() throws Exception
   {
      pluginImage  = new ImageIcon(de.freegroup.digitalsimulator.images.Resource.class.getResource("webshare.gif"));
      fileList = new JList(fileNames);
      contentPanel.setLayout(borderLayout1);
      inputPanel.setLayout(borderLayout2);
      actionButton.setText("Upload");
      actionButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(ActionEvent e) {
            actionButton_actionPerformed(e);
         }
      });
      fileNameTextField.setText("");
        fileNameTextField.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyTyped(KeyEvent e) {
                fileNameTextField_keyTyped(e);
            }
        });
      fileList.addListSelectionListener(new javax.swing.event.ListSelectionListener() {
         public void valueChanged(ListSelectionEvent e) {
            fileList_valueChanged(e);
         }
      });
        imageLabel.setIcon(pluginImage);
        fileNameLabel.setText("Filename: ");
        inputPanel.setOpaque(false);
        fileList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        jLabel1.setBackground(UIManager.getColor("info"));
        jLabel1.setMaximumSize(new Dimension(319, 37));
        jLabel1.setMinimumSize(new Dimension(319, 37));
        jLabel1.setOpaque(true);
        jLabel1.setPreferredSize(new Dimension(319, 37));
        jLabel1.setText("Enter filename or select a file to upload your simulation file");
        getContentPane().add(contentPanel);
        contentPanel.add(fileList, BorderLayout.CENTER);
        contentPanel.add(inputPanel, BorderLayout.SOUTH);
        inputPanel.add(actionButton, BorderLayout.EAST);
        inputPanel.add(fileNameTextField, BorderLayout.CENTER);
        inputPanel.add(fileNameLabel, BorderLayout.WEST);
        contentPanel.add(imageLabel, BorderLayout.WEST);
        contentPanel.add(jLabel1, BorderLayout.NORTH);
   }

   void actionButton_actionPerformed(ActionEvent e)
   {
      dispose();
   }

   public String getFilename()
   {
      return fileNameTextField.getText();
   }

   void fileList_valueChanged(ListSelectionEvent e)
   {
      String value = fileList.getSelectedValue().toString();
      fileNameTextField.setText(value);
   }

   /**
    * only to test his class
    */
    public static void main(String[] args)
    {
      Vector file = new Vector();
      file.add("Datei1");
      file.add("Datei2");
      file.add("Datei3");
      file.add("Datei4");
      file.add("Datei5");
      new GenericFileSelector(file, "File selection");
    }

    void fileNameTextField_keyTyped(KeyEvent e)
    {
        char c = e.getKeyChar();
        if(Character.isLetter(c) || c=='_')
            return;
        e.consume();
    }
}
