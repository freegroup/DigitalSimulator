/*
 * Translation editor for Java properties files.
 * 
 */
package de.freegroup.digitalsimulator.plugin.tool.I18NEditor;
import javax.swing.*;
import javax.swing.table.*;
import javax.swing.tree.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import java.text.*;

import de.freegroup.digitalsimulator.Configuration;
import de.freegroup.digitalsimulator.I18N;
import de.freegroup.digitalsimulator.plugin.tool.ITool;
import de.freegroup.util.i18n.*;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class I18NEditor
{
	private static String version = "1.0";
//	private static ResourceBundle labels = ResourceBundle.getBundle(I18NEditor.class.getName(), Locale.getDefault());
	private static UberProperties props = new UberProperties();
	private static String[] userFile = new String[] { ".java", "com", "Ostermiller", "attesoro", "Editor.ini" };
	private static String defaultFile = "de/freegroup/digitalsimulator/plugin/tool/I18NEditor/I18NEditor.ini";
	private JFrame frame = new JFrame(I18N.get("COMMON.DIALOGHEADER.LOCALISATIONTOOL"));
	private JCheckBox useDefaultComment = new JCheckBox(I18N.get("LOCALISATIONTOOL.USEDEFAULT.COMMENT"));
	private JTextArea defaultCommentArea = new JTextArea();
	private JTextArea commentArea = new JTextArea();
	private JCheckBox useDefaultText = new JCheckBox(I18N.get("LOCALISATIONTOOL.USEDEFAULT.TEXT"));
	private JTextArea defaultTextArea = new JTextArea();
	private JTextArea translationArea = new JTextArea();
	private JSplitPane textSplitPane, editingSplitPane, navigationSplitPane;
	private JComboBox languageBox, countryBox, variantBox;
	private JPanel newLocalePanel;
	private boolean modifying = false;
	private boolean globalModified = false;
	private DefaultMutableTreeNode workingNode = null;
	private String workingName = null;
	private int workingIndex = -1;
	private ArrayList names;
	private JTree tree;
	private DefaultTreeModel treeModel;
	private DefaultMutableTreeNode top;
	private JTable table;
	private JLabel defaultCommentLabel, commentLabel, translationLabel, defaultTranslationLabel;
	private JMenuItem revertKeyMenuItem, revertKeyPopupMenuItem, addKeyMenuItem, addKeyPopupMenuItem, addLangPopupMenuItem, addLangMenuItem, renameKeyMenuItem, renameKeyPopupMenuItem, deleteKeyMenuItem, deleteKeyPopupMenuItem;
	private JPopupMenu tablePopup, treePopup;
	private File openFile;
	private JMenuItem saveMenuItem;
  

  /**
	 * @param ind
	 * @return
	 */
	private Name getName(int ind)
	{
		return (Name) names.get(ind);
	}
  
	/**
	 * @param name
	 */
	private void addKey(String name)
	{
		saveTextAreas();
		Name n = new Name(name);
		n.isModified = true;
		names.add(n);
		Collections.sort(names);
		TranslationData data = (TranslationData) top.getUserObject();
		data.properties.setProperty(name, "");
		data.addremove = true;
		table.revalidate();
		table.repaint(table.getBounds());
		int rowNum = names.indexOf(n);
		table.setRowSelectionInterval(rowNum, rowNum);
		table.scrollRectToVisible(table.getCellRect(rowNum, 0, true));
		globalModified = true;
	}
  
	/**
	 * @param oldName
	 * @param newName
	 */
	private void renameKey(String oldName, String newName)
	{
		saveTextAreas();
		Name n = getName(workingIndex);
		n.name = newName;
		n.isModified = true;
		for (Enumeration nodeList = top.depthFirstEnumeration(); nodeList.hasMoreElements();)
		{
			TranslationData data = (TranslationData) (((DefaultMutableTreeNode) nodeList.nextElement()).getUserObject());
			data.properties.setProperty(newName, data.properties.getProperty(oldName), data.properties.getComment(oldName));
			data.properties.setProperty(oldName, null);
		}
		Collections.sort(names);
		int rowNum = names.indexOf(n);
		table.setRowSelectionInterval(rowNum, rowNum);
		table.scrollRectToVisible(table.getCellRect(rowNum, 0, true));
		globalModified = true;
	}

  /**
	 * @param name
	 */
	private void deleteKey(String name)
	{
		saveTextAreas();
		for (Enumeration nodeList = top.depthFirstEnumeration(); nodeList.hasMoreElements();)
		{
			UberProperties p = ((TranslationData) (((DefaultMutableTreeNode) nodeList.nextElement()).getUserObject())).properties;
			p.setProperty(name, null);
		}
		names.remove(workingIndex);
		table.clearSelection();
		table.revalidate();
		table.repaint(table.getBounds());
		globalModified = true;
	}
  
  
  
  
	private void saveTextAreas()
	{
		if (workingNode == null)
			return;
		if (workingName == null)
			return;
		TranslationData data = (TranslationData) workingNode.getUserObject();
		UberProperties saveProps = data.properties;
		String saveComment = null;
		if (!useDefaultComment.isSelected())
		{
			saveComment = commentArea.getText();
		}
		String saveTranslation = null;
		if (!useDefaultText.isSelected())
		{
			saveTranslation = translationArea.getText();
		}
		saveProps.setProperty(workingName, saveTranslation, saveComment);
		boolean wasModified = getName(workingIndex).isModified;
		boolean modified = isModified(workingName);
		getName(workingIndex).isDefault = isDefault(workingName);
		getName(workingIndex).isModified = modified;
		if (wasModified && !modified)
			data.modified--;
		if (!wasModified && modified)
			data.modified++;
		tree.repaint(tree.getBounds());
		table.repaint(table.getBounds());
	}
  
  
  
  
  
	private void fillNameData()
	{
		TranslationData data = null;
		if (workingNode != null)
			data = (TranslationData) workingNode.getUserObject();
		if (data != null)
			data.modified = 0;
		for (int i = 0; i < names.size(); i++)
		{
			getName(i).isDefault = isDefault(getName(i).name);
			getName(i).isModified = isModified(getName(i).name);
			if (data != null && getName(i).isModified)
				data.modified++;
		}
		if (tree != null)
			tree.repaint(tree.getBounds());
		if (table != null)
			table.repaint(table.getBounds());
	}
  
  
  
  
  /**
   * 
   * @param popup
   * @param component
   * @param x
   * @param y
   */
	private void showPopUpSmart(JPopupMenu popup, Component component, int x, int y)
	{
		popup.show(component, x, y);
		boolean reshow = false;
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		Dimension popupSize = popup.getSize();
		Point screenLocation = popup.getLocationOnScreen();
		x = screenLocation.x;
		y = screenLocation.y;
		if (screenLocation.x + popupSize.width > screenSize.width)
		{
			x = screenSize.width - popupSize.width;
			reshow = true;
		}
		if (screenLocation.y + popupSize.height > screenSize.height)
		{
			y = screenSize.height - popupSize.height;
			reshow = true;
		}
		if (reshow)
		{
			popup.setLocation(x, y);
		}
	}
  
  /**
   * 
   * @param name
   * @return
   */
	private boolean isDefault(String name)
	{
		if (workingNode == null)
			return false;
		TranslationData data = (TranslationData) workingNode.getUserObject();
		UberProperties saveProps = data.properties;
		UberProperties initProps = data.initProperties;
		return (saveProps.getProperty(name) == null && saveProps.getComment(name) == null);
	}
  
  /**
   * 
   * @param name
   * @return
   */
	private boolean isModified(String name)
	{
		if (workingNode == null)
			return false;
		TranslationData data = (TranslationData) workingNode.getUserObject();
		UberProperties saveProps = data.properties;
		UberProperties initProps = data.initProperties;
		return ((!stringsEqual(saveProps.getProperty(name), initProps.getProperty(name))) || (!stringsEqual(saveProps.getComment(name), initProps.getComment(name))));
	}
  
  /**
   * 
   * @param a
   * @param b
   * @return
   */
	private static boolean stringsEqual(String a, String b)
	{
		if (a == null && b == null)
			return true;
		if (a == null)
			return false;
		if (b == null)
			return false;
		return (a.equals(b));
	}
  
  /**
   * 
   *
   */
	private void setTextAreas()
	{
		modifying = true;
		boolean enable = workingNode != null && workingName != null;
		boolean isTop = (workingNode == null || top == workingNode);
		defaultTranslationLabel.setEnabled(!isTop);
		defaultCommentLabel.setEnabled(!isTop);
		commentLabel.setText(I18N.get(isTop ? "LOCALISATIONTOOL.LABEL.COMMENT" : "LOCALISATIONTOOL.LABEL.TRANSLATEDCOMMENT"));
		translationLabel.setText(I18N.get(isTop ? "LOCALISATIONTOOL.LABEL.TEXT" : "LOCALISATIONTOOL.LABEL.TRANSLATEDTEXT"));
		useDefaultText.setEnabled(!isTop && enable);
		String translation = getProperty();
		boolean useDefault = enable && (translation == null);
		useDefaultText.setSelected(!isTop && useDefault);
		translationArea.setText(((!enable) || (translation == null)) ? "" : translation);
		translationArea.setEditable(enable);
		defaultCommentArea.setText(getDefaultComment());
		useDefaultComment.setText(I18N.get(isTop ? "LOCALISATIONTOOL.LABEL.USEDEFAULTCOMMENT" : "LOCALISATIONTOOL.LABEL.USEDEFAULTCOMMENT"));
		useDefaultComment.setEnabled(enable && !useDefault);
		String comment = getComment();
		useDefaultComment.setSelected(enable && (useDefault || (comment == null)));
		commentArea.setText((useDefault || (comment == null)) ? "" : comment);
		commentArea.setEditable(enable && !useDefault);
		defaultTextArea.setText(getDefaultProperty());
		revertKeyMenuItem.setEnabled(enable);
		revertKeyPopupMenuItem.setEnabled(enable);
		addKeyMenuItem.setEnabled(enable);
		addKeyPopupMenuItem.setEnabled(enable);
		renameKeyMenuItem.setEnabled(enable);
		renameKeyPopupMenuItem.setEnabled(enable);
		deleteKeyMenuItem.setEnabled(enable);
		deleteKeyPopupMenuItem.setEnabled(enable);
		modifying = false;
	}
  
  /**
   * 
   * @return
   */
	private String getComment()
	{
		if (workingNode == null)
			return null;
		if (workingName == null)
			return null;
		return ((TranslationData) workingNode.getUserObject()).properties.getComment(workingName);
	}
  
  /**
   * 
   * @return
   */
	private String getProperty()
	{
		if (workingNode == null)
			return null;
		if (workingName == null)
			return null;
		return ((TranslationData) workingNode.getUserObject()).properties.getProperty(workingName);
	}
  
  /**
   * 
   * @return
   */
	private String getDefaultComment()
	{
		if (workingNode == null)
			return "";
		if (workingName == null)
			return "";
		DefaultMutableTreeNode tempNode = workingNode;
		while (!tempNode.isRoot())
		{
			tempNode = (DefaultMutableTreeNode) tempNode.getParent();
			String retval = ((TranslationData) tempNode.getUserObject()).properties.getComment(workingName);
			if (retval != null)
				return retval;
		}
		return "";
	}
  
  /**
   * 
   * @return
   */
	private String getDefaultProperty()
	{
		if (workingNode == null)
			return "";
		if (workingName == null)
			return "";
		DefaultMutableTreeNode tempNode = workingNode;
		while (!tempNode.isRoot())
		{
			tempNode = (DefaultMutableTreeNode) tempNode.getParent();
			String retval = ((TranslationData) tempNode.getUserObject()).properties.getProperty(workingName);
			if (retval != null)
				return retval;
		}
		return "";
	}
  
  /**
   * 
   * @param names
   * @return
   */
	private ArrayList getNames(String[] names)
	{
		ArrayList fullNames = new ArrayList(names.length);
		for (int i = 0; i < names.length; i++)
		{
			fullNames.add(new Name(names[i]));
		}
		return fullNames;
	}
  
  /**
   * 
   * @author Administrator
   *
   * To change the template for this generated type comment go to
   * Window>Preferences>Java>Code Generation>Code and Comments
   */
	private class Name implements Comparable
	{
		public String name;
		public boolean isDefault = false;
		public boolean isModified = false;
		public Name(String name)
		{
			this.name = name;
		}
		public int compareTo(Object o)
		{
			if (o == null)
				return -1;
			if (!(o instanceof Name))
				return -1;
			return name.compareTo(((Name) o).name);
		}
		public String toString()
		{
			return name;
		}
	}
  /**
   * 
   */
	private TableModel tableModel = new AbstractTableModel()
	{
		public int getColumnCount()
		{
			return 1;
		}
		public String getColumnName(int col)
		{
			return I18N.get("LOCALISATIONTOOL.LABEL.NAME");
		}
		public int getRowCount()
		{
			if (names == null)
				return 0;
			return names.size();
		}
		public Object getValueAt(int row, int col)
		{
			return getName(row);
		}
	};
  
  /**
   * 
   * @param s
   * @return
   */
	private static boolean isUpper(String s)
	{
		for (int i = 0; i < s.length(); i++)
		{
			char c = s.charAt(i);
			if (c < 'A' || c > 'Z')
				return false;
		}
		return true;
	}
  
  /**
   * 
   * @param s
   * @return
   */
	private static boolean isLower(String s)
	{
		for (int i = 0; i < s.length(); i++)
		{
			char c = s.charAt(i);
			if (c < 'a' || c > 'z')
				return false;
		}
		return true;
	}
  
  /**
   * 
   * @param args
   * @throws IOException
   */
	public void load(File f) throws IOException
	{
		if (f == null)
			throw new IOException();
		File parent = f.getCanonicalFile().getParentFile();
		if (parent == null)
			throw new IOException();
		String baseName = f.getName();
		if (baseName.endsWith(".properties"))
		{
			baseName = baseName.substring(0, baseName.length() - 11);
		}
		final String finalBaseName = baseName;
		frame.setTitle(I18N.get("COMMON.DIALOGHEADER.LOCALISATIONTOOL"));
		frame.setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
		//UberProperties props = new UberProperties();
		props.load(new FileInputStream(f));
		names = getNames(props.propertyNames());
		Collections.sort(names);
		top.removeAllChildren();
		top.setUserObject(new TranslationData(baseName, "", props));
		File[] transFiles = parent.listFiles(new FileFilter()
		{
			public boolean accept(File pathname)
			{
				String s = pathname.getName();
				if (!s.startsWith(finalBaseName + "_"))
					return false;
				if (!s.endsWith(".properties"))
					return false;
				String locale = s.substring(finalBaseName.length() + 1, s.length() - 11);
				String[] localeData = StringHelper.split(locale, "_");
				if (localeData.length < 1)
					return false;
				if (localeData.length > 3)
					return false;
				if (localeData[0].length() != 2)
					return false;
				if (!isLower(localeData[0]))
					return false;
				if (localeData.length > 1)
				{
					if (localeData[1].length() != 2)
						return false;
					if (!isUpper(localeData[1]))
						return false;
				}
				if (localeData.length > 2)
				{
					if (localeData[2].length() == 0)
						return false;
					if (!isUpper(localeData[2]))
						return false;
				}
				return true;
			}
		});
		Arrays.sort(transFiles);
		for (int i = 0; i < transFiles.length; i++)
		{
			String s = transFiles[i].getName();
			s = s.substring(finalBaseName.length() + 1, s.length() - 11);
			String language = null;
			String country = null;
			String variant = null;
			StringTokenizer st = new StringTokenizer(s, "_");
			if (st.hasMoreTokens())
				language = st.nextToken();
			if (st.hasMoreTokens())
				country = st.nextToken();
			if (st.hasMoreTokens())
				variant = st.nextToken();
			DefaultMutableTreeNode nextNode = createTreeNode(top, language, country, variant, new FileInputStream(transFiles[i]));
		}
		setTextAreas();
		fillNameData();
		workingNode = top;
		workingName = null;
		workingIndex = -1;
		addLangMenuItem.setEnabled(true);
		addLangPopupMenuItem.setEnabled(true);
		saveMenuItem.setEnabled(true);
		openFile = f.getAbsoluteFile();
		treeModel.reload();
		tree.expandPath(new TreePath(top));
		table.revalidate();
		table.repaint(table.getBounds());
		globalModified = false;
	}
  
  
  /**
   * 
   * @param top
   * @param language
   * @param country
   * @param variant
   * @param in
   * @return
   * @throws IOException
   */
	private DefaultMutableTreeNode createTreeNode(DefaultMutableTreeNode top, String language, String country, String variant, InputStream in) throws IOException
	{
		DefaultMutableTreeNode languageNode = null;
		String locale = language;
		for (Enumeration e = top.children(); e.hasMoreElements();)
		{
			DefaultMutableTreeNode node = (DefaultMutableTreeNode) e.nextElement();
			TranslationData data = (TranslationData) node.getUserObject();
			if (data.locale.equals(locale))
				languageNode = node;
		}
		if (languageNode == null)
		{
			String nodeName;
			try
			{
				nodeName = I18N.get("language_" + language);
			}
			catch (MissingResourceException mre)
			{
				nodeName = language;
			}
			UberProperties props = new UberProperties();
			if (country == null && in != null)
				props.load(in);
			languageNode = new DefaultMutableTreeNode(new TranslationData(nodeName, locale, props));
			top.add(languageNode);
		}
		if (country == null)
			return languageNode;
		DefaultMutableTreeNode countryNode = null;
		locale = language + "_" + country;
		for (Enumeration e = languageNode.children(); e.hasMoreElements();)
		{
			DefaultMutableTreeNode node = (DefaultMutableTreeNode) e.nextElement();
			TranslationData data = (TranslationData) node.getUserObject();
			if (data.locale.equals(locale))
				countryNode = node;
		}
		if (countryNode == null)
		{
			String nodeName;
			try
			{
				nodeName = I18N.get("country_" + country);
			}
			catch (MissingResourceException mre)
			{
				nodeName = country;
			}
			UberProperties props = new UberProperties();
			if (variant == null && in != null)
				props.load(in);
			countryNode = new DefaultMutableTreeNode(new TranslationData(nodeName, locale, props));
			languageNode.add(countryNode);
		}
		if (variant == null)
			return countryNode;
		DefaultMutableTreeNode variantNode = null;
		locale = language + "_" + country + "_" + variant;
		for (Enumeration e = countryNode.children(); e.hasMoreElements();)
		{
			DefaultMutableTreeNode node = (DefaultMutableTreeNode) e.nextElement();
			TranslationData data = (TranslationData) node.getUserObject();
			if (data.locale.equals(locale))
				variantNode = node;
		}
		if (variantNode == null)
		{
			String nodeName;
			try
			{
				nodeName = I18N.get("variant_" + variant);
			}
			catch (MissingResourceException mre)
			{
				nodeName = variant;
			}
			UberProperties props = new UberProperties();
			if (in != null)
				props.load(in);
			variantNode = new DefaultMutableTreeNode(new TranslationData(nodeName, locale, props));
			countryNode.add(variantNode);
		}
		return variantNode;
	}
  
  /**
   * 
   * @author Administrator
   *
   * To change the template for this generated type comment go to
   * Window>Preferences>Java>Code Generation>Code and Comments
   */
	private class TranslationData
	{
		public String locale;
		public UberProperties properties;
		public UberProperties initProperties;
		public boolean addremove = false;
		public int modified = 0;
		public String name;
		TranslationData(String name, String locale, UberProperties properties)
		{
			this.locale = locale;
			this.properties = properties;
			this.initProperties = new UberProperties(properties);
			this.name = name;
		}
		public String toString()
		{
			return name;
		}
	}
  
  /**
   * 
   * @throws IOException
   */
	public I18NEditor() throws IOException
	{
		new I18NEditor(null);
	}
  
  /**
   * 
   * @param f
   * @throws IOException
   */
	public I18NEditor(File f) throws IOException
	{
//		Browser.init();
		props.load(userFile, defaultFile);
		int x, y;
		try
		{
			x = Integer.parseInt(props.getProperty("window_size_x", "600"), 10);
			y = Integer.parseInt(props.getProperty("window_size_y", "440"), 10);
		}
		catch (NumberFormatException e)
		{
			x = 600;
			y = 440;
		}
		frame.setSize(x, y);
		try
		{
			x = Integer.parseInt(props.getProperty("window_location_x", "50"), 10);
			y = Integer.parseInt(props.getProperty("window_location_y", "50"), 10);
		}
		catch (NumberFormatException e)
		{
			x = 50;
			y = 50;
		}
		frame.setLocation(x, y);
//		frame.setIconImage(new ImageIcon(ClassLoader.getSystemResource("I18NEttesoro.png")).getImage());
		defaultCommentLabel = new JLabel(I18N.get("LOCALISATIONTOOL.LABEL.DEFAULTCOMMENT"));
		commentArea.setEditable(false);
		translationArea.setEditable(false);
		defaultCommentArea.setEditable(false);
		defaultCommentArea.setBackground(defaultCommentLabel.getBackground());
		defaultTextArea.setEditable(false);
		defaultTextArea.setBackground(defaultCommentLabel.getBackground());
		JPanel commentPane = new JPanel(new VerticalLayout());
		commentPane.add(defaultCommentLabel);
		commentPane.add(defaultCommentArea);
		BorderLayout commentLabelPanelLayout = new BorderLayout();
		commentLabelPanelLayout.setHgap(15);
		JPanel commentLabelPanel = new JPanel(commentLabelPanelLayout);
		commentLabel = new JLabel(I18N.get("LOCALISATIONTOOL.LABEL.COMMENT"));
		commentLabelPanel.add(commentLabel, BorderLayout.WEST);
		commentLabelPanel.add(useDefaultComment, BorderLayout.CENTER);
		commentPane.add(commentLabelPanel);
		commentPane.add(commentArea);
		useDefaultComment.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				if (!modifying)
				{
					modifying = true;
					commentArea.setText("");
					modifying = false;
					;
				}
			}
		});
		commentArea.getDocument().addDocumentListener(new DocumentListener()
		{
			public void changedUpdate(DocumentEvent e)
			{
			}
			public void insertUpdate(DocumentEvent e)
			{
				if (!modifying)
				{
					modifying = true;
					useDefaultComment.setSelected(false);
					if (!getName(workingIndex).isModified)
					{
						getName(workingIndex).isModified = true;
						((TranslationData) workingNode.getUserObject()).modified++;
						tree.repaint(tree.getBounds());
						table.repaint(table.getBounds());
					}
					modifying = false;
				}
			}
			public void removeUpdate(DocumentEvent e)
			{
			}
		});
		JPanel translationPane = new JPanel(new VerticalLayout());
		defaultTranslationLabel = new JLabel(I18N.get("LOCALISATIONTOOL.LABEL.TRANSLATION"));
		translationPane.add(defaultTranslationLabel);
		translationPane.add(defaultTextArea);
		BorderLayout translationLabelPanelLayout = new BorderLayout();
		translationLabelPanelLayout.setHgap(15);
		JPanel translationLabelPanel = new JPanel(translationLabelPanelLayout);
		translationLabel = new JLabel(I18N.get("LOCALISATIONTOOL.LABEL.TEXT"));
		translationLabelPanel.add(translationLabel, BorderLayout.WEST);
		translationLabelPanel.add(useDefaultText, BorderLayout.CENTER);
		translationPane.add(translationLabelPanel);
		translationPane.add(translationArea);
		useDefaultText.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				if (!modifying)
				{
					modifying = true;
					translationArea.setText("");
					commentArea.setText("");
					boolean state = useDefaultText.isSelected();
					boolean isTop = (workingNode == null || top == workingNode);
					useDefaultComment.setEnabled(!isTop && !state);
					useDefaultComment.setSelected(!isTop);
					commentArea.setEditable(!state);
					modifying = false;
					;
				}
			}
		});
		translationArea.getDocument().addDocumentListener(new DocumentListener()
		{
			public void changedUpdate(DocumentEvent e)
			{
			}
			public void insertUpdate(DocumentEvent e)
			{
				if (!modifying)
				{
					modifying = true;
					useDefaultText.setSelected(false);
					if (!getName(workingIndex).isModified)
					{
						getName(workingIndex).isModified = true;
						((TranslationData) workingNode.getUserObject()).modified++;
						tree.repaint(tree.getBounds());
						table.repaint(table.getBounds());
					}
					modifying = false;
				}
			}
			public void removeUpdate(DocumentEvent e)
			{
			}
		});
		textSplitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, new JScrollPane(translationPane), new JScrollPane(commentPane));
		top = new DefaultMutableTreeNode(new TranslationData("", "", new UberProperties()));
		treeModel = new DefaultTreeModel(top);
		tree = new JTree(treeModel);
		tree.addMouseListener(new MouseAdapter()
		{
			public void mousePressed(MouseEvent e)
			{
				int selRow = tree.getRowForLocation(e.getX(), e.getY());
				if (!tree.isRowSelected(selRow))
				{
					// select the row
					tree.setSelectionRow(selRow);
				}
				if (selRow != -1)
				{
					if (e.isPopupTrigger() || (e.getModifiers() & InputEvent.BUTTON3_MASK) != 0)
					{
						showPopUpSmart(treePopup, e.getComponent(), e.getX(), e.getY());
					}
				}
			}
		});
		tree.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
		tree.addTreeSelectionListener(new TreeSelectionListener()
		{
			public void valueChanged(TreeSelectionEvent e)
			{
				saveTextAreas();
				workingNode = (DefaultMutableTreeNode) tree.getLastSelectedPathComponent();
				setTextAreas();
				fillNameData();
			}
		});
		tree.setCellRenderer(new DefaultTreeCellRenderer()
		{
			public Component getTreeCellRendererComponent(JTree tree, Object value, boolean sel, boolean expanded, boolean leaf, int row, boolean hasFocus)
			{
				super.getTreeCellRendererComponent(tree, value, sel, expanded, leaf, row, hasFocus);
				TranslationData data = ((TranslationData) ((DefaultMutableTreeNode) value).getUserObject());
				boolean modified = ((data.modified > 0) || data.addremove);
				setForeground(modified ? Color.green.darker() : Color.black);
				return this;
			}
		});
		table = new JTable(tableModel);
		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		table.addMouseListener(new MouseAdapter()
		{
			public void mousePressed(MouseEvent e)
			{
				int selRow = table.rowAtPoint(e.getPoint());
				if (!table.isRowSelected(selRow))
				{
					// select the row
					table.setRowSelectionInterval(selRow, selRow);
				}
				if (selRow != -1)
				{
					if (e.isPopupTrigger() || (e.getModifiers() & InputEvent.BUTTON3_MASK) != 0)
					{
						showPopUpSmart(tablePopup, e.getComponent(), e.getX(), e.getY());
					}
				}
			}
		});
		table.setDefaultRenderer(Object.class, new DefaultTableCellRenderer()
		{
			public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column)
			{
				super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
				Color color = Color.black;
				Name name = (Name) value;
				if (name.isDefault)
					color = Color.blue.darker();
				if (name.isModified)
					color = Color.green.darker();
        if(isSelected)
          color = Color.white;
        if(!isSelected && workingNode!=null)
        {
          String trans = ((TranslationData)workingNode.getUserObject()).properties.getProperty(name.name);
          if(trans==null || trans.length()==0)
            color = Color.red;
        }
        setForeground(color);
				return this;
			}
		});
		table.getSelectionModel().addListSelectionListener(new ListSelectionListener()
		{
			public void valueChanged(ListSelectionEvent e)
			{
				if (e.getValueIsAdjusting())
					return;
				ListSelectionModel lsm = (ListSelectionModel) e.getSource();
				saveTextAreas();
				if (lsm.isSelectionEmpty())
				{
					workingName = null;
					workingIndex = -1;
				}
				else
				{
					workingIndex = lsm.getMinSelectionIndex();
					workingName = getName(workingIndex).name;
				}
				setTextAreas();
			}
		});
		navigationSplitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, new JScrollPane(tree), new JScrollPane(table));
		editingSplitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, navigationSplitPane, textSplitPane);
		frame.getContentPane().add(editingSplitPane);
		int splitpaneLocation;
		splitpaneLocation = 100;
		try
		{
			splitpaneLocation = Integer.parseInt(props.getProperty("editing_split_pane_divider", ""), 10);
			if (splitpaneLocation <= 0)
			{
				splitpaneLocation = 100;
			}
		}
		catch (NumberFormatException e)
		{
		}
		editingSplitPane.setDividerLocation(splitpaneLocation);
		splitpaneLocation = 250;
		try
		{
			splitpaneLocation = Integer.parseInt(props.getProperty("text_split_pane_divider", ""), 10);
			if (splitpaneLocation <= 0)
			{
				splitpaneLocation = 250;
			}
		}
		catch (NumberFormatException e)
		{
		}
		textSplitPane.setDividerLocation(splitpaneLocation);
		splitpaneLocation = 100;
		try
		{
			splitpaneLocation = Integer.parseInt(props.getProperty("navigation_split_pane_divider", ""), 10);
			if (splitpaneLocation <= 0)
			{
				splitpaneLocation = 100;
			}
		}
		catch (NumberFormatException e)
		{
		}
		navigationSplitPane.setDividerLocation(splitpaneLocation);
		frame.addWindowListener(new WindowAdapter()
		{
			public void windowClosing(WindowEvent e)
			{
				exitRoutine();
			}
		});
		JMenuBar menuBar = new JMenuBar();
		JMenu fileMenu = new JMenu(I18N.get("LOCALISATIONTOOL.MENU.FILE"));
    /*
    fileMenu.setMnemonic(I18N.get("file_menu_key").charAt(0));
		fileMenu.getAccessibleContext().setAccessibleDescription(I18N.get("file_menu_description"));
    JMenuItem loadMenuItem = new JMenuItem(I18N.get("load_menu_name"));
		loadMenuItem.setMnemonic(I18N.get("load_menu_key").charAt(0));
		loadMenuItem.getAccessibleContext().setAccessibleDescription(I18N.get("load_menu_description"));
		loadMenuItem.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				JFileChooser chooser = new JFileChooser(props.getProperty("open_directory", System.getProperty("user.home")));
				chooser.setFileFilter(new javax.swing.filechooser.FileFilter()
				{
					public boolean accept(File f)
					{
						if (f.isDirectory())
							return true;
						String name = f.getName();
						if (!name.endsWith(".properties"))
							return false;
						if (name.indexOf('_') != -1)
							return false;
						return true;
					}
					public String getDescription()
					{
						return (I18N.get("translation_files"));
					}
				});
				if (chooser.showOpenDialog(frame) == JFileChooser.APPROVE_OPTION)
				{
					props.setProperty("open_directory", chooser.getCurrentDirectory().getAbsolutePath());
					try
					{
						load(chooser.getSelectedFile());
					}
					catch (IOException iox)
					{
						System.err.println(iox.getMessage());
						JOptionPane.showMessageDialog(frame, I18N.get("error"), iox.getMessage(), JOptionPane.ERROR_MESSAGE);
					}
				}
			}
		});
		fileMenu.add(loadMenuItem);
*/    
		saveMenuItem = new JMenuItem(I18N.get("LOCALISATIONTOOL.MENU.FILE.SAVE"));
//		saveMenuItem.setMnemonic(I18N.get("save_menu_key").charAt(0));
//		saveMenuItem.getAccessibleContext().setAccessibleDescription(I18N.get("save_menu_description"));
		saveMenuItem.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				try
				{
					saveAll();
				}
				catch (IOException iox)
				{
					System.err.println(iox.getMessage());
					JOptionPane.showMessageDialog(frame, I18N.get("LOCALISATIONTOOL.MESSAGE.ERROR"), iox.getMessage(), JOptionPane.ERROR_MESSAGE);
				}
			}
		});
		saveMenuItem.setEnabled(false);
		fileMenu.add(saveMenuItem);
		menuBar.add(fileMenu);

		revertKeyMenuItem = new JMenuItem(I18N.get("LOCALISATIONTOOL.POPUPMENU.REVERT"));
//		revertKeyMenuItem.setMnemonic(I18N.get("revert_key_menu_key").charAt(0));
//		revertKeyMenuItem.getAccessibleContext().setAccessibleDescription(I18N.get("revert_key_menu_description"));
		revertKeyMenuItem.addActionListener(revertKeyActionListener);
		addKeyMenuItem = new JMenuItem(I18N.get("LOCALISATIONTOOL.POPUPMENU.ADD"));
//		addKeyMenuItem.setMnemonic(I18N.get("add_key_menu_key").charAt(0));
//		addKeyMenuItem.getAccessibleContext().setAccessibleDescription(I18N.get("add_key_menu_description"));
		addKeyMenuItem.addActionListener(addKeyActionListener);
		renameKeyMenuItem = new JMenuItem(I18N.get("LOCALISATIONTOOL.POPUPMENU.RENAME"));
//		renameKeyMenuItem.setMnemonic(I18N.get("rename_key_menu_key").charAt(0));
//		renameKeyMenuItem.getAccessibleContext().setAccessibleDescription(I18N.get("rename_key_menu_description"));
		renameKeyMenuItem.addActionListener(renameKeyActionListener);
		deleteKeyMenuItem = new JMenuItem(I18N.get("LOCALISATIONTOOL.POPUPMENU.DELETE"));
//		deleteKeyMenuItem.setMnemonic(I18N.get("delete_key_menu_key").charAt(0));
//		deleteKeyMenuItem.getAccessibleContext().setAccessibleDescription(I18N.get("delete_key_menu_description"));
		deleteKeyMenuItem.addActionListener(deleteKeyActionListener);
		JMenu langMenu = new JMenu(I18N.get("LOCALISATIONTOOL.POPUPMENU.LANGUAGE"));
//		langMenu.setMnemonic(I18N.get("lang_menu_key").charAt(0));
//		langMenu.getAccessibleContext().setAccessibleDescription(I18N.get("lang_menu_description"));
		addLangMenuItem = new JMenuItem(I18N.get("LOCALISATIONTOOL.POPUPMENU.LANGUAGE.ADD"));
//		addLangMenuItem.setMnemonic(I18N.get("add_lang_menu_key").charAt(0));
//		addLangMenuItem.getAccessibleContext().setAccessibleDescription(I18N.get("add_lang_menu_description"));
		addLangMenuItem.addActionListener(addLangActionListener);
		addLangMenuItem.setEnabled(false);
		langMenu.add(addLangMenuItem);
   
    frame.setJMenuBar(menuBar);
		tablePopup = new JPopupMenu();
		revertKeyPopupMenuItem = new JMenuItem(I18N.get("LOCALISATIONTOOL.POPUPMENU.REVERT"));
//		revertKeyPopupMenuItem.setMnemonic(I18N.get("revert_key_menu_key").charAt(0));
//		revertKeyPopupMenuItem.getAccessibleContext().setAccessibleDescription(I18N.get("revert_key_menu_description"));
		revertKeyPopupMenuItem.addActionListener(revertKeyActionListener);
		tablePopup.add(revertKeyPopupMenuItem);
		addKeyPopupMenuItem = new JMenuItem(I18N.get("LOCALISATIONTOOL.POPUPMENU.ADD"));
//		addKeyPopupMenuItem.setMnemonic(I18N.get("add_key_menu_key").charAt(0));
//		addKeyPopupMenuItem.getAccessibleContext().setAccessibleDescription(I18N.get("add_key_menu_description"));
		addKeyPopupMenuItem.addActionListener(addKeyActionListener);
		tablePopup.add(addKeyPopupMenuItem);
		renameKeyPopupMenuItem = new JMenuItem(I18N.get("LOCALISATIONTOOL.POPUPMENU.RENAME"));
//		renameKeyPopupMenuItem.setMnemonic(I18N.get("rename_key_menu_key").charAt(0));
//		renameKeyPopupMenuItem.getAccessibleContext().setAccessibleDescription(I18N.get("rename_key_menu_description"));
		renameKeyPopupMenuItem.addActionListener(renameKeyActionListener);
		tablePopup.add(renameKeyPopupMenuItem);
		deleteKeyPopupMenuItem = new JMenuItem(I18N.get("LOCALISATIONTOOL.POPUPMENU.DELETE"));
//		deleteKeyPopupMenuItem.setMnemonic(I18N.get("delete_key_menu_key").charAt(0));
//		deleteKeyPopupMenuItem.getAccessibleContext().setAccessibleDescription(I18N.get("delete_key_menu_description"));
		deleteKeyPopupMenuItem.addActionListener(deleteKeyActionListener);
		tablePopup.add(deleteKeyPopupMenuItem);
		treePopup = new JPopupMenu();
		addLangPopupMenuItem = new JMenuItem(I18N.get("LOCALISATIONTOOL.POPUPMENU.LANGUAGE.ADD"));
//		addLangPopupMenuItem.setMnemonic(I18N.get("LOCALISATIONTOOL.POPUPMENU.LANGUAGE.ADD").charAt(0));
//		addLangPopupMenuItem.getAccessibleContext().setAccessibleDescription(I18N.get("add_lang_menu_description"));
		addLangPopupMenuItem.addActionListener(addLangActionListener);
		addLangPopupMenuItem.setEnabled(false);
		treePopup.add(addLangPopupMenuItem);
		newLocalePanel = new JPanel(new GridLayout(6, 1));
		ArrayList languages = new ArrayList();
		ArrayList countries = new ArrayList();
		ArrayList variants = new ArrayList();
		countries.add(new LocaleElement(I18N.get("LOCALISATIONTOOL.LABEL.ALL"), null));
		variants.add(new LocaleElement(I18N.get("LOCALISATIONTOOL.LABEL.ALL"), null));
		for (Enumeration e = I18N.getKeys(); e.hasMoreElements();)
		{
			String key = (String) e.nextElement();
			if (key.startsWith("language_"))
			{
				languages.add(new LocaleElement(I18N.get(key), key.substring(9)));
			}
			else
				if (key.startsWith("country_"))
				{
					countries.add(new LocaleElement(I18N.get(key), key.substring(8)));
				}
				else
					if (key.startsWith("variant_"))
					{
						variants.add(new LocaleElement(I18N.get(key), key.substring(8)));
					}
		}
		Collections.sort(languages);
		Collections.sort(countries);
		Collections.sort(variants);
		languageBox = new JComboBox(languages.toArray(new LocaleElement[languages.size()]));
		newLocalePanel.add(new JLabel(I18N.get("LOCALISATIONTOOL.LABEL.LANGUAGE")), 0);
		newLocalePanel.add(languageBox, 1);
		countryBox = new JComboBox(countries.toArray(new LocaleElement[countries.size()]));
		newLocalePanel.add(new JLabel(I18N.get("LOCALISATIONTOOL.LABEL.COUNTRY")), 2);
		newLocalePanel.add(countryBox, 3);
		variantBox = new JComboBox(variants.toArray(new LocaleElement[variants.size()]));
		newLocalePanel.add(new JLabel(I18N.get("LOCALISATIONTOOL.LABEL.VARIANT")), 4);
		newLocalePanel.add(variantBox, 5);
		setTextAreas();
		if (f != null)
			load(f);
		frame.setVisible(true);
    frame.toFront();
	}
	private class LocaleElement implements Comparable
	{
		public String name;
		public String code;
		public LocaleElement(String name, String code)
		{
			this.name = name;
			this.code = code;
		}
		public String toString()
		{
			return (name + ((code == null) ? "" : (" (" + code + ")")));
		}
		public int compareTo(Object o)
		{
			if (o instanceof LocaleElement)
			{
				LocaleElement l = (LocaleElement) o;
				if (code == null)
					return -1;
				if (l.code == null)
					return 1;
				return name.compareTo(l.name);
			}
			else
			{
				return -1;
			}
		}
	}
	private boolean someModified()
	{
		if (globalModified)
			return true;
		for (Enumeration nodeList = top.depthFirstEnumeration(); nodeList.hasMoreElements();)
		{
			TranslationData data = (TranslationData) ((DefaultMutableTreeNode) nodeList.nextElement()).getUserObject();
			if (data.modified > 0)
				return true;
		}
		return false;
	}
  
	private void saveAll() throws IOException
	{
		saveTextAreas();
    String version = props.getProperty("__VERSION");
    try
    {
      int intVersion = Integer.parseInt(version);
      props.setProperty("__VERSION",""+(intVersion+1));
    }
    catch (Exception e)
    {
      // TODO: handle exception
    }
    String name = ((TranslationData) top.getUserObject()).name;
		File saveDir = openFile.getParentFile();
		for (Enumeration nodeList = top.depthFirstEnumeration(); nodeList.hasMoreElements();)
		{
			saveNode((DefaultMutableTreeNode) nodeList.nextElement());
		}
		for (int i = 0; i < names.size(); i++)
		{
			Name n = getName(i);
			n.isModified = false;
		}
		tree.repaint(tree.getBounds());
		table.repaint(table.getBounds());
    
    // notify all interested classes  for the changes of the language files
    // All registerd classes can now reload the new resource bundle.
    //
    Configuration.setString("Language",Configuration.getString("Language"));
	}
  
	private void saveNode(DefaultMutableTreeNode node) throws IOException
	{
		String name = ((TranslationData) top.getUserObject()).name;
		File saveDir = openFile.getParentFile();
		TranslationData data = (TranslationData) node.getUserObject();
		if (globalModified || data.modified > 0)
		{
      data.properties.save(new FileOutputStream(new File(saveDir, name + ((node == top) ? "" : "_") + data.locale + ".properties")));
			data.initProperties = new UberProperties(data.properties);
			data.modified = 0;
		}
	}
	private ActionListener revertKeyActionListener = new ActionListener()
	{
		public void actionPerformed(ActionEvent e)
		{
			saveTextAreas();
			TranslationData data = (TranslationData) workingNode.getUserObject();
			data.properties.setProperty(workingName, data.initProperties.getProperty(workingName), data.initProperties.getComment(workingName));
			setTextAreas();
		}
	};
	private ActionListener addKeyActionListener = new ActionListener()
	{
		public void actionPerformed(ActionEvent e)
		{
			String inputValue = JOptionPane.showInputDialog(I18N.get("LOCALISATIONTOOL.MESSAGE.ADD"));
			TranslationData data = (TranslationData) top.getUserObject();
			if (inputValue != null)
			{
				if (data.properties.contains(inputValue))
				{
					JOptionPane.showMessageDialog(frame, MessageFormat.format(I18N.get("LOCALISATIONTOOL.ERROR.KEYEXISTS"), new Object[] { inputValue }), I18N.get("LOCALISATIONTOOL.TITLE.ERROR"), JOptionPane.ERROR_MESSAGE);
				}
				else
				{
					addKey(inputValue);
				}
			}
		}
	};
	private ActionListener renameKeyActionListener = new ActionListener()
	{
		public void actionPerformed(ActionEvent e)
		{
			String oldName = workingName;
			String inputValue = JOptionPane.showInputDialog(I18N.get("LOCALISATIONTOOL.MESSAGE.RENAME"));
			TranslationData data = (TranslationData) top.getUserObject();
			if (inputValue != null)
			{
				if (data.properties.contains(inputValue))
				{
					JOptionPane.showMessageDialog(frame, MessageFormat.format(I18N.get("LOCALISATIONTOOL.ERROR.KEYEXISTs"), new Object[] { inputValue }), I18N.get("LOCALISATIONTOOL.TITLE.ERROR"), JOptionPane.ERROR_MESSAGE);
				}
				else
				{
					renameKey(oldName, inputValue);
				}
			}
		}
	};
	private ActionListener deleteKeyActionListener = new ActionListener()
	{
		public void actionPerformed(ActionEvent e)
		{
			int result = JOptionPane.showConfirmDialog(frame, I18N.get("LOCALISATIONTOOL.MESSAGE.DELETE"), I18N.get("LOCALISATIONTOOL.TITLE.DELETE"), JOptionPane.OK_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE);
			if (result == JOptionPane.OK_OPTION)
			{
				deleteKey(workingName);
			}
		}
	};
	private ActionListener addLangActionListener = new ActionListener()
	{
		public void actionPerformed(ActionEvent e)
		{
			int result = JOptionPane.showConfirmDialog(frame, newLocalePanel, I18N.get("LOCALISATIONTOOL.MESSAGE.ADD"), JOptionPane.OK_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE);
			if (result == JOptionPane.OK_OPTION)
			{
				saveTextAreas();
				String language = ((LocaleElement) (languageBox.getSelectedItem())).code;
				String country = ((LocaleElement) (countryBox.getSelectedItem())).code;
				String variant = ((LocaleElement) (variantBox.getSelectedItem())).code;
				try
				{
					DefaultMutableTreeNode newNode = createTreeNode(top, language, country, variant, null);
					treeModel.reload();
					TreePath newPath = new TreePath(newNode);
					tree.setSelectionPath(newPath);
					tree.expandPath(newPath);
					tree.scrollPathToVisible(newPath);
					globalModified = true;
				}
				catch (IOException iox)
				{
					// cannot happen, stream is null.
				}
			}
		}
	};
	private void exitRoutine()
	{
		boolean exit = true;
		if (someModified())
		{
			exit = false;
			Object[] options = { I18N.get("COMMON.BUTTON.SAVE"), I18N.get("COMMON.BUTTON.EXIT"), I18N.get("COMMON.BUTTON.CANCEL")};
			int result = JOptionPane.showOptionDialog(frame, I18N.get("LOCALISATIONTOOL.MESSAGE.SAVEFIRST"), I18N.get("LOCALISATIONTOOL.TITLE.SAVEFIRST"), JOptionPane.DEFAULT_OPTION, JOptionPane.QUESTION_MESSAGE, null, options, options[2]);
			if (result == 0)
			{
				try
				{
					saveAll();
					exit = true;
				}
				catch (IOException iox)
				{
					System.err.println(iox.getMessage());
					JOptionPane.showMessageDialog(frame, I18N.get("LOCALISATIONTOOL.TITLE.ERROR"), iox.getMessage(), JOptionPane.ERROR_MESSAGE);
				}
			}
			else
				if (result == 1)
				{
					exit = true;
				}
		}
		if (exit)
		{
			Dimension d = frame.getSize();
			props.setProperty("window_size_x", ("" + d.width));
			props.setProperty("window_size_y", ("" + d.height));
			Point p = frame.getLocation();
			props.setProperty("window_location_x", ("" + p.x));
			props.setProperty("window_location_y", ("" + p.y));
			props.setProperty("text_split_pane_divider", ("" + textSplitPane.getDividerLocation()));
			props.setProperty("editing_split_pane_divider", ("" + editingSplitPane.getDividerLocation()));
			props.setProperty("navigation_split_pane_divider", ("" + navigationSplitPane.getDividerLocation()));
			try
			{
				props.save(userFile);
			}
			catch (IOException iox)
			{
				System.err.println(iox.getMessage());
			}
			//System.exit(0);
      frame.dispose();
		}
		else
		{
			frame.setVisible(true);
		}
	}
	/**
	 * Main method.
	 */
	public static void main(String[] args) throws IOException
	{
		String load = null;
		if (args.length > 0)
			load = args[0];
		I18NEditor e = new I18NEditor((load == null) ? null : new File(load));
	}
	private class VerticalLayout implements LayoutManager
	{
		/**
		 * Adds the specified component with the specified name to the layout.
		 */
		public void addLayoutComponent(String name, Component comp)
		{
		}
		/**
		 * Lays out the container in the specified panel.
		 */
		public void layoutContainer(Container parent)
		{
			int currentYPos = 0;
			int width = parent.getWidth();
			Insets insets = parent.getInsets();
			width -= insets.left + insets.right;
			int numberComponents = parent.getComponentCount();
			for (int i = 0; i < numberComponents; i++)
			{
				Component c = parent.getComponent(i);
				if (c.isVisible())
				{
					Dimension d = c.getPreferredSize();
					d.width = width;
					if (i == numberComponents - 1 && currentYPos + d.height + insets.top + insets.bottom < parent.getHeight())
					{
						d.height = parent.getHeight() - (currentYPos + insets.top + insets.bottom);
					}
					c.setBounds(0, currentYPos, d.width, d.height);
					currentYPos += d.height;
				}
			}
		}
		/**
		 * Calculates the minimum size dimensions for the specified panel given the
		 * components in the specified parent container.
		 */
		public Dimension minimumLayoutSize(Container parent)
		{
			return preferredLayoutSize(parent);
		}
		/**
		 * Calculates the preferred size dimensions for the specified panel given
		 * the components in the specified parent container.
		 */
		public Dimension preferredLayoutSize(Container parent)
		{
			Dimension preferredSize = new Dimension(0, 0);
			int numberComponents = parent.getComponentCount();
			for (int i = 0; i < numberComponents; i++)
			{
				Component c = parent.getComponent(i);
				if (c.isVisible())
				{
					Dimension d = c.getPreferredSize();
					if (d.width > preferredSize.width)
						preferredSize.width = d.width;
					preferredSize.height += d.height;
				}
			}
			Insets insets = parent.getInsets();
			preferredSize.width += insets.left + insets.right;
			preferredSize.height += insets.top + insets.bottom;
			return preferredSize;
		}
		/**
		 * Removes the specified component from the layout.
		 */
		public void removeLayoutComponent(Component comp)
		{
		}
	}
}
