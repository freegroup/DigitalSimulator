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
import java.util.Iterator;
import java.util.Map;
import java.util.Vector;

import javax.swing.ImageIcon;

import com.jgraph.JGraph;
import com.jgraph.graph.DefaultGraphCell;
import com.jgraph.graph.DefaultPort;
import com.jgraph.graph.GraphConstants;

import de.freegroup.digitalsimulator.export.wired.db.CasePin;
import de.freegroup.digitalsimulator.export.wired.db.ElectricCase;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class GUIElectricCase extends DefaultGraphCell
{
  Object[] pins=new Object[0];
  
  public GUIElectricCase(JGraph graph, ElectricCase eCase)
  {
    super(eCase.getName());
    attributes = GraphConstants.createMap();
    
    setElectricCase(eCase);
    setCasePins(eCase.getCaseLayout().getCasePins());
    
    // Snap the Point to the Grid
    Point point = new Point(100,100);

    GraphConstants.setBounds(attributes,eCase.getBounds());

    GraphConstants.setOpaque(attributes, false);
    if(getElectricCase().getIconName()!=null && getElectricCase().getIconName().length()>0)
    {
      URL insertUrl = getClass().getResource(getElectricCase().getIconName());
      ImageIcon insertIcon = new ImageIcon(insertUrl);
      GraphConstants.setIcon(attributes, insertIcon);
    }
    else
    {
      GraphConstants.setBorderColor(attributes, Color.black);
      GraphConstants.setBackground(attributes, new Color(166,202,240));
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
    pins = new Object[getCasePins().size()];
    for(int i = 0; i<pins.length;i++)
    { 
      CasePin cPin = (CasePin)getCasePins().get(i);
      DefaultGraphCell  pin   = new DefaultGraphCell(""+cPin.getNumber());
      Map map = GraphConstants.createMap();
      GraphConstants.setBounds(map, cPin.getBounds());
      GraphConstants.setIcon(map, new ImageIcon(getClass().getResource("CasePin.gif")));
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
    getElectricCase().setBounds(GraphConstants.getBounds(getMap()),true);
    for(int i=0;i<getCasePins().size();i++)
    {
     CasePin cPin = (CasePin)getCasePins().get(i);
     DefaultGraphCell pin = (DefaultGraphCell)pins[i];
     cPin.setBounds(GraphConstants.getBounds(pin.getAttributes()),true);
    }
  }
  
  public ArrayList getCasePins()
  {
    return (ArrayList)getMap().get("ElectricCasePins");
  }
  
  public void setCasePins(ArrayList pins)
  {
    getMap().put("ElectricCasePins",pins);
  }
  
  public ElectricCase getElectricCase()
  {
    return (ElectricCase)getMap().get("ElectricCase");
  }
  
  public void setElectricCase(ElectricCase electricCase)
  {
    getMap().put("ElectricCase",electricCase);
  }
  
  /**
   * 
   * @return
   */
  public Map getMap()
  {
/*
    if(attr!=null)
      return attr;
    attr = GraphConstants.createMap();
*/    
    return attributes;
  }
}
