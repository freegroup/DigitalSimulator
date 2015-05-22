/*
 * Created on Dec 16, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.ui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.Border;
import javax.swing.border.EtchedBorder;
import javax.swing.border.LineBorder;

import com.jgoodies.forms.builder.PanelBuilder;
import com.jgoodies.forms.debug.FormDebugPanel;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import de.freegroup.digitalsimulator.Application;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class DialogInfoHeader extends JPanel
{
  static boolean     debug = !Application.isRunningInDigiSim();
  JPanel p = null;
  FormLayout textLayout=null;
  
  public DialogInfoHeader(String title, String info01)
  {
    this(title,info01,null);
  }
  
  /**
	 * 
	 */
	public DialogInfoHeader(String title, String info01, String info02)
	{
    // the text panel
    //
    textLayout = new FormLayout(
        "3dlu,10dlu,fill:p:grow",  // cols
        "p,p,1dlu,fill:p:grow");        // rows
    
    JPanel xPanel = new LRGradient(Color.white,new Color(212,208,200));
    PanelBuilder builder = new PanelBuilder(xPanel,textLayout);
    if(debug)
      builder = new PanelBuilder(new FormDebugPanel(),textLayout);
    
    //builder.setDefaultDialogBorder();
    CellConstraints cc = new CellConstraints();
    JLabel t = new JLabel(title);
    t.setFont(new Font("SansSerif", Font.BOLD, 16));

    builder.add(t      , cc.xywh(2, 1,2,1));

    if(info01!=null)
      builder.addLabel(info01 , cc.xy  (3, 2));
    
    if(info02!=null)
      builder.addLabel(info02       , cc.xy  (3, 4));
   

    p = builder.getPanel();
//    p.setBorder(new EtchedBorder());
    
    add(p);
  }

  
  public void paint(Graphics g)
  {
    Dimension d = getSize();
    p.setSize(d);
    p.setBounds(0,0, d.width,d.height);
    textLayout.layoutContainer(p);
    super.paint(g);
  }
  
	public static void main(String[] args)
	{
    JPanel panel = new DialogInfoHeader("Title","Message01","Message02");
    Frame f = new Frame("Java2D Demo - ");
    f.addWindowListener(new WindowAdapter()
        {
      public void windowClosing(WindowEvent e)
      {
        System.exit(0);
      }
    });
    f.add("Center", panel);
    f.pack();
    f.setSize(new Dimension(500, 300));
    f.setVisible(true);
  }
}
