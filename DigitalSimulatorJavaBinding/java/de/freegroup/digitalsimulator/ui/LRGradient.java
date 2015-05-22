/*
 * Created on Nov 22, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.ui;
import java.awt.*;
import java.awt.font.*;
import java.awt.event.*;
import java.awt.geom.Rectangle2D;
import java.awt.image.BufferedImage;
import javax.swing.*;

public class LRGradient extends JPanel
{
	protected Color leftColor, rightColor;
  
  public LRGradient()
  {
    leftColor = Color.lightGray;
    rightColor = Color.darkGray;
    setOpaque(false);
  }
  public LRGradient(Color left, Color right)
  {
    leftColor = left;
    rightColor = right;
    setOpaque(false);
  }
  
	public void paint(Graphics g)
	{
		Dimension d = getSize();
		Graphics2D g2 = (Graphics2D) g;
		render(d.width, d.height, g2);
    super.paint(g);
	}
  
	public void render(int w, int h, Graphics2D g2)
	{
		g2.setPaint(new GradientPaint(0, 0, leftColor, w, 0, rightColor));
		g2.fillRect(0, 0, w, h);
	}
  
	/**
	 * only to test this class
	 */
	public static void main(String s[])
	{
		JPanel panel = new LRGradient();
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
} // End Gradient class
