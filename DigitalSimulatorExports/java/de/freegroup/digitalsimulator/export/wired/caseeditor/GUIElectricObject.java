/*
 * Created on Jan 23, 2004
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.digitalsimulator.export.wired.caseeditor;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Point;
import java.awt.Rectangle;
import java.net.URL;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Map;
import java.util.Vector;

import javax.swing.ImageIcon;

import com.jgraph.JGraph;
import com.jgraph.graph.DefaultGraphCell;
import com.jgraph.graph.DefaultPort;
import com.jgraph.graph.GraphConstants;

import de.freegroup.digitalsimulator.export.wired.db.ElectricCase;
import de.freegroup.digitalsimulator.export.wired.db.ElectricObject;
import de.freegroup.digitalsimulator.export.wired.db.Object2Case;
import de.freegroup.digitalsimulator.export.wired.db.ObjectPin;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class GUIElectricObject extends DefaultGraphCell
{
  Object[] pins=new Object[0];
  
  public GUIElectricObject(JGraph graph, ElectricObject eObject)
  {
    this(graph, eObject, null);
  }
    
  public GUIElectricObject(JGraph graph, ElectricObject eObject, ElectricCase eCase)
  {
    super(eObject.getType());

    // The object must insert relative to its case. The object position will be ignore
    // and the position in the Object2Case relation is the 'real' position.
    //
    /*
    Object2Case o2c = Object2Case.findByKey(eCase, eObject);
    if(o2c!=null)
    {
      eObject.setX(o2c.getX(),false); // don't save this fake position in the database
      eObject.setY(o2c.getY(),false);
    }
    */
    attributes = GraphConstants.createMap();
    
    setElectricObject(eObject);
    setObjectPins(eObject.getObjectLayout().getObjectPins());
    
    // Snap the Point to the Grid
    Point point = new Point(100,100);

    GraphConstants.setBounds(attributes,eObject.getBounds());

    GraphConstants.setOpaque(attributes, false);
    
    /*
    if(getElectricObject().getIconName()!=null && getElectricObject().getIconName().length()>0)
    {
      URL insertUrl = getClass().getResource(getElectricObject().getIconName());
      ImageIcon insertIcon = new ImageIcon(insertUrl);
      GraphConstants.setIcon(attributes, insertIcon);
    }
    else
*/
    {
      GraphConstants.setBorderColor(attributes, Color.black);
      GraphConstants.setBackground(attributes, new Color(240,202,166));
      GraphConstants.setOpaque(attributes, true);
    }
    Hashtable at = new Hashtable();
    // Associate the Vertex with its Attributes
    at.put(this, attributes);
    // Insert the Vertex and its Attributes (can also use model)
    graph.getGraphLayoutCache().insert( new Object[] { this },at, null,null,null);
   
    
    // Add case pins
    //
    Hashtable pinAttributes = new Hashtable();
    pins = new Object[getObjectPins().size()];
    for(int i = 0; i<pins.length;i++)
    { 
      ObjectPin cPin = (ObjectPin)getObjectPins().get(i);
      DefaultGraphCell  pin   = new DefaultGraphCell(""+cPin.getNumber());
      Map map = GraphConstants.createMap();
      GraphConstants.setBounds(map, cPin.getAbsoluteBounds());
      GraphConstants.setIcon(map, new ImageIcon(getClass().getResource("ObjectPin.gif")));
      GraphConstants.setOpaque(map, false);
      GraphConstants.setHorizontalTextPosition(map,0);
      GraphConstants.setVerticalTextPosition(map,0);
      GraphConstants.setBendable(map,false);
      GraphConstants.setEditable(map,false);
      GraphConstants.setSizeable(map,false);
      // Associate the Vertex with its Attributes
      pins[i]=pin;
      pinAttributes.put(pin, map);
    }
    // Insert the Vertex and its Attributes (can also use model)
    graph.getGraphLayoutCache().insert( pins,pinAttributes, null,null,null);
  }
  
  /**
   * 
   *
   */
  public void save()
  {
    getElectricObject().setBounds(GraphConstants.getBounds(getMap()),true);
    for(int i=0;i<getObjectPins().size();i++)
    {
     ObjectPin cPin = (ObjectPin)getObjectPins().get(i);
     DefaultGraphCell pin = (DefaultGraphCell)pins[i];
     // The pins will be saved relative to its parent object
     //
     Point     pos = GraphConstants.getBounds(pin.getAttributes()).getLocation(); 
     Dimension dim = GraphConstants.getBounds(pin.getAttributes()).getSize();
     cPin.setAbsoluteBounds(new Rectangle(pos, dim),true);
    }
  }
  
  public ArrayList getObjectPins()
  {
    return (ArrayList)getMap().get("ElectricObjectPins");
  }
  
  public void setObjectPins(ArrayList pins)
  {
    getMap().put("ElectricObjectPins",pins);
  }
  
  public ElectricObject getElectricObject()
  {
    return (ElectricObject)getMap().get("ElectricObject");
  }
  
  public void setElectricObject(ElectricObject electricCase)
  {
    getMap().put("ElectricObject",electricCase);
  }
  
  /**
   * 
   * @return
   */
  public Map getMap()
  {
    return attributes;
  }
}
