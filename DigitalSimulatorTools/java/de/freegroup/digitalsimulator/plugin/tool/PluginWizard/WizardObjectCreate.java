/*
 * Created on Dec 3, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.plugin.tool.PluginWizard;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Frame;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.UIManager;

import com.jgoodies.forms.builder.ButtonBarBuilder;
import com.jgoodies.forms.builder.PanelBuilder;
import com.jgoodies.forms.debug.FormDebugPanel;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import java.awt.Toolkit;
import java.io.File;
import java.net.URL;

import de.freegroup.digitalsimulator.Application;
import de.freegroup.digitalsimulator.Configuration;
import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.WinUtil;
import de.freegroup.digitalsimulator.dialogs.GenericDialog;
import de.freegroup.digitalsimulator.plugin.object.ObjectPlugin;
import de.freegroup.digitalsimulator.ui.DialogInfoHeader;
import de.freegroup.digitalsimulator.ui.HGradient;
import de.freegroup.digitalsimulator.ui.VGradient;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class WizardObjectCreate extends GenericDialog implements KeyListener
{
  JTextField  nameField     = null;
  JLabel      warningLabel  = null;
  JLabel      merlinLabel   = null;
  
  /**
   * 
   * @param args
   */
  public static void main(String[] args)
  {
    try
    {
      UIManager.setLookAndFeel("com.jgoodies.plaf.plastic.PlasticXPLookAndFeel");
    }
    catch (Exception e)
    {
      // Likely PlasticXP is not in the class path; ignore.
    }
    new WizardObjectCreate();
  }
  
  /**
   * 
   *
   */
  public WizardObjectCreate()
  {
    super(I18N.get("COMMON.DIALOGHEADER.WIZARDOBJECTCREATE"),
          I18N.get("WIZARDOBJECTCREATE.LABEL.HELPHEADER"),
          I18N.get("WIZARDOBJECTCREATE.LABEL.HELPLINE01"),
          I18N.get("WIZARDOBJECTCREATE.LABEL.HELPLINE02"));
    show(600,450);
  }
  
  /**
   * 
   *
   */
  public void initComponents()
  {
    nameField    = new JTextField();
    merlinLabel  = new JLabel("");
    warningLabel = new JLabel("");
    
    ImageIcon merlin = new ImageIcon(getClass().getResource("merlin.gif"));
    merlinLabel.setIcon(merlin);

    nameField.addKeyListener(this);
  }
 
  /**
   * 
   * @return
   */
  public Component buildInputPanel()
  {
    FormLayout layout = new FormLayout(
            "right:pref, 5dlu,1dlu,5dlu,p, fill:200dlu:grow", 
            "10dlu:grow, p,10dlu:grow");  
        
    PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
    if(debug)
      builder = new PanelBuilder(new FormDebugPanel(),layout);
    builder.setDefaultDialogBorder();

    CellConstraints cc = new CellConstraints();

    builder.add(merlinLabel                                  , cc.xywh(1,  1, 1, 3));
    builder.add(new HGradient(Color.lightGray,Color.darkGray), cc.xywh(3,1,1,3,"f,f"));
    builder.addLabel(I18N.get("WIZARDOBJECTCREATE.LABEL.OBJECTTYPE")                 , cc.xy  (5, 2));
    builder.add(nameField                                    , cc.xy  (6, 2));
    builder.add(warningLabel                                 , cc.xy  (6, 3,"left,top"));
    return builder.getPanel();
  }
  

  /**
   * Invoked when a key has been typed.
   * See the class description for {@link KeyEvent} for a definition of 
   * a key typed event.
   */
  public void keyTyped(KeyEvent e)
  {
  }


  /**
   * Invoked when a key has been pressed. 
   * See the class description for {@link KeyEvent} for a definition of 
   * a key pressed event.
   */
  public void keyPressed(KeyEvent e)
  {
  }


  /**
   * Invoked when a key has been released.
   * See the class description for {@link KeyEvent} for a definition of 
   * a key released event.
   */
  public void keyReleased(KeyEvent e)
  {
    if(ObjectPlugin.isObjectNameFree(nameField.getText()))
      warningLabel.setText(null);
    else
      warningLabel.setText(I18N.get("WIZARDOBJECTCREATE.LABEL.WARNINGTEXT"));
  }


  public void onOk()
  {
      if(nameField.getText().length()>0)
      {
        try
        {
          String applicationPath = Configuration.getString(Configuration.APPLICATION_PATH);
          String pluginPath      = Configuration.getString(Configuration.PLUGIN_PATH);
          String javaHome        = Configuration.getString(Configuration.JAVA_HOME);

          // call the ant task from the command line
          //
          //Process p = Runtime.getRuntime().exec("cmd.exe /q /c start build.bat \""+javaHome+"\" \""+applicationPath+"\" \"-Dplugin.name="+nameField.getText()+"\"",null,new File(pluginPath+"/PluginWizard/"));
          Process p = Runtime.getRuntime().exec("rundll32 SHELL32.DLL,ShellExec_RunDLL  build.bat "+nameField.getText()+"",null,new File(pluginPath+"/PluginWizard/"));
          p.waitFor();
        }
        catch (Throwable exc)
        {
          Trace.error(exc);
        }
      }
  }


  /**
   * 
   * @param e
   */
  public void onCancel()
  {
  }
  
}
