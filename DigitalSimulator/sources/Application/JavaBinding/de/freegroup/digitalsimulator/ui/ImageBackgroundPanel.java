package de.freegroup.digitalsimulator.ui;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import javax.swing.JPanel;
import Configuration;
import Trace;
import java.net.URL;

/**
 *  Description of the Class
 *
 *@author     c5026971
 *@created    10. Januar 2002
 */
public class ImageBackgroundPanel extends JPanel
{
    TexturePaint  texture;
    BufferedImage bufferedImage=null;

    public ImageBackgroundPanel()
    {
        try
        {
            String imagePath = Configuration.getString(Configuration.BMP_PATH)+"bg.gif";
            Image img = Toolkit.getDefaultToolkit().getImage(imagePath);
            bufferedImage = toBufferedImage(img);
        }
        catch (Exception ex)
        {
            Trace.error("unable to init background panel",ex);
        }
    }


    // The class should override this method.
    /**
     *  Description of the Method
     *
     *@param  g  Description of Parameter
     */
    public void paintComponent(Graphics g)
    {
        Graphics2D g2d = (Graphics2D) g;

        texture = new TexturePaint(bufferedImage, new Rectangle(0, 0, getSize().width, getSize().height));
        g2d.setPaint(texture);
        // The next two lines should be in one line.
        g2d.fillRect(0, 0, getSize().width, getSize().height);
    }


    BufferedImage toBufferedImage(Image image)
    {
        // This code ensures that all the pixels in
        // the image are loaded.
        image = new ImageIcon(image).getImage();

        // Create the buffered image.
        BufferedImage bufferedImage =  new BufferedImage(
                image.getWidth(null), image.getHeight(null),
                BufferedImage.TYPE_INT_RGB);

        // Copy image to buffered image.
        Graphics g = bufferedImage.createGraphics();

        // Clear background and paint the image.
        g.setColor(Color.white);
        g.fillRect(0, 0, image.getWidth(null),
                image.getHeight(null));
        g.drawImage(image, 0, 0, null);
        g.dispose();

        return bufferedImage;
    }
}
