package de.freegroup.digitalsimulator.dialogs;
/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */

import java.awt.*;
import javax.swing.*;
import de.freegroup.digitalsimulator.ui.ImageBackgroundPanel;
import I18N;
import Trace;

public class DownloadReportDialog extends JDialog
{
    JPanel panel1 = null;
    BorderLayout borderLayout1 = new BorderLayout();
    JLabel jLabel1 = new JLabel();
    Component componentTop;
    Component componentBottom;
    Component componentRight;
    Component componentLeft;

    public static void main(String[] args)
    {
        DownloadReportDialog dlg =new DownloadReportDialog();
        dlg.setMessage("Dies ist ein sehr lange nachricht mir viel unsinn als text....");
        dlg.show();
    }

    public DownloadReportDialog()
    {
        this(null, I18N.translate("Download...."), false);
    }

    protected DownloadReportDialog(Frame frame, String title, boolean modal)
    {
        super(frame, title, modal);
        try
        {
            jbInit();
            pack();
        }
        catch(Exception ex)
        {
            Trace.error("unable to init the dialog",ex);
        }
    }

    void jbInit() throws Exception
    {
        panel1 = new ImageBackgroundPanel();

        componentTop = Box.createVerticalStrut(18);
        componentBottom = Box.createVerticalStrut(18);
        componentRight = Box.createHorizontalStrut(18);
        componentLeft = Box.createHorizontalStrut(18);
        panel1.setLayout(borderLayout1);
        jLabel1.setHorizontalTextPosition(SwingConstants.CENTER);
        jLabel1.setText("unset");
        getContentPane().add(panel1);
        panel1.add(jLabel1, BorderLayout.CENTER);
        panel1.add(componentTop, BorderLayout.NORTH);
        panel1.add(componentBottom, BorderLayout.SOUTH);
        panel1.add(componentRight, BorderLayout.EAST);
        panel1.add(componentLeft, BorderLayout.WEST);
    }

    public void setMessage(String message)
    {
        jLabel1.setText(message);
        pack();
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        int w = getSize().width;
        int h = getSize().height;
        int x = (dim.width-w)/2;
        int y = (dim.height-h)/2;

        setBounds(x, y, w, h);
    }
}