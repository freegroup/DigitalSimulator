package de.freegroup.digitalsimulator.dialogs;
/**
 * Title:        OBI (object browser interface for SMC)
 * Description:  Browser for the SMC category tree.
 * Copyright:    Copyright (c) 2002
 * Company:      OneStepAhead
 * @author
 * @version 1.0
 */


import java.awt.*;
import javax.swing.*;
import javax.swing.border.*;
import java.awt.event.*;
import javax.swing.event.*;
import de.freegroup.digitalsimulator.ui.ImageBackgroundPanel;
import de.freegroup.ui.SkinButton;
import com.borland.jbcl.layout.*;

import JUtil;
import Trace;
import de.freegroup.ui.HyperlinkedLabel;

public class UserPasswordDialog extends JDialog
{
   boolean  test=false;

   ImageIcon pluginImage = null;
   JPanel mainPanel = new ImageBackgroundPanel();
   BorderLayout mainLayout = new BorderLayout();
   JPanel buttonBarPanel = new JPanel();
   BorderLayout buttonBarLayout = new BorderLayout();
   JPanel buttonPanel = new JPanel();
   JButton okButton = new SkinButton();
   JButton cancelButton = new SkinButton();
   JPanel contentPanel = new JPanel();
   BorderLayout borderLayout3 = new BorderLayout();
   JTextField userTextField = new JTextField();
   JLabel userLabel = new JLabel();
   FlowLayout buttonLayout = new FlowLayout();
   BorderLayout borderLayout1 = new BorderLayout();
   JPanel inputPanel = new JPanel();
   TitledBorder titledBorder1;
   boolean ok = false;
   JPanel labelPanel = new JPanel();
   VerticalFlowLayout verticalFlowLayout1 = new VerticalFlowLayout();
   JLabel passwordLabel = new JLabel();
   VerticalFlowLayout verticalFlowLayout2 = new VerticalFlowLayout();
   JPasswordField passwordTextField = new JPasswordField();
   JLabel warningLabel = new JLabel();
    JLabel imageLabel = new JLabel();
    HyperlinkedLabel linkLabel = new HyperlinkedLabel("click here to get Information about WebShare","http://www.DigitalSimulator.de/webstore/index.php3");

   /**
    *
    */
   public UserPasswordDialog(String title, String message, String user)
   {
      super((Frame)null, title, true);
      try {
         jbInit();
         userTextField.setText(user);
         warningLabel.setText(message);
         pack();
         Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
         int w = 450;
         int h = 340;
         int x = (dim.width-w)/2;
         int y = (dim.height-h)/2;
         setBounds(x, y, w, h);
         JUtil.setWindowAlwaysOnTop(JUtil.getHwnd(getTitle()),true);
         show();
      }
      catch(Exception ex)
      {
         Trace.error("unable to create user/password dialog", ex);
      }
   }

   /**
    *
    */
   void jbInit() throws Exception {
      pluginImage  = new ImageIcon(de.freegroup.digitalsimulator.images.Resource.class.getResource("webshare.gif"));
      titledBorder1 = new TitledBorder("");
      mainPanel.setLayout(mainLayout);
      buttonBarPanel.setLayout(buttonBarLayout);
      okButton.setText("Ok");
      okButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(ActionEvent e) {
            okButton_actionPerformed(e);
         }
      });
      cancelButton.setText("Abbrechen");
      cancelButton.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(ActionEvent e) {
            cancelButton_actionPerformed(e);
         }
      });
      contentPanel.setBackground(Color.gray);
      contentPanel.setBorder(titledBorder1);
      contentPanel.setOpaque(false);
      contentPanel.setLayout(borderLayout3);


      userTextField.setMinimumSize(new Dimension(200, 21));
      userTextField.setNextFocusableComponent(passwordTextField);
      userTextField.setPreferredSize(new Dimension(200, 21));
      if(test)
      {
         userTextField.setEditable(false);
         userTextField.setText("testtaker3");
      }
      userTextField.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(ActionEvent e) {
            userTextField_actionPerformed(e);
         }
      });
      userLabel.setText("Benutzer: ");
      buttonPanel.setLayout(buttonLayout);
      inputPanel.setLayout(verticalFlowLayout1);
      buttonBarPanel.setOpaque(false);
      buttonPanel.setOpaque(false);
      inputPanel.setOpaque(false);
      passwordLabel.setText("Passwort: ");
      labelPanel.setLayout(verticalFlowLayout2);
      labelPanel.setOpaque(false);
//      warningLabel.setText("Passwort: ");
      warningLabel.setBackground(Color.yellow);
      warningLabel.setForeground(Color.red);
      warningLabel.setOpaque(true);
      if(test)
      {
         passwordTextField.setEditable(false);
         passwordTextField.setText("testtaker3");
      }
      passwordTextField.addActionListener(new java.awt.event.ActionListener() {
         public void actionPerformed(ActionEvent e) {
            passwordTextField_actionPerformed(e);
         }
      });
      imageLabel.setIcon(pluginImage);
      linkLabel.setHorizontalAlignment(SwingConstants.CENTER);
      getContentPane().add(mainPanel);
      mainPanel.add(buttonBarPanel,  BorderLayout.SOUTH);
      buttonBarPanel.add(buttonPanel,  BorderLayout.EAST);
      buttonPanel.add(okButton, null);
      buttonPanel.add(cancelButton, null);
      mainPanel.add(contentPanel, BorderLayout.CENTER);
      contentPanel.add(inputPanel, BorderLayout.EAST);
      contentPanel.add(warningLabel, BorderLayout.NORTH);
      contentPanel.add(labelPanel, BorderLayout.WEST);
      labelPanel.add(userLabel, null);
      labelPanel.add(passwordLabel, null);
        labelPanel.add(imageLabel, null);
        contentPanel.add(linkLabel, BorderLayout.SOUTH);
      inputPanel.add(userTextField, null);
      inputPanel.add(passwordTextField, null);
   }


   /**
    *
    */
   public boolean isOk()
   {
      return ok;
   }

   /**
    *
    */
   public String getUser()
   {
      return userTextField.getText();
   }

   /**
    *
    */
   public String getPassword()
   {
      return new String(passwordTextField.getPassword());
   }

   void okButton_actionPerformed(ActionEvent e)
   {
      ok = true;
      dispose();
   }

   void cancelButton_actionPerformed(ActionEvent e)
   {
      ok = false;
      dispose();
   }

   void userTextField_actionPerformed(ActionEvent e)
   {
      ok = true;
      dispose();
   }

   void passwordTextField_actionPerformed(ActionEvent e)
   {
      ok = true;
      dispose();
   }

    public static void main(String[] args)
    {
        new UserPasswordDialog("Bitte Passwort eingeben","","user");
        new UserPasswordDialog("Bitte Passwort eingeben","Passwort war falsch","user");
    }

}