package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.util;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;

/**
 * A JButton that is used to select a color using a JColorChooser.
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class ColorButton extends JButton implements ActionListener {
   private Color color;

   private Component chooserParent;
   private String chooserTitle;
   private String propName;
   private JDialog chooserDialog;
   private JColorChooser chooser;

   /**
    * Constructs a ColorButton
    * @param color
    * The initial color
    * @param text
    * Text to add to the ColorButton
    * @param chooserParent
    * Parent of the JColorChooser
    * @param chooserTitle
    * Title of the JColorChooser
    * @param propName
    * Name of the property to file. This button will fire a PropertyChagneEvent when the color has been changed
    * with an old value of oldColor and a new value of newColor
    */
   public ColorButton(Color color, String text, Component chooserParent, String chooserTitle, String propName) {
      this.color = color;

      this.propName = propName;
      this.chooserParent = chooserParent;
      this.chooserTitle = chooserTitle;
      if (text != null) {
         this.setText(text);
      }
      chooser = new JColorChooser();
      chooser.setColor(Color.blue);
      chooser.setColor(Color.red);
      chooser.setColor(color);
      chooserDialog = JColorChooser.createDialog(chooserParent, chooserTitle, true, chooser, this, this);

      this.setMargin(new Insets(2, 2, 2, 2));
      this.buildImage();
      this.addActionListener(this);
   }


   private void buildImage() {
      BufferedImage img = new BufferedImage(16, 16, BufferedImage.TYPE_INT_ARGB);
      Graphics g = img.getGraphics();
      g.setColor(color);
      g.fillRect(0, 0, 16, 16);
      this.setIcon(new ImageIcon(img));
      this.repaint();

   }

   public void setColor(Color color) {
      this.color = color;
      this.buildImage();
   }

   public Color getColor() {
      return color;
   }

   public void actionPerformed(ActionEvent e) {
      if (e.getSource() == this && !chooserDialog.isVisible()) {
         chooserDialog.setVisible(true);

      }
      if (e.getActionCommand().equals("OK")) {
         Color sel = chooser.getColor();
         if (sel != null) {
            this.firePropertyChange(propName, color, sel);
            this.setColor(sel);


         }
      }
   }


   public String getPropName() {
      return propName;
   }
   /**
    *
    * @param propName
    * The name of the PropertyChangeEvent
    */
   public void setPropName(String propName) {
      this.propName = propName;
   }

   public Component getChooserParent() {
      return chooserParent;
   }

   public void setChooserParent(Component chooserParent) {
      this.chooserParent = chooserParent;
   }

   public String getChooserTitle() {
      return chooserTitle;
   }

   public void setChooserTitle(String chooserTitle) {
      this.chooserTitle = chooserTitle;
   }
}
