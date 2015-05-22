package de.freegroup.ui;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
  * A HyperlinkedLabel object is a component for placing a hyperlink
  * into a container. A HyperlinkedLabel displays a single line of read-only text,
  * which is underlined to give the visual impression of a hyperlink.
  *
  * Clicking on the hyperlink will produce no result however. It is up
  * to the application developer to provide this functionality,
  * such as performing an action, displaying a web page, or activating a menu.
  *
  * <p>
  * Applications can catch hyperlink clicks by adding registering
  * an <code>ActionListener</code>, using the addActionListener method.
  *
  * @version 1.00 10/5/99
  * @author  David Reilly
  * @see         java.awt.event.ActionEvent
  * @see         java.awt.event.ActionListener
  */
public class HyperlinkedLabel extends JLabel implements MouseListener
{
    // URL
    private String url= null;
    // Color for the hyperlink (not the text)
    private Color  hyperlinkColor;

    private Color  originalTextColor;
    transient boolean clicked = false;
    transient ActionListener actionListener = null;

    /**
      * Creates a hyperlinked label with no specific hyperlink
      *
      * @param label	Text of label
      */
    public HyperlinkedLabel(String label)
    {
        this(label, null);
    }

    /**
      * Creates a hyperlinked label hyperlinked to the specified URL.
      *
      * @param label	Text of label
      * @param URL		Universal Resource Locator (URL)
      */
    public HyperlinkedLabel(String label, String URL)
    {
        this(label, URL, Color.blue);
    }

    /**
      * Creates a hyperlinked label hyperlinked to the specified URL,
      * in the specific color.
      *
      * @param label	Text of label
      * @param URL		Universal Resource Locator (URL)
      * @param color    Color of hyperlink
      */
    public HyperlinkedLabel(String label, String URL, Color color)
    {
        super(label);

        setURL  (URL);
        setHyperlinkColor(color);

        addMouseListener(this);
    }

    /**
      * Sets the URL destination for this hyperlink.
      *
      * @param URL		Universal Resource Locator (URL)
      */
    public void setURL(String url)
    {
        this.url=url;
    }

    /**
      * Sets the color for this hyperlink.
      *
      * @param color	Color of hyperlink
      */
    public void setHyperlinkColor (Color color)
    {
        this.hyperlinkColor=color;
    }

    /**
      * Returns the color for this hyperlink.
      *
      * @return Color of hyperlink
      */
    public Color getHyperlinkColor ()
    {
        return hyperlinkColor;
    }

    /**
      * Returns the URL for this hyperlink.
      *
      * @return Universal Resource Locator (URL) as a String
      */
    public String getURL ()
    {
        return url;
    }

    /**
      * Paints the hyperlink
      *
      * @param g    Graphics object for painting
      */
    public void paint(Graphics g)
    {
        // Call label's paint method
        super.paint(g);

        // Check that a hyperlink was specified
        if (url == null) return;

        // Set color for hyperlink
        g.setColor ( hyperlinkColor );

        // Get width of hyperlink label component
        Dimension d = getSize();
        int width = d.width;
        int height= d.height;

        // Get width of label text
        FontMetrics metrics = getFontMetrics(getFont());
        int strWidth = metrics.stringWidth( getText() );

        int offset = width - strWidth ;

        int align = getHorizontalAlignment();

        switch (align)
        {
        case SwingConstants.LEFT :
            // Safety factor of 2
            g.drawLine ( 2, height-3, 2 +strWidth, height-3);
            break;
        case SwingConstants.CENTER :
            // Safety factor of 1
            g.drawLine ( offset/2 + 1, height-3, width - offset/2 -1, height-3);
            break;
        case SwingConstants.RIGHT :
            // Safety factor of 2
            g.drawLine ( offset - 2, height-3, width, height-3);
            break;

        }
    }

    /**
     * Adds the specified action listener to receive action events from
     * this hyperlink.
     *
     * @param listener	ActionListener to add to event queue
     */
    public synchronized void addActionListener(ActionListener listener) {
        actionListener = AWTEventMulticaster.add(actionListener, listener);
    }

    /**
     * Removes the specified action listener from the list of action listeners
     * associated with this hyperlink.
     *
     * @param listener	ActionListener to add to event queue
     */
    public synchronized void removeActionListener(ActionListener listener) {
        actionListener = AWTEventMulticaster.remove(actionListener, listener);
    }

    public void mouseClicked(MouseEvent e) {
        if (actionListener != null) {
            ActionEvent actionE = new ActionEvent(this,
                ActionEvent.ACTION_PERFORMED, "Clicked");
            actionListener.actionPerformed(actionE);
        }
        try
        {
       Runtime.getRuntime().exec("cmd.exe /c start iexplore "+url);
        }
        catch (Exception ex)
        {
//            trace.error(ex);
        }
    }

    /**
      * Event handler for when the cursor enters the hyperlink
      * @param MouseEvent Event
      */
    public void mouseEntered(MouseEvent e)
    {
        setCursor (new Cursor(Cursor.HAND_CURSOR));
        setHyperlinkColor(Color.red);
        setForeground ( hyperlinkColor );
        repaint();
    }

    /**
      * Event handler for when the cursor leaves the hyperlink
      * @param MouseEvent Event
      */
    public void mouseExited(MouseEvent e)
    {
        setCursor (new Cursor(Cursor.DEFAULT_CURSOR));
        setHyperlinkColor(Color.blue);
        setForeground ( hyperlinkColor );
        repaint();
    }

    public void mousePressed(MouseEvent e) {
        clicked = true;
        originalTextColor = getForeground();
        setForeground ( hyperlinkColor );
        repaint();
    }

    public void mouseReleased(MouseEvent e)
    {
        clicked = false;
        setForeground ( originalTextColor );
        repaint();
    }

    /**
      * Returns the preferred size of the hyperlink.
      * @return Preferred dimensions
      */
    public Dimension getPreferredSize()
    {
        // Shave a little off original width
        FontMetrics metrics = getFontMetrics(getFont());
        int strWidth = metrics.stringWidth( getText() );

        Dimension original = super.getPreferredSize();
        return new Dimension (strWidth+2, original.height);
    }



  // This is just for testing ...
  public static void main(String args[]) {
    Frame f = new Frame();
    HyperlinkedLabel label = new HyperlinkedLabel("Test", "http://www.davidreilly.com/");

//    label.setHyperlinkColor(new Color ( 200, 40, 0));
    f.setLayout(new FlowLayout());
    f.add (new HyperlinkedLabel("hello there","abc") );
    f.add(label);
    label.setHorizontalAlignment(SwingConstants.CENTER);
    f.add (new Button("Ok") );
    JLabel tmp = new HyperlinkedLabel("hi","bk");
//    tmp.setForeground (Color.orange);
    tmp.setHorizontalAlignment (SwingConstants.CENTER);
    f.add(tmp);
    f.pack();
    f.setVisible(true);
  }

}

