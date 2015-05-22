/*
 * Created on Oct 24, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.ui;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.Collections;
import java.util.HashMap;
import java.util.Vector;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.ListSelectionModel;
import javax.swing.UIManager;
import javax.swing.event.ListSelectionEvent;

import com.holub.tools.Archive;

import de.freegroup.digitalsimulator.plugin.PluginManager;
import de.freegroup.ui.editor.JEditTextArea;
import de.freegroup.ui.editor.JavaTokenMarker;
import de.freegroup.util.clazz.MethodNode;

public class BeanEditor extends JDialog
{
	JPanel contentPanel = new JPanel(); //new JPanel();ImageBackgroundPanel
	BorderLayout borderLayout1 = new BorderLayout();
	JList fileList = null;
	JPanel inputPanel = new JPanel();
	BorderLayout borderLayout2 = new BorderLayout();
	JButton actionButton = new JButton();//SkinButton();
  JEditTextArea editor = new JEditTextArea();
	Vector methodNames = null;
	JLabel imageLabel = new JLabel();
	JLabel jLabel1 = new JLabel();
  String   currentMethod = null;
  Object   bean = null;
  HashMap  param2Class = new HashMap();
  
	public BeanEditor(Object object)
	{
		super((Frame) null, "Editor", true);
		try
		{
      bean = object;
      methodNames = new Vector();
      Field fields[]= object.getClass().getDeclaredFields();
      
      for(int i=0; i<fields.length; i++)
      {
          try
          {
            if(!Modifier.isPrivate(fields[i].getModifiers()))
            {
              String name  = fields[i].getName();
              if( object.getClass().getMethod("get"+firstUpper(name),new Class[0])!=null)
              {
                System.out.println(name);
                methodNames.add(name);
                param2Class.put(name, fields[i].getType());
              }
            }
          }
          catch (Exception ex)
          {
            System.out.println(ex);
            ex.printStackTrace();
          }
      }
      fileList = new JList(methodNames);
      
      contentPanel.setLayout(borderLayout1);
      inputPanel.setLayout(borderLayout2);
      actionButton.setText("Save");
      actionButton.addActionListener(new java.awt.event.ActionListener()
      {
        public void actionPerformed(ActionEvent e)
        {
          actionButton_actionPerformed(e);
        }
      });
      fileList.addListSelectionListener(new javax.swing.event.ListSelectionListener()
      {
        public void valueChanged(ListSelectionEvent e)
        {
          fileList_valueChanged(e);
        }
      });
      editor.setTokenMarker(new JavaTokenMarker());
      fileList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
      jLabel1.setBackground(UIManager.getColor("info"));
      jLabel1.setMaximumSize(new Dimension(319, 37));
      jLabel1.setMinimumSize(new Dimension(319, 37));
      jLabel1.setOpaque(true);
      jLabel1.setPreferredSize(new Dimension(319, 37));
      jLabel1.setText("Enter the object code.");
      getContentPane().add(contentPanel);
      contentPanel.add(fileList, BorderLayout.WEST);
      contentPanel.add(inputPanel, BorderLayout.SOUTH);
      contentPanel.add(editor, BorderLayout.CENTER);
      contentPanel.add(jLabel1, BorderLayout.NORTH);
      inputPanel.add(actionButton, BorderLayout.EAST);
			pack();
			Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
			int w = 500;
			int h = 300;
			int x = (dim.width - w) / 2;
			int y = (dim.height - h) / 2;
			setBounds(x, y, w, h);
   //   System.exit(1);
			show();
		}
		catch (Exception ex)
		{
			ex.printStackTrace();
		}
	}
 
	void actionButton_actionPerformed(ActionEvent e)
	{
		dispose();
    System.exit(1);
	}
  
  
	void fileList_valueChanged(ListSelectionEvent e)
	{

    if(currentMethod!=null)
    {
     
    }
    
    if(e.getValueIsAdjusting())
    {
      // save
    }
    else
    {
      // load
      currentMethod=fileList.getSelectedValue().toString();
      System.out.println(currentMethod);
      
      try
      {
        Class clazz=(Class)param2Class.get(currentMethod);
      
        Object[] data = { fileList.getSelectedValue()};
        Method method = bean.getClass().getMethod("set"+firstUpper(currentMethod),new Class[]{ (Class)param2Class.get(currentMethod)});
        System.out.println("calling '" + method.getName() + "'");
        method.invoke(bean, data);
      }
      catch(Throwable th)
      {
        th.printStackTrace();
      }
    }
  }
  
  String firstUpper(String prop)
  {
     return new String(new String(""+prop.charAt(0)).toUpperCase()  + prop.substring(1));
  }
}
