// Decompiled by Jad v1.5.8e2. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://kpdus.tripod.com/jad.html
// Decompiler options: packimports(3) 

package de.freegroup.digitalsimulator.plugin.rs232;

import com.jgoodies.forms.builder.AbstractFormBuilder;
import com.jgoodies.forms.builder.PanelBuilder;
import com.jgoodies.forms.debug.FormDebugPanel;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;
import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.dialogs.GenericDialog;
import de.freegroup.digitalsimulator.ui.HGradient;
import de.freegroup.ui.spinner.IntegerSpinner;

import java.awt.Color;
import java.awt.Component;

import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class RS232Dialog extends GenericDialog
{
  IntegerSpinner portId;
  int id;
  protected JLabel     imageLabel        = null;
  
    public RS232Dialog(int i)
    {
        super(I18N.get("COMMON.DIALOGHEADER.OBJECTRS232"), 
              I18N.get("OBJECTRS232.LABEL.HELPHEADER"), 
              I18N.get("OBJECTRS232.LABEL.HELPLINE01"), 
              I18N.get("OBJECTRS232.LABEL.HELPLINE02"));
        portId = null;
        id = 1;
        id = i;
        show(680, 550);
    }

    public Component buildInputPanel()
    {
        FormLayout formlayout = new FormLayout("5dlu,p:grow,1dlu,right:p,5dlu 50dlu", 
                                                "10dlu, p,10dlu");
        
        PanelBuilder builder = new PanelBuilder(new JPanel(), formlayout);
        if(GenericDialog.debug)
          builder = new PanelBuilder(new FormDebugPanel(), formlayout);
        builder.setDefaultDialogBorder();
        
        CellConstraints cc = new CellConstraints();
        builder.add(imageLabel                                   , cc.xy(2,  2));
        //builder.add(new HGradient(Color.lightGray,Color.darkGray), cc.xywh(3,1,1,8,"f,f"));
        builder.addLabel(I18N.get("OBJECTRS232.LABEL.PORTID"), cc.xy(4, 2));
        builder.add(portId, cc.xy(6, 2));
        return builder.getPanel();
    }

    public byte getPortId()
    {
        return (byte)portId.getValue();
    }

    public void initComponents()
    {
        portId = new IntegerSpinner(1, 2, 1, id);
        // image panel
        //
 //       pluginImage  = new ImageIcon(RS232Dialog.class.getResource("pinout.gif"));
        imageLabel = new JLabel();
        imageLabel.setIcon(new ImageIcon(RS232Dialog.class.getResource("pinout.gif")));
    }

    public static void main(String args[])
    {
        new RS232Dialog(10);
    }

    public void onCancel()
    {
    }

    public void onOk()
    {
    }
}
