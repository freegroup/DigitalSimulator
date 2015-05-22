package de.freegroup.digitalsimulator.plugin.tool.LiveUpdate;
/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */


import java.awt.*;

import javax.swing.*;
import java.awt.event.*;
import javax.swing.event.*;
import javax.swing.text.html.HTMLEditorKit;

import de.freegroup.digitalsimulator.Configuration;
import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.ui.*;
import de.freegroup.ui.editor.JEditTextArea;

import javax.swing.border.*;

import com.jgoodies.forms.builder.PanelBuilder;
import com.jgoodies.forms.debug.FormDebugPanel;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import de.freegroup.digitalsimulator.dialogs.GenericDialog;
import de.freegroup.digitalsimulator.dialogs.MsgBox;
import de.freegroup.digitalsimulator.ui.HGradient;

public class StatusReportDialog extends GenericDialog 
{
    protected JEditorPane report    = null;
    protected String message = "";

    public static void main(String[] args)
		{
			new StatusReportDialog("Dies <font color=\"FF0000\" ><b>ist</b></font> ein Text\nmit mehr als einer<br>Zeile",true);
		}
    
    public StatusReportDialog(String message, boolean restartRequired) 
    {
      super(I18N.get("COMMON.DIALOGHEADER.LIVEUPDATEREPORT"),
            I18N.get("LIVEUPDATEREPORT.LABEL.HELPHEADER_"+restartRequired),
            I18N.get("LIVEUPDATEREPORT.LABEL.HELPLINE01_"+restartRequired),
            I18N.get("LIVEUPDATEREPORT.LABEL.HELPLINE02_"+restartRequired));
       this.message = message;
       this.withCancelButton = false;
       show(630,450);
    }
  /* (non-Javadoc)
   * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#initComponents()
   */
  public void initComponents()
  {
    report = new JEditorPane();
    report.setEditorKit(new HTMLEditorKit());
    report.setText(message);
    report.setEditable(false);
  }

/* (non-Javadoc)
	 * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#buildInputPanel()
	 */
	public Component buildInputPanel()
	{
    FormLayout layout = new FormLayout(
        "fill:100dlu:grow", 
        "fill:100dlu:grow");  
   
    PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
    if(debug)
      builder = new PanelBuilder(new FormDebugPanel(),layout);
    builder.setDefaultDialogBorder();

    CellConstraints cc = new CellConstraints();
    builder.add(new JScrollPane(report) , cc.xy(1, 1));
    
    return builder.getPanel();
  }


	/* (non-Javadoc)
	 * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#onCancel()
	 */
	public void onCancel()
	{
	}

	/* (non-Javadoc)
	 * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#onOk()
	 */
	public void onOk()
	{
 	}
}