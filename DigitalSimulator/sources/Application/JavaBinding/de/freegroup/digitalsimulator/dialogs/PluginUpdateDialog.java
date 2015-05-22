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
import java.awt.event.*;
import javax.swing.event.*;
import de.freegroup.ui.*;
import javax.swing.border.*;
import de.freegroup.digitalsimulator.ui.ImageBackgroundPanel;
import I18N;
import Trace;

public class PluginUpdateDialog extends JDialog {

    ImageIcon pluginImage = null;

    JPanel framePanel    = null;
    JPanel inputPanel    = new JPanel();
    JPanel contentPanel  = new JPanel();
    JPanel imagePanel    = new JPanel();
    JPanel buttonPanel   = new JPanel();
    JPanel textPanel     = new JPanel();
    JPanel mainPanel     = new JPanel();
    JPanel inputPanelParent    = new JPanel();

    GridLayout   inputLayout   = new GridLayout();
    FlowLayout   buttonLayout  = new FlowLayout();
    GridLayout   contentLayout = new GridLayout();
    BorderLayout mainLayout    = new BorderLayout();
    BorderLayout frameLayout   = new BorderLayout();
    FlowLayout verticalFlowLayout1 = new FlowLayout();
    FlowLayout imageLayout = new FlowLayout();

    JLabel proxyServerLabel = new JLabel();
    JLabel proxyPortLabel   = new JLabel();
    JTextField proxyServerInput = new JTextField();
    JTextField proxyPortInput = new JTextField();
    JLabel useProxyLabel = new JLabel();
    JCheckBox useProxyCheckBox = new JCheckBox();

    SkinButton installButton = new SkinButton();
    SkinButton cancelButton = new SkinButton();
    SkinButton helpButton = new SkinButton();
    JLabel imageLabel = new JLabel();
    JLabel headerText = new JLabel();
    TitledBorder titledBorder1;
    JTextArea descText = new JTextArea();

    boolean isOk = false;
    GridLayout gridLayout1 = new GridLayout();

    public static void main(String[] args)
    {
        PluginUpdateDialog dlg =new PluginUpdateDialog();
        dlg.show();
    }

    protected PluginUpdateDialog(Frame frame, String title, boolean modal) {
        super(frame, title, modal);
        try
        {
            jbInit();
            pack();
            Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
            int w = getSize().width;
            int h = getSize().height;
            int x = (dim.width-w)/2;
            int y = (dim.height-h)/2;

            setBounds(x, y, w, h);
            toFront();
        }
        catch(Exception ex)
        {
            Trace.error("unable to init the dialog",ex);
        }
    }

    public PluginUpdateDialog()
    {
        this(null, "", true);
    }

    void jbInit() throws Exception
    {
        framePanel =new ImageBackgroundPanel();
        titledBorder1 = new TitledBorder("");
        setTitle( I18N.translate("Programm aktualisierung"));

        // input panel parent
        //
        verticalFlowLayout1.setAlignment(FlowLayout.RIGHT);
        verticalFlowLayout1.setVgap(50);
        inputPanelParent.setLayout(verticalFlowLayout1);
        gridLayout1.setRows(2);
        gridLayout1.setColumns(1);
        imageLayout.setHgap(10);
        imageLayout.setVgap(10);
        headerText.setBackground(SystemColor.info);
        descText.setBackground(SystemColor.info);
        inputPanelParent.add(inputPanel, null);
        inputPanelParent.setOpaque(false);

        // input panel
        //
        inputPanel.setLayout(inputLayout);
        inputPanel.setOpaque(false);
        inputLayout.setRows(3);
        inputLayout.setColumns(2);
        inputPanel.add(useProxyLabel, null);
        inputPanel.add(useProxyCheckBox, null);
        inputPanel.add(proxyServerLabel, null);
        inputPanel.add(proxyServerInput, null);
        inputPanel.add(proxyPortLabel, null);
        inputPanel.add(proxyPortInput, null);
        proxyServerLabel.setText(I18N.translate("HTTP-Proxy:"));
        proxyPortLabel.setText(I18N.translate("HTTP-Port:"));
        useProxyLabel.setText(I18N.translate("benutze einen HTTP Proxy"));
        proxyServerInput.setText("proxy");
        proxyServerInput.setEditable(false);
        proxyServerInput.setOpaque(false);
        proxyPortInput.setText("8080");
        proxyPortInput.setOpaque(false);
        proxyPortInput.setEditable(false);
        useProxyCheckBox.setOpaque(false);

        // image panel
        //
        imagePanel.setLayout(imageLayout);
        imagePanel.setOpaque(false);
        imageLayout.setAlignment(FlowLayout.CENTER);
        pluginImage  = new ImageIcon(de.freegroup.digitalsimulator.images.Resource.class.getResource("plugin.gif"));
        imageLabel.setIcon(pluginImage);
        imagePanel.add(imageLabel, null);

        // content panel
        //
        contentPanel.setLayout(contentLayout);
        contentPanel.setOpaque(false);
        contentLayout.setColumns(2);
        contentLayout.setRows(1);
        contentPanel.add(imagePanel);
        contentPanel.add(inputPanelParent);

        useProxyCheckBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(ActionEvent e) {
                useProxyCheckBox_actionPerformed(e);
            }
        });

        useProxyCheckBox.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                useProxyCheckBox_stateChanged(e);
            }
        });


        // Button Section
        //
        buttonLayout.setAlignment(FlowLayout.RIGHT);
        buttonPanel.setLayout(buttonLayout);
        buttonPanel.setOpaque(false);
        buttonPanel.add(installButton, null);
        buttonPanel.add(cancelButton, null);
        buttonPanel.add(helpButton, null);
        installButton.setText(I18N.translate("Aktualisieren"));
        cancelButton.setText(I18N.translate("Abbruch"));
        helpButton.setText(I18N.translate("Hilfe"));
        cancelButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(ActionEvent e) {
                cancelButton_actionPerformed(e);
            }
        });
        installButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(ActionEvent e) {
                installButton_actionPerformed(e);
            }
        });
        helpButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(ActionEvent e) {
                helpButton_actionPerformed(e);
            }
        });


        // Text section
        //
        textPanel.setLayout(gridLayout1);
        textPanel.add(headerText, null);
        textPanel.add(descText, null);
        textPanel.setBackground(SystemColor.info);
        textPanel.setOpaque(false);
        headerText.setFont(new java.awt.Font("SansSerif", 1, 18));
        headerText.setForeground(Color.black);
        headerText.setText(I18N.translate("Installieren von Programmerweiterungen."));
        headerText.setOpaque(true);
        descText.setText(I18N.translate("Es werden aktuelle Plugins von der WebSite www.DigitalSimulator.de herruntergeladen und aktiviert."));
        descText.setLineWrap(true);
        descText.setWrapStyleWord(true);
        descText.setEditable(false);
        descText.setFont(new java.awt.Font("SansSerif", 0, 12));
        descText.setOpaque(true);

        // main section
        //
        mainPanel.setOpaque(false);
        mainPanel.setLayout(mainLayout);
        mainPanel.setBorder(BorderFactory.createEtchedBorder());
        mainPanel.add(textPanel, BorderLayout.NORTH);
        mainPanel.add(contentPanel, BorderLayout.CENTER);


        // frame section
        //
        framePanel.setLayout(frameLayout);
        framePanel.setMaximumSize(new Dimension(600,380));
        framePanel.setMinimumSize(new Dimension(600, 380));
        framePanel.setPreferredSize(new Dimension(600, 380));
        framePanel.add(mainPanel  ,  BorderLayout.CENTER);
        framePanel.add(buttonPanel,  BorderLayout.SOUTH);
        getContentPane().add(framePanel, null);
        setContentPane(framePanel);
    }


    public boolean useProxy()
    {
        return useProxyCheckBox.isSelected();
    }

    public String getHTTPProxyHost()
    {
        return proxyServerInput.getText();
    }


    public String getHTTPProxyPort()
    {
        return proxyPortInput.getText();
    }

    public void setUseProxy(boolean value)
    {
        useProxyCheckBox.setSelected(value);
    }

    public void setHTTPProxyHost(String value)
    {
        proxyServerInput.setText(value);
    }


    public void setHTTPProxyPort(String value)
    {
        proxyPortInput.setText(value);
    }

    public boolean isOk()
    {
        return isOk;
    }
    void useProxyCheckBox_actionPerformed(ActionEvent e)
    {
        if(useProxyCheckBox.isSelected())
        {
            proxyServerInput.setEditable(true);
            proxyPortInput.setEditable(true);
        }
        else
        {
            proxyServerInput.setEditable(false);
            proxyPortInput.setEditable(false);
        }
    }

    void useProxyCheckBox_stateChanged(ChangeEvent e)
    {
        if(useProxyCheckBox.isSelected())
        {
            proxyServerInput.setEditable(true);
            proxyPortInput.setEditable(true);
        }
        else
        {
            proxyServerInput.setEditable(false);
            proxyPortInput.setEditable(false);
        }
    }

    void cancelButton_actionPerformed(ActionEvent e)
    {
        isOk = false;
        dispose();
    }

    void installButton_actionPerformed(ActionEvent e)
    {
        isOk = true;
        dispose();
    }

    void helpButton_actionPerformed(ActionEvent e)
    {
        new MsgBox(I18N.translate("Leider noch keine Hilfe verfügbar!"));
    }
}