package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.util;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.Properties;

/**
 * A collection of a JLabel and a JPanel that contains all that is needed to fiddle with
 * fields of a properties file. There is some type checking and in conjunction with a PropertiesGUI
 * will create quick dialogs to edit Properties objects.
 *
 * Note that PropertyChangeListeners added to this object will actually be added to the component that
 * handles the changing of the property. This may be a JTextFiels, a JCheckBox, or a ColorButton depending
 * on the type of this PropertiesGUIField.
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class PropertiesGUIField implements ActionListener, FocusListener, ChangeListener, PropertyChangeListener {

   public static final int TYPE_STRING = 0;
   public static final int TYPE_DOUBLE = 1;
   public static final int TYPE_INT = 2;
   public static final int TYPE_COLOR = 3;

   public static final int TYPE_BOOLEAN = 12;




   private Properties properties;
   private String fieldName;
   private int fieldType;


   private JLabel label;
   private JPanel line;
   private JComponent component;


   public PropertiesGUIField(Properties properties, String fieldName, int fieldType) {
      this.properties = properties;
      this.fieldName = fieldName;
      this.fieldType = fieldType;

      label = new JLabel(fieldName);
      this.buildComponents();

   }

   public JLabel getLabel() {
      return label;
   }

   public void setLabel(JLabel label) {
      this.label = label;
   }

   public JPanel getLine() {
      return line;
   }

   public JComponent getComponent() {
      return component;
   }

   public Properties getProperties() {
      return properties;
   }

   public String getFieldName() {
      return fieldName;
   }

   public int getFieldType() {
      return fieldType;
   }

   public void addPropertyChangeListener(PropertyChangeListener listener) {
      component.addPropertyChangeListener(listener);
   }

   protected void buildComponents() {
      line = new JPanel();
      line.setLayout(new BoxLayout(line, BoxLayout.X_AXIS));
      if (fieldType == PropertiesGUIField.TYPE_STRING) {
         JTextField text = new JTextField(this.getStringProperty());
         text.addActionListener(this);
         text.addFocusListener(this);
         component = text;
         line.add(text);
      }
      if (fieldType == PropertiesGUIField.TYPE_INT) {
         JTextField text = new JTextField("" + this.getIntProperty());
         text.addActionListener(this);
         text.addFocusListener(this);
         component = text;
         line.add(text);
      }
      if (fieldType == PropertiesGUIField.TYPE_DOUBLE) {
         JTextField text = new JTextField("" + this.getDoubleProperty());
         text.addActionListener(this);
         text.addFocusListener(this);
         component = text;
         line.add(text);
      }
      if (fieldType == PropertiesGUIField.TYPE_BOOLEAN) {
         JCheckBox box = new JCheckBox("", this.getBooleanProperty());
         box.addChangeListener(this);
         component = box;
         line.add(box);
      }
      if (fieldType == PropertiesGUIField.TYPE_COLOR) {
         Color color = new Color(this.getIntProperty());
         ColorButton colorB = new ColorButton(color, null, component, label.getText(), "colorchanged");
         colorB.addPropertyChangeListener(this);
         component = colorB;
         line.add(colorB);
      }


   }


   public void actionPerformed(ActionEvent e) {
      if (fieldType == PropertiesGUIField.TYPE_STRING) {
         String text = ((JTextField) component).getText();
         properties.setProperty(fieldName, text);
      }
      if (fieldType == PropertiesGUIField.TYPE_INT) {
         String text = ((JTextField) component).getText();
         try {
            int val = Integer.parseInt(text);
            component.firePropertyChange(fieldName, this.getIntProperty(), val);
            properties.setProperty(fieldName, "" + val);

         }
         catch (NumberFormatException e1) {
            JOptionPane.showMessageDialog(component, "You must enter an integer!");
            ((JTextField) component).setText("" + this.getIntProperty());

         }
      }
      if (fieldType == PropertiesGUIField.TYPE_DOUBLE) {
         String text = ((JTextField) component).getText();
         try {
            double val = Double.parseDouble(text);
            component.firePropertyChange(fieldName, this.getDoubleProperty(), val);
            properties.setProperty(fieldName, "" + val);
         }
         catch (NumberFormatException e1) {
            JOptionPane.showMessageDialog(component, "You must enter an number!");
            ((JTextField) component).setText("" + this.getDoubleProperty());

         }
      }
   }

   public void focusGained(FocusEvent e) {

   }

   public void focusLost(FocusEvent e) {
      if (fieldType == PropertiesGUIField.TYPE_STRING) {
         String text = ((JTextField) component).getText();
         properties.setProperty(fieldName, text);
      }
      if (fieldType == PropertiesGUIField.TYPE_INT) {
         String text = ((JTextField) component).getText();
         try {
            int val = Integer.parseInt(text);
            component.firePropertyChange(fieldName, this.getIntProperty(), val);
            properties.setProperty(fieldName, "" + val);
         }
         catch (NumberFormatException e1) {
            JOptionPane.showMessageDialog(component, "You must enter an integer!");
            ((JTextField) component).setText("" + this.getIntProperty());

         }
      }
      if (fieldType == PropertiesGUIField.TYPE_DOUBLE) {
         String text = ((JTextField) component).getText();
         try {
            double val = Double.parseDouble(text);
            component.firePropertyChange(fieldName, this.getDoubleProperty(), val);
            properties.setProperty(fieldName, "" + val);
         }
         catch (NumberFormatException e1) {
            JOptionPane.showMessageDialog(component, "You must enter an number!");
            ((JTextField) component).setText("" + this.getDoubleProperty());

         }
      }

   }

   public void stateChanged(ChangeEvent e) {
      if (fieldType == PropertiesGUIField.TYPE_BOOLEAN) {
         JCheckBox box = (JCheckBox) component;
         component.firePropertyChange(fieldName, this.getBooleanProperty(), box.isSelected());
         properties.setProperty(fieldName, "" + box.isSelected());

      }
   }

   public void propertyChange(PropertyChangeEvent evt) {

      if (fieldType == PropertiesGUIField.TYPE_COLOR && evt.getPropertyName().equals("colorchanged")) {
         ColorButton colorB = (ColorButton) component;
         colorB.firePropertyChange(fieldName, ((Color) evt.getOldValue()).getRGB(), ((Color) evt.getNewValue()).getRGB());
         properties.setProperty(fieldName, "" + ((Color) evt.getNewValue()).getRGB());

      }
   }

   public String getStringProperty() {
      return properties.getProperty(fieldName);
   }

   public int getIntProperty() {
      return Integer.parseInt(properties.getProperty(fieldName));
   }

   public double getDoubleProperty() {
      return Double.parseDouble(properties.getProperty(fieldName));
   }

   public boolean getBooleanProperty() {
      return Boolean.valueOf(properties.getProperty(fieldName)).booleanValue();
   }


}
