package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.util;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

/**
 * A JDialog that displays PropertiesGUIField's.
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class PropertiesGUI extends JDialog {
   private ArrayList fields;

   public PropertiesGUI(Frame owner, String title, boolean modal) throws HeadlessException {
      super(owner, title, modal);

      fields = new ArrayList();
      this.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
   }

   public void addPropertiesGUIField(PropertiesGUIField field) {
      fields.add(field);
   }

   public void buildGUI() {
      JPanel contents = new JPanel();
      contents.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
      contents.setLayout(new GridLayout(fields.size(), 2, 5, 5));
      for (int i = 0; i < fields.size(); i++) {
         PropertiesGUIField guiField = (PropertiesGUIField) fields.get(i);
         JLabel label = guiField.getLabel();
         JPanel components = guiField.getLine();
         contents.add(label);
         contents.add(components);
      }
      this.setContentPane(contents);
      this.pack();
      this.setLocationRelativeTo(this.getOwner());
   }

}
