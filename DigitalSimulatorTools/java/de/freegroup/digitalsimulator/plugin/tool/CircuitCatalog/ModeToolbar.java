package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

/**
 * A JToolBar used to change the mode of a PaintPanel.
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class ModeToolbar extends JToolBar implements PropertyChangeListener, ActionListener {
   private JToggleButton select;
   private JToggleButton line;
   private JToggleButton scribble;
   private JToggleButton rect;
   private JToggleButton oval;
   private JToggleButton text;
   private JToggleButton erase;
   private JToggleButton flood;
   private JToggleButton point;
   private JToggleButton arrow;
   private JToggleButton colorpick;


   private PaintPanel paintPanel;

   public ModeToolbar(PaintPanel paintPanel) {
      this.paintPanel = paintPanel;
      initModeButtons();
   }

   public void initModeButtons() {
      ImageIcon icon = new ImageIcon(this.getClass().getResource("graphics/select.png"));
      select = new JToggleButton(icon);
      select.setActionCommand("select");
      select.addActionListener(this);
      this.add(select);

      icon = new ImageIcon(this.getClass().getResource("graphics/line.png"));
      line = new JToggleButton(icon);
      line.setActionCommand("line");
      line.addActionListener(this);
      line.setSelected(true);
      this.add(line);

      icon = new ImageIcon(this.getClass().getResource("graphics/scribble.png"));
      scribble = new JToggleButton(icon);
      scribble.setActionCommand("scribble");
      scribble.addActionListener(this);
      this.add(scribble);

      icon = new ImageIcon(this.getClass().getResource("graphics/rect.png"));
      rect = new JToggleButton(icon);
      rect.setActionCommand("rect");
      rect.addActionListener(this);
      this.add(rect);

      icon = new ImageIcon(this.getClass().getResource("graphics/oval.png"));
      oval = new JToggleButton(icon);
      oval.setActionCommand("oval");
      oval.addActionListener(this);
      this.add(oval);

      icon = new ImageIcon(this.getClass().getResource("graphics/text.png"));
      text = new JToggleButton(icon);
      text.setActionCommand("text");
      text.addActionListener(this);
      this.add(text);

      icon = new ImageIcon(this.getClass().getResource("graphics/arrow.png"));
      arrow = new JToggleButton(icon);
      arrow.setActionCommand("arrow");
      arrow.addActionListener(this);
      this.add(arrow);

      this.addSeparator();

      icon = new ImageIcon(this.getClass().getResource("graphics/point.png"));
      point = new JToggleButton(icon);
      point.setActionCommand("point");
      point.addActionListener(this);
      this.add(point);

      icon = new ImageIcon(this.getClass().getResource("graphics/flood.png"));
      flood = new JToggleButton(icon);
      flood.setActionCommand("flood");
      flood.addActionListener(this);
      this.add(flood);

      icon = new ImageIcon(this.getClass().getResource("graphics/erase.png"));
      erase = new JToggleButton(icon);
      erase.setActionCommand("erase");
      erase.addActionListener(this);
      this.add(erase);

      icon = new ImageIcon(this.getClass().getResource("graphics/colorpick.png"));
      colorpick = new JToggleButton(icon);
      colorpick.setActionCommand("colorpick");
      colorpick.addActionListener(this);
      this.add(colorpick);


   }

   public void propertyChange(PropertyChangeEvent evt) {

      if (evt.getPropertyName().equals("fgColor")) {
         paintPanel.setDrawColor((Color) evt.getNewValue());
      }
      if (evt.getPropertyName().equals("font")) {
         paintPanel.setFont((Font) evt.getNewValue());
      }
      if (evt.getPropertyName().equals("mode")) {
         int val = ((Integer) evt.getNewValue()).intValue();

         select.setSelected(false);
         line.setSelected(false);
         scribble.setSelected(false);
         rect.setSelected(false);
         oval.setSelected(false);
         text.setSelected(false);
         erase.setSelected(false);
         flood.setSelected(false);
         point.setSelected(false);
         arrow.setSelected(false);
         colorpick.setSelected(false);


         if (val == PaintPanel.MODE_SELECT) {
            select.setSelected(true);

         }
         if (val == PaintPanel.MODE_LINE) {
            line.setSelected(true);
         }
         if (val == PaintPanel.MODE_SCRIBBLE) {
            scribble.setSelected(true);
         }
         if (val == PaintPanel.MODE_RECT) {
            rect.setSelected(true);
         }
         if (val == PaintPanel.MODE_OVAL) {
            oval.setSelected(true);
         }
         if (val == PaintPanel.MODE_TEXT) {
            text.setSelected(true);

         }
         if (val == PaintPanel.MODE_QUADARROW) {
            arrow.setSelected(true);

         }
         if (val == PaintPanel.MODE_ERASE) {
            erase.setSelected(true);
         }
         if (val == PaintPanel.MODE_FLOOD) {
            flood.setSelected(true);
         }
         if (val == PaintPanel.MODE_POINT) {
            point.setSelected(true);
         }
         if (val == PaintPanel.MODE_COLORPICK) {
            colorpick.setSelected(true);
         }
         this.revalidate();

      }
   }


   public void actionPerformed(ActionEvent e) {
      if (e.getActionCommand().equals("select")) {
         paintPanel.setCurrentMode(PaintPanel.MODE_SELECT);
      }
      if (e.getActionCommand().equals("line")) {
         paintPanel.setCurrentMode(PaintPanel.MODE_LINE);
      }
      if (e.getActionCommand().equals("scribble")) {
         paintPanel.setCurrentMode(PaintPanel.MODE_SCRIBBLE);
      }
      if (e.getActionCommand().equals("rect")) {
         paintPanel.setCurrentMode(PaintPanel.MODE_RECT);
      }
      if (e.getActionCommand().equals("oval")) {
         paintPanel.setCurrentMode(PaintPanel.MODE_OVAL);
      }
      if (e.getActionCommand().equals("text")) {
         paintPanel.setCurrentMode(PaintPanel.MODE_TEXT);
      }
      if (e.getActionCommand().equals("erase")) {
         paintPanel.setCurrentMode(PaintPanel.MODE_ERASE);
      }

      if (e.getActionCommand().equals("flood")) {
         paintPanel.setCurrentMode(PaintPanel.MODE_FLOOD);
      }
      if (e.getActionCommand().equals("point")) {
         paintPanel.setCurrentMode(PaintPanel.MODE_POINT);
      }
      if (e.getActionCommand().equals("arrow")) {
         paintPanel.setCurrentMode(PaintPanel.MODE_QUADARROW);
      }
      if (e.getActionCommand().equals("colorpick")) {
         paintPanel.setCurrentMode(PaintPanel.MODE_COLORPICK);
      }


   }
}
