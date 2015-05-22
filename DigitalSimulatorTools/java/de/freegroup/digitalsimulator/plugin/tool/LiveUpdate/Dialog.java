package de.freegroup.digitalsimulator.plugin.tool.LiveUpdate;
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

import de.freegroup.digitalsimulator.Configuration;
import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.ui.*;
import javax.swing.border.*;

import com.jgoodies.forms.builder.PanelBuilder;
import com.jgoodies.forms.debug.FormDebugPanel;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import de.freegroup.digitalsimulator.dialogs.GenericDialog;
import de.freegroup.digitalsimulator.dialogs.MsgBox;
import de.freegroup.digitalsimulator.ui.HGradient;

public class Dialog extends GenericDialog 
{
    protected ImageIcon  pluginImage       = null;
    protected JTextField proxyServerInput  = null;
    protected JTextField proxyPortInput    = null;
    protected JCheckBox  useProxyCheckBox  = null;
    protected JLabel     imageLabel        = null;

    boolean   useProxy = false;
    String    proxy    = "";
    String    port     = "";
    
    public Dialog() 
    {
      super(I18N.get("COMMON.DIALOGHEADER.LIVEUPDATE"),
            I18N.get("LIVEUPDATE.LABEL.HELPHEADER"),
            I18N.get("LIVEUPDATE.LABEL.HELPLINE01"),
            I18N.get("LIVEUPDATE.LABEL.HELPLINE02"));

       show(630,450);
    }

    public boolean useProxy()
    {
      return useProxy;
    }

    public String getHTTPProxyHost()
    {
        return proxy;
    }


    public String getHTTPProxyPort()
    {
        return port;
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

    
      /* (non-Javadoc)
   * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#initComponents()
   */
  public void initComponents()
  {
    proxyServerInput  = new JTextField();
    proxyPortInput    = new JTextField();
    useProxyCheckBox  = new JCheckBox();
    imageLabel        = new JLabel();
    
    proxyServerInput.setText("proxy");
    proxyServerInput.setEditable(false);
    proxyPortInput.setText("8080");
    proxyPortInput.setEditable(false);

    // image panel
    //
    pluginImage  = new ImageIcon(Dialog.class.getResource("plugin.gif"));
    imageLabel.setIcon(pluginImage);

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
    
    // load the configuration settings
    //
    setUseProxy((Configuration.getString("proxySet").equalsIgnoreCase("true")));
    setHTTPProxyHost(Configuration.getString("proxyHost"));
    setHTTPProxyPort(Configuration.getString("proxyPort"));
  }

/* (non-Javadoc)
	 * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#buildInputPanel()
	 */
	public Component buildInputPanel()
	{
    FormLayout layout = new FormLayout(
        "right:pref, 5dlu,1dlu,5dlu,p,2dlu, fill:100dlu:grow",  // rows
        "10dlu:grow, p,3dlu,p,3dlu,p,p,10dlu:grow");            // columns
    
    PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
    if(debug)
      builder = new PanelBuilder(new FormDebugPanel(),layout);
    builder.setDefaultDialogBorder();

    CellConstraints cc = new CellConstraints();

    builder.add(imageLabel                                  , cc.xywh(1,  1, 1, 8));
    builder.add(new HGradient(Color.lightGray,Color.darkGray), cc.xywh(3,1,1,8,"f,f"));

    builder.addLabel(I18N.get("LIVEUPDATE.LABEL.USEPROXY")   , cc.xy(5, 2));
    builder.add(useProxyCheckBox                             , cc.xy(7, 2));
    builder.addLabel(I18N.get("LIVEUPDATE.LABEL.PROXYHOST")  , cc.xy(5, 4));
    builder.add(proxyServerInput                             , cc.xy(7, 4));
    builder.addLabel(I18N.get("LIVEUPDATE.LABEL.PROXYPORT")  , cc.xy(5, 6));
    builder.add(proxyPortInput                               , cc.xy(7, 6));
    
    return builder.getPanel();
  }


	/* (non-Javadoc)
	 * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#onCancel()
	 */
	public void onCancel()
	{
	}

	/* (non-Javadoc)
	 * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#onOk()
	 */
	public void onOk()
	{
    proxy    = proxyServerInput.getText();
    port     = proxyPortInput.getText();
    useProxy = useProxyCheckBox.isSelected();
	}
}