package de.freegroup.ui;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import javax.swing.JButton;
import java.awt.event.*;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import javax.swing.JPanel;

import Configuration;
import Trace;


class SkinButtonMouseListener extends MouseAdapter
{
    SkinButtonMouseListener()
    {
    }

    public void mouseEntered(MouseEvent event)
    {
        SkinButton button= (SkinButton)event.getComponent();
        button.setOver(true);
    }

    public void mouseExited(MouseEvent event )
    {
        SkinButton button= (SkinButton)event.getComponent();
        button.setOver(false);
    }
}


public class SkinButton extends JButton
{
    BufferedImage bufferedImage_normal=null;
    BufferedImage bufferedImage_over  =null;

    boolean over=false;



    public SkinButton(String label)
    {
        super(label);

        String appPath = Configuration.getString(Configuration.BMP_PATH);

        bufferedImage_normal = toBufferedImage(Toolkit.getDefaultToolkit().createImage(appPath+"ButtonBG_normal.gif"));
        bufferedImage_over   = toBufferedImage(Toolkit.getDefaultToolkit().createImage(appPath+"ButtonBG_over.gif"));

        addMouseListener(new SkinButtonMouseListener());
    }

    public SkinButton()
    {
        String appPath = Configuration.getString(Configuration.BMP_PATH);

        bufferedImage_normal = toBufferedImage(Toolkit.getDefaultToolkit().createImage(appPath+"ButtonBG_normal.gif"));
        bufferedImage_over   = toBufferedImage(Toolkit.getDefaultToolkit().createImage(appPath+"ButtonBG_over.gif"));

        addMouseListener(new SkinButtonMouseListener());
    }

    public void setOver(boolean flag)
    {
        over =flag;
    }

    public void paintComponent(Graphics g)
    {
        TexturePaint texture = null;
        Graphics2D g2d = (Graphics2D) g;

        setOpaque(false);

        if(over)
            texture = new TexturePaint(bufferedImage_over, new Rectangle(0, 0, getSize().width, getSize().height));
        else
            texture = new TexturePaint(bufferedImage_normal, new Rectangle(0, 0, getSize().width, getSize().height));

        g2d.setPaint(texture);
        // The next two lines should be in one line.
        g2d.fillRect(0, 0, getSize().width, getSize().height);
        super.paintComponent(g);
    }

    BufferedImage toBufferedImage(Image image)
    {
        // This code ensures that all the pixels in
        // the image are loaded.
        image = new ImageIcon(image).getImage();

        // Create the buffered image.
        BufferedImage bufferedImage = new BufferedImage(
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