package de.freegroup.digitalsimulator.export.wired.util.db;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import java.util.HashMap;
import de.freegroup.digitalsimulator.export.wired.db.*;

public class FillDB
{
    static Object2Case schalter1XAusRel  = null;
    static Object2Case ne555Rel          = null;

    static HashMap     objects         = new HashMap();
    static HashMap     objects2cases   = new HashMap();
    
    private static ElectricObject getObject(String name)
    {
      return (ElectricObject)objects.get(name);
    }
    
    private static Object2Case getObject2Case(String name)
    {
      return (Object2Case)objects2cases.get(name);
    }
    
    public static void main(String[] args)
    {
      	CreateDB.main(args);
      	
        createO_INTERFACE_8_0();
        createI_INTERFACE_0_8();
        createBasic_Voltage("5VOLT","Versorgungsspannung 5 Volt Gleichspannung");
        createBasic_Resistor("200 OHM" ,"Widerstand 200 Ohm");
        createBasic_Resistor("470 OHM" ,"Widerstand 470 Ohm");
        createBasic_Resistor("820 OHM" ,"Widerstand 820 Ohm");
        createBasic_Resistor("3300 OHM","Widerstand 3.3k Ohm");
        createBasic_Resistor("1000 OHM","Widerstand 1k Ohm");
        createBasic_Resistor("4700 OHM","Widerstand 4.7k Ohm");

        createBasic_Trimmer("P100000 OHM","Trimmer 100k Ohm"); // 'P' stands for potentiometer
        createBasic_Trimmer("P1000000 OHM","Trimmer 1M Ohm");  // 'P' stands for potentiometer

        createBasic_Diode("1N914", "Diode 1N914");             // pin 1=Anode    pin2=Kathode 
        createBasic_Diode("LED", "Leuchtdiode");               // pin 1=Anode    pin2=Kathode 

        createBasic_TransistorNPN("BC107","Transistor BC107BP (npn)");

        createBasic_Kondensator("c10nF","Kondensator 10nF");
        createBasic_1UMSwitch();
        
        create7400();
        create7402();
        create7404();
        create7474();
        create7486();
        create7490();
        create74109();
        create747266();
        createSchalter1XAus();
        createBasic_NE555();

        createOBJ_POWERTASTER0();
        createOBJ_POWERTASTER1();

        createMacro_OBJ_SWITCH_AUS();
        createMacro_OBJ_LED();
        createMacro_OBJ_POWER_0_1();
        createMacro_OBJ_JK_SR_T_5_2();
        createMacro_OBJ_JK_R_T_4_2();
        createMacro_OBJ_JK_T_3_2();
        createMacro_OBJ_T_1_2();
        createMacro_OBJ_D_R_T_3_2();
        createMacro_OBJ_D_T_2_2();
        createMacro_GND_0_1();
        createMacro_High_0_1();
        createMarcro_OBJ_TAKT_0_1();
        createMacro_LED_BAR_red_1_0();
        createMacro_LED_BAR_red_2_0();
        createMacro_LED_BAR_red_3_0();
        createMacro_LED_BAR_red_4_0();
        createMacro_LED_BAR_red_5_0();
        createMacro_LED_BAR_red_6_0();
        createMacro_LED_BAR_red_7_0();
        createMacro_LED_BAR_red_8_0();
        createMacro_OBJ_BCDCOUNTER_2_4();
        System.exit(1);
    }

    /**
     *    Quad 2-input NAND gates.
     *        +---+--+---+             +---+---*---+           __
     *     1A |1  +--+ 14| VCC         | A | B |/Y |      /Y = AB
     *     1B |2       13| 4B          +===+===*===+
     *    /1Y |3       12| 4A          | 0 | 0 | 1 |
     *     2A |4  7400 11| /4Y         | 0 | 1 | 1 |
     *     2B |5       10| 3B          | 1 | 0 | 1 |
     *    /2Y |6        9| 3A          | 1 | 1 | 0 |
     *    GND |7        8| /3Y         +---+---*---+
     *        +----------+
     **/
    private static void create7400()
    {
        String objectName = "OBJ_NAND_2_1";
        String caseName   = "7400 (4xNAND)";

        // Layout eines Gehäuses erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance( "1A",1,cl,0, 0);
        CasePin     cp02  = CasePin.createInstance( "1B",2,cl,0, 0);
        CasePin     cp03  = CasePin.createInstance( "1Y",3,cl,0, 0);
        CasePin     cp04  = CasePin.createInstance( "2A",4,cl,0, 0);
        CasePin     cp05  = CasePin.createInstance( "2B",5,cl,0, 0);
        CasePin     cp06  = CasePin.createInstance( "2Y",6,cl,0, 0);
        CasePin     cp07  = CasePin.createInstance( "GND",7,cl,0, 0);
        CasePin     cp08  = CasePin.createInstance( "3Y",8,cl,0, 0);
        CasePin     cp09  = CasePin.createInstance( "3A",9,cl,0, 0);
        CasePin     cp10  = CasePin.createInstance( "3B",10,cl,0, 0);
        CasePin     cp11  = CasePin.createInstance( "4Y",11,cl,0, 0);
        CasePin     cp12  = CasePin.createInstance( "4A",12,cl,0, 0);
        CasePin     cp13  = CasePin.createInstance( "4B",13,cl,0, 0);
        CasePin     cp14  = CasePin.createInstance( "VCC",14,cl,0, 0);

        // Gehäuse mit dem Layout erzeugen
        //
        ElectricCase   c = ElectricCase.createInstance(caseName,"http://www.falstaff.demon.co.uk/7400.html",cl);
        
        // Abhängigkeiten des Gehäuses mit anderen Elementen (Stromversorgung....) anlegen
        //
        CaseDependency cd = CaseDependency.createInstance(getObject("5VOLT"),c); // Relation zu der Stromversorgung herstellen

        // Pins der Stromversorgung an das Gehäuse des 7400 legen
        //
        DependencyPin.createInstance(getObject2Case("5VOLT").getPin(1),c.getPin(14),cd);          // VCC-Pin der Stromversorgung mit dem Gehäuse verbinden
        DependencyPin.createInstance(getObject2Case("5VOLT").getPin(2),c.getPin(7),cd);           // GND-Pin der Stromversorgung mit dem Gehäuse verbinden

        
        // Objektlayout erzeugen
        //
        ObjectLayout ol = ObjectLayout.createInstance();
        
        // Objekt erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(false,objectName,ol ); // NAND mit 2 Eingänge und 1 Ausgang

        // Objekt in das Gehäuse einbetten. Es werden auch die Pins des Objektes mit den
        // des Gehäuses verbunden. z.B Gehäuse Pin2 geht an NAND Nummer 1 / Pin 1  
        // (In diesem Fall sind 4 NAND's in einem Gehäuse)
        //
        Object2Case o2c =Object2Case.createInstance(eobj,c);
        ObjectPin2CasePin      op11 = ObjectPin2CasePin.createInstance(cp01,o2c,ObjectPin.createInstance("A",1,ol));
        ObjectPin2CasePin      op12 = ObjectPin2CasePin.createInstance(cp02,o2c,ObjectPin.createInstance("B",2,ol));
        ObjectPin2CasePin      op13 = ObjectPin2CasePin.createInstance(cp03,o2c,ObjectPin.createInstance("Y",3,ol));

        o2c =Object2Case.createInstance(eobj,c);
        ObjectPin2CasePin      op21 = ObjectPin2CasePin.createInstance(cp04,o2c,ObjectPin.createInstance("A",1,ol));
        ObjectPin2CasePin      op22 = ObjectPin2CasePin.createInstance(cp05,o2c,ObjectPin.createInstance("B",2,ol));
        ObjectPin2CasePin      op23 = ObjectPin2CasePin.createInstance(cp06,o2c,ObjectPin.createInstance("Y",3,ol));

        o2c =Object2Case.createInstance(eobj,c);
        ObjectPin2CasePin      op31 = ObjectPin2CasePin.createInstance(cp09,o2c,ObjectPin.createInstance("A",1,ol));
        ObjectPin2CasePin      op32 = ObjectPin2CasePin.createInstance(cp10,o2c,ObjectPin.createInstance("B",2,ol));
        ObjectPin2CasePin      op33 = ObjectPin2CasePin.createInstance(cp08,o2c,ObjectPin.createInstance("Y",3,ol));

        o2c =Object2Case.createInstance(eobj,c);
        ObjectPin2CasePin      op41 = ObjectPin2CasePin.createInstance(cp12,o2c,ObjectPin.createInstance("A",1,ol));
        ObjectPin2CasePin      op42 = ObjectPin2CasePin.createInstance(cp13,o2c,ObjectPin.createInstance("B",2,ol));
        ObjectPin2CasePin      op43 = ObjectPin2CasePin.createInstance(cp11,o2c,ObjectPin.createInstance("Y",3,ol));

        objects.put(objectName  , eobj);
    }

    /**
     * 
     * @author Administrator
     * 7402
     * Quad 2-input NOR gates.
     *
     *     +---+  +---+             +---+---+---+           ___
     * /1Y |1  +--+ 14| VCC         | A | B I/Y |      /Y = A+B
     *  1A |2       13| /4Y         +===+===+===+
     *  1B |3       12| 4B          | 0 | 0 I 1 |
     * /2Y |4  7402 11| 4A          | 0 | 1 I 0 |
     *  2A |5       10| /3Y         | 1 | 0 I 0 |
     *  2B |6        9| 3B          | 1 | 1 I 0 |
     * GND |7        8| 3A          +---+---+---+
     *     +----------+
     **/
    private static void create7402()
    {
        String objectName = "OBJ_NOR_2_1";
        String caseName   = "7402 (4xNOR)";

        // Layout eines Gehäuses erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance( "1Y",1,cl,0, 0);
        CasePin     cp02  = CasePin.createInstance( "1A",2,cl,0, 0);
        CasePin     cp03  = CasePin.createInstance( "1B",3,cl,0, 0);
        CasePin     cp04  = CasePin.createInstance( "2Y",4,cl,0, 0);
        CasePin     cp05  = CasePin.createInstance( "2A",5,cl,0, 0);
        CasePin     cp06  = CasePin.createInstance( "2B",6,cl,0, 0);
        CasePin     cp07  = CasePin.createInstance( "GND",7,cl,0, 0);
        CasePin     cp08  = CasePin.createInstance( "3A",8,cl,0, 0);
        CasePin     cp09  = CasePin.createInstance( "3B",9,cl,0, 0);
        CasePin     cp10  = CasePin.createInstance( "3Y",10,cl,0, 0);
        CasePin     cp11  = CasePin.createInstance( "4A",11,cl,0, 0);
        CasePin     cp12  = CasePin.createInstance( "4B",12,cl,0, 0);
        CasePin     cp13  = CasePin.createInstance( "4Y",13,cl,0, 0);
        CasePin     cp14  = CasePin.createInstance( "VCC",14,cl,0, 0);

        // Gehäuse mit dem Layout erzeugen
        //
        ElectricCase   c     = ElectricCase.createInstance("7402 (TTL-Bausteil)","http://www.falstaff.demon.co.uk/7400.html",cl);
        
        // Abhängigkeiten des Gehäuses mit anderen Elementen (Stromversorgung....) anlegen
        //
        CaseDependency cd = CaseDependency.createInstance(getObject("5VOLT"),c); // Relation zu der Stromversorgung herstellen

        // Pins der Stromversorgung an das Gehäuse des 7400 legen
        //
        DependencyPin.createInstance(getObject2Case("5VOLT").getPin(1),c.getPin(14),cd);          // VCC-Pin der Stromversorgung mit dem Gehäuse verbinden
        DependencyPin.createInstance(getObject2Case("5VOLT").getPin(2),c.getPin(7),cd);           // GND-Pin der Stromversorgung mit dem Gehäuse verbinden

        
        // Objektlayout erzeugen
        //
        ObjectLayout ol = ObjectLayout.createInstance();
        
        // Objekt erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(false,"OBJ_NOR_2_1",ol ); // NAND mit 2 Eingänge und 1 Ausgang

        // Objekt in das Gehäuse einbetten. Es werden auch die Pins des Objektes mit den
        // des Gehäuses verbunden. z.B Gehäuse Pin2 geht an NAND Nummer 1 / Pin 1  
        // (In diesem Fall sind 4 NAND's in einem Gehäuse)
        //
        Object2Case o2c =Object2Case.createInstance(eobj,c);
        ObjectPin2CasePin      op11 = ObjectPin2CasePin.createInstance(cp01,o2c,ObjectPin.createInstance("Y",3,ol));
        ObjectPin2CasePin      op12 = ObjectPin2CasePin.createInstance(cp02,o2c,ObjectPin.createInstance("A",1,ol));
        ObjectPin2CasePin      op13 = ObjectPin2CasePin.createInstance(cp03,o2c,ObjectPin.createInstance("B",2,ol));

        o2c =Object2Case.createInstance(eobj,c);
        ObjectPin2CasePin      op21 = ObjectPin2CasePin.createInstance(cp04,o2c,ObjectPin.createInstance("Y",3,ol));
        ObjectPin2CasePin      op22 = ObjectPin2CasePin.createInstance(cp05,o2c,ObjectPin.createInstance("A",1,ol));
        ObjectPin2CasePin      op23 = ObjectPin2CasePin.createInstance(cp06,o2c,ObjectPin.createInstance("B",2,ol));

        o2c =Object2Case.createInstance(eobj,c);
        ObjectPin2CasePin      op31 = ObjectPin2CasePin.createInstance(cp08,o2c,ObjectPin.createInstance("A",1,ol));
        ObjectPin2CasePin      op32 = ObjectPin2CasePin.createInstance(cp09,o2c,ObjectPin.createInstance("B",2,ol));
        ObjectPin2CasePin      op33 = ObjectPin2CasePin.createInstance(cp10,o2c,ObjectPin.createInstance("Y",3,ol));

        o2c =Object2Case.createInstance(eobj,c);
        ObjectPin2CasePin      op41 = ObjectPin2CasePin.createInstance(cp11,o2c,ObjectPin.createInstance("A",1,ol));
        ObjectPin2CasePin      op42 = ObjectPin2CasePin.createInstance(cp12,o2c,ObjectPin.createInstance("B",2,ol));
        ObjectPin2CasePin      op43 = ObjectPin2CasePin.createInstance(cp13,o2c,ObjectPin.createInstance("Y",3,ol));

        objects.put(objectName  , eobj);
    }
    
    /**
     *    Hex inverters.
     *        +---+--+---+             +---*---+               _
     *     1A |1  +--+ 14| VCC         | A |/Y |          /Y = A
     *    /1Y |2       13| 6A          +===*===+
     *     2A |3       12| /6Y         | 0 | 1 |
     *    /2Y |4  7404 11| 5A          | 1 | 0 |
     *     3A |5       10| /5Y         +---*---+
     *    /3Y |6        9| 4A
     *    GND |7        8| /4Y
     *        +----------+
     **/
    private static void create7404()
    {
      // generate the Caselayout
      //
      CaseLayout    cl  = CaseLayout.createInstance();
      CasePin     cp01  = CasePin.createInstance("",1,cl,0l,0l);
      CasePin     cp02  = CasePin.createInstance("",2,cl,0l,0l);
      CasePin     cp03  = CasePin.createInstance("",3,cl,0l,0l);
      CasePin     cp04  = CasePin.createInstance("",4,cl,0l,0l);
      CasePin     cp05  = CasePin.createInstance("",5,cl,0l,0l);
      CasePin     cp06  = CasePin.createInstance("",6,cl,0l,0l);
      CasePin     cp07  = CasePin.createInstance("GND",7,cl,0l,0l);
      CasePin     cp08  = CasePin.createInstance("",8,cl,0l,0l);
      CasePin     cp09  = CasePin.createInstance("",9,cl,0l,0l);
      CasePin     cp10  = CasePin.createInstance("",10,cl,0l,0l);
      CasePin     cp11  = CasePin.createInstance("",11,cl,0l,0l);
      CasePin     cp12  = CasePin.createInstance("",12,cl,0l,0l);
      CasePin     cp13  = CasePin.createInstance("",13,cl,0l,0l);
      CasePin     cp14  = CasePin.createInstance("VCC",14,cl,0l,0l);

      // Gehäuse mit dem Layout verbinden
      //
      ElectricCase   c     = ElectricCase.createInstance("7404 (TTL-Baustein)","http://www.falstaff.demon.co.uk/7400.html",cl);

      // Abhängigkeiten des Gehäuses mit anderen Elementen (Stromversorgung....) anlegen
      //
      CaseDependency cd = CaseDependency.createInstance(getObject("5VOLT"),c); // Relation zu der Stromversorgung herstellen

      // Pins der Stromversorgung an das Gehäuse des 7400 legen
      //
      DependencyPin.createInstance(getObject2Case("5VOLT").getPin(1),c.getPin(14),cd);          // VCC-Pin der Stromversorgung mit dem Gehäuse verbinden
      DependencyPin.createInstance(getObject2Case("5VOLT").getPin(2),c.getPin(7),cd);           // GND-Pin der Stromversorgung mit dem Gehäuse verbinden

      // Objektlayout erzeugen
      //
      ObjectLayout ol = ObjectLayout.createInstance();
      
      // Objekt erzeugen
      //
      ElectricObject eobj = ElectricObject.createInstance(false,"OBJ_NOT_1_1",ol ); // NAND mit 2 Eingänge und 1 Ausgang

      // Objekt in das Gehäuse einbetten. Es werden auch die Pins des Objektes mit den
      // des Gehäuses verbunden. z.B Gehäuse Pin2 geht an NOT Nummer 1 / Pin 1  
      // (In diesem Fall sind 6 NOT's in einem Gehäuse)
      //
      Object2Case    o2c  = Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp01,o2c,ObjectPin.createInstance("",1,ol));
      ObjectPin2CasePin.createInstance(cp02,o2c,ObjectPin.createInstance("",2,ol));

      o2c =Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp03,o2c,ObjectPin.createInstance("",1,ol));
      ObjectPin2CasePin.createInstance(cp04,o2c,ObjectPin.createInstance("",2,ol));

      o2c =Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp05,o2c,ObjectPin.createInstance("",1,ol));
      ObjectPin2CasePin.createInstance(cp06,o2c,ObjectPin.createInstance("",2,ol));

      o2c =Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp09,o2c,ObjectPin.createInstance("",1,ol));
      ObjectPin2CasePin.createInstance(cp08,o2c,ObjectPin.createInstance("",2,ol));

      o2c =Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp11,o2c,ObjectPin.createInstance("",1,ol));
      ObjectPin2CasePin.createInstance(cp10,o2c,ObjectPin.createInstance("",2,ol));

      o2c =Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp13,o2c,ObjectPin.createInstance("",1,ol));
      ObjectPin2CasePin.createInstance(cp12,o2c,ObjectPin.createInstance("",2,ol));

    }

    
    /**
     *    Dual D flip-flop with set and reset.
     *          +---+--+---+           +---+---+----+----*---+---+
     *    /1RST |1  +--+ 14| VCC       | D |CLK|/SET|/RST| Q |/Q |
     *       1D |2       13| /2RST     +===+===+====+====*===+===+
     *     1CLK |3       12| 2D        | X | X |  0 |  0 | 1 | 1 |
     *    /1SET |4  7474 11| 2CLK      | X | X |  0 |  1 | 1 | 0 |
     *       1Q |5       10| /2SET     | X | X |  1 |  0 | 0 | 1 |
     *      /1Q |6        9| 2Q        | 0 | / |  1 |  1 | 0 | 1 |
     *      GND |7        8| /2Q       | 1 | / |  1 |  1 | 1 | 0 |
     *          +----------+           | X |!/ |  1 |  1 | - | - |
     *                                 +---+---+----+----*---+---+
     **/
    private static void create7474()
    {
      // generate the Caselayout
      //
      CaseLayout    cl  = CaseLayout.createInstance();
      CasePin     cp01  = CasePin.createInstance("1 !Reset",1,cl,0l,0l);
      CasePin     cp02  = CasePin.createInstance("1 D",2,cl,0l,0l);
      CasePin     cp03  = CasePin.createInstance("1 Clock",3,cl,0l,0l);
      CasePin     cp04  = CasePin.createInstance("1 !Set",4,cl,0l,0l);
      CasePin     cp05  = CasePin.createInstance("1 Q",5,cl,0l,0l);
      CasePin     cp06  = CasePin.createInstance("1 !Q",6,cl,0l,0l);
      CasePin     cp07  = CasePin.createInstance("GND",7,cl,0l,0l);
      CasePin     cp08  = CasePin.createInstance("2 !Q",8,cl,0l,0l);
      CasePin     cp09  = CasePin.createInstance("2 Q",9,cl,0l,0l);
      CasePin     cp10  = CasePin.createInstance("2 Set",10,cl,0l,0l);
      CasePin     cp11  = CasePin.createInstance("2 Clock",11,cl,0l,0l);
      CasePin     cp12  = CasePin.createInstance("2 D",12,cl,0l,0l);
      CasePin     cp13  = CasePin.createInstance("2 Reset",13,cl,0l,0l);
      CasePin     cp14  = CasePin.createInstance("VCC",14,cl,0l,0l);

      // Gehäuse mit dem Layout verbinden
      //
      ElectricCase   c     = ElectricCase.createInstance("7404 (TTL-Baustein)","http://www.falstaff.demon.co.uk/7400.html",cl);

      // Abhängigkeiten des Gehäuses mit anderen Elementen (Stromversorgung....) anlegen
      //
      CaseDependency cd = CaseDependency.createInstance(getObject("5VOLT"),c); // Relation zu der Stromversorgung herstellen

      // Pins der Stromversorgung an das Gehäuse des 7400 legen
      //
      DependencyPin.createInstance(getObject2Case("5VOLT").getPin(1),c.getPin(14),cd);          // VCC-Pin der Stromversorgung mit dem Gehäuse verbinden
      DependencyPin.createInstance(getObject2Case("5VOLT").getPin(2),c.getPin(7),cd);           // GND-Pin der Stromversorgung mit dem Gehäuse verbinden

      // Objektlayout erzeugen
      //
      ObjectLayout ol = ObjectLayout.createInstance();
      
      // Objekt erzeugen
      //
      ElectricObject eobj = ElectricObject.createInstance(false,"OBJ_D_SR_T_4_2",ol ); // NAND mit 2 Eingänge und 1 Ausgang
      
      // generate the internal object layout
      //
      Object2Case o2c =Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp04,o2c,ObjectPin.createInstance("Set",1,ol));
      ObjectPin2CasePin.createInstance(cp02,o2c,ObjectPin.createInstance("D",2,ol));
      ObjectPin2CasePin.createInstance(cp03,o2c,ObjectPin.createInstance("Clock",3,ol));
      ObjectPin2CasePin.createInstance(cp01,o2c,ObjectPin.createInstance("Reset",4,ol));
      ObjectPin2CasePin.createInstance(cp05,o2c,ObjectPin.createInstance("Q",5,ol));
      ObjectPin2CasePin.createInstance(cp06,o2c,ObjectPin.createInstance("!Q",6,ol));

      o2c =Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp10,o2c,ObjectPin.createInstance("Set",1,ol));
      ObjectPin2CasePin.createInstance(cp12,o2c,ObjectPin.createInstance("D",2,ol));
      ObjectPin2CasePin.createInstance(cp11,o2c,ObjectPin.createInstance("Clock",3,ol));
      ObjectPin2CasePin.createInstance(cp13,o2c,ObjectPin.createInstance("Reset",4,ol));
      ObjectPin2CasePin.createInstance(cp09,o2c,ObjectPin.createInstance("Q",5,ol));
      ObjectPin2CasePin.createInstance(cp08,o2c,ObjectPin.createInstance("!Q",6,ol));
    }

    /**
     *   Quad 2-input XOR gates.
     *       +---+--+---+             +---+---*---+                    _   _
     *    1A |1  +--+ 14| VCC         | A | B | Y |       Y = A$B = (A.B)+(A.B)
     *    1B |2       13| 4B          +===+===*===+
     *    1Y |3       12| 4A          | 0 | 0 | 0 |
     *    2A |4  7486 11| 4Y          | 0 | 1 | 1 |
     *    2B |5       10| 3B          | 1 | 0 | 1 |
     *    2Y |6        9| 3A          | 1 | 1 | 0 |
     *   GND |7        8| 3Y          +---+---*---+
     *       +----------+
     **/
    private static void create7486()
    {
      // generate the Caselayout
      //
      CaseLayout    cl  = CaseLayout.createInstance();
      CasePin     cp01  = CasePin.createInstance("", 1,cl,0l,0l);
      CasePin     cp02  = CasePin.createInstance("",2,cl,0l,0l);
      CasePin     cp03  = CasePin.createInstance("",3,cl,0l,0l);
      CasePin     cp04  = CasePin.createInstance("",4,cl,0l,0l);
      CasePin     cp05  = CasePin.createInstance("",5,cl,0l,0l);
      CasePin     cp06  = CasePin.createInstance("",6,cl,0l,0l);
      CasePin     cp07  = CasePin.createInstance("GND",7,cl,0l,0l);
      CasePin     cp08  = CasePin.createInstance("",8,cl,0l,0l);
      CasePin     cp09  = CasePin.createInstance("",9,cl,0l,0l);
      CasePin     cp10  = CasePin.createInstance("",10,cl,0l,0l);
      CasePin     cp11  = CasePin.createInstance("",11,cl,0l,0l);
      CasePin     cp12  = CasePin.createInstance("",12,cl,0l,0l);
      CasePin     cp13  = CasePin.createInstance("",13,cl,0l,0l);
      CasePin     cp14  = CasePin.createInstance("VCC",14,cl,0l,0l);

      // Gehäuse mit dem Layout verbinden
      //
      ElectricCase   c     = ElectricCase.createInstance("7486 (TTL-Baustein)","http://...",cl);

      // Abhängigkeiten des Gehäuses mit anderen Elementen (Stromversorgung....) anlegen
      //
      CaseDependency cd = CaseDependency.createInstance(getObject("5VOLT"),c); // Relation zu der Stromversorgung herstellen

      // Pins der Stromversorgung an das Gehäuse des 7400 legen
      //
      DependencyPin.createInstance(getObject2Case("5VOLT").getPin(1),c.getPin(14),cd);          // VCC-Pin der Stromversorgung mit dem Gehäuse verbinden
      DependencyPin.createInstance(getObject2Case("5VOLT").getPin(2),c.getPin(7),cd);           // GND-Pin der Stromversorgung mit dem Gehäuse verbinden

      // Objektlayout erzeugen
      //
      ObjectLayout ol = ObjectLayout.createInstance();
      
      // Objekt erzeugen
      //
      ElectricObject eobj = ElectricObject.createInstance(false,"OBJ_XOR_2_1",ol ); // 2eingänge und 1 Ausgang

      // generate the internal object layout
      //
      Object2Case o2c =Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp01,o2c,ObjectPin.createInstance("",1,ol));
      ObjectPin2CasePin.createInstance(cp02,o2c,ObjectPin.createInstance("",2,ol));
      ObjectPin2CasePin.createInstance(cp03,o2c,ObjectPin.createInstance("",3,ol));

      o2c =Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp04,o2c,ObjectPin.createInstance("",1,ol));
      ObjectPin2CasePin.createInstance(cp05,o2c,ObjectPin.createInstance("",2,ol));
      ObjectPin2CasePin.createInstance(cp06,o2c,ObjectPin.createInstance("",3,ol));

      o2c =Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp09,o2c,ObjectPin.createInstance("",1,ol));
      ObjectPin2CasePin.createInstance(cp10,o2c,ObjectPin.createInstance("",2,ol));
      ObjectPin2CasePin.createInstance(cp08,o2c,ObjectPin.createInstance("",3,ol));

      o2c =Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp12,o2c,ObjectPin.createInstance("",1,ol));
      ObjectPin2CasePin.createInstance(cp13,o2c,ObjectPin.createInstance("",2,ol));
      ObjectPin2CasePin.createInstance(cp11,o2c,ObjectPin.createInstance("",3,ol));
    }

    /**
     *    7490
     *    4-bit asynchronous decade counter with /2 and /5 sections, set(9) and reset.
     *    
     *          +---+  +---+
     *    /CLK1 |1  +--+ 14| /CLK0
     *     RST1 |2       13| NC
     *     RST2 |3       12| Q0
     *       NC |4  7490 11| Q3
     *      VCC |5       10| GND
     *     SET1 |6        9| Q1
     *     SET2 |7        8| Q2
     *          +----------+
    **/
    private static void create7490()
    {
        String objectName = "OBJECT.BCDCOUNTER.7490";
        String caseName   = "7490 (Asynchroner dezimaler Vorwärtszähler)";

        // Layout eines Gehäuses erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance( "B",1,cl,0, 0);
        CasePin     cp02  = CasePin.createInstance( "R01",2,cl,0, 0);
        CasePin     cp03  = CasePin.createInstance( "R02",3,cl,0, 0);
        CasePin     cp04  = CasePin.createInstance( "NC",4,cl,0, 0);
        CasePin     cp05  = CasePin.createInstance( "VCC",5,cl,0, 0);
        CasePin     cp06  = CasePin.createInstance( "S91",6,cl,0, 0);
        CasePin     cp07  = CasePin.createInstance( "S92",7,cl,0, 0);
        CasePin     cp08  = CasePin.createInstance( "Q2",8,cl,0, 0);
        CasePin     cp09  = CasePin.createInstance( "Q1",9,cl,0, 0);
        CasePin     cp10  = CasePin.createInstance( "GND",10,cl,0, 0);
        CasePin     cp11  = CasePin.createInstance( "Q3",11,cl,0, 0);
        CasePin     cp12  = CasePin.createInstance( "Q0",12,cl,0, 0);
        CasePin     cp13  = CasePin.createInstance( "NC",13,cl,0, 0);
        CasePin     cp14  = CasePin.createInstance( "A",14,cl,0, 0);

        // Gehäuse mit dem Layout erzeugen
        //
        ElectricCase   c     = ElectricCase.createInstance(caseName,"",cl);
        
        // Abhängigkeiten des Gehäuses mit anderen Elementen (Stromversorgung....) anlegen
        //
        CaseDependency cd = CaseDependency.createInstance(getObject("5VOLT"),c); // Relation zu der Stromversorgung herstellen

        // Pins der Stromversorgung an das Gehäuse des 7490 legen
        //
        DependencyPin.createInstance(getObject2Case("5VOLT").getPin(1),c.getPin(5),cd);       // VCC-Pin der Stromversorgung mit dem Gehäuse verbinden
        DependencyPin.createInstance(getObject2Case("5VOLT").getPin(2),c.getPin(10),cd);      // GND-Pin der Stromversorgung mit dem Gehäuse verbinden

        // Objektlayout erzeugen
        //
        ObjectLayout ol = ObjectLayout.createInstance();
        
        // Objekt erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(false,objectName,ol ); //BCD Counter

        // Objekt in das Gehäuse einbetten. Es werden auch die Pins des Objektes mit den
        // des Gehäuses verbunden. 
        //
        Object2Case o2c =Object2Case.createInstance(eobj,c);
        ObjectPin2CasePin.createInstance(cp02,o2c,ObjectPin.createInstance("R01",1,ol));
        ObjectPin2CasePin.createInstance(cp03,o2c,ObjectPin.createInstance("R02",2,ol));
        ObjectPin2CasePin.createInstance(cp06,o2c,ObjectPin.createInstance("S91",3,ol));
        ObjectPin2CasePin.createInstance(cp07,o2c,ObjectPin.createInstance("S92",4,ol));
        ObjectPin2CasePin.createInstance(cp14,o2c,ObjectPin.createInstance("A",5,ol));
        ObjectPin2CasePin.createInstance(cp01,o2c,ObjectPin.createInstance("B",6,ol));
        ObjectPin2CasePin.createInstance(cp12,o2c,ObjectPin.createInstance("Q0",7,ol));
        ObjectPin2CasePin.createInstance(cp09,o2c,ObjectPin.createInstance("Q1",8,ol));
        ObjectPin2CasePin.createInstance(cp08,o2c,ObjectPin.createInstance("Q2",9,ol));
        ObjectPin2CasePin.createInstance(cp11,o2c,ObjectPin.createInstance("Q3",10,ol));

        // objekt für späteren Zugriff merken
        objects.put(objectName  , eobj);
        objects2cases.put(objectName  , o2c);
    }


    /**
     * Dual J-/K flip-flops with set and reset.
     * 
     *         +---+--+---+           +---+---+---+----+----*---+---+
     *   /1RST |1  +--+ 16| VCC       | J |/K |CLK|/SET|/RST| Q |/Q |
     *      1J |2       15| /2RST     +===+===+===+====+====*===+===+
     *     /1K |3       14| 2J        | X | X | X |  0 |  0 | 1 | 1 |
     *    1CLK |4   74  13| /2K       | X | X | X |  0 |  1 | 1 | 0 |
     *   /1SET |5  109  12| 2CLK      | X | X | X |  1 |  0 | 0 | 1 |
     *      1Q |6       11| /2SET     | 0 | 0 | / |  1 |  1 | 0 | 1 |
     *     /1Q |7       10| 2Q        | 0 | 1 | / |  1 |  1 | - | - |
     *     GND |8        9| /2Q       | 1 | 0 | / |  1 |  1 |/Q | Q |
     *         +----------+           | 1 | 1 | / |  1 |  1 | 1 | 0 |
     *                                | X | X |!/ |  1 |  1 | - | - |
     *                                +---+---+---+----+----*---+---+
     **/
    private static void create74109()
    {
      String objectName = "OBJ_D_J!K_SR_T_5_2";
      String caseName   = "74109 (JK FlipFlop mit Setzt- und Rücksetzeingänge )";

      // generate the Caselayout
      //
      CaseLayout    cl  = CaseLayout.createInstance();
      CasePin     cp01  = CasePin.createInstance("1 !Reset",1,cl,0l,0l);
      CasePin     cp02  = CasePin.createInstance("1 J",2,cl,0l,0l);
      CasePin     cp03  = CasePin.createInstance("1 !K",3,cl,0l,0l);
      CasePin     cp04  = CasePin.createInstance("1 Clock",4,cl,0l,0l);
      CasePin     cp05  = CasePin.createInstance("1 '!Set",5,cl,0l,0l);
      CasePin     cp06  = CasePin.createInstance("1 Q",6,cl,0l,0l);
      CasePin     cp07  = CasePin.createInstance("1 !Q",7,cl,0l,0l);
      CasePin     cp08  = CasePin.createInstance("GND",8,cl,0l,0l);
      CasePin     cp09  = CasePin.createInstance("2 !Q",9,cl,0l,0l);
      CasePin     cp10  = CasePin.createInstance("2 Q",10,cl,0l,0l);
      CasePin     cp11  = CasePin.createInstance("2 !Set",11,cl,0l,0l);
      CasePin     cp12  = CasePin.createInstance("2 Clock",12,cl,0l,0l);
      CasePin     cp13  = CasePin.createInstance("2 !K",13,cl,0l,0l);
      CasePin     cp14  = CasePin.createInstance("2 J",14,cl,0l,0l);
      CasePin     cp15  = CasePin.createInstance("2 !Reset",15,cl,0l,0l);
      CasePin     cp16  = CasePin.createInstance("VCC",16,cl,0l,0l);

      // Gehäuse mit dem Layout erzeugen
      //
      ElectricCase   c     = ElectricCase.createInstance(caseName,"http://www.falstaff.demon.co.uk/74100.html",cl);
      
      // Abhängigkeiten des Gehäuses erzeugen
      //
      CaseDependency cd = CaseDependency.createInstance(getObject("5VOLT"),c);

      // Pins der Stromversorgung an das Gehäuse des 7490 legen
      //
      DependencyPin.createInstance(getObject2Case("5VOLT").getPin(1),c.getPin(16),cd);       // VCC-Pin der Stromversorgung mit dem Gehäuse verbinden
      DependencyPin.createInstance(getObject2Case("5VOLT").getPin(2),c.getPin(8),cd);      // GND-Pin der Stromversorgung mit dem Gehäuse verbinden

      // Objektlayout erzeugen
      //
      ObjectLayout ol = ObjectLayout.createInstance();
      
      // Objekt erzeugen
      //
      ElectricObject eobj = ElectricObject.createInstance(false,objectName,ol );

      // generate the internal object layout
      //
      Object2Case o2c =Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp02,o2c,ObjectPin.createInstance("R01",1,ol));
      ObjectPin2CasePin.createInstance(cp05,o2c,ObjectPin.createInstance("!Set",1,ol));
      ObjectPin2CasePin.createInstance(cp02,o2c,ObjectPin.createInstance("J",2,ol));
      ObjectPin2CasePin.createInstance(cp04,o2c,ObjectPin.createInstance("Clock",3,ol));
      ObjectPin2CasePin.createInstance(cp03,o2c,ObjectPin.createInstance("!K",4,ol));
      ObjectPin2CasePin.createInstance(cp01,o2c,ObjectPin.createInstance("!R",5,ol));
      ObjectPin2CasePin.createInstance(cp06,o2c,ObjectPin.createInstance("Q",6,ol));
      ObjectPin2CasePin.createInstance(cp07,o2c,ObjectPin.createInstance("!Q",6,ol));

      o2c =Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp11,o2c,ObjectPin.createInstance("!Set",1,ol));
      ObjectPin2CasePin.createInstance(cp14,o2c,ObjectPin.createInstance("J",2,ol));
      ObjectPin2CasePin.createInstance(cp12,o2c,ObjectPin.createInstance("Clock",3,ol));
      ObjectPin2CasePin.createInstance(cp13,o2c,ObjectPin.createInstance("!K",4,ol));
      ObjectPin2CasePin.createInstance(cp05,o2c,ObjectPin.createInstance("!R",5,ol));
      ObjectPin2CasePin.createInstance(cp10,o2c,ObjectPin.createInstance("Q",6,ol));
      ObjectPin2CasePin.createInstance(cp09,o2c,ObjectPin.createInstance("!Q",6,ol));
     }


    /**
     *    Quad 2-input XNOR gates.
     *        +---+--+---+             +---+---*---+          _     _ _
     *     1A |1  +--+ 14| VCC         | A | B |/Y |     Y = A$B = (A.B)+(A.B)
     *     1B |2       13| 4B          +===+===*===+
     *    /1Y |3  747  12| 4A          | 0 | 0 | 1 |
     *     2A |4  266  11| /4Y         | 0 | 1 | 0 |
     *     2B |5       10| 3B          | 1 | 0 | 0 |
     *    /2Y |6        9| 3A          | 1 | 1 | 1 |
     *    GND |7        8| /3Y         +---+---*---+
     *        +----------+
     **/
    private static void create747266()
    {
      String caseName   = "747266 (TTL-Baustein)";
      String objectName = "OBJ_XNOR_2_1";
      
      // generate the Caselayout
      //
      CaseLayout    cl  = CaseLayout.createInstance();
      CasePin     cp01  = CasePin.createInstance("", 1,cl,0l,0l);
      CasePin     cp02  = CasePin.createInstance("",2,cl,0l,0l);
      CasePin     cp03  = CasePin.createInstance("",3,cl,0l,0l);
      CasePin     cp04  = CasePin.createInstance("",4,cl,0l,0l);
      CasePin     cp05  = CasePin.createInstance("",5,cl,0l,0l);
      CasePin     cp06  = CasePin.createInstance("",6,cl,0l,0l);
      CasePin     cp07  = CasePin.createInstance("GND",7,cl,0l,0l);
      CasePin     cp08  = CasePin.createInstance("",8,cl,0l,0l);
      CasePin     cp09  = CasePin.createInstance("",9,cl,0l,0l);
      CasePin     cp10  = CasePin.createInstance("",10,cl,0l,0l);
      CasePin     cp11  = CasePin.createInstance("",11,cl,0l,0l);
      CasePin     cp12  = CasePin.createInstance("",12,cl,0l,0l);
      CasePin     cp13  = CasePin.createInstance("",13,cl,0l,0l);
      CasePin     cp14  = CasePin.createInstance("VCC",14,cl,0l,0l);

      // Gehäuse mit dem Layout erzeugen
      //
      ElectricCase   c     = ElectricCase.createInstance(caseName,"http://...",cl);
      
      // Abhängigkeiten des Gehäuses erzeugen
      //
      CaseDependency cd = CaseDependency.createInstance(getObject("5VOLT"),c);

      // Pins der Stromversorgung an das Gehäuse des 7490 legen
      //
      DependencyPin.createInstance(getObject2Case("5VOLT").getPin(1),c.getPin(16),cd);       // VCC-Pin der Stromversorgung mit dem Gehäuse verbinden
      DependencyPin.createInstance(getObject2Case("5VOLT").getPin(2),c.getPin(8),cd);      // GND-Pin der Stromversorgung mit dem Gehäuse verbinden

      // Objektlayout erzeugen
      //
      ObjectLayout ol = ObjectLayout.createInstance();
      
      // Objekt erzeugen
      //
      ElectricObject eobj = ElectricObject.createInstance(false,objectName,ol );
      
      // generate the internal object layout
      //
      Object2Case o2c =Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp01,o2c,ObjectPin.createInstance("",1,ol));
      ObjectPin2CasePin.createInstance(cp02,o2c,ObjectPin.createInstance("",2,ol));
      ObjectPin2CasePin.createInstance(cp03,o2c,ObjectPin.createInstance("",3,ol));

      o2c =Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp04,o2c,ObjectPin.createInstance("",1,ol));
      ObjectPin2CasePin.createInstance(cp05,o2c,ObjectPin.createInstance("",2,ol));
      ObjectPin2CasePin.createInstance(cp06,o2c,ObjectPin.createInstance("",3,ol));

      o2c =Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp09,o2c,ObjectPin.createInstance("",1,ol));
      ObjectPin2CasePin.createInstance(cp10,o2c,ObjectPin.createInstance("",2,ol));
      ObjectPin2CasePin.createInstance(cp08,o2c,ObjectPin.createInstance("",3,ol));

      o2c =Object2Case.createInstance(eobj,c);
      ObjectPin2CasePin.createInstance(cp12,o2c,ObjectPin.createInstance("",1,ol));
      ObjectPin2CasePin.createInstance(cp13,o2c,ObjectPin.createInstance("",2,ol));
      ObjectPin2CasePin.createInstance(cp11,o2c,ObjectPin.createInstance("",3,ol));
    }

    /**
     *    Spannungsversorgung für die IC erzeugen
     *
     *          +--------------+
     *          |              |
     *    Pin 1 |    X Volt    |  Pin 2
     *    ------+              +-----
     *          |VCC       GND |
     *          |              |
     *          |              |
     *          +--------------+
     *
     */
    private static void createBasic_Voltage(String objectName, String caseName)
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance( "VCC",1,cl,0,0);
        CasePin     cp02  = CasePin.createInstance( "GND",2,cl,0,0);

        // Gehäuse mit dem Layout erzeugen
        //
        ElectricCase   c    = ElectricCase.createInstance(caseName,"http://...",cl);

        // Objektlayout erzeugen
        //
        ObjectLayout ol = ObjectLayout.createInstance();
        ObjectPin op1 = ObjectPin.createInstance("VCC", 1,ol);
        ObjectPin op2 = ObjectPin.createInstance("GND", 2,ol);
        
        // Objekt mit dem Layout erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(true,objectName,ol);

        // Relation zwischen Objekt und Gehäuse setzten
        //
        Object2Case o2c = Object2Case.createInstance( eobj, c);
        
        // Objektpins mit den Gehäusepins verbinden
        ObjectPin2CasePin    op11 = ObjectPin2CasePin.createInstance(cp01,o2c,op1);
        ObjectPin2CasePin    op12 = ObjectPin2CasePin.createInstance(cp02,o2c,op2);
        
        // objekt für späteren Zugriff merken
        objects.put(objectName  , eobj);
        objects2cases.put(objectName, o2c);
    }

    /**
     *                      |    Collector
     *                      |    Pin 2
     *                      |
     *              --------+
     *            /        /  \
     *          /     |   /     \
     *         |      |  /       |
     *        |       | /         |
     *     ---+------+|X          |
     *  Basis |       | \         |
     *  Pin 1  |      |  \       |
     *          \     |   \ |   /
     *            \      ---|  /
     *              ----------/
     *                      |
     *                      |   Emitter
     *                      |   Pin 3
     */
    private static void createBasic_TransistorNPN(String objectName, String caseName)
    {
        // 1. Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance( "Basis",1,cl,0, 0);
        CasePin     cp02  = CasePin.createInstance( "Kathode",2,cl,0, 0);
        CasePin     cp03  = CasePin.createInstance( "Emitter",3,cl,0, 0);

        // 2. Gehäuse mit dem Layout erzeugen
        //
        ElectricCase   c    = ElectricCase.createInstance(caseName,"http://www.farnell.com/datasheets/5462001.pdf",cl);

        // 3. Objektlayout erzeugen
        //
        ObjectLayout ol = ObjectLayout.createInstance();
        ObjectPin op1 = ObjectPin.createInstance("Basis",1,ol);
        ObjectPin op2 = ObjectPin.createInstance("Kathode",2,ol);
        ObjectPin op3 = ObjectPin.createInstance("Emitter",3,ol);
        
        // 4. Objekt mit dem Layout erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(false,objectName,ol);

        // 5. Verbindung von Gehäuse und Objekt erstellen
        //
        Object2Case o2c = Object2Case.createInstance(eobj,c);
        
        // 6. Objektpins mit den Gehäusepins verbinden
        //
        ObjectPin2CasePin    op11 = ObjectPin2CasePin.createInstance(cp01,o2c,op1);
        ObjectPin2CasePin    op12 = ObjectPin2CasePin.createInstance(cp02,o2c,op2);
        ObjectPin2CasePin    op13 = ObjectPin2CasePin.createInstance(cp03,o2c,op3);
    
        // objekt für späteren Zugriff merken
        objects.put(objectName  , eobj);
        objects2cases.put(objectName, o2c);
    }

    /**
     *     Kondensator X nF
     *
     *       ------||-----
     *  pin 1             pin 2
     */
    private static void createBasic_Kondensator(String objectName, String caseName)
    {
      // Gehäuselayout erzeugen
      //
      CaseLayout    cl  = CaseLayout.createInstance();
      CasePin     cp01  = CasePin.createInstance("",1,cl,0, 0);
      CasePin     cp02  = CasePin.createInstance("",2,cl,0, 0);

      // Gehäuse mit Layout erzeugen
      //
      ElectricCase   c = ElectricCase.createInstance(caseName,"http://...",cl);
      
      // Objectlayout erzeugen
      //
      ObjectLayout ol = ObjectLayout.createInstance();
      ObjectPin op1 = ObjectPin.createInstance("", 1,ol);
      ObjectPin op2 = ObjectPin.createInstance("", 2,ol);
      
      // Objekt mit Layout erzeugen
      //
      ElectricObject eobj = ElectricObject.createInstance(false,objectName,ol);
      
      // Relation zwischen Objekt und Gehäuse setzten
      //
      Object2Case o2c = Object2Case.createInstance( eobj, c);

      // Objektpins mit den Gehäusepins verbinden
      //
      ObjectPin2CasePin    op11 = ObjectPin2CasePin.createInstance(cp01,o2c,op1);
      ObjectPin2CasePin    op12 = ObjectPin2CasePin.createInstance(cp02,o2c,op2);
    
      // objekt für späteren Zugriff merken
      objects.put(objectName  , eobj);
      objects2cases.put(objectName, o2c);
    }


    /**   
     * High/Low Schalter
     * 
     *    Eingang 1 Pin #1
     *      o------------o\ 
     *                     \
     *                      +----------- Ausgang Pin #3
     * 
     *      o------------o
     *    Eingang 2 Pin #2
     *
     **/
    private static void createBasic_1UMSwitch()
    {
      String objectName = "1UM";
      String caseName   = "1 x Um-Schalter";      
      // Gehäuselayout erzeugen
      //
      CaseLayout    cl  = CaseLayout.createInstance();
      CasePin     cp01  = CasePin.createInstance( "Eingang 1",1,cl,0, 0);
      CasePin     cp02  = CasePin.createInstance( "Eingang 2",2,cl,0, 0);
      CasePin     cp03  = CasePin.createInstance( "Ausgang"  ,3,cl,0, 0);

      // Gehäuse mit Layout erzeugen
      //
      ElectricCase   c = ElectricCase.createInstance(caseName,"http://...",cl);
      
      // Objectlayout erzeugen
      //
      ObjectLayout ol = ObjectLayout.createInstance();
      ObjectPin op1 = ObjectPin.createInstance("Ausgang"  , 1, ol);
      ObjectPin op2 = ObjectPin.createInstance("Eingang 1)", 2, ol);
      ObjectPin op3 = ObjectPin.createInstance("Eingang 2)", 3, ol);
      
      // Objekt mit Layout erzeugen
      //
      ElectricObject eobj = ElectricObject.createInstance(false,objectName,ol);

      // Relation zwischen Objekt und Gehäuse setzten
      //
      Object2Case o2c = Object2Case.createInstance( eobj, c);

      // Objektpins mit den Gehäusepins verbinden
      //
      ObjectPin2CasePin    op11 = ObjectPin2CasePin.createInstance(cp01,o2c,op1);
      ObjectPin2CasePin    op12 = ObjectPin2CasePin.createInstance(cp02,o2c,op2);
      ObjectPin2CasePin    op13 = ObjectPin2CasePin.createInstance(cp03,o2c,op3);

      objects.put(objectName, eobj);
    }


    
    /**
     * Ein Macroobjekt erzeug kein neues Gehäuse. Es erstellt aus bestehenden
     * Objekten (Transistor, LED, Widerstand) ein logische Objekt z.B. eine LED-Anzeige
     * 
     * Dazu werden diese Objekte in Relation zueinander gestzt und dann Verkabelt.
     *
     */
   private static void createMacro_OBJ_SWITCH_AUS()
    {
        // Logisches Objekt erzeugen
        //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj = ElectricObject.createInstance(false,"OBJ_SWITCH_AUS_1_1",ol);

        // Relation zu benötigten Objekten erstellen
        //
        RelatedObject r330_1    = RelatedObject.createInstance(eobj, getObject("3300 OHM")      );
        RelatedObject r330_2    = RelatedObject.createInstance(eobj, getObject("3300 OHM")      );
        RelatedObject switchOff = RelatedObject.createInstance(eobj, schalter1XAusRel.getObject());
        RelatedObject volt5     = RelatedObject.createInstance(eobj, getObject("5VOLT")         );

        // Interne Verkabelung erzeugen
        //
        Connection.createInstance(r330_1, 1, volt5,  1);
        Connection.createInstance(r330_2, 1, volt5,  1);
        Connection.createInstance(r330_1, 2, switchOff,  1);
        Connection.createInstance(r330_2, 2, switchOff,  2);

        // create the pin mapping between the 'real' and the simulation object
        //
        MacroPinMapping.createInstance(1, switchOff, 1, eobj);
        MacroPinMapping.createInstance(2, switchOff, 2, eobj);
    }

      /**
       *
       */
      private static void createMacro_OBJ_D_R_T_3_2()
      {
         // Objekt mit Gehäuse erzeugen
         //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj   = ElectricObject.createInstance(false,"OBJ_D_R_T_3_2",ol);
        ElectricObject relObj = ElectricObject.findByType("OBJ_D_SR_T_4_2");

         // Abhängigkeiten erzeugen
         //
         RelatedObject d_sr  = RelatedObject.createInstance(eobj, relObj);
         RelatedObject volt5 = RelatedObject.createInstance(eobj, getObject("5VOLT"));

         Connection.createInstance(d_sr , 1, volt5, 1);

         MacroPinMapping.createInstance(2, d_sr, 1, eobj);
         MacroPinMapping.createInstance(3, d_sr, 2, eobj);
         MacroPinMapping.createInstance(4, d_sr, 3, eobj);
         MacroPinMapping.createInstance(5, d_sr, 4, eobj);
         MacroPinMapping.createInstance(6, d_sr, 5, eobj);
      }

      /**
       *
       */
      private static void createMacro_LED_BAR_red_1_0()
      {
         // Objekt mit Gehäuse erzeugen
         //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj   = ElectricObject.createInstance(false,"LED-Bar (red)_1_0",ol);
        ElectricObject relObj = ElectricObject.findByType("LED");

         // Abhängigkeiten erzeugen
         //
         RelatedObject bar1  = RelatedObject.createInstance(eobj, relObj);

         // create the pin mapping between the 'real' and the simulation object
         //
         MacroPinMapping.createInstance(1, bar1, 1, eobj);
      }

      /**
       *
       */
      private static void createMacro_LED_BAR_red_2_0()
      {
         // Objekt mit Gehäuse erzeugen
         //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj   = ElectricObject.createInstance(false,"LED-Bar (red)_2_0",ol);
        ElectricObject relObj = ElectricObject.findByType("LED");

         // Abhängigkeiten erzeugen
         //
         RelatedObject bar1  = RelatedObject.createInstance(eobj, relObj);
         RelatedObject bar2  = RelatedObject.createInstance(eobj, relObj);

         // create the pin mapping between the 'real' and the simulation object
         //
         MacroPinMapping.createInstance(1, bar1, 1, eobj);
         MacroPinMapping.createInstance(1, bar2, 2, eobj);
      }
      /**
       *
       */
      private static void createMacro_LED_BAR_red_3_0()
      {
         // Objekt mit Gehäuse erzeugen
         //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj   = ElectricObject.createInstance(false,"LED-Bar (red)_3_0",ol);
         ElectricObject relObj = ElectricObject.findByType("LED");

         // Abhängigkeiten erzeugen
         //
         RelatedObject bar1  = RelatedObject.createInstance(eobj, relObj);
         RelatedObject bar2  = RelatedObject.createInstance(eobj, relObj);
         RelatedObject bar3  = RelatedObject.createInstance(eobj, relObj);

         // create the pin mapping between the 'real' and the simulation object
         //
         MacroPinMapping.createInstance(1, bar1, 1, eobj);
         MacroPinMapping.createInstance(1, bar2, 2, eobj);
         MacroPinMapping.createInstance(1, bar3, 3, eobj);
      }
      /**
       *
       */
      private static void createMacro_LED_BAR_red_4_0()
      {
         // Objekt mit Gehäuse erzeugen
         //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj   = ElectricObject.createInstance(false,"LED-Bar (red)_4_0",ol);
        ElectricObject relObj = ElectricObject.findByType("LED");

         // Abhängigkeiten erzeugen
         //
         RelatedObject bar1  = RelatedObject.createInstance(eobj, relObj);
         RelatedObject bar2  = RelatedObject.createInstance(eobj, relObj);
         RelatedObject bar3  = RelatedObject.createInstance(eobj, relObj);
         RelatedObject bar4  = RelatedObject.createInstance(eobj, relObj);

         // create the pin mapping between the 'real' and the simulation object
         //
         MacroPinMapping.createInstance(1, bar1, 1, eobj);
         MacroPinMapping.createInstance(1, bar2, 2, eobj);
         MacroPinMapping.createInstance(1, bar3, 3, eobj);
         MacroPinMapping.createInstance(1, bar4, 4, eobj);
      }
      /**
       *
       */
      private static void createMacro_LED_BAR_red_5_0()
      {
         // Objekt mit Gehäuse erzeugen
         //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj   = ElectricObject.createInstance(false,"LED-Bar (red)_5_0",ol);
        ElectricObject relObj = ElectricObject.findByType("LED");

         // Abhängigkeiten erzeugen
         //
         RelatedObject bar1  = RelatedObject.createInstance(eobj, relObj);
         RelatedObject bar2  = RelatedObject.createInstance(eobj, relObj);
         RelatedObject bar3  = RelatedObject.createInstance(eobj, relObj);
         RelatedObject bar4  = RelatedObject.createInstance(eobj, relObj);
         RelatedObject bar5  = RelatedObject.createInstance(eobj, relObj);

         // create the pin mapping between the 'real' and the simulation object
         //
         MacroPinMapping.createInstance(1, bar1, 1, eobj);
         MacroPinMapping.createInstance(1, bar2, 2, eobj);
         MacroPinMapping.createInstance(1, bar3, 3, eobj);
         MacroPinMapping.createInstance(1, bar4, 4, eobj);
         MacroPinMapping.createInstance(1, bar5, 5, eobj);
      }
      /**
       *
       */
      /**
       *
       */
      private static void createMacro_LED_BAR_red_6_0()
      {
         // Objekt mit Gehäuse erzeugen
         //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj   = ElectricObject.createInstance(false,"LED-Bar (red)_6_0",ol);
        ElectricObject relObj = ElectricObject.findByType("LED");

         // Abhängigkeiten erzeugen
         //
         RelatedObject bar1  = RelatedObject.createInstance(eobj, relObj);
         RelatedObject bar2  = RelatedObject.createInstance(eobj, relObj);
         RelatedObject bar3  = RelatedObject.createInstance(eobj, relObj);
         RelatedObject bar4  = RelatedObject.createInstance(eobj, relObj);
         RelatedObject bar5  = RelatedObject.createInstance(eobj, relObj);
         RelatedObject bar6  = RelatedObject.createInstance(eobj, relObj );

         // create the pin mapping between the 'real' and the simulation object
         //
         MacroPinMapping.createInstance(1, bar1, 1, eobj);
         MacroPinMapping.createInstance(1, bar2, 2, eobj);
         MacroPinMapping.createInstance(1, bar3, 3, eobj);
         MacroPinMapping.createInstance(1, bar4, 4, eobj);
         MacroPinMapping.createInstance(1, bar5, 5, eobj);
         MacroPinMapping.createInstance(1, bar6, 6, eobj);
      }
     /**
       *
       */
       /**
       *
       */
      private static void createMacro_LED_BAR_red_7_0()
      {
         // Objekt mit Gehäuse erzeugen
         //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj   = ElectricObject.createInstance(false,"LED-Bar (red)_7_0",ol);
         ElectricObject relObj = ElectricObject.findByType("LED");

         // Abhängigkeiten erzeugen
         //
         RelatedObject bar1  = RelatedObject.createInstance(eobj, relObj  );
         RelatedObject bar2  = RelatedObject.createInstance(eobj, relObj  );
         RelatedObject bar3  = RelatedObject.createInstance(eobj, relObj  );
         RelatedObject bar4  = RelatedObject.createInstance(eobj, relObj  );
         RelatedObject bar5  = RelatedObject.createInstance(eobj, relObj  );
         RelatedObject bar6  = RelatedObject.createInstance(eobj, relObj  );
         RelatedObject bar7  = RelatedObject.createInstance(eobj, relObj  );

         // create the pin mapping between the 'real' and the simulation object
         //
         MacroPinMapping.createInstance(1, bar1, 1, eobj);
         MacroPinMapping.createInstance(1, bar2, 2, eobj);
         MacroPinMapping.createInstance(1, bar3, 3, eobj);
         MacroPinMapping.createInstance(1, bar4, 4, eobj);
         MacroPinMapping.createInstance(1, bar5, 5, eobj);
         MacroPinMapping.createInstance(1, bar6, 6, eobj);
         MacroPinMapping.createInstance(1, bar7, 7, eobj);
      }
      /**
       *
       */
      /**
       *
       */
      private static void createMacro_LED_BAR_red_8_0()
      {
         // Objekt mit Gehäuse erzeugen
         //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj   = ElectricObject.createInstance(false,"LED-Bar (red)_8_0",ol);
        ElectricObject relObj = ElectricObject.findByType("LED");

         // Abhängigkeiten erzeugen
         //
         RelatedObject bar1  = RelatedObject.createInstance(eobj, relObj );
         RelatedObject bar2  = RelatedObject.createInstance(eobj, relObj );
         RelatedObject bar3  = RelatedObject.createInstance(eobj, relObj );
         RelatedObject bar4  = RelatedObject.createInstance(eobj, relObj );
         RelatedObject bar5  = RelatedObject.createInstance(eobj, relObj );
         RelatedObject bar6  = RelatedObject.createInstance(eobj, relObj );
         RelatedObject bar7  = RelatedObject.createInstance(eobj, relObj );
         RelatedObject bar8  = RelatedObject.createInstance(eobj, relObj );

         // create the pin mapping between the 'real' and the simulation object
         //
         MacroPinMapping.createInstance(1, bar1, 1, eobj);
         MacroPinMapping.createInstance(1, bar2, 2, eobj);
         MacroPinMapping.createInstance(1, bar3, 3, eobj);
         MacroPinMapping.createInstance(1, bar4, 4, eobj);
         MacroPinMapping.createInstance(1, bar5, 5, eobj);
         MacroPinMapping.createInstance(1, bar6, 6, eobj);
         MacroPinMapping.createInstance(1, bar7, 7, eobj);
         MacroPinMapping.createInstance(1, bar8, 8, eobj);
      }

      /**
       * GND  |
       *      +---- PIN 1
       *      |
       */
      private static void createMacro_GND_0_1()
      {
         // Objekt mit Gehäuse erzeugen
         //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj   = ElectricObject.createInstance(false,"GND_0_1",ol);

         // Abhängigkeiten erzeugen
         //
         RelatedObject volt5 = RelatedObject.createInstance(eobj, getObject("5VOLT"));

         // create the pin mapping between the 'real' and the simulation object
         //
         MacroPinMapping.createInstance(2, volt5, 1, eobj);
      }

    /**
     * Entprellter Schalter. Dies ist notwendig, da normale Taster/Schalter prellen.
     * Dies würde bei einem Zähler z.B. somit nicht 1 sondern eventuell 100 Impulse auslösen
     *
     *                   +5Volt
     *  
     *                   |#7 
     *                 +-++
     *                 |  |
     *                 |  |
     *                 |R1| 4,7k Ohm
     *                 |  |
     *                 +--+
     *                   |             |---
     *             +-----*-------------|    \
     *             |#2      #6         |     |
     *             |                   |NAND1|O---*---OUT
     *             /               ----|     |    |
     *       #1   / 1xUM           |   |    /     |
     *      +----/                 |   ----       |
     *      |      |     +5Volt    |              |#8
     *      |      |#3   |#4       -------------- |
     *    --+--    |     |                      | |
     *   GND       |   +-++                     | |
     *             |   |  |          -----------|--
     *             |   |  |4,7k Ohm  | ----     |
     *             |   |R2|          | |    \   |
     *             |   |  |          --|     |  |#9                    pin1
     *             |   +--+            |NAND2|O-|                      ---*
     *             |     |#5           |     |                             \--- pin3
     *             +-----*-------------|    /                          ---*
     *                                 |---                            pin2
     *                 
     **/
    private static void createMacro_OBJ_POWER_0_1()
    {
        // Objekt mit Gehäuse erzeugen
        //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj = ElectricObject.createInstance(false,"OBJ_POWER_0_1",ol);

        // Abhängigkeiten erzeugen
        //
        RelatedObject volt5  = RelatedObject.createInstance(eobj, getObject("5VOLT"));
        RelatedObject um1    = RelatedObject.createInstance(eobj, getObject("1UM"));
        RelatedObject r1     = RelatedObject.createInstance(eobj, getObject("4700 OHM"));
        RelatedObject r2     = RelatedObject.createInstance(eobj, getObject("4700 OHM"));
        RelatedObject nand1  = RelatedObject.createInstance(eobj, getObject("OBJ_NAND_2_1"));
        RelatedObject nand2  = RelatedObject.createInstance(eobj, getObject("OBJ_NAND_2_1"));

        // Verbindungen der einzelnen Objekte erstellen
        //
        
        Connection.createInstance(um1  , 3, volt5, 2);   // Verbindung #1
        Connection.createInstance(um1  , 1, r1,    2);   // Verbindung #2
        Connection.createInstance(um1  , 2, r2,    2);   // Verbindung #3
        Connection.createInstance(r2   , 1, volt5, 1);   // Verbindung #4
        Connection.createInstance(r2   , 2, nand2, 2);   // Verbindung #5
        Connection.createInstance(r1   , 2, nand1, 1);   // Verbindung #6
        Connection.createInstance(r1   , 1, volt5, 1);   // Verbindung #7
        Connection.createInstance(nand1, 3, nand2, 1);   // Verbindung #8
        Connection.createInstance(nand2, 3, nand1, 2);   // Verbindung #9

        // create the pin mapping between the 'real' and the simulation object
        //
        MacroPinMapping.createInstance(3, nand1, 1, eobj);
    }

      /**
       *
       */
      private static void createMacro_High_0_1()
      {
         // Objekt mit Gehäuse erzeugen
         //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj   = ElectricObject.createInstance(false,"High_0_1",ol);

         // Abhängigkeiten erzeugen
         //
         RelatedObject volt5 = RelatedObject.createInstance(eobj, getObject("5VOLT"));

         // create the pin mapping between the 'real' and the simulation object
         //
         MacroPinMapping.createInstance(1, volt5, 1, eobj);
      }

      /**
       *
       */
      private static void createMacro_OBJ_D_T_2_2()
      {
         // Objekt mit Gehäuse erzeugen
         //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj   = ElectricObject.createInstance(false,"OBJ_D_T_2_2",ol);
        ElectricObject relObj = ElectricObject.findByType("OBJ_D_SR_T_4_2");

         // Abhängigkeiten erzeugen
         //
         RelatedObject d_sr  = RelatedObject.createInstance(eobj, relObj            );
         RelatedObject volt5 = RelatedObject.createInstance(eobj, getObject("5VOLT"));

         Connection.createInstance(d_sr , 1, volt5, 1);
         Connection.createInstance(d_sr , 4, volt5, 1);

         // create the pin mapping between the 'real' and the simulation object
         //
         MacroPinMapping.createInstance(2, d_sr, 1, eobj);
         MacroPinMapping.createInstance(3, d_sr, 2, eobj);
         MacroPinMapping.createInstance(5, d_sr, 3, eobj);
         MacroPinMapping.createInstance(6, d_sr, 4, eobj);
      }

    /**
     *
     */
    private static void createMacro_OBJ_T_1_2()
    {
        // Objekt mit Gehäuse erzeugen
        //
      ObjectLayout ol = ObjectLayout.createInstance();
      ElectricObject eobj = ElectricObject.createInstance(false,"OBJ_T_1_2",ol);
       ElectricObject jkObj = ElectricObject.findByType("OBJ_D_J!K_SR_T_5_2");

        // Abhängigkeiten erzeugen
        //
        RelatedObject jk    = RelatedObject.createInstance(eobj, jkObj);
        RelatedObject volt5 = RelatedObject.createInstance(eobj, getObject("5VOLT"));

        Connection.createInstance(volt5 , 1, jk, 1); // J auf High legen
        Connection.createInstance(volt5 , 2, jk, 4); // !K auf Low legen
        Connection.createInstance(volt5 , 1, jk, 1); // !Set auf High legen
        Connection.createInstance(volt5 , 1, jk, 5); // !Reset auf High legen

        // create the pin mapping between the 'real' and the simulation object
        //
        MacroPinMapping.createInstance(3, jk  , 1, eobj); // C
        MacroPinMapping.createInstance(6, jk  , 4, eobj); // Q
        MacroPinMapping.createInstance(7, jk  , 5, eobj); // !Q
    }

    /**
     *
     */
    private static void createMarcro_OBJ_TAKT_0_1()
    {
        // Objekt mit Gehäuse erzeugen
        //
      	ObjectLayout ol = ObjectLayout.createInstance();
      	ElectricObject eobj = ElectricObject.createInstance(false,"OBJ_TAKT_0_1",ol);

        // Abhängigkeiten erzeugen
        //
        RelatedObject r1 = RelatedObject.createInstance(eobj, getObject("1000 OHM"));
        RelatedObject r2 = RelatedObject.createInstance(eobj, getObject("P1000000 OHM"));
        RelatedObject r3 = RelatedObject.createInstance(eobj, getObject("1000 OHM"));
        RelatedObject r4 = RelatedObject.createInstance(eobj, getObject("P1000000 OHM"));
        RelatedObject r5 = RelatedObject.createInstance(eobj, getObject("4700 OHM"));

        RelatedObject d1 = RelatedObject.createInstance(eobj, getObject("1N914"));
        RelatedObject d2 = RelatedObject.createInstance(eobj, getObject("1N914"));

        RelatedObject c1 = RelatedObject.createInstance(eobj, getObject("c10nF"));
        RelatedObject c2 = RelatedObject.createInstance(eobj, getObject("c10nF"));

        RelatedObject ne = RelatedObject.createInstance(eobj, ne555Rel.getObject());

        RelatedObject volt5 = RelatedObject.createInstance(eobj, getObject("5VOLT"));

        Connection.createInstance(ne,   8, volt5, 1);
        Connection.createInstance(ne,   4, volt5, 1);
        Connection.createInstance(ne,   1, volt5, 2);
        Connection.createInstance(ne,   5, c2   , 1);
        Connection.createInstance(ne,   2, ne   , 6);
        Connection.createInstance(c1,   1, ne   , 2);
        Connection.createInstance(c1,   2, c2   , 2);
        Connection.createInstance(c2,   2, volt5, 2);
        Connection.createInstance(d1,   2, ne   , 6);
        Connection.createInstance(d1,   1, ne   , 7);
        Connection.createInstance(d2,   2, ne   , 7);
        Connection.createInstance(r1,   1, ne   , 4);
        Connection.createInstance(r2,   2, ne   , 7);
        Connection.createInstance(r2,   3, ne   , 7);
        Connection.createInstance(r2,   1, r1   , 2);
        Connection.createInstance(r3,   2, d2   , 1);
        Connection.createInstance(r4,   3, d1   , 2);
        Connection.createInstance(r4,   3, r4   , 2);
        Connection.createInstance(r4,   2, r4   , 3);
        Connection.createInstance(r4,   1, r3   , 1);
        Connection.createInstance(r5 ,  2, ne,    3);
        Connection.createInstance(r5,   1, volt5, 1);
        
        // create the pin mapping between the 'real' and the simulation object
        //
        MacroPinMapping.createInstance(3, ne, 1, eobj);  // takt
    }

    /**
     *
     */
    private static void createMacro_OBJ_JK_T_3_2()
    {
      // Objekt mit Gehäuse erzeugen
      //
      ObjectLayout ol = ObjectLayout.createInstance();
      ElectricObject eobj   = ElectricObject.createInstance(false,"OBJ_JK_T_3_2",ol);
      
      ElectricObject jkObj  = ElectricObject.findByType("OBJ_D_J!K_SR_T_5_2");
      ElectricObject notObj = ElectricObject.findByType("OBJ_NOT_1_1");

        // Abhängigkeiten erzeugen
        //
        RelatedObject jk    = RelatedObject.createInstance(eobj, jkObj);
        RelatedObject not   = RelatedObject.createInstance(eobj, notObj);
        RelatedObject volt5 = RelatedObject.createInstance(eobj, getObject("5VOLT"));

        Connection.createInstance(jk , 4, not, 2);
        Connection.createInstance(volt5 , 1, jk, 1); // !Set auf High legen
        Connection.createInstance(volt5 , 1, jk, 5); // !Reset auf High legen

        // create the pin mapping between the 'real' and the simulation object
        //
        MacroPinMapping.createInstance(2, jk  , 1, eobj); // J
        MacroPinMapping.createInstance(3, jk  , 2, eobj); // C
        MacroPinMapping.createInstance(1, not , 3, eobj); // K
        MacroPinMapping.createInstance(6, jk  , 4, eobj); // Q
        MacroPinMapping.createInstance(7, jk  , 5, eobj); // !Q
    }

    /**
     *
     */
    private static void createMacro_OBJ_JK_R_T_4_2()
    {
      // Objekt mit Gehäuse erzeugen
      //
      ObjectLayout ol = ObjectLayout.createInstance();
      ElectricObject eobj   = ElectricObject.createInstance(false,"OBJ_JK_R_T_4_2",ol);
      ElectricObject jkObj  = ElectricObject.findByType("OBJ_D_J!K_SR_T_5_2");
      ElectricObject notObj = ElectricObject.findByType("OBJ_NOT_1_1");

      // Abhängigkeiten erzeugen
      //
      RelatedObject jk    = RelatedObject.createInstance(eobj, jkObj);
      RelatedObject not   = RelatedObject.createInstance(eobj, notObj);
      RelatedObject volt5 = RelatedObject.createInstance(eobj, getObject("5VOLT"));

      Connection.createInstance(jk , 4, not, 2);
      Connection.createInstance(volt5 , 1, jk, 1); // !Set auf High legen

      // create the pin mapping between the 'real' and the simulation object
      //
      MacroPinMapping.createInstance(2, jk  , 1, eobj); // J
      MacroPinMapping.createInstance(3, jk  , 2, eobj); // C
      MacroPinMapping.createInstance(1, not , 3, eobj); // K
      MacroPinMapping.createInstance(5, jk  , 4, eobj); // !R
      MacroPinMapping.createInstance(6, jk  , 5, eobj); // Q
      MacroPinMapping.createInstance(7, jk  , 6, eobj); // !Q
    }

    /**
     *
     */
    private static void createMacro_OBJ_JK_SR_T_5_2()
    {
      // Objekt mit Gehäuse erzeugen
      //
      ObjectLayout ol = ObjectLayout.createInstance();
      ElectricObject eobj   = ElectricObject.createInstance(false,"OBJ_JK_SR_T_5_2",ol);
      ElectricObject jkObj  = ElectricObject.findByType("OBJ_D_J!K_SR_T_5_2");
      ElectricObject notObj = ElectricObject.findByType("OBJ_NOT_1_1");

      // Abhängigkeiten erzeugen
      //
      RelatedObject jk    = RelatedObject.createInstance(eobj, jkObj);
      RelatedObject not   = RelatedObject.createInstance(eobj, notObj);

      Connection.createInstance(jk , 4, not, 2);

      // create the pin mapping between the 'real' and the simulation object
      //
      MacroPinMapping.createInstance(1, jk  , 1, eobj);  // !Set
      MacroPinMapping.createInstance(2, jk  , 2, eobj);  // J
      MacroPinMapping.createInstance(3, jk  , 3, eobj);  // C
      MacroPinMapping.createInstance(1, not , 4, eobj);  // K
      MacroPinMapping.createInstance(5, jk  , 5, eobj);  // !Reset
      MacroPinMapping.createInstance(6, jk  , 6, eobj);  // Q
      MacroPinMapping.createInstance(7, jk  , 7, eobj);  // !Q
    }
    
    /**
     *
     */
    private static void createMacro_OBJ_LED()
    {
      // create the LED if the source of the input has an fan out >2
      {
        // Objekt mit Layout erzeugen
        //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj = ElectricObject.createInstance(false,"OBJ_LED_1_0",ol);
  
        // Abhängigkeiten erzeugen
        //
        RelatedObject r330  = RelatedObject.createInstance(eobj, getObject("3300 OHM"));
        RelatedObject r470  = RelatedObject.createInstance(eobj, getObject("470 OHM") );
        RelatedObject t107  = RelatedObject.createInstance(eobj, getObject("BC107")   );
        RelatedObject led   = RelatedObject.createInstance(eobj, getObject("LED")     );
        RelatedObject volt5 = RelatedObject.createInstance(eobj, getObject("5VOLT")   );
  
        Connection.createInstance(led , 2, volt5, 2);
        Connection.createInstance(r470, 1, volt5, 1);
        Connection.createInstance(r470, 2, t107,  2);
        Connection.createInstance(t107, 3, led,   1);
        Connection.createInstance(r330, 2, t107,  1);
  
        // create the pin mapping between the 'real' and the simulation object
        //
        MacroPinMapping.createInstance(1, r330, 1, eobj);
      }
      // if the source has only an fanout of 1, than we can use a simple variant of
      // the LED. The LED consumes only 20mA max. - this is ok for TTL ic.
      //
      {
        // Objekt mit Layout erzeugen
        //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj = ElectricObject.createInstance(false,"OBJ_LED_fanout(1)_1_0",ol);
  
        // Abhängigkeiten erzeugen
        //
        RelatedObject r820  = RelatedObject.createInstance(eobj, getObject("820 OHM") );
        RelatedObject led   = RelatedObject.createInstance(eobj, getObject("LED")     );
        RelatedObject volt5 = RelatedObject.createInstance(eobj, getObject("5VOLT")   );
  
        Connection.createInstance(led , 2, volt5, 2);
        Connection.createInstance(led , 1, r820,  2);
  
        // create the pin mapping between the 'real' and the simulation object
        //
        MacroPinMapping.createInstance(1, r820, 1, eobj);
      }
    }

    /**
     *
     */
    private static void createMacro_OBJ_BCDCOUNTER_2_4()
    {
      // Objekt mit Layout erzeugen
      //
      ObjectLayout ol = ObjectLayout.createInstance();
      ElectricObject eobj = ElectricObject.createInstance(false,"OBJ_BCDCOUNTER_2_4",ol);

      // Abhängigkeiten erzeugen
      //
      RelatedObject _7490 = RelatedObject.createInstance(eobj, getObject("OBJECT.BCDCOUNTER.7490"));
      RelatedObject volt5 = RelatedObject.createInstance(eobj, getObject("5VOLT"));

      // Notwendige Verbindungen erzeugen
      //
      Connection.createInstance(_7490, 7, _7490,  6);  // Q0 auf B legen
      Connection.createInstance(volt5, 2, _7490,  1);  // LOW auf R01 legen
      Connection.createInstance(volt5, 2, _7490,  3);  // LOW auf S91 legen
      Connection.createInstance(volt5, 2, _7490,  4);  // LOW auf S92 legen

      // create the pin mapping between the 'real' and the simulation object
      //
      MacroPinMapping.createInstance(5,  _7490, 1, eobj);  // 1 = Takt
      MacroPinMapping.createInstance(2,  _7490, 2, eobj);  // 2 = Reset
      MacroPinMapping.createInstance(7,  _7490, 3, eobj);  // 3 = Q0
      MacroPinMapping.createInstance(8,  _7490, 4, eobj);  // 4 = Q1
      MacroPinMapping.createInstance(9,  _7490, 5, eobj);  // 5 = Q2
      MacroPinMapping.createInstance(10, _7490, 6, eobj);  // 6 = Q3
    }

    /**
     * Schalter 1 x Aus
     *
     *
     *               \
     *                \
     *   --------o     O---------
     *
     *       pin 1     pin 2
     *
     */
    private static void createSchalter1XAus()
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance("Input",1,cl,0, 0);
        CasePin     cp02  = CasePin.createInstance("Output",2,cl,0, 0);

        // Objekt mit Gehäuse erzeugen
        //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj = ElectricObject.createInstance(false,"SWITCH1XOFF",ol);
        ElectricCase   c    = ElectricCase.createInstance("Schalter 1 x Aus","http://...",cl);
        schalter1XAusRel = Object2Case.createInstance( eobj, c);

        // Objektlayout im Gehäuse erzeugen
        //
        ObjectPin2CasePin    op11 = ObjectPin2CasePin.createInstance(cp01,schalter1XAusRel,ObjectPin.createInstance("Input", 1,ol));
        ObjectPin2CasePin    op12 = ObjectPin2CasePin.createInstance(cp02,schalter1XAusRel,ObjectPin.createInstance("Output", 2,ol));
    }

    /**
     * Resistor
     *            XYZ Ohm
     *           ______
     *  --------|______|-----
     *  pin 1             pin 2
     */
    private static void createBasic_Resistor(String objectName, String caseName)
    {
      // Gehäuselayout erzeugen
      //
      CaseLayout    cl  = CaseLayout.createInstance();
      CasePin     cp01  = CasePin.createInstance( "",1,cl,0, 0);
      CasePin     cp02  = CasePin.createInstance( "",2,cl,0, 0);
      
      // Gehäuse erzeugen
      ElectricCase   c    = ElectricCase.createInstance(caseName,"http://...",cl);
      
      
      // Objektlayout erzeugen
      //
      ObjectLayout ol = ObjectLayout.createInstance();
      ObjectPin op1 = ObjectPin.createInstance("", 1,ol);
      ObjectPin op2 = ObjectPin.createInstance("", 2,ol);
      
      // Objekt erzeugen
      ElectricObject eobj = ElectricObject.createInstance(false,objectName,ol);
      
      // Objekt in das Gehäuse einbetten
      Object2Case resistor = Object2Case.createInstance( eobj, c);
      
      // Objektpins mit den Gehäusepins verbinden
      //
      ObjectPin2CasePin    op11 = ObjectPin2CasePin.createInstance(cp01,resistor,op1);
      ObjectPin2CasePin    op12 = ObjectPin2CasePin.createInstance(cp02,resistor,op2);
      
      // erzeugten Widerstand (wortspiel :-)) für späteren Zugriff merken
      objects.put(objectName,eobj);
    }
   


   /**
     *    Diode 1N914
     *
     * (Anode)  |\     (Kathode)
     *    ______| \|______
     *          | /|
     *  pin 1   |/          pin 2
     */
    private static void createBasic_Diode(String objectName, String caseName)
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance( "Anode",1,cl,0, 0);
        CasePin     cp02  = CasePin.createInstance( "Kathode",2,cl,0, 0);

        // Gehäuse erzeugen
        //
        ElectricCase   c    = ElectricCase.createInstance(caseName,"http://...",cl);

        // Objektlayout erzeugen
        //
        ObjectLayout ol = ObjectLayout.createInstance();
        
        // Objekt erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(false,objectName,ol);
        
        // Relation zwischen Gehäuse und Objekt herstellen
        //
        Object2Case o2c = Object2Case.createInstance( eobj, c);

        // Objektpins mit den Gehäusepins verbinden
        //
        ObjectPin2CasePin    op11 = ObjectPin2CasePin.createInstance(cp01,o2c,ObjectPin.createInstance("Anode"  , 1,ol));
        ObjectPin2CasePin    op12 = ObjectPin2CasePin.createInstance(cp02,o2c,ObjectPin.createInstance("Kathode", 2,ol));
        
        // Objekt für spätere zugriffe merken
        //
        objects.put(objectName,eobj);
    }

   /**
     *      Trimmer with n Ohm
     * 
     *                pin 2   
     *           ___/__
     *  --------|__/___|-----
     *  pin 1             pin 3
     */
    private static void createBasic_Trimmer(String objectName, String caseName)
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance( "Eingang" ,1,cl,0, 0);
        CasePin     cp02  = CasePin.createInstance( "Abnehmer",2,cl,0, 0);
        CasePin     cp03  = CasePin.createInstance( "Eingang" ,3,cl,0, 0);

        // Objekt mit Gehäuse erzeugen
        //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj = ElectricObject.createInstance(false,objectName,ol);
        ElectricCase   c    = ElectricCase.createInstance(caseName,"http://...",cl);
        Object2Case trimmer = Object2Case.createInstance( eobj, c);

        // Objektlayout im Gehäuse erzeugen
        //
        ObjectPin2CasePin    op11 = ObjectPin2CasePin.createInstance(cp01,trimmer,ObjectPin.createInstance("Eingang", 1,ol));
        ObjectPin2CasePin    op12 = ObjectPin2CasePin.createInstance(cp02,trimmer,ObjectPin.createInstance("Abnehmer", 2,ol));
        ObjectPin2CasePin    op13 = ObjectPin2CasePin.createInstance(cp03,trimmer,ObjectPin.createInstance("Eingang", 3,ol));
        
        objects.put(objectName, eobj);
    }

    /**
     *    Steckerleiste
     *
     */
    private static void createO_INTERFACE_8_0()
    {
         // Gehäuselayout erzeugen
         //
         CaseLayout    cl  = CaseLayout.createInstance();
         CasePin     cp01  = CasePin.createInstance( "Pin 1" ,1,cl,0, 0);
         CasePin     cp02  = CasePin.createInstance( "Pin 2" ,2,cl,0, 0);
         CasePin     cp03  = CasePin.createInstance( "Pin 3" ,3,cl,0, 0);
         CasePin     cp04  = CasePin.createInstance( "Pin 4" ,4,cl,0, 0);
         CasePin     cp05  = CasePin.createInstance( "Pin 5" ,5,cl,0, 0);
         CasePin     cp06  = CasePin.createInstance( "Pin 6" ,6,cl,0, 0);
         CasePin     cp07  = CasePin.createInstance( "Pin 7" ,7,cl,0, 0);
         CasePin     cp08  = CasePin.createInstance( "Pin 8" ,8,cl,0, 0);

         // Objekt mit Gehäuse erzeugen
         //
         ObjectLayout ol = ObjectLayout.createInstance();
         ElectricObject eobj = ElectricObject.createInstance(false,"O_INTERFACE_8_0",ol);
         ElectricCase   c    = ElectricCase.createInstance("Steckleiste mit 8 Leitungen (Ausgang)","http://...",cl);
         Object2Case o2c = Object2Case.createInstance( eobj, c);

         // Objektlayout im Gehäuse erzeugen
         //
         ObjectPin2CasePin.createInstance(cp01,o2c,ObjectPin.createInstance("Pin 1", 1,ol));
         ObjectPin2CasePin.createInstance(cp02,o2c,ObjectPin.createInstance("Pin 2", 2,ol));
         ObjectPin2CasePin.createInstance(cp03,o2c,ObjectPin.createInstance("Pin 3", 3,ol));
         ObjectPin2CasePin.createInstance(cp04,o2c,ObjectPin.createInstance("Pin 4", 4,ol));
         ObjectPin2CasePin.createInstance(cp05,o2c,ObjectPin.createInstance("Pin 5", 5,ol));
         ObjectPin2CasePin.createInstance(cp06,o2c,ObjectPin.createInstance("Pin 6", 6,ol));
         ObjectPin2CasePin.createInstance(cp07,o2c,ObjectPin.createInstance("Pin 7", 7,ol));
         ObjectPin2CasePin.createInstance(cp08,o2c,ObjectPin.createInstance("Pin 8", 8,ol));
    }

   /**
     *    Steckerleiste
     *
     */
    private static void createI_INTERFACE_0_8()
    {
         // Gehäuselayout erzeugen
         //
         CaseLayout    cl  = CaseLayout.createInstance();
         CasePin     cp01  = CasePin.createInstance( "Pin 1" ,1,cl,0, 0);
         CasePin     cp02  = CasePin.createInstance( "Pin 2" ,2,cl,0, 0);
         CasePin     cp03  = CasePin.createInstance( "Pin 3" ,3,cl,0, 0);
         CasePin     cp04  = CasePin.createInstance( "Pin 4" ,4,cl,0, 0);
         CasePin     cp05  = CasePin.createInstance( "Pin 5" ,5,cl,0, 0);
         CasePin     cp06  = CasePin.createInstance( "Pin 6" ,6,cl,0, 0);
         CasePin     cp07  = CasePin.createInstance( "Pin 7" ,7,cl,0, 0);
         CasePin     cp08  = CasePin.createInstance( "Pin 8" ,8,cl,0, 0);

         // Objekt mit Gehäuse erzeugen
         //
         ObjectLayout ol = ObjectLayout.createInstance();
         ElectricObject eobj = ElectricObject.createInstance(false,"I_INTERFACE_0_8",ol);
         ElectricCase   c    = ElectricCase.createInstance("Steckleiste mit 8 Leitungen (Eingang)","http://...",cl);
         Object2Case o2c = Object2Case.createInstance( eobj, c);

         // Objektlayout im Gehäuse erzeugen
         //
         ObjectPin2CasePin.createInstance(cp01,o2c,ObjectPin.createInstance("Pin 1", 1,ol));
         ObjectPin2CasePin.createInstance(cp02,o2c,ObjectPin.createInstance("Pin 2", 2,ol));
         ObjectPin2CasePin.createInstance(cp03,o2c,ObjectPin.createInstance("Pin 3", 3,ol));
         ObjectPin2CasePin.createInstance(cp04,o2c,ObjectPin.createInstance("Pin 4", 4,ol));
         ObjectPin2CasePin.createInstance(cp05,o2c,ObjectPin.createInstance("Pin 5", 5,ol));
         ObjectPin2CasePin.createInstance(cp06,o2c,ObjectPin.createInstance("Pin 6", 6,ol));
         ObjectPin2CasePin.createInstance(cp07,o2c,ObjectPin.createInstance("Pin 7", 7,ol));
         ObjectPin2CasePin.createInstance(cp08,o2c,ObjectPin.createInstance("Pin 8", 8,ol));
    }

    /**
     *           NE 555
     *        +---+--+---+
     *    GND |1  +--+  8| VCC
     * Trigger|2        7| Entladung
     *    Out |3 NE555  6| Schwelle
     *  Reset |4        5| Steuerspannung
     *        +----------+
     **/
    private static void createBasic_NE555()
    {
        // generate the Caselayout
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance( "GND",1,cl,0, 0);
        CasePin     cp02  = CasePin.createInstance( "Trigger",2,cl,0, 0);
        CasePin     cp03  = CasePin.createInstance( "Out",3,cl,0, 0);
        CasePin     cp04  = CasePin.createInstance( "Reset",4,cl,0, 0);
        CasePin     cp05  = CasePin.createInstance( "Steuerspannung",5,cl,0, 0);
        CasePin     cp06  = CasePin.createInstance( "Schwelle",6,cl,0, 0);
        CasePin     cp07  = CasePin.createInstance( "Entladung",7,cl,0, 0);
        CasePin     cp08  = CasePin.createInstance( "VCC",8,cl,0, 0);

        // generate the object and the case
        //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj = ElectricObject.createInstance(false,"NE555",ol); //
        ElectricCase   c     = ElectricCase.createInstance("Timmerbaustein NE555","http://www.e-online.de/public/schaerer/timer555.htm",cl);
        ne555Rel = Object2Case.createInstance( eobj, c);

        // generate the internal object layout
        //
        ObjectPin2CasePin      op11 = ObjectPin2CasePin.createInstance(cp01,ne555Rel, ObjectPin.createInstance("GND"           ,1,ol));
        ObjectPin2CasePin      op12 = ObjectPin2CasePin.createInstance(cp02,ne555Rel, ObjectPin.createInstance("Trigger"       ,2,ol));
        ObjectPin2CasePin      op13 = ObjectPin2CasePin.createInstance(cp03,ne555Rel, ObjectPin.createInstance("Out"           ,3,ol));
        ObjectPin2CasePin      op14 = ObjectPin2CasePin.createInstance(cp04,ne555Rel, ObjectPin.createInstance("Reset"         ,4,ol));
        ObjectPin2CasePin      op15 = ObjectPin2CasePin.createInstance(cp05,ne555Rel, ObjectPin.createInstance("Steuerspannung",5,ol));
        ObjectPin2CasePin      op16 = ObjectPin2CasePin.createInstance(cp06,ne555Rel, ObjectPin.createInstance("Schwelle"      ,6,ol));
        ObjectPin2CasePin      op17 = ObjectPin2CasePin.createInstance(cp07,ne555Rel, ObjectPin.createInstance("Entladung"     ,7,ol));
        ObjectPin2CasePin      op18 = ObjectPin2CasePin.createInstance(cp08,ne555Rel, ObjectPin.createInstance("VCC"           ,8,ol));
    }


   
    /**   
     * High/Low Taster
     * 
     *    Eingang 1          
     *    HIGH o------------o
     *                       _
     *                       | /+----------- Ausgang
     *                       |/
     *    LOW  o------------o/
     *    Eingang 2
     */
    private static void createOBJ_POWERTASTER0()
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance( "Eingang 1"                   ,1,cl,0, 0);
        CasePin     cp02  = CasePin.createInstance( "Eingang 2 (default Stellung)",2,cl,0, 0);
        CasePin     cp03  = CasePin.createInstance( "Ausgang"                     ,3,cl,0, 0);

        // Objekt mit Gehäuse erzeugen
        //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj = ElectricObject.createInstance(false,"OBJ_POWERTASTER0_0_1",ol);
        ElectricCase   c    = ElectricCase.createInstance("1 x Um Taster (GND default)","http://...",cl);
        Object2Case c2o=Object2Case.createInstance( eobj, c);

        // Objektlayout im Gehäuse erzeugen
        //
        ObjectPin2CasePin    op11 = ObjectPin2CasePin.createInstance(cp03,c2o,ObjectPin.createInstance("Eingang 1"                   , 1, ol));
        ObjectPin2CasePin    op12 = ObjectPin2CasePin.createInstance(cp02,c2o,ObjectPin.createInstance("Eingang 2 (default Stellung)", 2, ol));
        ObjectPin2CasePin    op13 = ObjectPin2CasePin.createInstance(cp01,c2o,ObjectPin.createInstance("Ausgang"                     , 3, ol));

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(getObject("5VOLT"),c);

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(getObject2Case("5VOLT").getPin(1),c.getPin(1),cd);
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(getObject2Case("5VOLT").getPin(2),c.getPin(2),cd);
    }

    
    /**   
     * High/Low Taster
     * 
     *    Eingang 1           _
     *    HIGH o------------o\|
     *                        \
     *                          +----------- Ausgang
     * 
     *    LOW  o------------o
     *    Eingang 2
     */
    private static void createOBJ_POWERTASTER1()
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance( "Eingang 1",1,cl,0, 0);
        CasePin     cp02  = CasePin.createInstance( "Eingang 2 (default Stellung)",2,cl,0, 0);
        CasePin     cp03  = CasePin.createInstance( "Ausgang"  ,3,cl,0, 0);

        // Objekt mit Gehäuse erzeugen
        //
        ObjectLayout ol = ObjectLayout.createInstance();
        ElectricObject eobj = ElectricObject.createInstance(false,"OBJ_POWERTASTER1_0_1",ol);
        ElectricCase   c    = ElectricCase.createInstance("1 x Um Taster (VCC default)","http://...",cl);
        Object2Case c2o=Object2Case.createInstance( eobj, c);

        // Objektlayout im Gehäuse erzeugen
        //
        ObjectPin2CasePin    op11 = ObjectPin2CasePin.createInstance(cp01,c2o,ObjectPin.createInstance("Eingang 1", 1,ol));
        ObjectPin2CasePin    op12 = ObjectPin2CasePin.createInstance(cp02,c2o,ObjectPin.createInstance("Eingang 2 (default Stellung)", 2,ol));
        ObjectPin2CasePin    op13 = ObjectPin2CasePin.createInstance(cp03,c2o,ObjectPin.createInstance("Ausgang"  , 3,ol));

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(getObject("5VOLT"),c);

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(getObject2Case("5VOLT").getPin(1),c.getPin(2),cd);  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(getObject2Case("5VOLT").getPin(2),c.getPin(1),cd); // Minuspool
    }
}

