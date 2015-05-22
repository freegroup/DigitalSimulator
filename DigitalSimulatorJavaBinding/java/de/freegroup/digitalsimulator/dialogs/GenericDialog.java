/*
 * Created on Jan 4, 2004
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.dialogs;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.UIManager;

import com.jgoodies.forms.builder.ButtonBarBuilder;
import com.jgoodies.forms.builder.PanelBuilder;
import com.jgoodies.forms.debug.FormDebugPanel;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import de.freegroup.digitalsimulator.Application;
import de.freegroup.digitalsimulator.Configuration;
import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.WinUtil;
import de.freegroup.digitalsimulator.ui.DialogInfoHeader;


/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public abstract class GenericDialog extends JDialog
{  
  JButton     okButton        = null;
  JButton     cancelButton    = null;
  DialogInfoHeader headerComp = null;
  boolean     isOk            = false;
  
  JLabel      icon            = null;
  
  String title       = "";
  String header      = "";
  String headerLine01= "";
  String headerLine02= "";
  
  protected boolean withCancelButton=true;
  static protected boolean     debug = !Application.isRunningInDigiSim();
  
  /**
   * 
   *
   */
  public abstract void initComponents();
  public abstract Component buildInputPanel();
  public abstract void onCancel();
  public abstract void onOk();

  /**
   * 
   *
   */
  public GenericDialog(String title, String header, String headerLine01, String headerLine02)
  {
    super((Frame)null,title,true);
    
    headerComp=new DialogInfoHeader(header,headerLine01, headerLine02);
    this.title = title;
    this.header = header;
    this.headerLine01 = headerLine01;
    this.headerLine02 = headerLine02;
  }
  
  /**
   * 
   *
   */
  public GenericDialog(String title, String header, String headerLine01, String headerLine02, boolean hasIcon)
  {
    this(title,header, headerLine01, headerLine02);
    if(hasIcon==true)
    {
    	icon = new JLabel();
    	icon.setIcon(new ImageIcon(GenericDialog.class.getResource("icon.gif")));
    }
  }
  
  protected void show(int w, int h)
  {
    getContentPane().add(buildMainPanel());
    pack();
    
    Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
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
  final public JComponent buildMainPanel()
  {
    // Separating the component initialization and configuration
    // from the layout code makes both parts easier to read.
    initComponents();

    okButton = new JButton(I18N.get("COMMON.BUTTON.OK"));
    okButton.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        okButton_actionPerformed(e);
      }
    });
    
    cancelButton = new JButton(I18N.get("COMMON.BUTTON.CANCEL"));
    cancelButton.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        cancelButton_actionPerformed(e);
      }
    });

    // create the button bar
    //
    ButtonBarBuilder buttonBuilder = new ButtonBarBuilder();
    buttonBuilder.addGlue();
    buttonBuilder.addGridded(okButton);
    if(withCancelButton)
    {
    	buttonBuilder.addRelatedGap();
    	buttonBuilder.addGridded(cancelButton);
    }
    
    return wrap(buttonBuilder.getPanel(), buildInputPanel());
  }
  
  
  // Helper Code ************************************************************
  final private JComponent wrap(Component buttonBar, Component inputPanel)
  {
    if(icon!=null)
    {
      FormLayout layout = new FormLayout(
          "3dlu, fill:default:grow,p, 3dlu", // cols 
          "p,fill:p:grow, 4dlu, p,3dlu");  // rows
      PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
      if(debug)
      	builder = new PanelBuilder(new FormDebugPanel(),layout);
      
      CellConstraints cc = new CellConstraints();
      builder.add(headerComp, cc.xywh(1, 1,2,1,"left,top"));
      builder.add(icon, cc.xy(3, 1));
      builder.add(inputPanel, cc.xywh(2, 2,2,1));
      builder.addSeparator("",cc.xywh(2, 3,2,1));
      builder.add(buttonBar,  cc.xywh(2, 4,2,1));
      return builder.getPanel();
    }
    else
    {
      FormLayout layout = new FormLayout(
          "3dlu, fill:default:grow,3dlu", // cols 
          "p,fill:p:grow, 4dlu, p,3dlu");  // rows
      PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
      if(debug)
      	builder = new PanelBuilder(new FormDebugPanel(),layout);
      
      CellConstraints cc = new CellConstraints();
      builder.add(headerComp, cc.xywh(1, 1,3,1));
      builder.add(inputPanel, cc.xywh(2, 2,2,1));
      builder.addSeparator("",cc.xywh(2, 3,2,1));
      builder.add(buttonBar,  cc.xywh(2, 4,2,1));
      return builder.getPanel();
    }
  }

   final protected void setHelpIcon(ImageIcon i)
   {
   	  if(icon!=null && i!=null)
   	  	icon.setIcon(i);
      else
      	icon.setIcon(new ImageIcon(GenericDialog.class.getResource("icon.gif")));
   }
   
  final void okButton_actionPerformed(ActionEvent e)
  {
    onOk();
    isOk=true;
    dispose();
  }


  /**
   * 
   * @param e
   */
  final void cancelButton_actionPerformed(ActionEvent e)
  {
    onCancel();
    isOk=false;
    dispose();
  }
  /**
   * @return
   */
  public final boolean isOk()
  {
    return isOk;
  }

}