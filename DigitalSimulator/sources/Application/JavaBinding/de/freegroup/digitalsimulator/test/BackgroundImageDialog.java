package de.freegroup.digitalsimulator.test;

import java.awt.*;
import javax.swing.*;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */

public class BackgroundImageDialog extends JDialog {
    JPanel panel1 = new JPanel();
    BorderLayout borderLayout1 = new BorderLayout();
    JLabel jLabel1 = new JLabel();
    JButton jButton1 = new JButton();

    public BackgroundImageDialog(Frame frame, String title, boolean modal) {
        super(frame, title, modal);
        try {
            jbInit();
            pack();
        }
        catch(Exception ex) {
            ex.printStackTrace();
        }
    }

    public BackgroundImageDialog() {
        this(null, "", false);
    }
    void jbInit() throws Exception {
        panel1.setLayout(borderLayout1);
        jLabel1.setOpaque(true);
        jLabel1.setHorizontalAlignment(SwingConstants.CENTER);
        jLabel1.setText("jLabel1");
        jButton1.setMaximumSize(new Dimension(79, 28));
        jButton1.setMinimumSize(new Dimension(79, 28));
        jButton1.setPreferredSize(new Dimension(79, 28));
        jButton1.setText("jButton1");
        panel1.setMinimumSize(new Dimension(300, 450));
        panel1.setPreferredSize(new Dimension(300, 450));
        this.setContentPane(panel1);
        this.setResizable(false);
//        getContentPane().add(panel1);
        panel1.add(jLabel1,  BorderLayout.CENTER);
        panel1.add(jButton1,  BorderLayout.SOUTH);
    }

   public static void main(String[] args)
    {
        JOptionPane.showMessageDialog(new Frame(""), "Line1 Line Line Line Line2","Error",JOptionPane.ERROR_MESSAGE);
    }
}