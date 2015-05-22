package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog;


import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.util.*;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

/**
 * A JToolBar to control painting options of a PaintPanel. 
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class OptionsToolbar extends JToolBar implements ActionListener, PropertyChangeListener, ChangeListener {
   private JToggleButton anti;
   private FontChooserPanel font;
   private PaintPanel paintPanel;
   private ColorButton fgColor;
   private StrokeChooserPanel stroke;
   private JToggleButton fill;
   private JSlider alpha;


   public OptionsToolbar(PaintPanel paintPanel) 
   {
      this.setName("Paint Options");
      this.paintPanel = paintPanel;
      paintPanel.addPropertyChangeListener(this);
      ImageIcon icon = new ImageIcon(this.getClass().getResource("graphics/anti.png"));
      anti = new JToggleButton(icon);
      anti.setSelected(paintPanel.isAntialiased());
      anti.addActionListener(this);
      anti.setActionCommand("anti");
      this.add(anti);

      icon = new ImageIcon(this.getClass().getResource("graphics/fill.png"));
      fill = new JToggleButton(icon);
      fill.setSelected(paintPanel.isFilled());
      fill.addActionListener(this);
      fill.setActionCommand("fill");
      this.add(fill);

      fgColor = new ColorButton(paintPanel.getDrawColor(), "", paintPanel, "Foreground Color", "fgColor");
      this.add(fgColor);
      fgColor.addPropertyChangeListener(this);

      this.addSeparator();

      font = new FontChooserPanel(paintPanel.getFont(), "font");
      font.addPropertyChangeListener(this);
      this.add(font);

      this.addSeparator();

      stroke = new StrokeChooserPanel(paintPanel.getStroke(), "stroke");
      stroke.addPropertyChangeListener(this);
      this.add(stroke);

      alpha = new JSlider(JSlider.HORIZONTAL, 0, 255, (int) (paintPanel.getAlpha() * 255));
      alpha.addChangeListener(this);
      alpha.setPreferredSize(new Dimension(100, 24));
      this.add(alpha);
   }

   public void propertyChange(PropertyChangeEvent evt) 
   {
      if (evt.getPropertyName().equals("fgColor")) 
      {
         paintPanel.setDrawColor((Color) evt.getNewValue());
      }
      if (evt.getPropertyName().equals("pickcolor")) 
      {
         fgColor.setColor((Color) evt.getNewValue());
         fgColor.repaint();
      }
      if (evt.getPropertyName().equals("font")) 
      {
         paintPanel.setFont((Font) evt.getNewValue());
      }
      if (evt.getPropertyName().equals("stroke")) 
      {
         paintPanel.setStroke((Stroke) evt.getNewValue());
      }
//    if (evt.getPropertyName().equals("selection")) {
//      paintPanel.setArcWidth(((int[]) evt.getNewValue())[0]);
//      paintPanel.setArcHeight(((int[]) evt.getNewValue())[1]);
//    }
   }

   public void actionPerformed(ActionEvent e) 
   {
      if (e.getActionCommand().equals("anti")) 
      {
         anti.setSelected(anti.isSelected());
         paintPanel.setAntialiased(anti.isSelected());
      }
      if (e.getActionCommand().equals("fill")) 
      {
         fill.setSelected(fill.isSelected());
         paintPanel.setFilled(fill.isSelected());
      }
   }

   public void stateChanged(ChangeEvent e) 
   {
      if (e.getSource().equals(alpha)) 
      {
         float newVal = (float) (alpha.getValue()) / 255.0f;
         paintPanel.setAlpha(newVal);
      }
   }
}
