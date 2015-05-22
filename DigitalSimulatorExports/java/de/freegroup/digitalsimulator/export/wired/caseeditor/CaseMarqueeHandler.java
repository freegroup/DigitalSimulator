/*
 * Created on Aug 20, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.export.wired.caseeditor;

import java.awt.Color;
import java.awt.Cursor;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.event.MouseEvent;

import javax.swing.JPopupMenu;
import javax.swing.SwingUtilities;

import com.jgraph.graph.BasicMarqueeHandler;
import com.jgraph.graph.DefaultPort;
import com.jgraph.graph.GraphConstants;
import com.jgraph.graph.PortView;

// MarqueeHandler that Connects Vertices and Displays PopupMenus
public class CaseMarqueeHandler extends BasicMarqueeHandler {

	// Holds the Start and the Current Point
	protected Point start, current;
	// Holds the First and the Current Port
	protected PortView port, firstPort;
	protected CaseGraph graph;
	protected CaseView view;
	
	CaseMarqueeHandler(CaseGraph _graph, CaseView _view)
	{
		graph = _graph;
		view  = _view;
	}
	
	// Override to Gain Control (for PopupMenu and ConnectMode)
	public boolean isForceMarqueeEvent(MouseEvent e) {
		// If Right Mouse Button we want to Display the PopupMenu
		if (SwingUtilities.isRightMouseButton(e))
			// Return Immediately
			return true;
		// Find and Remember Port
		port = getSourcePortAt(e.getPoint());
		// If Port Found and in ConnectMode (=Ports Visible)
		if (port != null && graph.isPortsVisible())
			return true;
		// Else Call Superclass
		return super.isForceMarqueeEvent(e);
	}

	// Display PopupMenu or Remember Start Location and First Port
	public void mousePressed(final MouseEvent e) {
		// If Right Mouse Button
		if (SwingUtilities.isRightMouseButton(e)) {
			// Scale From Screen to Model
			Point loc = graph.fromScreen(e.getPoint());
			// Find Cell in Model Coordinates
			Object cell = graph.getFirstCellForLocation(loc.x, loc.y);
			// Create PopupMenu for the Cell
			JPopupMenu menu = view.createPopupMenu(e.getPoint(), cell);
			// Display PopupMenu
			menu.show(graph, e.getX(), e.getY());

			// Else if in ConnectMode and Remembered Port is Valid
		} else if (
			port != null && !e.isConsumed() && graph.isPortsVisible()) {
			// Remember Start Location
			start = graph.toScreen(port.getLocation(null));
			// Remember First Port
			firstPort = port;
			// Consume Event
			e.consume();
		} else
			// Call Superclass
			super.mousePressed(e);
	}

	// Find Port under Mouse and Repaint Connector
	public void mouseDragged(MouseEvent e) {
		// If remembered Start Point is Valid
		if (start != null && !e.isConsumed()) {
			// Fetch Graphics from Graph
			Graphics g = graph.getGraphics();
			// Xor-Paint the old Connector (Hide old Connector)
			paintConnector(Color.black, graph.getBackground(), g);
			// Reset Remembered Port
			port = getTargetPortAt(e.getPoint());
			// If Port was found then Point to Port Location
			if (port != null)
				current = graph.toScreen(port.getLocation(null));
			// Else If no Port was found then Point to Mouse Location
			else
				current = graph.snap(e.getPoint());
			// Xor-Paint the new Connector
			paintConnector(graph.getBackground(), Color.black, g);
			// Consume Event
			e.consume();
		}
		// Call Superclass
		super.mouseDragged(e);
	}

	public PortView getSourcePortAt(Point point) {
		// Scale from Screen to Model
		Point tmp = graph.fromScreen(new Point(point));
		// Find a Port View in Model Coordinates and Remember
		return graph.getPortViewAt(tmp.x, tmp.y);
	}

	// Find a Cell at point and Return its first Port as a PortView
	protected PortView getTargetPortAt(Point point) {
		// Find Cell at point (No scaling needed here)
		Object cell = graph.getFirstCellForLocation(point.x, point.y);
		// Loop Children to find PortView
		for (int i = 0; i < graph.getModel().getChildCount(cell); i++) {
			// Get Child from Model
			Object tmp = graph.getModel().getChild(cell, i);
			// Get View for Child using the Graph's View as a Cell Mapper
			tmp = graph.getGraphLayoutCache().getMapping(tmp, false);
			// If Child View is a Port View and not equal to First Port
			if (tmp instanceof PortView && tmp != firstPort)
				// Return as PortView
				return (PortView) tmp;
		}
		// No Port View found
		return getSourcePortAt(point);
	}

	// Connect the First Port and the Current Port in the Graph or Repaint
	public void mouseReleased(MouseEvent e) {
		// If Valid Event, Current and First Port
		if (e != null
			&& !e.isConsumed()
			&& port != null
			&& firstPort != null
			&& firstPort != port) {
			// Then Establish Connection
			view.connect((DefaultPort) firstPort.getCell(), (DefaultPort) port.getCell());
			// Consume Event
			e.consume();
			// Else Repaint the Graph
		} else
			graph.repaint();
		// Reset Global Vars
		firstPort = port = null;
		start = current = null;
		// Call Superclass
		super.mouseReleased(e);
	}

	// Show Special Cursor if Over Port
	public void mouseMoved(MouseEvent e) {
		// Check Mode and Find Port
		if (e != null
			&& getSourcePortAt(e.getPoint()) != null
			&& !e.isConsumed()
			&& graph.isPortsVisible()) {
			// Set Cusor on Graph (Automatically Reset)
			graph.setCursor(new Cursor(Cursor.HAND_CURSOR));
			// Consume Event
			e.consume();
		}
		// Call Superclass
		super.mouseReleased(e);
	}

	// Use Xor-Mode on Graphics to Paint Connector
	protected void paintConnector(Color fg, Color bg, Graphics g) {
		// Set Foreground
		g.setColor(fg);
		// Set Xor-Mode Color
		g.setXORMode(bg);
		// Highlight the Current Port
		paintPort(graph.getGraphics());
		// If Valid First Port, Start and Current Point
		if (firstPort != null && start != null && current != null)
			// Then Draw A Line From Start to Current Point
			g.drawLine(start.x, start.y, current.x, current.y);
	}

	// Use the Preview Flag to Draw a Highlighted Port
	protected void paintPort(Graphics g) 
	{
		// If Current Port is Valid
		if (port != null) {
			// If Not Floating Port...
			boolean o =	(GraphConstants.getOffset(port.getAttributes()) != null);
			// ...Then use Parent's Bounds
			Rectangle r =	(o) ? port.getBounds() : port.getParentView().getBounds();
			// Scale from Model to Screen
			r = graph.toScreen(new Rectangle(r));
			// Add Space For the Highlight Border
			r.setBounds(r.x - 3, r.y - 3, r.width + 6, r.height + 6);
			// Paint Port in Preview (=Highlight) Mode
			graph.getUI().paintCell(g, port, r, true);
		}
	
	}

} // End of Editor.MyMarqueeHandler