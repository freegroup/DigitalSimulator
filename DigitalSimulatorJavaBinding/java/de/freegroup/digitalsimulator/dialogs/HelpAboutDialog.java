/*
 * Created on Dec 16, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.dialogs;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.Set;
import java.util.Vector;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.table.DefaultTableModel;

import com.jgoodies.forms.builder.ButtonBarBuilder;
import com.jgoodies.forms.builder.PanelBuilder;
import com.jgoodies.forms.debug.FormDebugPanel;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import de.freegroup.digitalsimulator.Application;
import de.freegroup.digitalsimulator.Configuration;
import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.WinUtil;
import de.freegroup.digitalsimulator.ui.DialogInfoHeader;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class HelpAboutDialog extends JDialog
{
  JLabel  developerField        = null;
  JLabel  emailField            = null;
  JLabel  urlField              = null;
  
  JLabel  groupField            = null;
  JLabel  versionField          = null;
  JLabel  nameField             = null;

  JButton     okButton          = null;
  boolean debug = !Application.isRunningInDigiSim();
  
  public static void main(String[] args)
  {
    new HelpAboutDialog();
  }
  
  public HelpAboutDialog()
  {
    super((Frame)null,I18N.get("COMMON.DIALOGHEADER.HELPABOUT"),true);
   
    JComponent panel = buildPanel();
    
    getContentPane().add(panel);
    pack();
    
    Dimension dim = java.awt.Toolkit.getDefaultToolkit().getScreenSize();
    // set the default width ans height
    //
    int w = 500;
    int h = 400;
    
    // center the window
    //
    int x = (dim.width-w)/2;
    int y = (dim.height-h)/2;
    
    setBounds(x, y, w, h);
    WinUtil.setWindowAlwaysOnTop(getTitle());
    show();  
  }
  

  /**
   * 
   * @return
   */
  public JComponent buildPanel()
  {
    // Separating the component initialization and configuration
    // from the layout code makes both parts easier to read.
    initComponents();

    // create the tab-pane component
    //
    JTabbedPane tabbedPane = new JTabbedPane();
    tabbedPane.putClientProperty("jgoodies.noContentBorder", Boolean.TRUE);
    tabbedPane.add(buildProgramInfoPanel() ,  I18N.get("HELPABOUT.TAB.PROGRAM"));
    tabbedPane.add(buildSystemInfoPanel()  ,  I18N.get("HELPABOUT.TAB.SYSTEM"));

    // create the button bar
    //
    ButtonBarBuilder buttonBuilder = new ButtonBarBuilder();
    buttonBuilder.addGlue();
    buttonBuilder.addGridded(okButton);
   
    return wrap(buttonBuilder.getPanel(),tabbedPane);
  }
  
  /**
   * 
   *
   */
  private void initComponents()
  {
    developerField    = new JLabel();
    emailField        = new JLabel();
    urlField          = new JLabel();
    versionField      = new JLabel();
    groupField        = new JLabel();
    nameField         = new JLabel();
    
    okButton = new JButton(I18N.get("COMMON.BUTTON.OK"));
    okButton.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        okButton_actionPerformed(e);
      }
    });
  }
  
  /**
   * 
   * @return
   */
  private Component buildProgramInfoPanel()
  {
    FormLayout layout = new FormLayout(
        "3dlu, fill:p:grow",                              // cols
        "p, 3dlu,p, 3dlu, p, 3dlu, p, fill:p:grow");    // rows
    
    PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
    if(debug)
      builder = new PanelBuilder(new FormDebugPanel(),layout);
    builder.setDefaultDialogBorder();

    CellConstraints cc = new CellConstraints();
    String version = Configuration.getString("ApplicationVersion");
    
    builder.addLabel("DigtalSimulator Version "+version,             cc.xy  (2,  3));
    builder.addLabel("Copyright 2003 FreeGroup Andreas Herz, www.FreeGroup.de",  cc.xy  (2,  5));
   
    return builder.getPanel();
  }
  
  
  /**
   * 
   * @return
   */
  private Component buildSystemInfoPanel()
  {
    Object[][] data = new Object[System.getProperties().entrySet().size()][2];
    Iterator iter = System.getProperties().keySet().iterator();
    int pos=0;
    while(iter.hasNext())
		{
    	String key   = (String)iter.next();
      String value = (String)System.getProperty(key);
      data[pos][0]= key;
      data[pos][1]= value;
      pos++;
		}
    JTable      eventList           = new JTable(data, new String[]{"Property","Value"});
    JScrollPane eventListScrollPane = new JScrollPane(eventList);
    eventListScrollPane.setPreferredSize(new Dimension(100, 100));
//    eventListScrollPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
    return eventListScrollPane;
  }
  
  // Helper Code ************************************************************
  private JComponent wrap(Component buttonBar, Component inputPanel)
  {
    FormLayout layout = new FormLayout("3dlu, fill:default:grow, 3dlu",  // cols 
                                       "p,fill:p:grow, 4dlu, p,3dlu");   // rows
    PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
    if(debug)
      builder = new PanelBuilder(new FormDebugPanel(),layout);
    CellConstraints cc = new CellConstraints();
    builder.add(buildInfoPanel(), cc.xywh(1, 1,3,1));
    builder.add(inputPanel, cc.xy(2, 2));
    builder.add(buttonBar,  cc.xy(2, 4));
    return builder.getPanel();
  }
  

  /**
   * create the information component for the user
   * 
   * @return
   */
  private Component buildInfoPanel()
  {
    return new DialogInfoHeader(I18N.get("HELPABOUTDIALOG.LABEL.HELPHEADER"),
                                I18N.get("HELPABOUTDIALOG.LABEL.HELPLINE01"),
                                I18N.get("HELPABOUTDIALOG.LABEL.HELPLINE02")
                                );
  }
  
  void okButton_actionPerformed(ActionEvent e)
  {
     dispose();
  }
}
  