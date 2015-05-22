/*
 * Created on Dec 6, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.ui.spinner;

import javax.swing.JTextField;

import de.freegroup.digitalsimulator.Trace;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class IntegerSpinner extends Spinner implements SpinListener
{
  JTextField text = null;
  int        step = 1;
  int        minValue=0;
  int        maxValue=0;
  public IntegerSpinner(int minValue, int maxValue, int step, int start)
  {
    super(new JTextField());
    text = (JTextField)getComponent();
    text.setEnabled(false);
    text.setDisabledTextColor(text.getForeground());
    addSpinListener(this);
    text.setText(""+start);
    this.step = step;
    this.minValue=minValue;
    this.maxValue=maxValue;
  }
  
  public void spinnerSpunUp(SpinEvent event)
  {
    int current = Integer.parseInt(text.getText());
    current +=step;
    current= Math.min(maxValue,current);
    text.setText(""+current);
  }


  public void spinnerSpunDown(SpinEvent event)
  {
    int current = Integer.parseInt(text.getText());
    current -=step;
    current= Math.max(minValue,current);
    text.setText(""+current);
  }
  
  public void setValue(int value)
  {
    text.setText(""+value);
  }
  
  public int getValue()
  {
    return Integer.parseInt(text.getText());
  }
}
