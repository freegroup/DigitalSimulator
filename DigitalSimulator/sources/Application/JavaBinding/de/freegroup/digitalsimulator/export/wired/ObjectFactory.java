package de.freegroup.digitalsimulator.export.wired;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import java.util.*;
import de.freegroup.digitalsimulator.export.wired.db.*;
import de.freegroup.digitalsimulator.dialogs.MsgBox;
import I18N;
import Trace;

public  class ObjectFactory
{
    public static class Connection
    {
        Connection(CasePin _from, CasePin _to)
        {
            from = _from;
            to   = _to;

        }
        CasePin from;
        CasePin to;
        public String toString()
        {
            //return "";
            String fromId = java.lang.Long.toHexString(from.getCaseLayout().getCurrentElectricCase().hashCode()).toUpperCase();
            String toId   = java.lang.Long.toHexString(to.getCaseLayout().getCurrentElectricCase().hashCode()).toUpperCase();
            return  "["+fromId +"]."+from.getNumber() +" -> "+"["+toId +"]."+to.getNumber();
        }

        public CasePin getFromCasePin()
        {
            return from;
        }

        public CasePin getToCasePin()
        {
           return to;
        }
    }

    private static Collection freeObjects = new Vector();
    private static Collection usedObjects = new Vector();
    private static Collection usedCases   = new Vector();
    private static Collection connections = new Vector();

    protected static void reset()
    {
       freeObjects = new Vector();
       usedObjects = new Vector();
       usedCases   = new Vector();
       connections = new Vector();
    }

    public static Collection getUsedCases()
    {
      return new Vector(usedCases);
    }

    public static Collection getUsedConnections()
    {
      return new Vector(connections);
    }

    /**
     *
     */
    public static ElectricObject getElectricObject(String type)
    {
        // erst einmal in die bereits geladenen und freien objecte
        // nachschauen.
        //
        for(Iterator iter = freeObjects.iterator();iter.hasNext();)
        {
            ElectricObject eobj = (ElectricObject)iter.next();
            if(eobj.getType().equals(type))
            {
                Trace.info("OBject ["+eobj.getType()+"] isSingeton="+eobj.getIsSingelton());
                if(eobj.getIsSingelton()>0)
                {
                    // singelton => nur einmal hinzufuegen
                    if(!usedObjects.contains(eobj))
                        usedObjects.add(eobj);
                }
                else
                {
                    freeObjects.remove(eobj);
                    usedObjects.add(eobj);
                }
                return eobj;
            }
        }

        // the required object are not found in the current
        // prefeched object set. Try to find them in the db.
        //
        ElectricObject eobj = ElectricObject.findByType(type);
        if(eobj!=null)
        {

            ArrayList eCases = eobj.getAllCases();
            if(eCases.size()>0)
            {
                ElectricCase eCase =(ElectricCase) eCases.get(0);

                eCase.reserveResources();
                usedCases.add(eCase);
                // insert all objects of the case in the prefetched objectList
                //
                for(Iterator i=eCase.getObject2Cases().iterator();i.hasNext();)
                {
                    Object2Case o2c =(Object2Case)i.next();
                    freeObjects.add(o2c.getCurrentElectricObject());
                }

                ArrayList dep = eCase.getCaseDependencies();
                for(Iterator iter = dep.iterator(); iter.hasNext();)
                {
                    CaseDependency cd= (CaseDependency)iter.next();
                    // the required object from the DB
                    ElectricObject depObj = cd.getObject();
                    // and try to find the prefetched instance in the cache!!!!
                    depObj = getElectricObject(depObj.getType());
                    // get the objet pin
                    Iterator depIter = cd.getDependencyPins().iterator();
                    while(depIter.hasNext())
                    {
                       DependencyPin dp = (DependencyPin)depIter.next();
                       long objectPinNum = dp.getObjectPin().getNumber();
                       long casePinNum   = dp.getCasePin().getNumber();
                       CasePin p1 = depObj.getCasePin(objectPinNum);
                       CasePin p2 = eCase.getPin(casePinNum);

                       connect(p1,p2);
                    }
                }
               return getElectricObject(type);
            }
            // it must be a macro
            else
            {
              eobj.reserveResources();
              ArrayList connections = de.freegroup.digitalsimulator.export.wired.db.Connection.findByElectricObject(eobj);
              return eobj;
            }
        }
        new MsgBox(I18N.translate("Objekt nicht gefunden: ")+type);
        return null;
    }

    /**
     *
     */
    public static void connect(CasePin from, CasePin to)
    {
        if(from==null || to==null)
            throw new java.lang.NullPointerException("One or more parameter are null from=['"+from+"] to=["+to+"]");

        connections.add(new Connection(from,to));
    }

    /**
     *
     */
    public static String status()
    {
        String result="\nused Objects:";
        // the Objectlist
        for(Iterator iter=usedObjects.iterator(); iter.hasNext();)
        {
            result = result + "\n"+iter.next();
        }

        result += "\n\nused Cases";
        // the connection list
         for(Iterator iter=usedCases.iterator(); iter.hasNext();)
        {
            result = result + "\n"+iter.next();
        }

        result += "\n\nused Connectors";
         for(Iterator iter=connections.iterator(); iter.hasNext();)
        {
            result = result + "\n"+iter.next();
        }

        return result;
    }
}