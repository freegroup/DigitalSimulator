package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.util;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


/**
 * Currently only provides a JSpinner to set a Basic Strokes width.
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class StrokeChooserPanel extends JPanel implements ActionListener, ChangeListener {
   private JSpinner strokeWidth;
   private String propName;
   private Stroke stroke;


   public StrokeChooserPanel(Stroke stroke, String propName) {
      super();
      this.propName = propName;
      this.setStroke(stroke);
      this.add(getStrokeWidthSpinner());

   }

   public StrokeChooserPanel(String propName) {
      this(new BasicStroke(1.0f), propName);

   }

   public Stroke getStroke() {
      return stroke;
   }

   public void setStroke(Stroke stroke) {
      this.stroke = stroke;
   }


   public JSpinner getStrokeWidthSpinner() {
      SpinnerNumberModel model = new SpinnerNumberModel(1.0, 0.5, 100.0, 0.5);
      strokeWidth = new JSpinner(model);
      strokeWidth.addChangeListener(this);
      return strokeWidth;
   }


   public void actionPerformed(ActionEvent e) {
      Stroke oldS = this.getStroke();
      this.setStroke(new BasicStroke(((Double) strokeWidth.getModel().getValue()).floatValue()));
      this.firePropertyChange(propName, oldS, this.getStroke());
   }

   public void stateChanged(ChangeEvent e) {
      Stroke oldS = this.getStroke();
      this.setStroke(new BasicStroke(((Double) strokeWidth.getModel().getValue()).floatValue()));
      this.firePropertyChange(propName, oldS, this.getStroke());
   }


}
