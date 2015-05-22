/*
 * Created on Jan 10, 2004
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.dialogs;


import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Locale;
import java.util.ResourceBundle;
import javax.accessibility.AccessibleContext;

import com.jgoodies.forms.builder.PanelBuilder;
import com.jgoodies.forms.debug.FormDebugPanel;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import de.freegroup.digitalsimulator.Application;
import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.WinUtil;



public class WaitDialog extends JDialog 
{
  static protected boolean     debug = !Application.isRunningInDigiSim();
  String label = "";
  /**
   * 
   *
   */
  public WaitDialog(String title, String label)
  {
    super((Frame)null,title,false);
    this.label       = label;
    show(500,320);
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
    JLabel icon = new JLabel();
    icon.setIcon(new ImageIcon(WaitDialog.class.getResource("wait.gif")));
    
    FormLayout layout = new FormLayout(
        "3dlu,p, fill:default:grow, 3dlu",      // cols 
        "p:grow,p,3dlu,p,p:grow");       // rows
    PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
    if(debug)
      builder = new PanelBuilder(new FormDebugPanel(),layout);
    CellConstraints cc = new CellConstraints();
    builder.add(icon, cc.xy(2, 2));
    builder.addLabel(label, cc.xy(3, 2));
    
    
    return builder.getPanel();
  }
  
  public static void main(String[] args)
  {
    new WaitDialog("Download","FileXYZ");
  }
} 

