
/**
 * Title:        FREEObject
 * Description:
 * Copyright:    Copyright (c) 2000
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */

package de.freegroup.digitalsimulator.export.wired.caseeditor;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.InputStreamReader;
import java.io.StringWriter;
import java.net.URL;
import java.security.InvalidParameterException;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.Map;
import java.util.Properties;
import java.util.Vector;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.ImageIcon;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.JToolBar;
import javax.swing.event.UndoableEditEvent;

import com.jgraph.JGraph;
import com.jgraph.event.GraphSelectionEvent;
import com.jgraph.event.GraphSelectionListener;
import com.jgraph.graph.ConnectionSet;
import com.jgraph.graph.DefaultEdge;
import com.jgraph.graph.DefaultGraphCell;
import com.jgraph.graph.DefaultPort;
import com.jgraph.graph.GraphConstants;
import com.jgraph.graph.GraphUndoManager;

import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.export.wired.db.ElectricCase;
import de.freegroup.digitalsimulator.export.wired.db.ElectricObject;


public class ObjectView extends JPanel implements GraphSelectionListener, KeyListener
{
	public static final int HIT_NO     = 0;
	public static final int HIT_START  = 1;
	public static final int HIT_NORMAL = 2;

  Vector nodes          = new Vector();
  File    file          = null;
  Class   callbackClass = null;
	int lastHitResult = HIT_NO;
	
	// JGraph instance
	protected JGraph graph;
	// Undo Manager
	protected GraphUndoManager undoManager;

	// Actions which Change State
	protected Action undo;
	protected Action redo;
	protected Action remove;
	protected Action cut;
	protected Action copy;
	protected Action paste;
  ElectricObject electricObject;
  
    public ObjectView(ElectricObject _electricObject)
    {
      electricObject = _electricObject;
      try
      {
      	setLayout(new BorderLayout());
      	// Construct the Graph
      	graph = new ObjectGraph(new Model(),this);
        graph.setGridEnabled(true);
        graph.setGridMode(JGraph.DOT_GRID_MODE);
        graph.setGridVisible(true);
        graph.setGridColor(Color.black);
        graph.setGridSize(25);
      	// Construct Command History
      	//
      	// Create a GraphUndoManager which also Updates the ToolBar
      	undoManager = new GraphUndoManager() 
      	{
      		// Override Superclass
      		  public void undoableEditHappened(UndoableEditEvent e) 
      		  {
      		  	// First Invoke Superclass
      		  	super.undoableEditHappened(e);
      		  	// Then Update Undo/Redo Buttons
      		  	updateHistoryButtons();
      		  }
      	};

      	// Add Listeners to Graph
      	//
      	// Register UndoManager with the Model
      	graph.getModel().addUndoableEditListener(undoManager);
      	// Update ToolBar based on Selection Changes
      	graph.getSelectionModel().addGraphSelectionListener(this);
      	// Listen for Delete Keystroke when the Graph has Focus
      	graph.addKeyListener(this);

      	// Construct Panel
      	//
      	// Add a ToolBar
      	add(createToolBar(), BorderLayout.NORTH);
      	// Add the Graph as Center Component
      	JScrollPane sp = new JScrollPane(graph);
      	add(sp, BorderLayout.CENTER);
        
        if(electricObject!=null)
        {
          insert(electricObject); 
        }
      }
      catch (Exception ex)
      {
         Trace.error("Contextview konnte nicht angelegt werden");
         Trace.error(ex);
      }
    }


	// Insert a new Vertex at point
	public void insert(ElectricObject eCase) 
	{	
		// Construct Vertex with no Label
    GUIElectricObject vertex = new GUIElectricObject(graph, eCase);
 	}

	// Undo the last Change to the Model or the View
	public void undo() 
	{
		try
		 {
			undoManager.undo(graph.getGraphLayoutCache());
		} 
		catch (Exception ex) 
		{
			System.err.println(ex);
		}
		 finally 
		{
			updateHistoryButtons();
		}
	}

	// Redo the last Change to the Model or the View
	public void redo() 
	{
		try 
		{
			undoManager.redo(graph.getGraphLayoutCache());
		} 
		catch (Exception ex) 
		{
			System.err.println(ex);
		} 
		finally 
		{
			updateHistoryButtons();
		}
	}

	// Insert a new Edge between source and target
	public void connect(DefaultPort source, DefaultPort target) 
	{
    String fromNode = source.getParent().toString();
    String toNode   = target.getParent().toString();
    Color  color    = Color.gray;
    
    // Connections that will be inserted into the Model
    ConnectionSet cs = new ConnectionSet();
    // Construct Edge with no label
    DefaultEdge edge = new DefaultEdge();
    
    
    // Create Connection between source and target using edge
    cs.connect(edge, source, target);
    
    // Create a Map thath holds the attributes for the edge
    Map map = GraphConstants.createMap();
    // Add a Line End Attribute
 //   GraphConstants.setLineEnd(map, GraphConstants.ARROW_SIMPLE);
    GraphConstants.setLineColor(map, color);
    
    // Construct a Map from cells to Maps (for insert)
    Hashtable attributes = new Hashtable();
    // Associate the Edge with its Attributes
    attributes.put(edge, map);
    // Insert the Edge and its Attributes
    graph.getGraphLayoutCache().insert( new Object[] { edge },  attributes, cs, null,null);
  }

	// Update Undo/Redo Button State based on Undo Manager
	protected void updateHistoryButtons() 
	{
		// The View Argument Defines the Context
		undo.setEnabled(undoManager.canUndo(graph.getGraphLayoutCache()));
		redo.setEnabled(undoManager.canRedo(graph.getGraphLayoutCache()));
	}

	// From GraphSelectionListener Interface
	public void valueChanged(GraphSelectionEvent e) 
	{
		if(graph!=null)
		{		
			// Group Button only Enabled if more than One Cell Selected
			//group.setEnabled(graph.getSelectionCount() > 1);
			// Update Button States based on Current Selection
			boolean enabled = !graph.isSelectionEmpty();
			remove.setEnabled(enabled);
			//ungroup.setEnabled(enabled);
			//tofront.setEnabled(enabled);
			//toback.setEnabled(enabled);
			//copy.setEnabled(enabled);
			//cut.setEnabled(enabled);
			if(graph.getSelectionCount()==1)
			{
				Object obj = graph.getSelectionCells()[0];
/*
        if(obj instanceof ContextTransition)
					MainFrame.setCurrentTransition((ContextTransition)obj);
*/          
			}
		//	if(enabled)
		//		System.out.println( graph.getSelectionCells()[0]);
		}
	}
	
	//
	// KeyListener for Delete KeyStroke
	//
	public void keyReleased(KeyEvent e) 
	{
	}
	
	public void keyTyped(KeyEvent e) 
	{
	}
	
	public void keyPressed(KeyEvent e) 
	{
		// Listen for Delete Key Press
		if (e.getKeyCode() == KeyEvent.VK_DELETE)
		{
			// Execute Remove Action on Delete Key Press
			remove.actionPerformed(null);
		}
	}



	//
	// Custom MarqueeHandler

	//
	// PopupMenu
	//
	public JPopupMenu createPopupMenu(final Point pt, final Object cell) {
		JPopupMenu menu = new JPopupMenu();
		if (cell != null) {
			// Edit
			menu.add(new AbstractAction("Edit") {
				public void actionPerformed(ActionEvent e) {
					graph.startEditingAtCell(cell);
				}
			});
		}
		// Remove
		if (!graph.isSelectionEmpty()) {
			menu.addSeparator();
			menu.add(new AbstractAction("Remove") {
				public void actionPerformed(ActionEvent e) {
					remove.actionPerformed(e);
				}
			});
		}
		menu.addSeparator();
		// Insert
		menu.add(new AbstractAction("Insert") {
			public void actionPerformed(ActionEvent ev) {
//				insert("NEW",null,pt,new Dimension(50,50));
			}
		});
		return menu;
	}

	//
	// ToolBar
	//
	public JToolBar createToolBar() {
		JToolBar toolbar = new JToolBar();
		toolbar.setFloatable(false);

		// Insert
		URL insertUrl = getClass().getResource("insert.gif");
		ImageIcon insertIcon = new ImageIcon(insertUrl);
		toolbar.add(new AbstractAction("", insertIcon) {
			public void actionPerformed(ActionEvent e) {
//				insert("NEW",null,new Point(10, 10),new Dimension(50,50));
			}
		});

		// Toggle Connect Mode
		URL connectUrl =getClass().getResource("connecton.gif");
		ImageIcon connectIcon = new ImageIcon(connectUrl);
		toolbar.add(new AbstractAction("", connectIcon) {
			public void actionPerformed(ActionEvent e) {
				graph.setPortsVisible(!graph.isPortsVisible());
				URL url;
				if (graph.isPortsVisible())
					url =	getClass().getResource("connecton.gif");
				else
					url =	getClass().getResource("connectoff.gif");
				ImageIcon i = new ImageIcon(url);
				putValue(SMALL_ICON, i);
			}
		});

		// Undo
		toolbar.addSeparator();
		URL undoUrl = getClass().getResource("undo.gif");
		ImageIcon undoIcon = new ImageIcon(undoUrl);
		undo = new AbstractAction("", undoIcon) {
			public void actionPerformed(ActionEvent e) {
				undo();
			}
		};
		undo.setEnabled(false);
		toolbar.add(undo);

		// Redo
		URL redoUrl = getClass().getResource("redo.gif");
		ImageIcon redoIcon = new ImageIcon(redoUrl);
		redo = new AbstractAction("", redoIcon) {
			public void actionPerformed(ActionEvent e) {
				redo();
			}
		};
		redo.setEnabled(false);
		toolbar.add(redo);

		//
		// Edit Block
		//
	//	toolbar.addSeparator();
		Action action;
		URL url;
/*
		// Copy
		action = graph.getTransferHandler().getCopyAction();
		url = getClass().getClassLoader().getResource("copy.gif");
		action.putValue(Action.SMALL_ICON, new ImageIcon(url));
		toolbar.add(copy = new EventRedirector(action));

		// Paste
		action = graph.getTransferHandler().getPasteAction();
		url = getClass().getClassLoader().getResource("paste.gif");
		action.putValue(Action.SMALL_ICON, new ImageIcon(url));
		toolbar.add(paste = new EventRedirector(action));

		// Cut
		action = graph.getTransferHandler().getCutAction();
		url = getClass().getClassLoader().getResource("cut.gif");
		action.putValue(Action.SMALL_ICON, new ImageIcon(url));
		toolbar.add(cut = new EventRedirector(action));
*/
		// Remove
		URL removeUrl = getClass().getResource("delete.gif");
		ImageIcon removeIcon = new ImageIcon(removeUrl);
		remove = new AbstractAction("", removeIcon) {
			public void actionPerformed(ActionEvent e) {
				if (!graph.isSelectionEmpty()) {
					Object[] cells = graph.getSelectionCells();
					cells = graph.getDescendants(cells);
					graph.getModel().remove(cells);
				}
			}
		};
		remove.setEnabled(false);
		toolbar.add(remove);

		// Zoom Std
		toolbar.addSeparator();
		URL zoomUrl = getClass().getResource("zoom.gif");
		ImageIcon zoomIcon = new ImageIcon(zoomUrl);
		toolbar.add(new AbstractAction("", zoomIcon) {
			public void actionPerformed(ActionEvent e) {
				graph.setScale(1.0);
			}
		});
		// Zoom In
		URL zoomInUrl = getClass().getResource("zoomin.gif");
		ImageIcon zoomInIcon = new ImageIcon(zoomInUrl);
		toolbar.add(new AbstractAction("", zoomInIcon) {
			public void actionPerformed(ActionEvent e) {
				graph.setScale(1.2 * graph.getScale());
			}
		});
		// Zoom Out
		URL zoomOutUrl = getClass().getResource("zoomout.gif");
		ImageIcon zoomOutIcon = new ImageIcon(zoomOutUrl);
		toolbar.add(new AbstractAction("", zoomOutIcon) {
			public void actionPerformed(ActionEvent e) {
				graph.setScale(graph.getScale() / 1.2);
			}
		});
/*
		// Group
		toolbar.addSeparator();
		URL groupUrl = getClass().getClassLoader().getResource("group.gif");
		ImageIcon groupIcon = new ImageIcon(groupUrl);
		group = new AbstractAction("", groupIcon) {
			public void actionPerformed(ActionEvent e) {
				group(graph.getSelectionCells());
			}
		};
		group.setEnabled(false);
		toolbar.add(group);

		// Ungroup
		URL ungroupUrl = getClass().getClassLoader().getResource("ungroup.gif");
		ImageIcon ungroupIcon = new ImageIcon(ungroupUrl);
		ungroup = new AbstractAction("", ungroupIcon) {
			public void actionPerformed(ActionEvent e) {
				ungroup(graph.getSelectionCells());
			}
		};
		ungroup.setEnabled(false);
		toolbar.add(ungroup);

		// To Front
		toolbar.addSeparator();
		URL toFrontUrl = getClass().getClassLoader().getResource("tofront.gif");
		ImageIcon toFrontIcon = new ImageIcon(toFrontUrl);
		tofront = new AbstractAction("", toFrontIcon) {
			public void actionPerformed(ActionEvent e) {
				if (!graph.isSelectionEmpty())
					toFront(graph.getSelectionCells());
			}
		};
		tofront.setEnabled(false);
		toolbar.add(tofront);

		// To Back
		URL toBackUrl = getClass().getClassLoader().getResource("toback.gif");
		ImageIcon toBackIcon = new ImageIcon(toBackUrl);
		toback = new AbstractAction("", toBackIcon) {
			public void actionPerformed(ActionEvent e) {
				if (!graph.isSelectionEmpty())
					toBack(graph.getSelectionCells());
			}
		};
		toback.setEnabled(false);
		toolbar.add(toback);
		*/

		return toolbar;
	}
  
  public void save()
  {
    try
    {
      Object[] objs = graph.getRoots();
      for(int i=0; i<objs.length; i++)
      {

        if(objs[i] instanceof GUIElectricObject)
        {
          GUIElectricObject node = (GUIElectricObject)objs[i];
          node.save();
        }
        
      }
    }
    catch (Exception ex)
    {
      System.out.println(ex);
      ex.printStackTrace();
    }
  }
  
}
