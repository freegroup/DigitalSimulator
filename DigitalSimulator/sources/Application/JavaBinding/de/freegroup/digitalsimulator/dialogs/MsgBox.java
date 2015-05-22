package de.freegroup.digitalsimulator.dialogs;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import de.freegroup.digitalsimulator.ui.ImageBackgroundPanel;
import de.freegroup.ui.SkinButton;
import Configuration;
import I18N;
import Trace;
import JUtil;

/**
 *  Description of the Class
 *
 *@author     Andreas Herz
 *@created    10. Januar 2002
 */
public class MsgBox extends JDialog implements ActionListener
{
    JButton ok;
    JPanel   p ;
    JPanel   textPanel;
    JPanel   buttonPanel;

    public MsgBox(String msg)
    {
        super(new Frame(""), I18N.translate("Information"), true);

        p = new ImageBackgroundPanel();
        textPanel   = new JPanel();
        buttonPanel = new JPanel();

        getContentPane().add(p);
        p.setMinimumSize(new Dimension(400, 100));
        p.setLayout(new BorderLayout());

        p.add(textPanel,BorderLayout.CENTER);
        p.add(buttonPanel,BorderLayout.SOUTH);

        // the Message
        //
        FlowLayout flowLayout = new FlowLayout();
        flowLayout.setVgap(20);
        flowLayout.setHgap(20);
        textPanel.setLayout(flowLayout);
        textPanel.setOpaque(false);
        textPanel.setBorder(BorderFactory.createEtchedBorder());
        JLabel l= new JLabel(msg);
        l.setHorizontalAlignment(SwingConstants.CENTER);
        textPanel.add(l);

        // the button
        //
        buttonPanel.setOpaque(false);
        ok = new SkinButton(I18N.translate("Ok"));
        buttonPanel.add(ok);
        ok.addActionListener(this);

        pack();

        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        int w = getSize().width;
        int h = getSize().height;
        int x = (dim.width-w)/2;
        int y = (dim.height-h)/2;

        setBounds(x, y, w, h);

        setResizable(false);
        JUtil.setWindowAlwaysOnTop(JUtil.getHwnd(getTitle()),true);
        setVisible(true);
    }


    /**
     *  Description of the Method
     *
     *@param  ae  Description of Parameter
     */
    public void actionPerformed(ActionEvent ae)
    {
        if(ae.getSource() == ok)
        {
            dispose();
        }
    }

    public static void main(String[] args)
    {
        new MsgBox("Unable to connect to the host www.digital-simulator.de!");
        new MsgBox("Unable to connect to the host www.digital-simulator.deUnable to connect to the host www.digital-simulator.deUnable to connect to the host www.digital-simulator.de!");
    }
}

