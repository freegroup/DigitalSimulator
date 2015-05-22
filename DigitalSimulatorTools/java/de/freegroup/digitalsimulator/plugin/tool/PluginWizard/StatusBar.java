/*
 * Created on Dec 9, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.plugin.tool.PluginWizard;

import java.awt.Graphics;

import javax.swing.BoxLayout;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;

import de.freegroup.digitalsimulator.I18N;
import de.freegroup.ui.editor.JEditTextArea;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */

public class StatusBar extends JComponent implements CaretListener
{
  public StatusBar(JEditTextArea area)
  {
    super();
    area.addCaretListener(this);
    setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
    initialize();
  }
  
  public void caretUpdate(CaretEvent e)
  {
    Object o = e.getSource();
    JEditTextArea t;  
    if(o instanceof JEditTextArea)
    {
      t = (JEditTextArea)e.getSource();
      int offset = t.getCaretPosition();
      int line = 1 + t.getLineOfOffset(offset);
  
      removeAll(); 
      add(new JLabel(I18N.get("OBJECTWIZARD.LABEL.LINENUMBER") + line +"  "));
      revalidate();
    }
  }
  
  public void initialize()
  {
    removeAll();
    add(new JLabel(I18N.get("OBJECTWIZARD.LABEL.LINENUMBER")+" 1    "));
    revalidate();
  }
  
  public void paint(Graphics g)
  {
    super.paint(g);
  }
}

