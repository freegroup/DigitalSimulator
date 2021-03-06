package de.freegroup.digitalsimulator.export.wired.db;

/**
 * Class generated by automatic ClassGenerator
 * Date: Wed Feb 27 17:58:17 GMT+01:00 2002
 */
import de.freegroup.digitalsimulator.db.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.sql.*;
import Trace;

public class Object2Case extends _dbObject2Case
{
   ArrayList      currentObjectPins = null;
   ElectricCase   currentCase       = null;
   ElectricObject currentElectricObject = null;

   public ArrayList getObjectPins()
   {
        if(currentObjectPins!=null)
            return currentObjectPins;

        return super.getObjectPins();
   }

   protected void reserveResources(ElectricCase ecase)
   {
//        System.out.println("reserve "+getClass().getName()+"@"+this.hashCode());
      currentCase = ecase;
      currentElectricObject = this.getObject();
      currentElectricObject.reserveResources(ecase, this);
      currentObjectPins = super.getObjectPins();
      Iterator iter = currentObjectPins.iterator();
      while(iter.hasNext())
      {
         ObjectPin objectPin= (ObjectPin)iter.next();
         objectPin.reserveResources(this);
      }
   }

   protected ElectricCase getCurrentElectricCase()
   {
        return currentCase;
   }
   public ElectricObject getCurrentElectricObject()
   {
        return currentElectricObject;
   }
//

    public String toString()
    {
        return "["+super.toString()+"]@"+ this.hashCode();
    }

    public ObjectPin getPin(long number)
    {
        Iterator iter = getObjectPins().iterator();
        while(iter.hasNext())
        {
            ObjectPin opin= (ObjectPin)iter.next();
            if(opin.getNumber()==number)
                return opin;
        }
        return null;
    }

}
