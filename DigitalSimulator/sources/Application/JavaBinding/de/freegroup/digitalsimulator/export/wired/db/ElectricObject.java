package de.freegroup.digitalsimulator.export.wired.db;

/**
 * Class generated by automatic ClassGenerator
 * Date: Wed Feb 27 17:58:16 GMT+01:00 2002
 */
import de.freegroup.digitalsimulator.db.*;
import de.freegroup.digitalsimulator.export.wired.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.sql.*;
import Trace;
import java.util.*;

public class ElectricObject extends _dbElectricObject
{
    private ElectricCase currentCase         = null;
    private Object2Case currentObject2Case = null;
    private ArrayList    pinMappingObjects   = new ArrayList();
    private HashMap      relatedObjects      = new HashMap();

    public ArrayList     getAllCases()
    {
        ArrayList result = new ArrayList();
        ArrayList c2o = getObject2Cases();
        Iterator iter = c2o.iterator();
        while(iter.hasNext())
        {
            Object2Case eobj = (Object2Case)iter.next();
            result.add(eobj.getElectricCase());
        }

        return result;
    }

   public ObjectPin getPin(long number)
    {
//        if(currentObject2Case==null)
//         return getObject2Cases().get
        Iterator iter = currentObject2Case.getObjectPins().iterator();
        while(iter.hasNext())
        {
            ObjectPin opin= (ObjectPin)iter.next();
            if(opin.getNumber()==number)
                return opin;
        }
        return null;
    }

    public ElectricCase getCurrentElectricCase()
    {
      return currentCase;
    }

    /**
     *
     */
    public CasePin getCasePin(long objectPinIndex)
    {
        if(pinMappingObjects.size()!=0)
        {
           for(Iterator iter= pinMappingObjects.iterator(); iter.hasNext();)
           {
               MacroPinMapping mapping = (MacroPinMapping) iter.next();
               if(mapping.electricObjectPinNum==objectPinIndex)
                  return mapping.getMappedCasePin();
           }
        }
        else
        {
           Iterator iter = currentObject2Case.getObjectPins().iterator();
           while(iter.hasNext())
           {
               ObjectPin opin= (ObjectPin)iter.next();
               if(opin.getNumber()==objectPinIndex)
                   return opin.getCasePin();
           }
        }
        return null;
    }

    /**
     *
     */
    protected void reserveResources( ElectricCase _currentCase, Object2Case _object2Case)
    {
//        System.out.println("reserve "+getClass().getName()+"@"+this.hashCode());
        currentCase        = _currentCase;
        currentObject2Case = _object2Case;
//
//       currentObject2Case.reserveResources(this);
    }


    public void reserveResources()
    {

        try
        {

           // get all related  objects to this macro and cache them
           //
           Iterator relIter = RelatedObject.findByMasterObject(this).iterator();
           while(relIter.hasNext())
           {
               RelatedObject relObj = (RelatedObject)relIter.next();
               if(relObj==null)
                  Trace.error("related object is null");
               ElectricObject eobj = ObjectFactory.getElectricObject(relObj.getRelatedObject().getType());
               if(eobj==null)
                  Trace.error("unable to resolve dependencies to ["+relObj.getRelatedObject()+"]");
               relatedObjects.put(relObj.getId(), eobj);
           }

           ArrayList connections = de.freegroup.digitalsimulator.export.wired.db.Connection.findByElectricObject(this);
           for(Iterator iter = connections.iterator(); iter.hasNext();)
            {
               Connection con = (Connection)iter.next();
               long fromNum = con.getFromPinNuum();
               long toNum   = con.getToPinNum();

               ElectricObject from  = (ElectricObject)relatedObjects.get( con.fromRelatedObject_id);
               ElectricObject to    = (ElectricObject)relatedObjects.get( con.toRelatedObject_id);

               ObjectFactory.connect(from.getCasePin(fromNum),to.getCasePin(toNum));
            }

           ArrayList mappings  = this.getMacroPinMappings();
           for(Iterator iter = mappings.iterator(); iter.hasNext();)
           {
              MacroPinMapping mapping = (MacroPinMapping)iter.next();
              mapping.reserveResources(this, (ElectricObject)(relatedObjects.get(mapping.getRelatedObject().getId()) ));
              pinMappingObjects.add(mapping);
           }
        }
        catch (Exception ex)
        {
            Trace.error("unable to resolveResources", ex);
        }
     }


//    public ObjectLayout getObjectLayout()
//    {
//      if(currentObjectLayout!=null)
//         return currentObjectLayout;
//
//      return null;
//    }
//

    public String toString()
    {
        return "["+super.toString()+"]@"+ this.hashCode();
    }
}