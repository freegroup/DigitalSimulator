package de.freegroup.digitalsimulator.export.webshare.dialogs;

import java.awt.Color;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.io.IOException;
import java.net.MalformedURLException;
import java.util.StringTokenizer;
import java.util.Vector;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;

import org.apache.tools.ant.taskdefs.Sleep;
import org.xml.sax.SAXException;

import HTTPClient.Codecs;
import HTTPClient.HTTPConnection;
import HTTPClient.HTTPResponse;
import HTTPClient.ModuleException;
import HTTPClient.NVPair;

import com.jgoodies.forms.builder.PanelBuilder;
import com.jgoodies.forms.debug.FormDebugPanel;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;
import com.meterware.httpunit.GetMethodWebRequest;
import com.meterware.httpunit.WebConversation;
import com.meterware.httpunit.WebRequest;
import com.meterware.httpunit.WebResponse;

import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.dialogs.GenericDialog;
import de.freegroup.digitalsimulator.ui.HGradient;

public class WebFileManager extends GenericDialog
{
  String user;
  String passwd;
  String simFile;
  String screenShoot;
  
  JButton  deleteButton        = null;
  JList fileList = null;
  Vector fileNames = null;
  JLabel imageLabel = new JLabel();
  JTextField fileNameTextField = new JTextField();

  public WebFileManager( String user,  String passwd,  String simFile,  String screenShoot)
  {
    super(
      I18N.get("COMMON.DIALOGHEADER.WEBSHARE"),
      I18N.get("WEBSHARE.LABEL.HELPHEADER"),
      I18N.get("WEBSHARE.LABEL.HELPLINE01"),
      I18N.get("WEBSHARE.LABEL.HELPLINE02"));

    this.user =user;
    this.passwd=passwd;
    this.simFile=simFile;
    this.screenShoot=screenShoot;
    
    show(650, 400);
  }

  public void initComponents()
  {
    ImageIcon pluginImage = new ImageIcon( de.freegroup.digitalsimulator.images.Resource.class.getResource("webshare.gif"));
    imageLabel.setIcon(pluginImage);

    
    deleteButton = new JButton(I18N.get("COMMON.BUTTON.DELETE"));
    deleteButton.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        onDelete();
      }
    });
    
    fileList = new JList(fileNames);
    fileList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
    fileList.addListSelectionListener(new javax.swing.event.ListSelectionListener()
    {
      public void valueChanged(ListSelectionEvent e)
      {
        fileList_valueChanged(e);
      }
    });
    buildFileList();
    
    fileNameTextField.setText("");
    fileNameTextField.addKeyListener(new java.awt.event.KeyAdapter()
    {
      public void keyTyped(KeyEvent e)
      {
        fileNameTextField_keyTyped(e);
      }
    });
  }

  /**
   *  
   */
  public Component buildInputPanel()
  {
    FormLayout layout = new FormLayout
    												(
        											"p,pref:grow, 2dlu, 12dlu, fill:pref:grow,p",
        											"fill:pref:grow, 2dlu, p"
        										);

    PanelBuilder builder = new PanelBuilder(new JPanel(), layout);
    if (debug)
      builder = new PanelBuilder(new FormDebugPanel(), layout);
    builder.setDefaultDialogBorder();

    CellConstraints cc = new CellConstraints();

    builder.add(new HGradient(Color.lightGray, Color.darkGray), cc.xy(3, 1));

    builder.add(imageLabel, cc.xywh(1, 1,2,1));
    builder.add(fileList, cc.xywh(5, 1,2,1));
    builder.add(fileNameTextField, cc.xy(5, 3));
    builder.addLabel("Dateiname:", cc.xywh(2, 3,3,1,"r,f"));
    builder.add(deleteButton, cc.xy(6,3));
    
    return builder.getPanel();
  }

  /**
   *  Upload the selected file to the WebShare
   */
  public void onOk()
  {
    try
    {
      HTTPConnection con = new HTTPConnection("www.DigitalSimulator.de");
      NVPair[] opts = {
          				new NVPair("user", user),
          				new NVPair("password", passwd),
          				new NVPair("targetName", getFilename())};
      NVPair[] file = { 
          				new NVPair("simFile", simFile), 
          				new NVPair("screenshoot", screenShoot)};
      NVPair[] hdrs = new NVPair[1];
      byte[] data = Codecs.mpFormDataEncode(opts, file, hdrs);
      HTTPResponse res = con.Post("webstore/upload.php3", data, hdrs);
    }
    catch (Exception e)
    {
      e.printStackTrace();
    }
  }

  /**
   *  
   */
  public void onCancel()
  {
  }

  /**
   *  
   */
  public void onDelete()
  {
    try
    {
      HTTPConnection con = new HTTPConnection("www.DigitalSimulator.de");
      NVPair[] opts = {
          new NVPair("user", user),
          new NVPair("password", passwd),
          new NVPair("targetName", getFilename())};
 //      NVPair[] hdrs = new NVPair[1];
 //     byte[] data = Codecs.mpFormDataEncode(opts, hdrs);
      HTTPResponse res = con.Post("webstore/delete.php3", opts);
      // wait a time before refresh the file list.
      Thread.sleep(1000);
      buildFileList();
    }
    catch (Exception e)
    {
      e.printStackTrace();
    }
  }

  private void buildFileList()
  {
    try
    {
      System.out.println("BUILD FILE LIST:");
      WebConversation conversation = new WebConversation();
      WebRequest request =   new GetMethodWebRequest("http://www.DigitalSimulator.de/webstore/filelist.php3");
      request.setParameter("dummy",""+ System.currentTimeMillis());
      request.setParameter("user", user);
      request.setParameter("password", passwd);
      WebResponse response = conversation.getResponse(request);

      StringTokenizer token = new StringTokenizer(response.getText(), "\n\r");
      fileNames = new Vector();
      while (token.hasMoreTokens())
      {
        String filename = token.nextToken();
        filename = filename.substring(0, filename.length() - 5);
        System.out.println("\tadding:"+filename);
        fileNames.add(filename);
      }
      
      fileList.setListData(fileNames);
      fileList.setSelectedIndex(-1);
    }
    catch (Exception e)
    {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
  }
  /**
   * @return
   */
  public String getFilename()
  {
    return fileNameTextField.getText();
  }

  void fileList_valueChanged(ListSelectionEvent e)
  {
    if(fileList.getSelectedValue()!=null)
      fileNameTextField.setText(fileList.getSelectedValue().toString());
    else
    fileNameTextField.setText("");
  }

  void fileNameTextField_keyTyped(KeyEvent e)
  {
    char c = e.getKeyChar();
    if (Character.isLetter(c) || c == '_')
      return;
    else if (Character.isISOControl(c))
      return;
    else if (Character.isDigit(c))
      return;
    e.consume();
  }

  /**
   * only to test his class
   */
  public static void main(String[] args)
  {
    new WebFileManager("andreas_herz","anshez","xyz.dsim","xyz.png");
    System.exit(1);
  }
}
