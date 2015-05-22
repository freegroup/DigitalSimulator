package de.freegroup.digitalsimulator.plugin.switchondelay;

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
import java.awt.event.*;
import de.freegroup.digitalsimulator.WinUtil;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.dialogs.GenericDialog;
import de.freegroup.ui.spinner.IntegerSpinner;

public class DelayDialog extends GenericDialog 
{
  IntegerSpinner delayInput   = null;
  int            delay        = 1;

  public DelayDialog(int delay)
  {
    super(I18N.get("COMMON.DIALOGHEADER.OBJECTSWITCHONDELAYDIALOG"),
      I18N.get("OBJECTSWITCHONDELAYDIALOG.LABEL.HELPHEADER"),
      I18N.get("OBJECTSWITCHONDELAYDIALOG.LABEL.HELPLINE01"),
      I18N.get("OBJECTSWITCHONDELAYDIALOG.LABEL.HELPLINE02"));
    this.delay = Math.max(1,delay);
    show(500,250);
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

    builder.addLabel(I18N.get("OBJECTSWITCHONDELAYDIALOG.LABEL.DELAY") , cc.xy  (2, 2));
    builder.add(delayInput                                     , cc.xy  (4, 2));
    return builder.getPanel();
  }
  
  /* (non-Javadoc)
   * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#initComponents()
   */
  public void initComponents()
  {
    delayInput = new IntegerSpinner(1,500,1,delay);
  }
  
  public int getDelay()
  {
    return delayInput.getValue();
  }

  public static void main(String[] args)
  {
    new DelayDialog(10);
  }

  public void onOk()
  {
  }

  public void onCancel()
  {
  }
}
