package de.freegroup.digitalsimulator.export.webshare.dialogs;
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

import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.dialogs.GenericDialog;
import de.freegroup.digitalsimulator.ui.HGradient;
import de.freegroup.digitalsimulator.ui.VGradient;

import com.borland.jbcl.layout.*;
import com.jgoodies.clearlook.ClearLookManager;
import com.jgoodies.clearlook.ClearLookMode;
import com.jgoodies.forms.builder.PanelBuilder;
import com.jgoodies.forms.debug.FormDebugPanel;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;
import com.jgoodies.plaf.*;
import com.jgoodies.plaf.plastic.Plastic3DLookAndFeel;
import com.jgoodies.plaf.plastic.PlasticLookAndFeel;
import com.jgoodies.plaf.plastic.theme.DesertBlue;

import java.awt.*;
import java.io.PrintStream;
import javax.swing.*;
import javax.swing.border.EmptyBorder;

import de.freegroup.ui.HyperlinkedLabel;

public class UserPasswordDialog extends GenericDialog
{
   JTextField       userTextField     = null;
   JPasswordField   passwordTextField = null;
   JLabel           warningLabel      = null;
   HyperlinkedLabel linkLabel         = null;

   String message ="";
   String user    ="";
   /**
    *
    */
   public UserPasswordDialog(String message, String user)
   {
    super(I18N.get("COMMON.DIALOGHEADER.WEBSHARE"),
          I18N.get("WEBSHARE.LABEL.HELPHEADER"),
          I18N.get("WEBSHARE.LABEL.HELPLINE01"),
          I18N.get("WEBSHARE.LABEL.HELPLINE02"));

         this.user    = user;
         this.message = message;
         show(500,400);
   }

   public void initComponents()
   {
    userTextField     = new JTextField(user);
    passwordTextField = new JPasswordField();
    warningLabel      = new JLabel(message);
    linkLabel         = new HyperlinkedLabel(I18N.get("COMMON.LABEL.INFO"),"http://www.DigitalSimulator.de/webstore/index.php3");
   }
   
   /**
    *
    */
   public Component buildInputPanel()
   {
      warningLabel.setBackground(Color.yellow);
      warningLabel.setForeground(Color.red);
      warningLabel.setOpaque(true);

     FormLayout layout = new FormLayout(
             "r:pref:grow, 8dlu, 2dlu, 8dlu, r:pref, 4dlu, 50dlu, 4dlu, min,4dlu",
             " 20dlu,t:pref:grow(0.3), pref, 4dlu, pref,pref, pref:grow(0.7), 20dlu"
     );
     JLabel w1 = new JLabel("Wilkommen bei");
     JLabel w2 = new JLabel("WebShare");
     JLabel w3 = new JLabel("Benutzer und Passwort eingeben");
     JLabel w4 = new JLabel("und 'Ok' anklicken");
     
     w2.setHorizontalTextPosition(SwingConstants.RIGHT);
     w2.setFont( new Font("",Font.PLAIN,35));
     w1.setForeground(Color.gray);
     w2.setForeground(Color.gray);
     w3.setForeground(Color.gray);
     w4.setForeground(Color.gray);
     PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
     if(debug)
      builder = new PanelBuilder(new FormDebugPanel(),layout);
     builder.setDefaultDialogBorder();
     
     CellConstraints cc = new CellConstraints();
    
     builder.add(new HGradient(Color.lightGray,Color.darkGray),    cc.xywh(3,2,1,6));
     builder.add(w1, cc.xywh(1,2,1,1,"RIGHT,BOTTOM"));
     builder.add(w2, cc.xywh(1,3,1,3));
     builder.add(w3, cc.xywh(1,6,1,1,"RIGHT,TOP"));
     builder.add(w4, cc.xywh(1,7,1,1,"RIGHT,TOP"));
     builder.addLabel(I18N.get("COMMON.LABEL.USER"),     cc.xy(5,3));
     builder.add(userTextField,                          cc.xy(7,3));
     builder.addLabel(I18N.get("COMMON.LABEL.PASSWORD"), cc.xy(5,5));
     builder.add(passwordTextField,                      cc.xy(7,5));
     builder.add(linkLabel,                              cc.xywh(1,8,9,1,"RIGHT,BOTTOM"));

    return builder.getPanel();
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

   public void onOk()
   {
   }

   public void onCancel()
   {
   }


    public static void main(String[] args)
    {
       new UserPasswordDialog("","user");
       System.exit(1);
    }
    

}