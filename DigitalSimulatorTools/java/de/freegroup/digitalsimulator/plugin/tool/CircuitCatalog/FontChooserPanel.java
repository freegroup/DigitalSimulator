package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


/**
 * A panel that has widgets to fiddle with a font.
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */

public class FontChooserPanel extends JPanel implements ActionListener, ChangeListener {
   private JComboBox box;
   private JToggleButton bold;
   private JToggleButton italic;
   private JSpinner size;
   private String propName;


   public FontChooserPanel(Font font, String propName) {
      super();
      this.propName = propName;
      this.setFont(font);
      this.add(getFontNameBox());
      this.add(getSizeSpinner());
      this.add(getBoldButton());
      this.add(getItalicButton());

   }

   public JComboBox getFontNameBox() {
      String[] fonts = GraphicsEnvironment.getLocalGraphicsEnvironment().getAvailableFontFamilyNames();
      box = new JComboBox(fonts);
      String font = this.getFont().getFontName();
      String fontName = font;
      if (font.indexOf(".") > -1) {
         fontName = font.substring(0, font.indexOf("."));
      }


      box.setSelectedItem(fontName);
      box.addActionListener(this);
      return box;
   }

   public JSpinner getSizeSpinner() {
      SpinnerNumberModel model = new SpinnerNumberModel(this.getFont().getSize(), 1, 1000, 1);
      size = new JSpinner(model);
      size.addChangeListener(this);
      return size;
   }

   public JToggleButton getBoldButton() {
      ImageIcon icon = new ImageIcon(this.getClass().getResource("graphics/bold.png"));
      bold = new JToggleButton(icon);

      bold.setMargin(new Insets(2, 2, 2, 2));
      bold.setToolTipText("Bold");
      bold.setFocusPainted(false);
      bold.addChangeListener(this);
      return bold;
   }

   public JToggleButton getItalicButton() {
      ImageIcon icon = new ImageIcon(this.getClass().getResource("graphics/italic.png"));
      italic = new JToggleButton(icon);

      italic.setMargin(new Insets(2, 2, 2, 2));
      italic.setFocusPainted(false);
      italic.setToolTipText("Italic");
      italic.addChangeListener(this);
      return italic;
   }


   public void actionPerformed(ActionEvent e) {
      Font oldF = this.getFont();
      int b = Font.PLAIN;
      if (bold.isSelected()) {
         b = Font.BOLD;
      }
      int i = Font.PLAIN;
      if (italic.isSelected()) {
         i = Font.ITALIC;
      }
      Font newF = new Font(box.getSelectedItem().toString(), b | i, ((Integer) size.getModel().getValue()).intValue());
      this.firePropertyChange(propName, oldF, newF);
   }

   public void stateChanged(ChangeEvent e) {
      Font oldF = this.getFont();
      int b = Font.PLAIN;
      if (bold.isSelected()) {
         b = Font.BOLD;
      }
      int i = Font.PLAIN;
      if (italic.isSelected()) {
         i = Font.ITALIC;
      }
      Font newF = new Font(box.getSelectedItem().toString(), b | i, ((Integer) size.getModel().getValue()).intValue());
      this.firePropertyChange(propName, oldF, newF);
   }

   public void setFont(Font font) {
      super.setFont(font);
      if (font != null && bold != null) {
         bold.setSelected(font.isBold());
         italic.setSelected(font.isItalic());
         size.setValue(new Integer(font.getSize()));
         String fontName = font.getFontName().substring(0, font.getFontName().indexOf("."));
         box.setSelectedItem(fontName);
      }


   }


}
