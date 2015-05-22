/*
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

package de.freegroup.digitalsimulator.plugin.tool.PluginWizard;
import java.awt.Component;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Vector;

import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.event.ListSelectionEvent;
import javax.swing.text.PlainDocument;

import com.jgoodies.forms.builder.PanelBuilder;
import com.jgoodies.forms.debug.FormDebugPanel;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import de.freegroup.digitalsimulator.Configuration;
import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.dialogs.GenericDialog;
import de.freegroup.digitalsimulator.plugin.object.*;
import de.freegroup.ui.editor.JEditTextArea;
import de.freegroup.ui.editor.JavaTokenMarker;
import de.freegroup.ui.spinner.IntegerSpinner;


public final class WizardObjectCustomize extends GenericDialog
{
  JTextField  developerField        = null;
  JTextField  emailField            = null;
  JTextField  urlField              = null;
  
  JTextArea   objectDescription     = null;
  JComboBox   groupCombo            = null;
  JTextField  nameField             = null;

//  IntegerSpinner  versionField      = null;
  IntegerSpinner  widthField        = null;
  IntegerSpinner  heightField       = null;
  IntegerSpinner  inputField        = null;
  IntegerSpinner  outputField       = null;
  IntegerSpinner  parameterField    = null;

  JComponent  objectDescriptionPane = null;
  JList         eventList           = null;
  JScrollPane   eventListScrollPane = null;
  JEditTextArea eventCode           = null;
  String        currentMethod       = null;
  Vector        objectGroups        = null;
  String[]      methods             = null;
  Map           modifiedMethods     = null;                                      
  MutableObjectPlugin object        = null;
  JTabbedPane   tabbedPane          = null;
  
	public static void main(String[] args)
	{
//    Application.onInit();
	//	new WizardObjectCustomize(new SimpleLED());
	}
  
	public WizardObjectCustomize(MutableObjectPlugin obj)
	{
    super(I18N.get("COMMON.DIALOGHEADER.WIZARDOBJECTCUSTOMIZE"),
          I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.HELPHEADER"),
          I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.HELPLINE01"),
          I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.HELPLINE02"));

    object=obj;

    // set the default width and height
    //
    int w = 650;
    int h = 500;
    
    // try to restore the last dialog size from the property file
    //
    try{w = Configuration.getInt("WizardObjectCustomize.width",w);}catch(Exception exc){Trace.error("unable to parse width");}
    try{h = Configuration.getInt("WizardObjectCustomize.height",h);}catch(Exception exc){Trace.error("unable to parse height");}
    show(w,h);
	}


  /**
   * 
   * @return
   */
	public Component buildInputPanel()
	{
    // create the tab-pane component
    //
//		tabbedPane.putClientProperty("jgoodies.noContentBorder", Boolean.TRUE);
    tabbedPane.add(buildSteckbriefPanel()   ,  I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.DESCRIPTION"));
    tabbedPane.add(buildEigenschaftenPanel(),  I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.PROPERTIES"));
    tabbedPane.add(buildVerhaltenPanel()    ,  I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.BEHAVIOUR"));
    
    // select the last displayed tab pane
    //
    int index = Configuration.getInt("WizardObjectCustomize.selectedTab",0);
    tabbedPane.setSelectedIndex(index);
    
    // select the last display/edited method on the behaviour pane
    //
    String lastMethod = Configuration.getString("WizardObjectCustomize.selectedMethod");
    if(lastMethod!=null && lastMethod.length()>0)
    {
      setCurrentMethod(lastMethod);
      eventList.setSelectedValue(lastMethod,true);
    }
    
    return tabbedPane;
	}
  
  /**
   * 
   *
   */
  public void initComponents()
  {
    methods = new String[]{         "layoutInput",
                                    "layoutOutput",
                                    "onButtonClick",
                                    "onButtonDblClick",
                                    "onButtonDown",
                                    "onButtonUp",
                                    "onMouseOver",
                                    "onMouseOverStart",
                                    "onMouseOverEnd",
                                    "onStartCalculate",
                                    "onStopCalculate",
                                    "paint",
                                    "calculate"
                                    };
    modifiedMethods = new HashMap();
    objectGroups = new Vector();
    Vector transObjectGroups = new Vector();
    Enumeration enum =  I18N.getKeys();
    while (enum.hasMoreElements())
		{
			String element = (String) enum.nextElement();
      if(element.startsWith("OBJECTGROUP"))
      {
        objectGroups.add(element);
        transObjectGroups.add(I18N.get(element));
      }
    }
    tabbedPane        = new JTabbedPane();
    developerField    = new JTextField();
    emailField        = new JTextField();
    urlField          = new JTextField();
    groupCombo        = new JComboBox(transObjectGroups.toArray());
    nameField         = new JTextField();
    objectDescription = new JTextArea("");
    eventCode         = new JEditTextArea();
    eventCode.setTokenMarker(new JavaTokenMarker());
    eventCode.setText("");
    eventCode.getDocument().putProperty(PlainDocument.tabSizeAttribute, new Integer(4));
    
    
//    versionField      = new IntegerSpinner(1,100,1,1);
    widthField        = new IntegerSpinner(50,500,10,100);
    heightField       = new IntegerSpinner(50,500,10,100);
    inputField        = new IntegerSpinner(0,10,1,1);
    outputField       = new IntegerSpinner(0,10,1,1);
    parameterField    = new IntegerSpinner(0,10,1,1);
    
//    versionField.setEnabled(false);
    
    objectDescriptionPane =  new JScrollPane(objectDescription);
    if(object!=null)
    {
      developerField.setText(object.getProgrammerName());
      emailField.setText(object.getProgrammerMail());
      urlField.setText(object.getProgrammerURL());
      objectDescription.setText(object.getDescription());
//      versionField.setValue(object.getVersion());
      groupCombo.setSelectedItem(I18N.get(object.getGroup()));
      nameField.setText(object.getName());
      widthField.setValue(object.getSize(1,1)[0]);
      heightField.setValue(object.getSize(1,1)[1]);
      inputField.setValue(object.getInputCountRange()[0]);
      outputField.setValue(object.getOutputCountRange()[0]);
      parameterField.setValue(object.getParamCount());
    }
    
    eventList = new JList(methods);
    eventListScrollPane = new JScrollPane(eventList);
    eventList.addListSelectionListener(new javax.swing.event.ListSelectionListener()
    {
        public void valueChanged(ListSelectionEvent e)
        {
          eventList_valueChanged(e);
        }
    });
  }
 
  /**
   * 
   * @return
   */
	private Component buildSteckbriefPanel()
	{
    // Create a FormLayout instance on the given column and row specs. 
    // For almost all forms you specify the columns; sometimes rows are 
    // created dynamically. In this case the labels are right aligned.
    FormLayout layout = new FormLayout(
            "right:pref, 3dlu, fill:200dlu:grow",                              // cols
            "p, 3dlu,p, 3dlu, p, 3dlu, p, 9dlu, p, 3dlu, p, 3dlu, p, 3dlu, p, 3dlu, fill:50dlu:grow");    // rows
        
    // Create a builder that assists in adding components to the container. 
    // Wrap the panel with a standardized border.
    PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
    if(debug)
      builder = new PanelBuilder(new FormDebugPanel(),layout);
    builder.setDefaultDialogBorder();

    // Obtain a reusable constraints object to place components in the grid.
    CellConstraints cc = new CellConstraints();

    // Fill the grid with components; the builder offers to create
    // frequently used components, e.g. separators and labels.
        
    // Add a titled separator to cell (1, 1) that spans 7 columns and 1 row.
    builder.addSeparator(I18N.get("WIZARDOBJECTCUSTOMIZE.SEPARATOR.DEVELOPER"),   cc.xywh(1,  1, 3, 1));
    builder.addLabel(I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.NAME"),             cc.xy  (1,  3));
    builder.add(developerField,                    cc.xy  (3,  3));
    builder.addLabel(I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.EMAIL"),            cc.xy  (1,  5));
    builder.add(emailField,                        cc.xy  (3,  5));
    builder.addLabel(I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.URL"),              cc.xy  (1,  7));
    builder.add(urlField,                          cc.xy  (3,  7));

    builder.addSeparator(I18N.get("WIZARDOBJECTCUSTOMIZE.SEPARATOR.OBJECT"),       cc.xywh(1, 9, 3, 1));
    builder.addLabel(I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.NAME"),             cc.xy  (1, 11));
    builder.add(nameField,                         cc.xy  (3, 11));
    builder.addLabel(I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.GROUP"),           cc.xy  (1, 13));
    builder.add(groupCombo,                        cc.xy  (3, 13));
    builder.addLabel(I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.VERSION"),          cc.xy  (1, 15));
    if(object!=null)
    	builder.addLabel(""+object.getVersion(),                      cc.xy  (3, 15));
    builder.addLabel(I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.DESCRIPTION"),     cc.xy  (1, 17,"right, top"));
    builder.add(objectDescriptionPane,             cc.xy  (3, 17,"fill, fill"));
        
		return builder.getPanel();
	}
  
  /**
   * 
   * @return
   */
  private Component buildEigenschaftenPanel()
  {
    // Create a FormLayout instance on the given column and row specs. 
    // For almost all forms you specify the columns; sometimes rows are 
    // created dynamically. In this case the labels are right aligned.
    FormLayout layout = new FormLayout(
            "right:pref, 3dlu, fill:200dlu:grow",                              // cols
            "p, 3dlu,p, 3dlu, p, 3dlu, p, 9dlu, p, 3dlu, p, 3dlu, p, 3dlu, p, 3dlu, fill:50dlu:grow");    // rows
        
    // Create a builder that assists in adding components to the container. 
    // Wrap the panel with a standardized border.
    PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
    if(debug)
      builder = new PanelBuilder(new FormDebugPanel(),layout);
    builder.setDefaultDialogBorder();

    // Obtain a reusable constraints object to place components in the grid.
    CellConstraints cc = new CellConstraints();

    // Fill the grid with components; the builder offers to create
    // frequently used components, e.g. separators and labels.
        
    // Add a titled separator to cell (1, 1) that spans 7 columns and 1 row.
    builder.addSeparator(I18N.get("WIZARDOBJECTCUSTOMIZE.SEPARATOR.VIEW"),    cc.xywh(1,  1, 3, 1));
    builder.addLabel(I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.WIDTH"),           cc.xy  (1,  3));
    builder.add(widthField,                                                   cc.xy  (3,  3));
    builder.addLabel(I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.HEIGHT"),          cc.xy  (1,  5));
    builder.add(heightField,                                                  cc.xy  (3,  5));

    builder.addSeparator(I18N.get("WIZARDOBJECTCUSTOMIZE.SEPARATOR.FUNCTION"),cc.xywh(1, 9, 3, 1));
    builder.addLabel(I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.INPUTCOUNT"),      cc.xy  (1, 11));
    builder.add(inputField,                                                   cc.xy  (3, 11));
    builder.addLabel(I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.OUTPUTCOUNT"),     cc.xy  (1, 13));
    builder.add(outputField,                                                  cc.xy  (3, 13));
    builder.addLabel(I18N.get("WIZARDOBJECTCUSTOMIZE.LABEL.PARAMETERS"),      cc.xy  (1, 15));
    builder.add(parameterField,                                               cc.xy  (3, 15));
        
    return builder.getPanel();
  }
  
  
  /**
   * 
   * @return
   */
  private Component buildVerhaltenPanel()
  {
    // Create a FormLayout instance on the given column and row specs. 
    // For almost all forms you specify the columns; sometimes rows are 
    // created dynamically.
    FormLayout layout = new FormLayout(
            "p, 2dlu,5dlu,2dlu, fill:200dlu:grow,p",  // cols
            "p, fill:50dlu:grow,p");        // rows
        
    // Create a builder that assists in adding components to the container. 
    // Wrap the panel with a standardized border.
    PanelBuilder builder = new PanelBuilder(new JPanel(),layout);
    if(debug)
      builder = new PanelBuilder(new FormDebugPanel(),layout);
    builder.setDefaultDialogBorder();

    // Obtain a reusable constraints object to place components in the grid.
    //
    CellConstraints cc = new CellConstraints();

    // Fill the grid with components; the builder offers to create
    // frequently used components, e.g. separators and labels.
    //
    builder.addSeparator(I18N.get("WIZARDOBJECTCUSTOMIZE.SEPARATOR.EVENT"),     cc.xy(1, 1));
    builder.add(eventListScrollPane,            cc.xywh(1, 2, 1, 2));
    builder.addSeparator(I18N.get("WIZARDOBJECTCUSTOMIZE.SEPARATOR.CODE"),  cc.xy(5, 1));
    builder.add(eventCode,                      cc.xy(5, 2));
    builder.add(new StatusBar(eventCode),       cc.xy(5,3));
    return builder.getPanel();
  }

  public void onOk()
  {
    Configuration.setString("WizardObjectCustomize.selectedTab",""+tabbedPane.getSelectedIndex());
    Configuration.setString("WizardObjectCustomize.selectedMethod",currentMethod);
    if(object!=null)
    {
			object.setProgrammerName(developerField.getText());
			object.setProgrammerMail(emailField.getText());
			object.setProgrammerURL(urlField.getText());
			object.setDescription(objectDescription.getText());
      
			object.setGroup((String)objectGroups.get(groupCombo.getSelectedIndex()));
//			object.setVersion(versionField.getValue());
      object.setName(nameField.getText());
			object.setWidth(widthField.getValue());
			object.setHeight(heightField.getValue());
			object.setInputCount(inputField.getValue());
			object.setOutputCount(outputField.getValue());
			object.setParamCount(parameterField.getValue());

      
      //  update all modified methods of the object
      //  
			Iterator iter = modifiedMethods.keySet().iterator();
			while (iter.hasNext())
			{
				String event    = (String) iter.next();
				String newCode  = (String) modifiedMethods.get(event);
        String origCode = object.getData(event);
        if(!newCode.equals(origCode))
        {
        	object.setData(event, newCode);
          object.setChanged(true);
        }
			}
      // update the current edited method
      //
			if (currentMethod != null)
      { 
        String newCode = eventCode.getText();
        String oldCode = object.getData(currentMethod);
        if(!newCode.equals(oldCode))
        {  
          object.setData(currentMethod, eventCode.getText());
          object.setChanged(true);
        }
      }
      
      if(object.hasChanged())
      {
        object.setVersion(object.getVersion()+1);
        object.setChanged(false);
      }
      
      int w = getSize().width;
      int h = getSize().height;
			Configuration.setString("WizardObjectCustomize.width", "" + w);
			Configuration.setString("WizardObjectCustomize.height", "" + h);
    }
  }


  public void onCancel()
  {
  }

  private void eventList_valueChanged(ListSelectionEvent e)
  {
    if(!e.getValueIsAdjusting())
    {
      String code  ="";
      if(currentMethod!=null)
      {
        code = eventCode.getText();
        modifiedMethods.put(currentMethod,code);        
      }
      setCurrentMethod((String)eventList.getSelectedValue());
    }
  }
  /**
   * update the editor and the internal state with the new code
   * for the selected object method.
   * 
   * @param method
   */
  private void setCurrentMethod(String method)
  {
    currentMethod = method;
    String code = (String)modifiedMethods.get(method);
    if(code==null && object!=null)
    {
      code =object.getData(method);
      modifiedMethods.put(method,code);
    }
    eventCode.setText(code);
    eventCode.setCaretPosition(0);
  }
}
