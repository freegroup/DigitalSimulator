package de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation;
/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */


import java.awt.Component;
import java.io.StringReader;
import java.io.StringWriter;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.UIManager;

import org.exolab.castor.xml.MarshalException;
import org.exolab.castor.xml.Marshaller;
import org.exolab.castor.xml.ValidationException;

import com.jgoodies.clearlook.ClearLookManager;
import com.jgoodies.clearlook.ClearLookMode;
import com.jgoodies.forms.builder.PanelBuilder;
import com.jgoodies.forms.debug.FormDebugPanel;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;
import com.jgoodies.plaf.FontSizeHints;
import com.jgoodies.plaf.Options;
import com.jgoodies.plaf.plastic.Plastic3DLookAndFeel;

import de.freegroup.digitalsimulator.Document;
import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.dialogs.GenericDialog;
import de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.DocumentDocumentation;
import de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.V01x00;
import de.freegroup.util.xml.XMLSAXCopyToHandler;
import de.freegroup.util.xml.XMLWriter;

public class Dialog extends GenericDialog 
{
  JTextArea  shortDescription = null;
  JTextArea  longDescription  = null;
  
  JTextField firstName = null;
  JTextField lastName  = null;
  JTextField street    = null;
  JTextField number    = null;
  JTextField zipCode   = null;
  JTextField city      = null;
  JTextField eMail     = null;
  JTextField version   = null;
  
  DocumentDocumentation docObject = null;
  String                readedVersion=null;
  /**
     * only to test this class
     * 
     * @param args
     */
    public static void main(String[] args)
		{
      UIManager.put("Application.useSystemFontSettings", Boolean.TRUE);
      Options.setGlobalFontSizeHints(FontSizeHints.MIXED);
      ClearLookManager.setMode(ClearLookMode.ON);
      try
      {
        UIManager.setLookAndFeel("com.jgoodies.plaf.plastic.PlasticXPLookAndFeel");
      }
      catch (Exception e)
      {
        // Likely PlasticXP is not in the class path; ignore.
      }
      Plastic3DLookAndFeel.setHighContrastFocusColorsEnabled(true);
      UIManager.put("Application.useSystemFontSettings", Boolean.TRUE);
      UIManager.put(Options.USE_SYSTEM_FONTS_APP_KEY, Boolean.TRUE);
      UIManager.put("ScrollBar.is3DEnabled", Boolean.FALSE);
      Options.setGlobalFontSizeHints(FontSizeHints.MIXED);
      Plastic3DLookAndFeel.setFontSizeHints(FontSizeHints.SYSTEM);
			new Dialog();
		}
  
    /**
     * The main constructor
     *
     */
    public Dialog() 
    {
      super(I18N.get("COMMON.DIALOGHEADER.DOCUMENTDOCUMENTATION"),
            I18N.get("DOCUMENTDOCUMENTATION.LABEL.HELPHEADER"),
            I18N.get("DOCUMENTDOCUMENTATION.LABEL.HELPLINE01"),
            I18N.get("DOCUMENTDOCUMENTATION.LABEL.HELPLINE02"));
      
       show(750,600);
    }


    
  /* (non-Javadoc)
   * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#initComponents()
   */
  public void initComponents()
  {
    shortDescription =  new JTextArea();
    longDescription  =  new JTextArea();
    
    firstName = new JTextField();
    lastName  = new JTextField();
    street    = new JTextField();
    number    = new JTextField();
    zipCode   = new JTextField();
    city      = new JTextField();
    eMail     = new JTextField();
    version   = new JTextField();
    
    try
		{
      String currentDoc =Document.getCurrentDocumentation();
      if(currentDoc.equals(""))
        currentDoc = V01x00_template;
 
      try
			{
				docObject = DocumentDocumentation.unmarshal(new StringReader(currentDoc));
			}
			catch (Exception e1)
			{
				// unable to parse the documentation XML. Init it with a new default
        // value
				Trace.error(e1);
        docObject = DocumentDocumentation.unmarshal(new StringReader(V01x00_template));
      }
      // version switch between the different documentation schemas
      //
      if(docObject.getVersion().getV01x00()!=null)
      {
        readedVersion = "V01x00";
        V01x00 doc = docObject.getVersion().getV01x00();
        firstName.setText(doc.getAuthor().getFirstName());
        lastName.setText(doc.getAuthor().getLastName());
        street.setText(doc.getAuthor().getStreet());
        number.setText(doc.getAuthor().getNumber());
        zipCode.setText(doc.getAuthor().getZipCode());
        city.setText(doc.getAuthor().getCity());
        eMail.setText(doc.getAuthor().getEMail());
        shortDescription.setText(doc.getCircuit().getShortDescription());
        longDescription.setText(doc.getCircuit().getLongDescription());
        version.setText(doc.getCircuit().getVersion());
      }
		}
		catch (Exception e)
		{
			Trace.error(e);
		}
  }

  /* (non-Javadoc)
	 * @see de.freegroup.digitalsimulator.dialogs.GenericDialog#buildInputPanel()
	 */
	public Component buildInputPanel()
	{
    FormLayout layout = new FormLayout(
        "5dlu,right:p,3dlu,fill:p:grow,5dlu",    // cols
        "5dlu,p,3dlu,p,3dlu,p,3dlu,p,3dlu,p,3dlu,p,3dlu,p,3dlu,p,3dlu,p,3dlu,p,3dlu,fill:50dlu,3dlu,fill:p:grow,5dlu");   // rows
    
    PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
    if(debug)
      builder = new PanelBuilder(new FormDebugPanel(),layout);
    builder.setDefaultDialogBorder();

    CellConstraints cc = new CellConstraints();

    builder.addSeparator(I18N.get("DOCUMENTDOCUMENTATION.LABEL.AUTHOR"), cc.xywh(1,2,5,1));
    builder.addLabel(I18N.get("DOCUMENTDOCUMENTATION.LABEL.FIRSTNAME"), cc.xy(2,4));
    builder.add(firstName, cc.xy(4,4));

    builder.addLabel(I18N.get("DOCUMENTDOCUMENTATION.LABEL.LASTNAME"), cc.xy(2,6));
    builder.add(lastName, cc.xy(4,6));

    builder.addLabel(I18N.get("DOCUMENTDOCUMENTATION.LABEL.STREET"), cc.xy(2,8));
    builder.add(street, cc.xy(4,8));

    builder.addLabel(I18N.get("DOCUMENTDOCUMENTATION.LABEL.NUMBER"), cc.xy(2,10));
    builder.add(number, cc.xy(4,10));

    builder.addLabel(I18N.get("DOCUMENTDOCUMENTATION.LABEL.ZIPCODE"), cc.xy(2,12));
    builder.add(zipCode, cc.xy(4,12));

    builder.addLabel(I18N.get("DOCUMENTDOCUMENTATION.LABEL.CITY"), cc.xy(2,14));
    builder.add(city, cc.xy(4,14));
    
    builder.addLabel(I18N.get("DOCUMENTDOCUMENTATION.LABEL.EMAIL"), cc.xy(2,16));
    builder.add(eMail, cc.xy(4,16));
    
    
    builder.addSeparator(I18N.get("DOCUMENTDOCUMENTATION.LABEL.CIRCUIT"), cc.xywh(1,18,5,1));
    builder.addLabel(I18N.get("DOCUMENTDOCUMENTATION.LABEL.VERSION"), cc.xy(2,20,"right,top"));
    builder.add(version, cc.xy(4,20));
    
    builder.addLabel(I18N.get("DOCUMENTDOCUMENTATION.LABEL.SHORTDESCRIPTION"), cc.xy(2,22,"right,top"));
    builder.add(new JScrollPane(shortDescription), cc.xy(4,22));
    
    builder.addLabel(I18N.get("DOCUMENTDOCUMENTATION.LABEL.LONGDESCRIPTION"), cc.xy(2,24,"right,top"));
    builder.add(new JScrollPane(longDescription), cc.xy(4,24));
    
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
    try
		{
			// write in the same version 
			//
			if(readedVersion.equals("V01x00"))
			{  
				V01x00 doc = docObject.getVersion().getV01x00();
			  doc.getAuthor().setFirstName(firstName.getText());
			  doc.getAuthor().setLastName(lastName.getText());
        doc.getAuthor().setCity(city.getText());
        doc.getAuthor().setNumber(number.getText());
        doc.getAuthor().setStreet(street.getText());
        doc.getAuthor().setZipCode(zipCode.getText());
        doc.getCircuit().setLongDescription(longDescription.getText());
        doc.getCircuit().setShortDescription(shortDescription.getText());
			}
			Document.setCurrentDocumentation(toXml(docObject));
		}
		catch (Exception e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    
 	}
  
  public final static String toXml(Object document) throws Exception
  {
    StringWriter sw = new StringWriter();
    XMLWriter xw = new XMLWriter(sw,false);
    XMLSAXCopyToHandler dh = new XMLSAXCopyToHandler(xw);
    Marshaller.marshal(document, dh);

    return sw.toString();
  }
  
  String V01x00_template=
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"+
"<DocumentDocumentation>"+
"  <version>"+
"    <v_01x00>"+
"      <author>"+
"        <firstName></firstName>"+
"        <lastName></lastName>"+
"        <street></street>"+
"        <number></number>"+
"        <city></city>"+
"        <zipCode></zipCode>"+
"        <eMail></eMail>"+
"      </author>"+
"      <circuit>"+
"        <name></name>"+
"        <version></version>"+
"        <shortDescription></shortDescription>"+
"        <longDescription></longDescription>"+
"      </circuit>"+
"    </v_01x00>"+
"  </version>"+
"</DocumentDocumentation>";

}