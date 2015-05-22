package de.freegroup.digitalsimulator.plugin.export;


import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import javax.swing.event.*;

import de.freegroup.digitalsimulator.Configuration;
import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.ui.*;
import javax.swing.border.*;

import com.jgoodies.forms.builder.PanelBuilder;
import com.jgoodies.forms.debug.FormDebugPanel;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import java.util.*;
import java.util.Collections;

import de.freegroup.digitalsimulator.dialogs.GenericDialog;
import de.freegroup.digitalsimulator.dialogs.MsgBox;
import de.freegroup.digitalsimulator.plugin.export.*;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */

public class SelectExportModulDialog extends GenericDialog 
{
    JTextArea descText = new JTextArea();

    JList exportList = new JList();
    JTextArea beschreibung = new JTextArea();
    JScrollPane scrollPane1 = new JScrollPane();
    Vector      transformers = new Vector();
    IExport transformer=null;

    public static void main(String[] args)
    {
        ExportManager.registerExportModul(TestExportModul.class.getName());
        SelectExportModulDialog dlg =new SelectExportModulDialog();
    }

    protected SelectExportModulDialog() {
      super(I18N.get("COMMON.DIALOGHEADER.EXPORTDIALOG"),
        I18N.get("EXPORTDIALOG.LABEL.HELPHEADER"),
        I18N.get("EXPORTDIALOG.LABEL.HELPLINE01"),
        I18N.get("EXPORTDIALOG.LABEL.HELPLINE02"),
        true /*with icon*/);
      
      show(680,550);
    }

    public void initComponents()
    {
        beschreibung.setEditable(false);
        beschreibung.setText("");
        beschreibung.setRequestFocusEnabled(false);

        scrollPane1.getViewport().add(beschreibung, null);
        beschreibung.setBorder(new BevelBorder(BevelBorder.RAISED));
        // selection panel
        //
        Iterator iter = new Vector(ExportManager.getExportModuls().keySet()).iterator();
        Vector plugins = new Vector();
        while(iter.hasNext())
        {
          String transId = iter.next().toString();
          transformers.add(ExportManager.getModul(transId));
          plugins.add(I18N.get(transId)); 
        }
        Object []data = plugins.toArray();
        exportList = new JList(data);
        exportList.setBorder(new BevelBorder(BevelBorder.RAISED));
        exportList.addListSelectionListener(new javax.swing.event.ListSelectionListener()
        {
            public void valueChanged(ListSelectionEvent e)
            {
                exportList_valueChanged(e);
            }
        });
        // Retrieve the last selected export modul from the config file.
        // This export modul will be preselect. Friendly GUI :-)
        //
        int selectedIndex = Configuration.getInt("SelectExportModulDialog.selectedIndex",0);
        exportList.setSelectedIndex(selectedIndex);
        exportList_valueChanged(null);
    }

    /* (non-Javadoc)
     * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#buildInputPanel()
     */
    public Component buildInputPanel()
    {
      FormLayout layout = new FormLayout(
          "p,5dlu,fill:p:grow",    // cols
          "p,3dlu,fill:p:grow");          // rows
      
      PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
      if(debug)
        builder = new PanelBuilder(new FormDebugPanel(),layout);
      //builder.setDefaultDialogBorder();

      CellConstraints cc = new CellConstraints();

      builder.addLabel(I18N.get("EXPORTDIALOG.LABEL.MODUL"), cc.xy(1,1));
      builder.addLabel(I18N.get("EXPORTDIALOG.LABEL.DESCRIPTION"), cc.xy(3,1));
      builder.add(exportList, cc.xy(1,3));
      builder.add(beschreibung, cc.xy(3,3));
      return builder.getPanel();
    }

    public IExport getTransformer()
    {
      return transformer;
    }

    public void onCancel()
    {
    }

    /**
     * This method will be called if the user press the OK-button.
     * Save required configuration data for the next startup or/and
     * start the selected action
     * 
     */
    public void onOk()
    {
      // write the selected export selection to the configuration
      // At the next startup the dialog will preselect this export 
      // modul.
      Configuration.setString("SelectExportModulDialog.selectedIndex",""+exportList.getSelectedIndex());
    }


    void exportList_valueChanged(ListSelectionEvent e) 
    {
      if(e==null || e.getValueIsAdjusting())
      {
        int index = exportList.getSelectedIndex();
        Trace.info("Index of selection:"+index);
      	transformer = (IExport)transformers.get(index);
      	Trace.info(transformer.getClass().getName());
        beschreibung.setText(I18N.get(transformer.getDescription()));
        try {setHelpIcon(transformer.getIcon());}
				catch (Throwable e1)
				{/*ignore*/}
      }
   }
}