package de.freegroup.digitalsimulator.export.wired.test;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import de.freegroup.digitalsimulator.export.wired.db.*;
import de.freegroup.digitalsimulator.export.wired.*;
import java.util.ArrayList;
import java.util.Iterator;

public class TestCase01
{
    public static void main(String[] args)
    {
        // we have 2 objects
        // 2 AND
        //                       +-----+
        //                     1 |     |
        //    -------------------+     |
        //         +-----+       |  &   o----
        //       1 |     |     2 |     | 3
        //    -----+     |   +---+     |
        //         |  &   O--+   +-----+
        //       2 |     |3      object2
        //    -----+     |
        //         +-----+
        //         object1
        //

        // beide eventuel verschieden object finden
        //
        ElectricObject object1 = ObjectFactory.getElectricObject("OBJ_NAND");
        ElectricObject object2 = ObjectFactory.getElectricObject("OBJ_NAND");

//        ObjectPin opin1= object1.getPin(3);
//        ObjectPin opin2= object2.getPin(2);
//
//        ObjectFactory.connect(opin1.getCasePin(),opin2.getCasePin());
//
//       // System.out.println("Gehäuse "+object1.getCurrentElectricCase()+" pin "+opin1.getCasePin().getNumber()+" \n-->\nGehäuse "+object2.getCurrentElectricCase()+" pin "+opin2.getCasePin().getNumber());
//
//        System.out.println(ObjectFactory.status());
    }
}