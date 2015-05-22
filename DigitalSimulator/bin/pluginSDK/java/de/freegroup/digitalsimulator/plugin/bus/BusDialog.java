package de.freegroup.digitalsimulator.plugin.bus;

/**
 * Title:        DigitalSimulator java Pugins
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import java.awt.*;

import javax.swing.*;

import com.jgoodies.forms.builder.PanelBuilder;
import com.jgoodies.forms.debug.FormDebugPanel;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import de.freegroup.digitalsimulator.Configuration;
import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.WinUtil;
import java.awt.event.*;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.dialogs.GenericDialog;
import de.freegroup.ui.spinner.IntegerSpinner;

public class BusDialog extends GenericDialog
{
    IntegerSpinner    busId   = null;
    int id = 1;
    public BusDialog(int _id)
    {
      super(I18N.get("COMMON.DIALOGHEADER.OBJECTBUSDIALOG"),
            I18N.get("OBJECTBUSDIALOG.LABEL.HELPHEADER"),
            I18N.get("OBJECTBUSDIALOG.LABEL.HELPLINE01"),
            I18N.get("OBJECTBUSDIALOG.LABEL.HELPLINE02"));
      id = _id;
      show(600,450);
    }
  
    public byte getBusId()
    {
        return (byte)busId.getValue();
    }
  
    public static void main(String[] args)
    {
        new BusDialog(10);
    }
  
    public void onOk()
    {
    }
  
    public void onCancel()
    {
    }
    
    /* (non-Javadoc)
     * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#buildInputPanel()
     */
    public Component buildInputPanel()
    {
      FormLayout layout = new FormLayout(
          "5dlu,right:100dlu:grow,5dlu 50dlu",    // cols
          "10dlu, p,10dlu");      // rows
      
      PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
      if(debug)
        builder = new PanelBuilder(new FormDebugPanel(),layout);
      builder.setDefaultDialogBorder();

      CellConstraints cc = new CellConstraints();

      builder.addLabel(I18N.get("OBJECTBUSDIALOG.LABEL.BUSID") , cc.xy  (2, 2));
      builder.add(busId                                        , cc.xy  (4, 2));
      return builder.getPanel();
    }
    
    /* (non-Javadoc)
     * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#initComponents()
     */
    public void initComponents()
    {
    	busId = new IntegerSpinner(1,100,1,id);
    }
}
