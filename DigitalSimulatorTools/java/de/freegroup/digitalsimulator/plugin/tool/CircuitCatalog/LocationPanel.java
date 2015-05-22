package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog;

import javax.swing.*;
import java.awt.*;

/**
 * Provides an JLabel used to draw the x,y location of the mouse pointer.
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class LocationPanel extends JPanel {
   private JLabel label;
   private String nullText;

   public LocationPanel(String nullText) {
      this.setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
      this.nullText = nullText;
      label = new JLabel(nullText);

      this.add(Box.createHorizontalGlue());
      this.add(label);

   }

   public void updateLocation(Point point) {
      if (point != null) {
         label.setText("(" + point.x + ", " + point.y + ")");
      }
      else {
         label.setText(nullText);
      }
   }
}
