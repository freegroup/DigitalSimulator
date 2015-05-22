/*
 * Created on Dec 8, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.plugin.tool.PluginWizard;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.UIManager;
import javax.swing.text.PlainDocument;

import org.apache.tools.ant.taskdefs.Sleep;

import bsh.EvalError;

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
import de.freegroup.digitalsimulator.plugin.object.*;
import de.freegroup.ui.editor.JEditTextArea;
import de.freegroup.ui.editor.JavaTokenMarker;


/**
 * Demonstrates how to build button bars using a ButtonBarBuilder.
 *
 * @author  Andreas Herz
 * @version $Revision: 1.1 $
 * @see     ButtonBarBuilder
 * @see     ButtonBarFactory
 */
public final class WizardObjectErrorDialog extends JDialog
{
  JButton     hideButton              = null;
  JButton     saveButton              = null;

  static boolean     debug = !Application.isRunningInDigiSim();
  static JLabel        function  = null;
  static WizardObjectErrorDialog dialog=null;

  static JEditTextArea code       = null;
  static JTextArea     stackTrace = null;
  static JLabel        lineNumber = null;
  static JLabel        errorText  = null;
  static MutableObjectPlugin object = null;
  public static void main(String[] args)
	{
    try
		{
			Thread.sleep(2000);
		}
		catch (InterruptedException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		show(new EvalError("",null,null),"/*kein code*/","keineFunction", null);
	}
  
  static
  {
    try
    {
      // The Thread is for the second event loop.
      // Is there no Thread the main GUI from the DigitalSimulator
      // will not receive any paint requests.
      //
      Thread thread = new Thread(new Runnable()
      {
        public void run()
        {
          dialog = new WizardObjectErrorDialog();
          dialog.hide();
        }
      });
      if(debug==false)
        thread.setDaemon(true);
      thread.start();
     // Thread.sleep(1000);
    }
    catch (Exception ex)
    {
      Trace.error("Unable to create Dialog Thread", ex);
    }
  }
  
  public static void show(EvalError eval, String errorCode, String func, MutableObjectPlugin obj)
  {
    try
		{
			object = obj;
			function.setText(func);
			code.setText(errorCode);
			code.setCaretPosition(0);
      stackTrace.setText(""+Trace.toString(eval));
      errorText.setText(""+eval.getErrorText());
      lineNumber.setText(""+eval.getErrorLineNumber());
    }
		catch (Throwable e)
		{
			// TODO Auto-generated catch block
		  Trace.error(e);
		}
    dialog.invalidate();
    dialog.show();
  }
  
  private WizardObjectErrorDialog()
  {
    super((Frame)null,I18N.get("COMMON.DIALOGHEADER.WIZARDOBJECTERROR"),false);
    JComponent panel = buildPanel();
    
    getContentPane().add(panel);
    pack();
    
    Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
    Configuration.getString("WizardObjectErrorDialog.width");
    // set the default width ans height
    //
    int w = getSize().width;
    int h = getSize().height;
    // try to restore the last dialog size from the property file
    //
    try{w = Integer.parseInt(Configuration.getString("WizardObjectErrorDialog.width"));}catch(Exception exc){}
    try{h = Integer.parseInt(Configuration.getString("WizardObjectErrorDialog.height"));}catch(Exception exc){}
    
    // center the window
    //
    int x = (dim.width-w)/2;
    int y = (dim.height-h)/2;
    
    setBounds(x, y, w, h);
    WinUtil.setWindowAlwaysOnTop(getTitle());
    
//    show();  
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

    // create the button bar
    //
    ButtonBarBuilder buttonBuilder = new ButtonBarBuilder();
    buttonBuilder.addGlue();
    buttonBuilder.addGridded(hideButton);
    buttonBuilder.addRelatedGap();
    buttonBuilder.addGridded(saveButton);
 
    return wrap(buttonBuilder.getPanel(),buildSteckbriefPanel());
  }
  
  /**
   * 
   *
   */
  private void initComponents()
  {
    lineNumber = new JLabel();
    errorText  = new JLabel();
    function   = new JLabel();
    
    code = new JEditTextArea();
    code.setTokenMarker(new JavaTokenMarker());
    code.setText("");
    code.getDocument().putProperty(PlainDocument.tabSizeAttribute, new Integer(4));
    
    stackTrace = new JTextArea("");
        
    hideButton = new JButton(I18N.get("COMMON.BUTTON.CLOSE"));
    hideButton.addActionListener(new java.awt.event.ActionListener() {
        public void actionPerformed(ActionEvent e) {
          hideButton_actionPerformed(e);
        }
    });

    saveButton = new JButton(I18N.get("COMMON.BUTTON.SAVE"));
    saveButton.addActionListener(new java.awt.event.ActionListener() {
        public void actionPerformed(ActionEvent e) {
          saveButton_actionPerformed(e);
        }
    });
  }
 
  /**
   * 
   * @return
   */
  private Component buildSteckbriefPanel()
  {
    // Create a FormLayout instance on the given column and row specs. 
    // For almost all forms you specify the columns; sometimes rows are 
    // created dynamically. In this case the labels are right aligned.
    FormLayout layout = new FormLayout(
            "right:pref, 3dlu, fill:200dlu:grow",                              // cols
            "p, 3dlu,p, 3dlu, p,3dlu, p, 3dlu,fill:50dlu:grow, 3dlu, fill:50dlu:grow,p");    // rows
        
    // Create a builder that assists in adding components to the container. 
    // Wrap the panel with a standardized border.
    PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
    if(debug)
      builder = new PanelBuilder(new FormDebugPanel(),layout);
    builder.setDefaultDialogBorder();

    // Obtain a reusable constraints object to place components in the grid.
    CellConstraints cc = new CellConstraints();

    // Fill the grid with components; the builder offers to create
    // frequently used components, e.g. separators and labels.
        
    // Add a titled separator to cell (1, 1) that spans 7 columns and 1 row.
    //
    builder.addSeparator(I18N.get("WIZZARDERROR.LABEL.ERROR"),cc.xywh(1,  1, 3, 1));
    builder.addLabel(I18N.get("WIZZARDERROR.LABEL.REASONOFERROR"),   cc.xy(1,3));
    builder.add(errorText,                                    cc.xy(3,3));
    builder.addLabel(I18N.get("WIZZARDERROR.LABEL.FUNCTION"), cc.xy(1,5));
    builder.add(function,                                     cc.xy(3,5));
    builder.addLabel(I18N.get("WIZZARDERROR.LABEL.LINE"),     cc.xy(1,7));
    builder.add(lineNumber,                                   cc.xy(3,7));
    builder.addLabel(I18N.get("WIZZARDERROR.LABEL.CALLSTACK"),cc.xy(1,9 ,"right, top"));
    builder.add(new JScrollPane(stackTrace),                  cc.xy(3,9));
    builder.addLabel(I18N.get("WIZZARDERROR.LABEL.CODE"),     cc.xy(1,11,"right, top"));
    builder.add(code,                                         cc.xy(3,11));
    builder.add(new StatusBar(code),                          cc.xy(3,12));

    return builder.getPanel();
  }
  

  // Helper Code ************************************************************
  private JComponent wrap(Component buttonBar, Component inputPanel)
  {
    FormLayout layout = new FormLayout("fill:default:grow",      // cols 
                                       "fill:p:grow, 4dlu, p");  // rows
    PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
    if(debug)
      builder = new PanelBuilder(new FormDebugPanel(),layout);
    CellConstraints cc = new CellConstraints();
    builder.add(inputPanel, cc.xy(1, 1));
    builder.add(buttonBar,  cc.xy(1, 3));
    return builder.getPanel();
  }


  void hideButton_actionPerformed(ActionEvent e)
  {
      int w = getSize().width;
      int h = getSize().height;
      Configuration.setString("WizardObjectErrorDialog.width", "" + w);
      Configuration.setString("WizardObjectErrorDialog.height", "" + h);
      hide();
  }

  void saveButton_actionPerformed(ActionEvent e)
  {
    if(object!=null)
    {
      object.setData(function.getText(),code.getText());
    }
    hide();
  }
}
