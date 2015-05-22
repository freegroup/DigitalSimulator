/*
 * Created on Aug 20, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.export.wired.caseeditor;
import com.jgraph.graph.DefaultGraphModel;


// A Custom Model that does not allow Self-References
public class Model extends DefaultGraphModel 
{
	/*
	// Override Superclass Method
	public boolean acceptsSource(Object edge, Object port) 
	{
		// Source only Valid if not Equal Target
		return (((Edge) edge).getTarget() != port);
	}
	// Override Superclass Method
	public boolean acceptsTarget(Object edge, Object port) 
	{
		// Target only Valid if not Equal Source
		return (((Edge) edge).getSource() != port);
	}
	*/
}
