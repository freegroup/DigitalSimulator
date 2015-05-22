package de.freegroup.digitalsimulator.export.dialog;


import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import javax.swing.event.*;
import de.freegroup.ui.*;
import javax.swing.border.*;
import java.util.*;
import java.util.Collections;
import de.freegroup.digitalsimulator.ui.ImageBackgroundPanel;
import de.freegroup.digitalsimulator.dialogs.MsgBox;
import I18N;
import Trace;
import de.freegroup.digitalsimulator.export.*;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */

public class SelectExportModulDialog extends JDialog {


    JPanel framePanel    = null;
    JPanel inputPanel    = new JPanel();
    JPanel contentPanel  = new JPanel();
    JPanel imagePanel    = new JPanel();
    JPanel buttonPanel   = new JPanel();
    JPanel textPanel     = new JPanel();
    JPanel mainPanel     = new JPanel();

    BorderLayout inputLayout   = new BorderLayout();
    FlowLayout   buttonLayout  = new FlowLayout();
    BorderLayout   contentLayout = new BorderLayout();
    BorderLayout mainLayout    = new BorderLayout();
    BorderLayout frameLayout   = new BorderLayout();
    FlowLayout verticalFlowLayout1 = new FlowLayout();
    FlowLayout imageLayout = new FlowLayout();

    SkinButton exportButton = new SkinButton();
    SkinButton cancelButton  = new SkinButton();
    SkinButton helpButton    = new SkinButton();

    JLabel headerText = new JLabel();
    TitledBorder titledBorder1;
    JTextArea descText = new JTextArea();

    boolean isOk = false;
    GridLayout gridLayout1 = new GridLayout();
    JList exportList = new JList();
    JTextArea beschreibung = new JTextArea();
    JScrollPane scrollPane1 = new JScrollPane();

   ITransformer transformer=null;

    public static void main(String[] args)
    {
        SelectExportModulDialog dlg =new SelectExportModulDialog();
        dlg.show();
    }

    protected SelectExportModulDialog(Frame frame, String title, boolean modal) {
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

    public SelectExportModulDialog()
    {
        this(null, "", true);
    }

    void jbInit() throws Exception
    {
        framePanel =new ImageBackgroundPanel();
        titledBorder1 = new TitledBorder("");
        setTitle( I18N.translate("Schaltung exportieren"));

        // input panel parent
        //
        verticalFlowLayout1.setAlignment(FlowLayout.RIGHT);
        verticalFlowLayout1.setVgap(50);
        gridLayout1.setRows(2);
        gridLayout1.setColumns(1);
        imageLayout.setHgap(10);
        imageLayout.setVgap(10);
        headerText.setBackground(SystemColor.info);
        descText.setBackground(SystemColor.info);

        // input panel
        //
        inputPanel.setLayout(inputLayout);
        inputPanel.setOpaque(false);
        beschreibung.setEditable(false);
        beschreibung.setText("");
       // beschreibung.setLineWrap(true);
        beschreibung.setOpaque(false);
        beschreibung.setRequestFocusEnabled(false);
        beschreibung.setDoubleBuffered(true);
        beschreibung.setEditable(false);
        scrollPane1.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        scrollPane1.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
        scrollPane1.getViewport().add(beschreibung, null);
        inputPanel.add(scrollPane1, BorderLayout.CENTER);
        inputPanel.setOpaque(false);

        // selection panel
        //
        Vector plugins = new Vector(ExportManager.getExportModuls().keySet());
        Collections.sort(plugins);
        Object []data = plugins.toArray();
     //   Collections.sort();
        exportList = new JList(data);
        exportList.setOpaque(false);
        exportList.addListSelectionListener(new javax.swing.event.ListSelectionListener()
        {
            public void valueChanged(ListSelectionEvent e)
            {
                exportList_valueChanged(e);
            }
        });
        imagePanel.setLayout(imageLayout);
        imagePanel.setOpaque(false);
        imageLayout.setAlignment(FlowLayout.LEFT);
        imagePanel.add(exportList, null);


        // content panel
        //
        contentPanel.setLayout(contentLayout);
        contentPanel.setOpaque(false);
//        contentLayout.setColumns(2);
//        contentLayout.setRows(1);
        contentPanel.add(imagePanel,BorderLayout.WEST);
        contentPanel.add(inputPanel,BorderLayout.CENTER);

        // Button Section
        //
        buttonLayout.setAlignment(FlowLayout.RIGHT);
        buttonPanel.setLayout(buttonLayout);
        buttonPanel.setOpaque(false);
        buttonPanel.add(exportButton, null);
        buttonPanel.add(cancelButton, null);
        buttonPanel.add(helpButton, null);
        exportButton.setText(I18N.translate("Exportieren"));
        cancelButton.setText(I18N.translate("Abbruch"));
        helpButton.setText(I18N.translate("Hilfe"));
        cancelButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(ActionEvent e) {
                cancelButton_actionPerformed(e);
            }
        });
        exportButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(ActionEvent e) {
                exportButton_actionPerformed(e);
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
        headerText.setText(I18N.translate("Exportieren der digital Schaltung"));
        headerText.setOpaque(true);
        descText.setText(I18N.translate("Bitte wählen Sie das Format in welches Sie die Schaltung exportieren wollen, und bestätigen Sie dies mit dem 'Export' Button."));
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
        framePanel.setMinimumSize(new Dimension(650, 380));
        framePanel.setPreferredSize(new Dimension(650, 380));
        framePanel.add(mainPanel  ,  BorderLayout.CENTER);
        framePanel.add(buttonPanel,  BorderLayout.SOUTH);
        getContentPane().add(framePanel, null);
        setContentPane(framePanel);
    }


    public boolean isOk()
    {
        return isOk;
    }

    public ITransformer getTransformer()
    {
      return transformer;
    }

    void cancelButton_actionPerformed(ActionEvent e)
    {
        isOk = false;
        dispose();
    }

    void exportButton_actionPerformed(ActionEvent e)
    {
        isOk = true;
        dispose();
    }

    void helpButton_actionPerformed(ActionEvent e)
    {
        new MsgBox(I18N.translate("Leider noch keine Hilfe verfügbar!"));
    }

   void exportList_valueChanged(ListSelectionEvent e) {
    transformer = ExportManager.getModul((String) ((JList) e.getSource()).getSelectedValue());

      beschreibung.setText(transformer.getDescription());
   }
}