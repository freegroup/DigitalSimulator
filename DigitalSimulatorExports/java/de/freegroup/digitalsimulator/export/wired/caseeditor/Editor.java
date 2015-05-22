package de.freegroup.digitalsimulator.export.wired.caseeditor;


import java.awt.Component;
import java.util.HashMap;
import java.util.Vector;

import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextArea;
import javax.swing.border.BevelBorder;
import javax.swing.event.ListSelectionEvent;

import com.jgoodies.forms.builder.PanelBuilder;
import com.jgoodies.forms.debug.FormDebugPanel;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import de.freegroup.digitalsimulator.Configuration;
import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.dialogs.GenericDialog;
import de.freegroup.digitalsimulator.export.wired.db.CaseLayout;
import de.freegroup.digitalsimulator.export.wired.db.ElectricCase;
import de.freegroup.digitalsimulator.export.wired.db.ElectricObject;
import de.freegroup.digitalsimulator.plugin.export.ExportManager;
import de.freegroup.digitalsimulator.plugin.export.IExport;


/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */

public class Editor extends GenericDialog 
{
    JList     caseList   = null;
    JList     objectList = null;
    StackPane caseTab    = null;
    StackPane objectTab  = null;
  
    public static void main(String[] args)
    {
        new Editor();
        System.exit(1);
    }

    protected Editor() 
    {
      super(I18N.get("COMMON.DIALOGHEADER.EXPORTDIALOG"),
        I18N.get("EXPORTDIALOG.LABEL.HELPHEADER"),
        I18N.get("EXPORTDIALOG.LABEL.HELPLINE01"),
        I18N.get("EXPORTDIALOG.LABEL.HELPLINE02"));
      
      show(680,550);
    }

    public void initComponents()
    {
      caseList   = new JList();
      objectList = new JList();
      caseTab    = new StackPane();
      objectTab  = new StackPane();
      
      // fill the case data
      //
      Object []caseData = ElectricCase.getAll().toArray();
      caseList = new JList(caseData);
      caseList.setBorder(new BevelBorder(BevelBorder.RAISED));
      caseList.addListSelectionListener(new javax.swing.event.ListSelectionListener()
      {
          public void valueChanged(ListSelectionEvent e)
          {
              caseList_valueChanged(e);
          }
      });
      // Retrieve the last selected export modul from the config file.
      // This export modul will be preselect. Friendly GUI :-)
      //
      caseList.setSelectedIndex(Configuration.getInt("CaseEditor.selectedIndex",0));
      caseList_valueChanged(null);
      
      // add all views for each ElectricCase
      //
      for(int i = 0; i<caseData.length; i++)
      {
        caseTab.add(new CaseView((ElectricCase)caseData[i]),""+i);
      }
        
      
      // fill the object data
      //
      Object []objectData = ElectricObject.getAll().toArray();
      objectList = new JList(objectData);
      objectList.setBorder(new BevelBorder(BevelBorder.RAISED));
      objectList.addListSelectionListener(new javax.swing.event.ListSelectionListener()
          {
        public void valueChanged(ListSelectionEvent e)
        {
          objectList_valueChanged(e);
        }
      });
      // Retrieve the last selected export modul from the config file.
      // This export modul will be preselect. Friendly GUI :-)
      //
      objectList.setSelectedIndex(Configuration.getInt("CaseEditor.selectedIndex",0));
      objectList_valueChanged(null);
      
      // add all views for each ElectricCase
      //
      for(int i = 0; i<objectData.length; i++)
      {
        objectTab.add(new ObjectView((ElectricObject)objectData[i]),""+i);
      }
      }

    /* (non-Javadoc)
     * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#buildInputPanel()
     */
    public Component buildInputPanel()
    {
      // create the tab-pane component
      //
      JTabbedPane tabbedPane = new JTabbedPane();
      tabbedPane.putClientProperty("jgoodies.noContentBorder", Boolean.TRUE);
      tabbedPane.add(buildObjectPanel() ,  "Object");
      tabbedPane.add(buildCasePanel()   ,  "Case");
      return tabbedPane;
    }
    
    /* (non-Javadoc)
     * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#buildInputPanel()
     */
    public Component buildCasePanel()
    {
      FormLayout layout = new FormLayout(
          "p,5dlu,fill:p:grow",    // cols
          "p,3dlu,fill:p:grow");          // rows
      
      PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
      if(debug)
        builder = new PanelBuilder(new FormDebugPanel(),layout);
      builder.setDefaultDialogBorder();

      CellConstraints cc = new CellConstraints();
      
      builder.addLabel(I18N.get("EXPORTDIALOG.LABEL.MODUL"), cc.xy(1,1));
      builder.addLabel(I18N.get("EXPORTDIALOG.LABEL.DESCRIPTION"), cc.xy(3,1));
      builder.add(new JScrollPane(caseList), cc.xy(1,3));
      builder.add(caseTab, cc.xy(3,3,"fill,fill"));
      
      return builder.getPanel();
    }

    /* (non-Javadoc)
     * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#buildInputPanel()
     */
    public Component buildObjectPanel()
    {
      FormLayout layout = new FormLayout(
          "p,5dlu,fill:p:grow",    // cols
          "p,3dlu,fill:p:grow");          // rows
      
      PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
      if(debug)
        builder = new PanelBuilder(new FormDebugPanel(),layout);
      builder.setDefaultDialogBorder();

      CellConstraints cc = new CellConstraints();
      
      builder.addLabel(I18N.get("EXPORTDIALOG.LABEL.MODUL"), cc.xy(1,1));
      builder.addLabel(I18N.get("EXPORTDIALOG.LABEL.DESCRIPTION"), cc.xy(3,1));
      builder.add(new JScrollPane(objectList), cc.xy(1,3));
      builder.add(objectTab, cc.xy(3,3,"fill,fill"));
      
      return builder.getPanel();
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
      Configuration.setString("CaseEditor.selectedIndex",""+caseList.getSelectedIndex());
      
      // save all cases
      //
      for(int i = 0; i<caseTab.getComponentCount();i++)
      {
        CaseView view = (CaseView)caseTab.getComponent(i);
        view.save();
      }

      // save all objects
      //
      for(int i = 0; i<caseTab.getComponentCount();i++)
      {
        ObjectView view = (ObjectView)objectTab.getComponent(i);
        view.save();
      }
    }


    void caseList_valueChanged(ListSelectionEvent e) 
    {
      if(e==null || e.getValueIsAdjusting())
      {
        int index = caseList.getSelectedIndex();
        caseTab.showCard(""+index);
      }
    }
    void objectList_valueChanged(ListSelectionEvent e) 
    {
      if(e==null || e.getValueIsAdjusting())
      {
        int index = objectList.getSelectedIndex();
        objectTab.showCard(""+index);
      }
    }
 }