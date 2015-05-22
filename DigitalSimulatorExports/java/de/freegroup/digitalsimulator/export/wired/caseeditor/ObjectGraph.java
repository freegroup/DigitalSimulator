/*
 * Created on Aug 20, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.export.wired.caseeditor;

import java.awt.event.MouseEvent;

import com.jgraph.JGraph;
import com.jgraph.graph.CellMapper;
import com.jgraph.graph.Edge;
import com.jgraph.graph.EdgeView;
import com.jgraph.graph.GraphModel;

// Defines a Graph that uses the Shift-Button (Instead of the Right
// Mouse Button, which is Default) to add/remove point to/from an edge.
public class ObjectGraph extends JGraph 
{
	public ObjectGraph() 
	{
		super();
	}
	
	// Construct the Graph using the Model as its Data Source
	public ObjectGraph(GraphModel model, ObjectView view) 
	{
		super(model);
		// Use a Custom Marquee Handler
		setMarqueeHandler(new ObjectMarqueeHandler(this,view));
		// Tell the Graph to Select new Cells upon Insertion
//		setSelectNewCells(true);
		// Make Ports Visible by Default
		setPortsVisible(true);
		setAntiAliased(true);
		//setGridEnabled(true);
		setGridSize(6);
		setTolerance(2);
	}

	// Override Superclass Method to Return Custom EdgeView
	protected EdgeView createEdgeView(Edge e, CellMapper cm) 
	{
		// Return Custom EdgeView
		return new EdgeView(e, this, cm) 
		{
			// Override Superclass Method
			public boolean isAddPointEvent(MouseEvent event) 
			{
				// Points are Added using Shift-Click
				return event.isShiftDown();
			}
			// Override Superclass Method
			public boolean isRemovePointEvent(MouseEvent event) 
			{
				// Points are Removed using Shift-Click
				return event.isShiftDown();
			}
		};
	}
}
