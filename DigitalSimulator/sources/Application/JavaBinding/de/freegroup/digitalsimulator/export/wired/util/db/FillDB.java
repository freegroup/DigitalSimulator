package de.freegroup.digitalsimulator.export.wired.util.db;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import de.freegroup.digitalsimulator.export.wired.db.*;

public class FillDB
{
    static Object2Case volt5Rel          = null;
    static Object2Case schalter1XAusRel  = null;
    static Object2Case wider200Rel       = null;
    static Object2Case wider470Rel       = null;
    static Object2Case wider1000Rel      = null;
    static Object2Case wider3300Rel      = null;
    static Object2Case wider4700Rel      = null;
    static Object2Case trimmer100kRel    = null;
    static Object2Case diode1N914Rel     = null;
    static Object2Case tBC107Rel         = null;
    static Object2Case ledRel            = null;
    static Object2Case kondensator10nRel = null;
    static Object2Case ne555Rel          = null;

    public static void main(String[] args)
    {
        Object2Case.destroyAll();
        ElectricObject.destroyAll();
        ObjectPin.destroyAll();
        CasePin.destroyAll();
        CaseLayout.destroyAll();
        ElectricCase.destroyAll();
        CaseDependency.destroyAll();
        DependencyPin.destroyAll();
        Connection.destroyAll();
        RelatedObject.destroyAll();
        MacroPinMapping.destroyAll();

        createO_INTERFACE_8_0();
        createI_INTERFACE_0_8();
        create5VOLT();
        createResistor200();
        createResistor3300();
        createResistor470();
        createResistor1000();
        createResistor4700();
        createTrimmer100k();
        createDiode1N914();
        createSchalter1XAus();
        createOBJ_SWITCH_AUS();
        createTransistorBC107();
        createKondensator10n();
        createNE555();
        createLED();
        createOBJ_LED();
        createOBJ_POWER();
        createOBJ_POWERTASTER0();
        createOBJ_POWERTASTER1();
        create7400();
        create7402();
        create7404();
        create7408();
        create7410();
        create7411();
        create7420();
        create7421();
        create7427();
        create7430();
        create7432();
        create7442();
        create7474();
        create7486();
        create74109();
        create747266();
        createOBJ_JK_SR_T_5_2();
        createOBJ_JK_R_T_4_2();
        createOBJ_JK_T_3_2();
        createOBJ_T_1_2();
        createOBJ_D_R_T_3_2();
        createOBJ_D_T_2_2();
        createGND_0_1();
        createHigh_0_1();
        createOBJ_TAKT_0_1();
        createLED_BAR_red_1_0();
        createLED_BAR_red_2_0();
        createLED_BAR_red_3_0();
        createLED_BAR_red_4_0();
        createLED_BAR_red_5_0();
        createLED_BAR_red_6_0();
        createLED_BAR_red_7_0();
        createLED_BAR_red_8_0();

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
        // generate the Caselayout
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "", 1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "",3,cl,0);
        CasePin     cp04  = CasePin.createInstance(0, "",4,cl,0);
        CasePin     cp05  = CasePin.createInstance(0, "",5,cl,0);
        CasePin     cp06  = CasePin.createInstance(0, "",6,cl,0);
        CasePin     cp07  = CasePin.createInstance(0, "GND",7,cl,0);
        CasePin     cp08  = CasePin.createInstance(0, "",8,cl,0);
        CasePin     cp09  = CasePin.createInstance(0, "",9,cl,0);
        CasePin     cp10  = CasePin.createInstance(0, "",10,cl,0);
        CasePin     cp11  = CasePin.createInstance(0, "",11,cl,0);
        CasePin     cp12  = CasePin.createInstance(0, "",12,cl,0);
        CasePin     cp13  = CasePin.createInstance(0, "",13,cl,0);
        CasePin     cp14  = CasePin.createInstance(0, "VCC",14,cl,0);

        // generate the object and the case
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_NAND_2_1"); // 2eingänge und 1 Ausgang
        ElectricCase   c     = ElectricCase.createInstance("7400 (TTL-Bausteil)","http://www.falstaff.demon.co.uk/7400.html",cl);

        // generate the internal object layout
        //
        Object2Case o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op11 = ObjectPin.createInstance(o2c, "",1,cp02);
        ObjectPin      op12 = ObjectPin.createInstance(o2c, "",2,cp01);
        ObjectPin      op13 = ObjectPin.createInstance(o2c, "",3,cp03);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op21 = ObjectPin.createInstance(o2c, "",1,cp05);
        ObjectPin      op22 = ObjectPin.createInstance(o2c, "",2,cp04);
        ObjectPin      op23 = ObjectPin.createInstance(o2c, "",3,cp06);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op31 = ObjectPin.createInstance(o2c, "",1,cp09);
        ObjectPin      op32 = ObjectPin.createInstance(o2c, "",2,cp10);
        ObjectPin      op33 = ObjectPin.createInstance(o2c, "",3,cp08);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op41 = ObjectPin.createInstance(o2c, "",1,cp12);
        ObjectPin      op42 = ObjectPin.createInstance(o2c, "",2,cp13);
        ObjectPin      op43 = ObjectPin.createInstance(o2c, "",3,cp11);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(14));  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(7)); // Minuspool
    }

    /**
     *    Quad 2-input NOR gates.
     *        +---+--+---+             +---+---*---+           ___
     *    /1Y |1  +--+ 14| VCC         | A | B |/Y |      /Y = A+B
     *     1A |2       13| /4Y         +===+===*===+
     *     1B |3       12| 4B          | 0 | 0 | 1 |
     *    /2Y |4  7402 11| 4A          | 0 | 1 | 0 |
     *     2A |5       10| /3Y         | 1 | 0 | 0 |
     *     2B |6        9| 3B          | 1 | 1 | 0 |
     *    GND |7        8| 3A          +---+---*---+
     *        +----------+
     **/
    private static void create7402()
    {
        // generate the Caselayout
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "",3,cl,0);
        CasePin     cp04  = CasePin.createInstance(0, "",4,cl,0);
        CasePin     cp05  = CasePin.createInstance(0, "",5,cl,0);
        CasePin     cp06  = CasePin.createInstance(0, "",6,cl,0);
        CasePin     cp07  = CasePin.createInstance(0, "GND",7,cl,0);
        CasePin     cp08  = CasePin.createInstance(0, "",8,cl,0);
        CasePin     cp09  = CasePin.createInstance(0, "",9,cl,0);
        CasePin     cp10  = CasePin.createInstance(0, "",10,cl,0);
        CasePin     cp11  = CasePin.createInstance(0, "",11,cl,0);
        CasePin     cp12  = CasePin.createInstance(0, "",12,cl,0);
        CasePin     cp13  = CasePin.createInstance(0, "",13,cl,0);
        CasePin     cp14  = CasePin.createInstance(0, "VCC",14,cl,0);

        // generate the object and the case
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_NOR_2_1"); // 2eingänge und 1 Ausgang
        ElectricCase   c     = ElectricCase.createInstance("7402 (TTL-Baustein)","http://www.falstaff.demon.co.uk/7400.html",cl);

        // generate the internal object layout
        //
        Object2Case    o2c   = Object2Case.createInstance(c, eobj);
        ObjectPin      op11 = ObjectPin.createInstance(o2c, "",1,cp02);
        ObjectPin      op12 = ObjectPin.createInstance(o2c, "",2,cp03);
        ObjectPin      op13 = ObjectPin.createInstance(o2c, "",3,cp01);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op21 = ObjectPin.createInstance(o2c, "",1,cp05);
        ObjectPin      op22 = ObjectPin.createInstance(o2c, "",2,cp06);
        ObjectPin      op23 = ObjectPin.createInstance(o2c, "",3,cp04);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op31 = ObjectPin.createInstance(o2c, "",1,cp09);
        ObjectPin      op32 = ObjectPin.createInstance(o2c, "",2,cp08);
        ObjectPin      op33 = ObjectPin.createInstance(o2c, "",3,cp10);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op41 = ObjectPin.createInstance(o2c, "",1,cp12);
        ObjectPin      op42 = ObjectPin.createInstance(o2c, "",2,cp11);
        ObjectPin      op43 = ObjectPin.createInstance(o2c, "",3,cp13);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(14));  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(7)); // Minuspool
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
        CasePin     cp01  = CasePin.createInstance(0, "",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "",3,cl,0);
        CasePin     cp04  = CasePin.createInstance(0, "",4,cl,0);
        CasePin     cp05  = CasePin.createInstance(0, "",5,cl,0);
        CasePin     cp06  = CasePin.createInstance(0, "",6,cl,0);
        CasePin     cp07  = CasePin.createInstance(0, "GND",7,cl,0);
        CasePin     cp08  = CasePin.createInstance(0, "",8,cl,0);
        CasePin     cp09  = CasePin.createInstance(0, "",9,cl,0);
        CasePin     cp10  = CasePin.createInstance(0, "",10,cl,0);
        CasePin     cp11  = CasePin.createInstance(0, "",11,cl,0);
        CasePin     cp12  = CasePin.createInstance(0, "",12,cl,0);
        CasePin     cp13  = CasePin.createInstance(0, "",13,cl,0);
        CasePin     cp14  = CasePin.createInstance(0, "VCC",14,cl,0);

        // generate the object and the case
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_NOT_1_1"); // 1 Eingang und 1 Ausgang
        ElectricCase   c     = ElectricCase.createInstance("7404 (TTL-Baustein)","http://www.falstaff.demon.co.uk/7400.html",cl);

        // generate the internal object layout
        //
        Object2Case    o2c   = Object2Case.createInstance(c, eobj);
        ObjectPin      op11 = ObjectPin.createInstance(o2c, "",1,cp01);
        ObjectPin      op12 = ObjectPin.createInstance(o2c, "",2,cp02);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op21 = ObjectPin.createInstance(o2c, "",1,cp03);
        ObjectPin      op22 = ObjectPin.createInstance(o2c, "",2,cp04);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op31 = ObjectPin.createInstance(o2c, "",1,cp05);
        ObjectPin      op32 = ObjectPin.createInstance(o2c, "",2,cp06);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op41 = ObjectPin.createInstance(o2c, "",1,cp09);
        ObjectPin      op42 = ObjectPin.createInstance(o2c, "",2,cp08);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op51 = ObjectPin.createInstance(o2c, "",1,cp11);
        ObjectPin      op52 = ObjectPin.createInstance(o2c, "",2,cp10);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op61 = ObjectPin.createInstance(o2c, "",1,cp13);
        ObjectPin      op62 = ObjectPin.createInstance(o2c, "",2,cp12);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(14));  // Plus
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(7)); // Minuspool
    }

    /**
      *   Quad 2-input AND gates.
      *       +---+--+---+             +---+---*---+
      *    1A |1  +--+ 14| VCC         | A | B | Y |       Y = AB
      *    1B |2       13| 4B          +===+===*===+
      *    1Y |3       12| 4A          | 0 | 0 | 0 |
      *    2A |4  7408 11| 4Y          | 0 | 1 | 0 |
      *    2B |5       10| 3B          | 1 | 0 | 0 |
      *    2Y |6        9| 3A          | 1 | 1 | 1 |
      *   GND |7        8| 3Y          +---+---*---+
      *       +----------+
      **/
    private static void create7408()
    {
        // generate the Caselayout
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "",3,cl,0);
        CasePin     cp04  = CasePin.createInstance(0, "",4,cl,0);
        CasePin     cp05  = CasePin.createInstance(0, "",5,cl,0);
        CasePin     cp06  = CasePin.createInstance(0, "",6,cl,0);
        CasePin     cp07  = CasePin.createInstance(0, "GND",7,cl,0);
        CasePin     cp08  = CasePin.createInstance(0, "",8,cl,0);
        CasePin     cp09  = CasePin.createInstance(0, "",9,cl,0);
        CasePin     cp10  = CasePin.createInstance(0, "",10,cl,0);
        CasePin     cp11  = CasePin.createInstance(0, "",11,cl,0);
        CasePin     cp12  = CasePin.createInstance(0, "",12,cl,0);
        CasePin     cp13  = CasePin.createInstance(0, "",13,cl,0);
        CasePin     cp14  = CasePin.createInstance(0, "VCC",14,cl,0);

        // generate the object and the case
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_AND_2_1"); // 1 Eingang und 1 Ausgang
        ElectricCase   c     = ElectricCase.createInstance("7408 (TTL-Baustein)","http://www.falstaff.demon.co.uk/7400.html",cl);

        // generate the internal object layout
        //
        Object2Case o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op11 = ObjectPin.createInstance(o2c, "",1,cp02);
        ObjectPin      op12 = ObjectPin.createInstance(o2c, "",2,cp01);
        ObjectPin      op13 = ObjectPin.createInstance(o2c, "",3,cp03);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op21 = ObjectPin.createInstance(o2c, "",1,cp05);
        ObjectPin      op22 = ObjectPin.createInstance(o2c, "",2,cp04);
        ObjectPin      op23 = ObjectPin.createInstance(o2c, "",3,cp06);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op31 = ObjectPin.createInstance(o2c, "",1,cp09);
        ObjectPin      op32 = ObjectPin.createInstance(o2c, "",2,cp10);
        ObjectPin      op33 = ObjectPin.createInstance(o2c, "",3,cp08);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op41 = ObjectPin.createInstance(o2c, "",1,cp12);
        ObjectPin      op42 = ObjectPin.createInstance(o2c, "",2,cp13);
        ObjectPin      op43 = ObjectPin.createInstance(o2c, "",3,cp11);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(14));  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(7)); // Minuspool
    }

    /**
     *    Triple 3-input NAND gates.
     *        +---+--+---+             +---+---+---*---+       ___
     *     1A |1  +--+ 14| VCC         | A | B | C |/Y |  /Y = ABC
     *     1B |2       13| 1C          +===+===+===*===+
     *     2A |3       12| /1Y         | 0 | X | X | 1 |
     *     2B |4  7410 11| 3C          | 1 | 0 | X | 1 |
     *     2C |5       10| 3B          | 1 | 1 | 0 | 1 |
     *    /2Y |6        9| 3A          | 1 | 1 | 1 | 0 |
     *    GND |7        8| /3Y         +---+---+---*---+
     *        +----------+
     **/
    private static void create7410()
    {
        // generate the Caselayout
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "",3,cl,0);
        CasePin     cp04  = CasePin.createInstance(0, "",4,cl,0);
        CasePin     cp05  = CasePin.createInstance(0, "",5,cl,0);
        CasePin     cp06  = CasePin.createInstance(0, "",6,cl,0);
        CasePin     cp07  = CasePin.createInstance(0, "GND",7,cl,0);
        CasePin     cp08  = CasePin.createInstance(0, "",8,cl,0);
        CasePin     cp09  = CasePin.createInstance(0, "",9,cl,0);
        CasePin     cp10  = CasePin.createInstance(0, "",10,cl,0);
        CasePin     cp11  = CasePin.createInstance(0, "",11,cl,0);
        CasePin     cp12  = CasePin.createInstance(0, "",12,cl,0);
        CasePin     cp13  = CasePin.createInstance(0, "",13,cl,0);
        CasePin     cp14  = CasePin.createInstance(0, "VCC",14,cl,0);

        // generate the object and the case
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_NAND_3_1"); // 1 Eingang und 1 Ausgang
        ElectricCase   c     = ElectricCase.createInstance("7410 (TTL-Baustein)","http://www.falstaff.demon.co.uk/7400.html",cl);

        // generate the internal object layout
        //
        Object2Case o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op11 = ObjectPin.createInstance(o2c, "",1,cp01);
        ObjectPin      op12 = ObjectPin.createInstance(o2c, "",2,cp02);
        ObjectPin      op13 = ObjectPin.createInstance(o2c, "",3,cp13);
        ObjectPin      op14 = ObjectPin.createInstance(o2c, "",4,cp12);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op21 = ObjectPin.createInstance(o2c, "",1,cp03);
        ObjectPin      op22 = ObjectPin.createInstance(o2c, "",2,cp04);
        ObjectPin      op23 = ObjectPin.createInstance(o2c, "",3,cp05);
        ObjectPin      op24 = ObjectPin.createInstance(o2c, "",4,cp06);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op31 = ObjectPin.createInstance(o2c, "",1,cp09);
        ObjectPin      op32 = ObjectPin.createInstance(o2c, "",2,cp10);
        ObjectPin      op33 = ObjectPin.createInstance(o2c, "",3,cp11);
        ObjectPin      op34 = ObjectPin.createInstance(o2c, "",4,cp08);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(14));  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(7)); // Minuspool
    }

    /**
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
        // generate the Caselayout
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "1 !Reset",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "1 J",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "1 !K",3,cl,0);
        CasePin     cp04  = CasePin.createInstance(0, "1 Clock",4,cl,0);
        CasePin     cp05  = CasePin.createInstance(0, "1 '!Set",5,cl,0);
        CasePin     cp06  = CasePin.createInstance(0, "1 Q",6,cl,0);
        CasePin     cp07  = CasePin.createInstance(0, "1 !Q",7,cl,0);
        CasePin     cp08  = CasePin.createInstance(0, "GND",8,cl,0);
        CasePin     cp09  = CasePin.createInstance(0, "2 !Q",9,cl,0);
        CasePin     cp10  = CasePin.createInstance(0, "2 Q",10,cl,0);
        CasePin     cp11  = CasePin.createInstance(0, "2 !Set",11,cl,0);
        CasePin     cp12  = CasePin.createInstance(0, "2 Clock",12,cl,0);
        CasePin     cp13  = CasePin.createInstance(0, "2 !K",13,cl,0);
        CasePin     cp14  = CasePin.createInstance(0, "2 J",14,cl,0);
        CasePin     cp15  = CasePin.createInstance(0, "2 !Reset",15,cl,0);
        CasePin     cp16  = CasePin.createInstance(0, "VCC",16,cl,0);

        // generate the object and the case
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_D_J!K_SR_T_5_2"); // 1 Eingang und 1 Ausgang
        ElectricCase   c     = ElectricCase.createInstance("74109 (TTL-Baustein)","http://www.falstaff.demon.co.uk/74100.html",cl);

        // generate the internal object layout
        //
        Object2Case o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op11 = ObjectPin.createInstance(o2c, "!Set",1,cp05);
        ObjectPin      op12 = ObjectPin.createInstance(o2c, "J",2,cp02);
        ObjectPin      op13 = ObjectPin.createInstance(o2c, "Clock",3,cp04);
        ObjectPin      op14 = ObjectPin.createInstance(o2c, "!K",4,cp03);
        ObjectPin      op15 = ObjectPin.createInstance(o2c, "!R",5,cp01);
        ObjectPin      op16 = ObjectPin.createInstance(o2c, "Q",6,cp06);
        ObjectPin      op17 = ObjectPin.createInstance(o2c, "!Q",6,cp07);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op21 = ObjectPin.createInstance(o2c, "!Set",1,cp11);
        ObjectPin      op22 = ObjectPin.createInstance(o2c, "J",2,cp14);
        ObjectPin      op23 = ObjectPin.createInstance(o2c, "Clock",3,cp12);
        ObjectPin      op24 = ObjectPin.createInstance(o2c, "!K",4,cp13);
        ObjectPin      op25 = ObjectPin.createInstance(o2c, "!R",5,cp05);
        ObjectPin      op26 = ObjectPin.createInstance(o2c, "Q",6,cp10);
        ObjectPin      op27 = ObjectPin.createInstance(o2c, "!Q",6,cp09);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(16));  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(8)); // Minuspool
      }

    /**
     *    Triple 3-input AND gates.
     *        +---+--+---+             +---+---+---*---+
     *     1A |1  +--+ 14| VCC         | A | B | C | Y |   Y = ABC
     *     1B |2       13| 1C          +===+===+===*===+
     *     2A |3       12| 1Y          | 0 | X | X | 0 |
     *     2B |4  7411 11| 3C          | 1 | 0 | X | 0 |
     *     2C |5       10| 3B          | 1 | 1 | 0 | 0 |
     *     2Y |6        9| 3A          | 1 | 1 | 1 | 1 |
     *    GND |7        8| 3Y          +---+---+---*---+
     *        +----------+
     **/
    private static void create7411()
    {
        // generate the Caselayout
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "",3,cl,0);
        CasePin     cp04  = CasePin.createInstance(0, "",4,cl,0);
        CasePin     cp05  = CasePin.createInstance(0, "",5,cl,0);
        CasePin     cp06  = CasePin.createInstance(0, "",6,cl,0);
        CasePin     cp07  = CasePin.createInstance(0, "GND",7,cl,0);
        CasePin     cp08  = CasePin.createInstance(0, "",8,cl,0);
        CasePin     cp09  = CasePin.createInstance(0, "",9,cl,0);
        CasePin     cp10  = CasePin.createInstance(0, "",10,cl,0);
        CasePin     cp11  = CasePin.createInstance(0, "",11,cl,0);
        CasePin     cp12  = CasePin.createInstance(0, "",12,cl,0);
        CasePin     cp13  = CasePin.createInstance(0, "",13,cl,0);
        CasePin     cp14  = CasePin.createInstance(0, "VCC",14,cl,0);

        // generate the object and the case
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_AND_3_1"); // 1 Eingang und 1 Ausgang
        ElectricCase   c     = ElectricCase.createInstance("7411 (TTL-Baustein)","http://www.falstaff.demon.co.uk/7400.html",cl);

        // generate the internal object layout
        //
        Object2Case o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op11 = ObjectPin.createInstance(o2c, "",1,cp01);
        ObjectPin      op12 = ObjectPin.createInstance(o2c, "",2,cp02);
        ObjectPin      op13 = ObjectPin.createInstance(o2c, "",3,cp13);
        ObjectPin      op14 = ObjectPin.createInstance(o2c, "",4,cp12);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op21 = ObjectPin.createInstance(o2c, "",1,cp03);
        ObjectPin      op22 = ObjectPin.createInstance(o2c, "",2,cp04);
        ObjectPin      op23 = ObjectPin.createInstance(o2c, "",3,cp05);
        ObjectPin      op24 = ObjectPin.createInstance(o2c, "",4,cp06);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op31 = ObjectPin.createInstance(o2c, "",1,cp09);
        ObjectPin      op32 = ObjectPin.createInstance(o2c, "",2,cp10);
        ObjectPin      op33 = ObjectPin.createInstance(o2c, "",3,cp11);
        ObjectPin      op34 = ObjectPin.createInstance(o2c, "",4,cp08);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(14));  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(7)); // Minuspool
    }

    /**
     *    Dual 4-input NAND gates.
     *        +---+--+---+             +---+---+---+---*---+        ____
     *     1A |1  +--+ 14| VCC         | A | B | C | D |/Y |   /Y = ABCD
     *     1B |2       13| 2D          +===+===+===+===*===+
     *        |3       12| 2C          | 0 | X | X | X | 1 |
     *     1C |4  7420 11|             | 1 | 0 | X | X | 1 |
     *     1D |5       10| 2B          | 1 | 1 | 0 | X | 1 |
     *    /1Y |6        9| 2A          | 1 | 1 | 1 | 0 | 1 |
     *    GND |7        8| /2Y         | 1 | 1 | 1 | 1 | 0 |
     *        +----------+             +---+---+---+---*---+
     **/
    private static void create7420()
    {
        // generate the Caselayout
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "",3,cl,0);
        CasePin     cp04  = CasePin.createInstance(0, "",4,cl,0);
        CasePin     cp05  = CasePin.createInstance(0, "",5,cl,0);
        CasePin     cp06  = CasePin.createInstance(0, "",6,cl,0);
        CasePin     cp07  = CasePin.createInstance(0, "GND",7,cl,0);
        CasePin     cp08  = CasePin.createInstance(0, "",8,cl,0);
        CasePin     cp09  = CasePin.createInstance(0, "",9,cl,0);
        CasePin     cp10  = CasePin.createInstance(0, "",10,cl,0);
        CasePin     cp11  = CasePin.createInstance(0, "",11,cl,0);
        CasePin     cp12  = CasePin.createInstance(0, "",12,cl,0);
        CasePin     cp13  = CasePin.createInstance(0, "",13,cl,0);
        CasePin     cp14  = CasePin.createInstance(0, "VCC",14,cl,0);

        // generate the object and the case
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_NAND_4_1"); // 1 Eingang und 1 Ausgang
        ElectricCase   c     = ElectricCase.createInstance("7420 (TTL-Baustein)","http://www.falstaff.demon.co.uk/7400.html",cl);

        // generate the internal object layout
        //
        Object2Case o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op11 = ObjectPin.createInstance(o2c, "",1,cp01);
        ObjectPin      op12 = ObjectPin.createInstance(o2c, "",2,cp02);
        ObjectPin      op13 = ObjectPin.createInstance(o2c, "",3,cp04);
        ObjectPin      op14 = ObjectPin.createInstance(o2c, "",4,cp05);
        ObjectPin      op15 = ObjectPin.createInstance(o2c, "",5,cp06);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op21 = ObjectPin.createInstance(o2c, "",1,cp09);
        ObjectPin      op22 = ObjectPin.createInstance(o2c, "",2,cp10);
        ObjectPin      op23 = ObjectPin.createInstance(o2c, "",3,cp12);
        ObjectPin      op24 = ObjectPin.createInstance(o2c, "",4,cp13);
        ObjectPin      op25 = ObjectPin.createInstance(o2c, "",5,cp08);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(14));  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(7)); // Minuspool
    }

    /**
     *    Dual 4-input AND gates.
     *        +---+--+---+             +---+---+---+---*---+
     *     1A |1  +--+ 14| VCC         | A | B | C | D | Y |    Y = ABCD
     *     1B |2       13| 2D          +===+===+===+===*===+
     *        |3       12| 2C          | 0 | X | X | X | 0 |
     *     1C |4  7421 11|             | 1 | 0 | X | X | 0 |
     *     1D |5       10| 2B          | 1 | 1 | 0 | X | 0 |
     *     1Y |6        9| 2A          | 1 | 1 | 1 | 0 | 0 |
     *    GND |7        8| 2Y          | 1 | 1 | 1 | 1 | 1 |
     *        +----------+             +---+---+---+---*---+
     **/
    private static void create7421()
    {
        // generate the Caselayout
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "",3,cl,0);
        CasePin     cp04  = CasePin.createInstance(0, "",4,cl,0);
        CasePin     cp05  = CasePin.createInstance(0, "",5,cl,0);
        CasePin     cp06  = CasePin.createInstance(0, "",6,cl,0);
        CasePin     cp07  = CasePin.createInstance(0, "GND",7,cl,0);
        CasePin     cp08  = CasePin.createInstance(0, "",8,cl,0);
        CasePin     cp09  = CasePin.createInstance(0, "",9,cl,0);
        CasePin     cp10  = CasePin.createInstance(0, "",10,cl,0);
        CasePin     cp11  = CasePin.createInstance(0, "",11,cl,0);
        CasePin     cp12  = CasePin.createInstance(0, "",12,cl,0);
        CasePin     cp13  = CasePin.createInstance(0, "",13,cl,0);
        CasePin     cp14  = CasePin.createInstance(0, "VCC",14,cl,0);

        // generate the object and the case
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_AND_4_1"); // 1 Eingang und 1 Ausgang
        ElectricCase   c     = ElectricCase.createInstance("7421 (TTL-Baustein)","http://www.falstaff.demon.co.uk/7400.html",cl);

        // generate the internal object layout
        //
        Object2Case o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op11 = ObjectPin.createInstance(o2c, "",1,cp01);
        ObjectPin      op12 = ObjectPin.createInstance(o2c, "",2,cp02);
        ObjectPin      op13 = ObjectPin.createInstance(o2c, "",3,cp04);
        ObjectPin      op14 = ObjectPin.createInstance(o2c, "",4,cp05);
        ObjectPin      op15 = ObjectPin.createInstance(o2c, "",5,cp06);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op21 = ObjectPin.createInstance(o2c, "",1,cp09);
        ObjectPin      op22 = ObjectPin.createInstance(o2c, "",2,cp10);
        ObjectPin      op23 = ObjectPin.createInstance(o2c, "",3,cp12);
        ObjectPin      op24 = ObjectPin.createInstance(o2c, "",4,cp13);
        ObjectPin      op25 = ObjectPin.createInstance(o2c, "",5,cp08);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(14));  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(7)); // Minuspool
    }


    /**
     *    Triple 3-input NOR gates.
     *        +---+--+---+             +---+---+---*---+       _____
     *     1A |1  +--+ 14| VCC         | A | B | C |/Y |  /Y = A+B+C
     *     1B |2       13| 1C          +===+===+===*===+
     *     2A |3       12| /1Y         | 0 | 0 | 0 | 1 |
     *     2B |4  7427 11| 3C          | 0 | 0 | 1 | 0 |
     *     2C |5       10| 3B          | 0 | 1 | X | 0 |
     *    /2Y |6        9| 3A          | 1 | X | X | 0 |
     *    GND |7        8| /3Y         +---+---+---*---+
     *        +----------+
     **/
    private static void create7427()
    {
        // generate the Caselayout
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "",3,cl,0);
        CasePin     cp04  = CasePin.createInstance(0, "",4,cl,0);
        CasePin     cp05  = CasePin.createInstance(0, "",5,cl,0);
        CasePin     cp06  = CasePin.createInstance(0, "",6,cl,0);
        CasePin     cp07  = CasePin.createInstance(0, "GND",7,cl,0);
        CasePin     cp08  = CasePin.createInstance(0, "",8,cl,0);
        CasePin     cp09  = CasePin.createInstance(0, "",9,cl,0);
        CasePin     cp10  = CasePin.createInstance(0, "",10,cl,0);
        CasePin     cp11  = CasePin.createInstance(0, "",11,cl,0);
        CasePin     cp12  = CasePin.createInstance(0, "",12,cl,0);
        CasePin     cp13  = CasePin.createInstance(0, "",13,cl,0);
        CasePin     cp14  = CasePin.createInstance(0, "VCC",14,cl,0);

        // generate the object and the case
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_NOR_3_1"); // 1 Eingang und 1 Ausgang
        ElectricCase   c     = ElectricCase.createInstance("7427 (TTL-Baustein)","http://www.falstaff.demon.co.uk/7400.html",cl);

        // generate the internal object layout
        //
        Object2Case o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op11 = ObjectPin.createInstance(o2c, "",1,cp01);
        ObjectPin      op12 = ObjectPin.createInstance(o2c, "",2,cp02);
        ObjectPin      op13 = ObjectPin.createInstance(o2c, "",3,cp13);
        ObjectPin      op14 = ObjectPin.createInstance(o2c, "",4,cp12);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op21 = ObjectPin.createInstance(o2c, "",1,cp03);
        ObjectPin      op22 = ObjectPin.createInstance(o2c, "",2,cp04);
        ObjectPin      op23 = ObjectPin.createInstance(o2c, "",3,cp05);
        ObjectPin      op24 = ObjectPin.createInstance(o2c, "",4,cp06);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op31 = ObjectPin.createInstance(o2c, "",1,cp09);
        ObjectPin      op32 = ObjectPin.createInstance(o2c, "",2,cp10);
        ObjectPin      op33 = ObjectPin.createInstance(o2c, "",3,cp11);
        ObjectPin      op34 = ObjectPin.createInstance(o2c, "",4,cp08);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(14));  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(7)); // Minuspool
    }


    /**
     *    8-input NAND gate.
     *        +---+--+---+                 ________
     *      A |1  +--+ 14| VCC        /Y = ABCDEFGH
     *      B |2       13|
     *      C |3       12| H
     *      D |4  7430 11| G
     *      E |5       10|
     *      F |6        9|
     *    GND |7        8| /Y
     *        +----------+
     **/
    private static void create7430()
    {
        // generate the Caselayout
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "",3,cl,0);
        CasePin     cp04  = CasePin.createInstance(0, "",4,cl,0);
        CasePin     cp05  = CasePin.createInstance(0, "",5,cl,0);
        CasePin     cp06  = CasePin.createInstance(0, "",6,cl,0);
        CasePin     cp07  = CasePin.createInstance(0, "GND",7,cl,0);
        CasePin     cp08  = CasePin.createInstance(0, "",8,cl,0);
        CasePin     cp09  = CasePin.createInstance(0, "",9,cl,0);
        CasePin     cp10  = CasePin.createInstance(0, "",10,cl,0);
        CasePin     cp11  = CasePin.createInstance(0, "",11,cl,0);
        CasePin     cp12  = CasePin.createInstance(0, "",12,cl,0);
        CasePin     cp13  = CasePin.createInstance(0, "",13,cl,0);
        CasePin     cp14  = CasePin.createInstance(0, "VCC",14,cl,0);

        // generate the object and the case
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_NAND_8_1"); // 1 Eingang und 1 Ausgang
        ElectricCase   c     = ElectricCase.createInstance("7430 (TTL-Baustein)","http://www.falstaff.demon.co.uk/7400.html",cl);

        // generate the internal object layout
        //
        Object2Case o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op11 = ObjectPin.createInstance(o2c, "",1,cp01);
        ObjectPin      op12 = ObjectPin.createInstance(o2c, "",2,cp02);
        ObjectPin      op13 = ObjectPin.createInstance(o2c, "",3,cp03);
        ObjectPin      op14 = ObjectPin.createInstance(o2c, "",4,cp04);
        ObjectPin      op15 = ObjectPin.createInstance(o2c, "",5,cp05);
        ObjectPin      op16 = ObjectPin.createInstance(o2c, "",6,cp06);
        ObjectPin      op17 = ObjectPin.createInstance(o2c, "",7,cp11);
        ObjectPin      op18 = ObjectPin.createInstance(o2c, "",8,cp12);
        ObjectPin      op19 = ObjectPin.createInstance(o2c, "",9,cp08);


        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(14));  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(7)); // Minuspool
    }


    /**
     *    Quad 2-input OR gates.
     *        +---+--+---+             +---+---*---+
     *     1A |1  +--+ 14| VCC         | A | B | Y |       Y = A+B
     *     1B |2       13| 4B          +===+===*===+
     *     1Y |3       12| 4A          | 0 | 0 | 0 |
     *     2A |4  7432 11| 4Y          | 0 | 1 | 1 |
     *     2B |5       10| 3B          | 1 | 0 | 1 |
     *     2Y |6        9| 3A          | 1 | 1 | 1 |
     *    GND |7        8| 3Y          +---+---*---+
     *        +----------+
     **/
    private static void create7432()
    {
        // generate the Caselayout
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "",3,cl,0);
        CasePin     cp04  = CasePin.createInstance(0, "",4,cl,0);
        CasePin     cp05  = CasePin.createInstance(0, "",5,cl,0);
        CasePin     cp06  = CasePin.createInstance(0, "",6,cl,0);
        CasePin     cp07  = CasePin.createInstance(0, "GND",7,cl,0);
        CasePin     cp08  = CasePin.createInstance(0, "",8,cl,0);
        CasePin     cp09  = CasePin.createInstance(0, "",9,cl,0);
        CasePin     cp10  = CasePin.createInstance(0, "",10,cl,0);
        CasePin     cp11  = CasePin.createInstance(0, "",11,cl,0);
        CasePin     cp12  = CasePin.createInstance(0, "",12,cl,0);
        CasePin     cp13  = CasePin.createInstance(0, "",13,cl,0);
        CasePin     cp14  = CasePin.createInstance(0, "VCC",14,cl,0);

        // generate the object and the case
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_OR_2_1"); // 1 Eingang und 1 Ausgang
        ElectricCase   c     = ElectricCase.createInstance("7432 (TTL-Baustein)","http://www.falstaff.demon.co.uk/7400.html",cl);

        // generate the internal object layout
        //
        Object2Case o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op11 = ObjectPin.createInstance(o2c, "E1",1,cp01);
        ObjectPin      op12 = ObjectPin.createInstance(o2c, "E2",2,cp02);
        ObjectPin      op13 = ObjectPin.createInstance(o2c, "Q",3,cp13);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op21 = ObjectPin.createInstance(o2c, "E1",1,cp04);
        ObjectPin      op22 = ObjectPin.createInstance(o2c, "E2",2,cp05);
        ObjectPin      op23 = ObjectPin.createInstance(o2c, "Q",3,cp06);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op31 = ObjectPin.createInstance(o2c, "E1",1,cp09);
        ObjectPin      op32 = ObjectPin.createInstance(o2c, "E2",2,cp10);
        ObjectPin      op33 = ObjectPin.createInstance(o2c, "Q",3,cp08);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op41 = ObjectPin.createInstance(o2c, "E1",1,cp12);
        ObjectPin      op42 = ObjectPin.createInstance(o2c, "E2",2,cp13);
        ObjectPin      op43 = ObjectPin.createInstance(o2c, "Q",3,cp11);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(14));  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(7)); // Minuspool
    }


    /**
     *    1-of-10 inverting decoder/demultiplexer.
     *        +---+--+---+             +---+---+---+---*---+---+---+---+
     *    /Y0 |1  +--+ 16| VCC         | S3| S2| S1| S0|/Y0|/Y1|...|/Y9|
     *    /Y1 |2       15| S0          +===+===+===+===*===+===+===+===+
     *    /Y2 |3       14| S1          | 0 | 0 | 0 | 0 | 0 | 1 | 1 | 1 |
     *    /Y3 |4       13| S2          | 0 | 0 | 0 | 1 | 1 | 0 | 1 | 1 |
     *    /Y4 |5  7442 12| S3          | . | . | . | . | 1 | 1 | . | 1 |
     *    /Y5 |6       11| /Y9         | 1 | 0 | 0 | 1 | 1 | 1 | 1 | 0 |
     *    /Y6 |7       10| /Y8         | 1 | 0 | 1 | X | 1 | 1 | 1 | 1 |
     *    GND |8        9| /Y7         | 1 | 1 | X | X | 1 | 1 | 1 | 1 |
     *        +----------+             +---+---+---+---*---+---+---+---+
     **/
    private static void create7442()
    {
        // generate the Caselayout
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "A1",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "A2",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "A3",3,cl,0);
        CasePin     cp04  = CasePin.createInstance(0, "A4",4,cl,0);
        CasePin     cp05  = CasePin.createInstance(0, "A5",5,cl,0);
        CasePin     cp06  = CasePin.createInstance(0, "A6",6,cl,0);
        CasePin     cp07  = CasePin.createInstance(0, "A7",7,cl,0);
        CasePin     cp08  = CasePin.createInstance(0, "GND",8,cl,0);
        CasePin     cp09  = CasePin.createInstance(0, "A8",9,cl,0);
        CasePin     cp10  = CasePin.createInstance(0, "A9",10,cl,0);
        CasePin     cp11  = CasePin.createInstance(0, "A10",11,cl,0);
        CasePin     cp12  = CasePin.createInstance(0, "D4",12,cl,0);
        CasePin     cp13  = CasePin.createInstance(0, "D3",13,cl,0);
        CasePin     cp14  = CasePin.createInstance(0, "D2",14,cl,0);
        CasePin     cp15  = CasePin.createInstance(0, "D1",15,cl,0);
        CasePin     cp16  = CasePin.createInstance(0, "VCC",16,cl,0);

        // generate the object and the case
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_BCDtoDEZ_4_10"); // 1 Eingang und 1 Ausgang
        ElectricCase   c     = ElectricCase.createInstance("7442 (TTL-Baustein)","http://www.falstaff.demon.co.uk/7400.html",cl);

        // generate the internal object layout
        //
        Object2Case o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op11 = ObjectPin.createInstance(o2c, "D1",1,cp15);
        ObjectPin      op12 = ObjectPin.createInstance(o2c, "D2",2,cp14);
        ObjectPin      op13 = ObjectPin.createInstance(o2c, "D3",3,cp13);
        ObjectPin      op14 = ObjectPin.createInstance(o2c, "D4",4,cp12);
        ObjectPin      op15 = ObjectPin.createInstance(o2c, "A1",5,cp01);
        ObjectPin      op16 = ObjectPin.createInstance(o2c, "A2",6,cp02);
        ObjectPin      op17 = ObjectPin.createInstance(o2c, "A3",7,cp03);
        ObjectPin      op18 = ObjectPin.createInstance(o2c, "A4",8,cp04);
        ObjectPin      op19 = ObjectPin.createInstance(o2c, "A5",9,cp05);
        ObjectPin      op110 = ObjectPin.createInstance(o2c, "A6",10,cp06);
        ObjectPin      op111 = ObjectPin.createInstance(o2c, "A7",11,cp07);
        ObjectPin      op112 = ObjectPin.createInstance(o2c, "A8",12,cp09);
        ObjectPin      op113 = ObjectPin.createInstance(o2c, "A9",13,cp10);
        ObjectPin      op114 = ObjectPin.createInstance(o2c, "A10",14,cp11);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(14));  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(7)); // Minuspool
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
        CasePin     cp01  = CasePin.createInstance(0, "1 !Reset",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "1 D",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "1 Clock",3,cl,0);
        CasePin     cp04  = CasePin.createInstance(0, "1 !Set",4,cl,0);
        CasePin     cp05  = CasePin.createInstance(0, "1 Q",5,cl,0);
        CasePin     cp06  = CasePin.createInstance(0, "1 !Q",6,cl,0);
        CasePin     cp07  = CasePin.createInstance(0, "GND",7,cl,0);
        CasePin     cp08  = CasePin.createInstance(0, "2 !Q",8,cl,0);
        CasePin     cp09  = CasePin.createInstance(0, "2 Q",9,cl,0);
        CasePin     cp10  = CasePin.createInstance(0, "2 Set",10,cl,0);
        CasePin     cp11  = CasePin.createInstance(0, "2 Clock",11,cl,0);
        CasePin     cp12  = CasePin.createInstance(0, "2 D",12,cl,0);
        CasePin     cp13  = CasePin.createInstance(0, "2 Reset",13,cl,0);
        CasePin     cp14  = CasePin.createInstance(0, "VCC",14,cl,0);

        // generate the object and the case
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_D_SR_T_4_2"); // 1 Eingang und 1 Ausgang
        ElectricCase   c     = ElectricCase.createInstance("7474 (TTL-Baustein)","http://www.falstaff.demon.co.uk/7400.html",cl);

        // generate the internal object layout
        //
        Object2Case o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op11 = ObjectPin.createInstance(o2c, "Set",1,cp04);
        ObjectPin      op12 = ObjectPin.createInstance(o2c, "D",2,cp02);
        ObjectPin      op13 = ObjectPin.createInstance(o2c, "Clock",3,cp03);
        ObjectPin      op14 = ObjectPin.createInstance(o2c, "Reset",4,cp01);
        ObjectPin      op15 = ObjectPin.createInstance(o2c, "Q",5,cp05);
        ObjectPin      op16 = ObjectPin.createInstance(o2c, "!Q",6,cp06);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op21 = ObjectPin.createInstance(o2c, "Set",1,cp10);
        ObjectPin      op22 = ObjectPin.createInstance(o2c, "D",2,cp12);
        ObjectPin      op23 = ObjectPin.createInstance(o2c, "Clock",3,cp11);
        ObjectPin      op24 = ObjectPin.createInstance(o2c, "Reset",4,cp13);
        ObjectPin      op25 = ObjectPin.createInstance(o2c, "Q",5,cp09);
        ObjectPin      op26 = ObjectPin.createInstance(o2c, "!Q",6,cp08);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(14));  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(7)); // Minuspool
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
        CasePin     cp01  = CasePin.createInstance(0, "", 1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "",3,cl,0);
        CasePin     cp04  = CasePin.createInstance(0, "",4,cl,0);
        CasePin     cp05  = CasePin.createInstance(0, "",5,cl,0);
        CasePin     cp06  = CasePin.createInstance(0, "",6,cl,0);
        CasePin     cp07  = CasePin.createInstance(0, "GND",7,cl,0);
        CasePin     cp08  = CasePin.createInstance(0, "",8,cl,0);
        CasePin     cp09  = CasePin.createInstance(0, "",9,cl,0);
        CasePin     cp10  = CasePin.createInstance(0, "",10,cl,0);
        CasePin     cp11  = CasePin.createInstance(0, "",11,cl,0);
        CasePin     cp12  = CasePin.createInstance(0, "",12,cl,0);
        CasePin     cp13  = CasePin.createInstance(0, "",13,cl,0);
        CasePin     cp14  = CasePin.createInstance(0, "VCC",14,cl,0);

        // generate the object and the case
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_XOR_2_1"); // 2eingänge und 1 Ausgang
        ElectricCase   c     = ElectricCase.createInstance("7486 (TTL-Baustein)","http://www.falstaff.demon.co.uk/741000.html",cl);

        // generate the internal object layout
        //
        Object2Case o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op11 = ObjectPin.createInstance(o2c, "",1,cp01);
        ObjectPin      op12 = ObjectPin.createInstance(o2c, "",2,cp02);
        ObjectPin      op13 = ObjectPin.createInstance(o2c, "",3,cp03);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op21 = ObjectPin.createInstance(o2c, "",1,cp04);
        ObjectPin      op22 = ObjectPin.createInstance(o2c, "",2,cp05);
        ObjectPin      op23 = ObjectPin.createInstance(o2c, "",3,cp06);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op31 = ObjectPin.createInstance(o2c, "",1,cp09);
        ObjectPin      op32 = ObjectPin.createInstance(o2c, "",2,cp10);
        ObjectPin      op33 = ObjectPin.createInstance(o2c, "",3,cp08);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op41 = ObjectPin.createInstance(o2c, "",1,cp12);
        ObjectPin      op42 = ObjectPin.createInstance(o2c, "",2,cp13);
        ObjectPin      op43 = ObjectPin.createInstance(o2c, "",3,cp11);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(14));  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(7)); // Minuspool
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
        // generate the Caselayout
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "", 1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "",3,cl,0);
        CasePin     cp04  = CasePin.createInstance(0, "",4,cl,0);
        CasePin     cp05  = CasePin.createInstance(0, "",5,cl,0);
        CasePin     cp06  = CasePin.createInstance(0, "",6,cl,0);
        CasePin     cp07  = CasePin.createInstance(0, "GND",7,cl,0);
        CasePin     cp08  = CasePin.createInstance(0, "",8,cl,0);
        CasePin     cp09  = CasePin.createInstance(0, "",9,cl,0);
        CasePin     cp10  = CasePin.createInstance(0, "",10,cl,0);
        CasePin     cp11  = CasePin.createInstance(0, "",11,cl,0);
        CasePin     cp12  = CasePin.createInstance(0, "",12,cl,0);
        CasePin     cp13  = CasePin.createInstance(0, "",13,cl,0);
        CasePin     cp14  = CasePin.createInstance(0, "VCC",14,cl,0);

        // generate the object and the case
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_XNOR_2_1"); // 2eingänge und 1 Ausgang
        ElectricCase   c     = ElectricCase.createInstance("747266 (TTL-Baustein)","http://www.falstaff.demon.co.uk/741000.html",cl);

        // generate the internal object layout
        //
        Object2Case o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op11 = ObjectPin.createInstance(o2c, "",1,cp01);
        ObjectPin      op12 = ObjectPin.createInstance(o2c, "",2,cp02);
        ObjectPin      op13 = ObjectPin.createInstance(o2c, "",3,cp03);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op21 = ObjectPin.createInstance(o2c, "",1,cp04);
        ObjectPin      op22 = ObjectPin.createInstance(o2c, "",2,cp05);
        ObjectPin      op23 = ObjectPin.createInstance(o2c, "",3,cp06);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op31 = ObjectPin.createInstance(o2c, "",1,cp09);
        ObjectPin      op32 = ObjectPin.createInstance(o2c, "",2,cp10);
        ObjectPin      op33 = ObjectPin.createInstance(o2c, "",3,cp08);

        o2c =Object2Case.createInstance(c, eobj);
        ObjectPin      op41 = ObjectPin.createInstance(o2c, "",1,cp12);
        ObjectPin      op42 = ObjectPin.createInstance(o2c, "",2,cp13);
        ObjectPin      op43 = ObjectPin.createInstance(o2c, "",3,cp11);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(14));  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(7)); // Minuspool
    }

    /**
     * 5 Volt Spannungsversorgung für die IC erzeugen
     *
     *          +--------------+
     *          |              |
     *    Pin 1 |    5 Volt    |  Pin 2
     *    ------+              +-----
     *          |VCC       GND |
     *          |              |
     *          |              |
     *          +--------------+
     *
     */
    private static void create5VOLT()
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "VCC",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "GND",2,cl,0);

        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(1,"5VOLT");
        ElectricCase   c    = ElectricCase.createInstance("Spannungsversorgung 5V Gleichspannung","http://...",cl);

        // Objektlayout im Gehäuse erzeugen
        //
        volt5Rel = Object2Case.createInstance(c, eobj);
        ObjectPin    op11 = ObjectPin.createInstance(volt5Rel,"VCC", 1,cp01);
        ObjectPin    op12 = ObjectPin.createInstance(volt5Rel,"GND", 2,cp02);
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
    private static void createTransistorBC107()
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "Basis",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "Kathode",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "Emitter",3,cl,0);

        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"BC107");
        ElectricCase   c    = ElectricCase.createInstance("Transistor BC107BP (npn)","http://www.farnell.com/datasheets/5462001.pdf",cl);

        // Objektlayout im Gehäuse erzeugen
        //
        tBC107Rel = Object2Case.createInstance(c,  eobj);
        ObjectPin    op11 = ObjectPin.createInstance(tBC107Rel,"Basis",1,cp01);
        ObjectPin    op12 = ObjectPin.createInstance(tBC107Rel,"Kathode",2,cp02);
        ObjectPin    op13 = ObjectPin.createInstance(tBC107Rel,"Emitter",3,cp03);

    }


    /**
     *            200 Ohm
     *           ______
     *  --------|______|-----
     *  pin 1             pin 2
     */
    private static void createResistor200()
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);

        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"200 OHM");
        ElectricCase   c    = ElectricCase.createInstance("Widerstand 200 Ohm","http://...",cl);

        // Objektlayout im Gehäuse erzeugen
        //
        wider200Rel = Object2Case.createInstance(c, eobj);
        ObjectPin    op11 = ObjectPin.createInstance(wider200Rel,"",1,cp01);
        ObjectPin    op12 = ObjectPin.createInstance(wider200Rel,"",2,cp02);

    }

    /**
     *
     */
   private static void createOBJ_SWITCH_AUS()
    {
        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_SWITCH_AUS_1_1");

        // Abhängigkeiten erzeugen
        //
        RelatedObject r330_1    = RelatedObject.createInstance(wider3300Rel.getObject()     , eobj);
        RelatedObject r330_2    = RelatedObject.createInstance(wider3300Rel.getObject()     , eobj);
        RelatedObject switchOff = RelatedObject.createInstance(schalter1XAusRel.getObject() , eobj);
        RelatedObject volt5     = RelatedObject.createInstance(volt5Rel.getObject()         , eobj);

        // interne verkabelung erzeugen
        //
        Connection.createInstance(r330_1, 1, volt5,  1);
        Connection.createInstance(r330_2, 1, volt5,  1);
        Connection.createInstance(r330_1, 2, switchOff,  1);
        Connection.createInstance(r330_2, 2, switchOff,  2);

        // interne pins an das 'gehäuse' legen
        MacroPinMapping.createInstance(1, switchOff, 1, eobj);
        MacroPinMapping.createInstance(2, switchOff, 2, eobj);
    }

      /**
       *
       */
      private static void createOBJ_D_R_T_3_2()
      {
         // Objekt mit Gehäuse erzeugen
         //
         ElectricObject eobj   = ElectricObject.createInstance(0,"OBJ_D_R_T_3_2");
         ElectricObject relObj = ElectricObject.findByType("OBJ_D_SR_T_4_2");

         // Abhängigkeiten erzeugen
         //
         RelatedObject d_sr  = RelatedObject.createInstance(relObj               , eobj);
         RelatedObject volt5 = RelatedObject.createInstance(volt5Rel.getObject() , eobj);

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
      private static void createLED_BAR_red_1_0()
      {
         // Objekt mit Gehäuse erzeugen
         //
         ElectricObject eobj   = ElectricObject.createInstance(0,"LED-Bar (red)_1_0");
         ElectricObject relObj = ElectricObject.findByType("LED");

         // Abhängigkeiten erzeugen
         //
         RelatedObject bar1  = RelatedObject.createInstance(relObj  , eobj);

         MacroPinMapping.createInstance(1, bar1, 1, eobj);
      }

      /**
       *
       */
      private static void createLED_BAR_red_2_0()
      {
         // Objekt mit Gehäuse erzeugen
         //
         ElectricObject eobj   = ElectricObject.createInstance(0,"LED-Bar (red)_2_0");
         ElectricObject relObj = ElectricObject.findByType("LED");

         // Abhängigkeiten erzeugen
         //
         RelatedObject bar1  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar2  = RelatedObject.createInstance(relObj  , eobj);

         MacroPinMapping.createInstance(1, bar1, 1, eobj);
         MacroPinMapping.createInstance(1, bar2, 2, eobj);
      }
      /**
       *
       */
      private static void createLED_BAR_red_3_0()
      {
         // Objekt mit Gehäuse erzeugen
         //
         ElectricObject eobj   = ElectricObject.createInstance(0,"LED-Bar (red)_3_0");
         ElectricObject relObj = ElectricObject.findByType("LED");

         // Abhängigkeiten erzeugen
         //
         RelatedObject bar1  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar2  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar3  = RelatedObject.createInstance(relObj  , eobj);

         MacroPinMapping.createInstance(1, bar1, 1, eobj);
         MacroPinMapping.createInstance(1, bar2, 2, eobj);
         MacroPinMapping.createInstance(1, bar3, 3, eobj);
      }
      /**
       *
       */
      private static void createLED_BAR_red_4_0()
      {
         // Objekt mit Gehäuse erzeugen
         //
         ElectricObject eobj   = ElectricObject.createInstance(0,"LED-Bar (red)_4_0");
         ElectricObject relObj = ElectricObject.findByType("LED");

         // Abhängigkeiten erzeugen
         //
         RelatedObject bar1  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar2  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar3  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar4  = RelatedObject.createInstance(relObj  , eobj);

         MacroPinMapping.createInstance(1, bar1, 1, eobj);
         MacroPinMapping.createInstance(1, bar2, 2, eobj);
         MacroPinMapping.createInstance(1, bar3, 3, eobj);
         MacroPinMapping.createInstance(1, bar4, 4, eobj);
      }
      /**
       *
       */
      private static void createLED_BAR_red_5_0()
      {
         // Objekt mit Gehäuse erzeugen
         //
         ElectricObject eobj   = ElectricObject.createInstance(0,"LED-Bar (red)_5_0");
         ElectricObject relObj = ElectricObject.findByType("LED");

         // Abhängigkeiten erzeugen
         //
         RelatedObject bar1  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar2  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar3  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar4  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar5  = RelatedObject.createInstance(relObj  , eobj);

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
      private static void createLED_BAR_red_6_0()
      {
         // Objekt mit Gehäuse erzeugen
         //
         ElectricObject eobj   = ElectricObject.createInstance(0,"LED-Bar (red)_6_0");
         ElectricObject relObj = ElectricObject.findByType("LED");

         // Abhängigkeiten erzeugen
         //
         RelatedObject bar1  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar2  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar3  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar4  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar5  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar6  = RelatedObject.createInstance(relObj  , eobj);

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
      private static void createLED_BAR_red_7_0()
      {
         // Objekt mit Gehäuse erzeugen
         //
         ElectricObject eobj   = ElectricObject.createInstance(0,"LED-Bar (red)_7_0");
         ElectricObject relObj = ElectricObject.findByType("LED");

         // Abhängigkeiten erzeugen
         //
         RelatedObject bar1  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar2  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar3  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar4  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar5  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar6  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar7  = RelatedObject.createInstance(relObj  , eobj);

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
      private static void createLED_BAR_red_8_0()
      {
         // Objekt mit Gehäuse erzeugen
         //
         ElectricObject eobj   = ElectricObject.createInstance(0,"LED-Bar (red)_8_0");
         ElectricObject relObj = ElectricObject.findByType("LED");

         // Abhängigkeiten erzeugen
         //
         RelatedObject bar1  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar2  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar3  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar4  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar5  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar6  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar7  = RelatedObject.createInstance(relObj  , eobj);
         RelatedObject bar8  = RelatedObject.createInstance(relObj  , eobj);

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
       *
       */
      private static void createGND_0_1()
      {
         // Objekt mit Gehäuse erzeugen
         //
         ElectricObject eobj   = ElectricObject.createInstance(0,"GND_0_1");

         // Abhängigkeiten erzeugen
         //
         RelatedObject volt5 = RelatedObject.createInstance(volt5Rel.getObject() , eobj);

         MacroPinMapping.createInstance(2, volt5, 1, eobj);
      }

      /**
       *
       */
      private static void createHigh_0_1()
      {
         // Objekt mit Gehäuse erzeugen
         //
         ElectricObject eobj   = ElectricObject.createInstance(0,"High_0_1");

         // Abhängigkeiten erzeugen
         //
         RelatedObject volt5 = RelatedObject.createInstance(volt5Rel.getObject() , eobj);

         MacroPinMapping.createInstance(1, volt5, 1, eobj);
      }

      /**
       *
       */
      private static void createOBJ_D_T_2_2()
      {
         // Objekt mit Gehäuse erzeugen
         //
         ElectricObject eobj   = ElectricObject.createInstance(0,"OBJ_D_T_2_2");
         ElectricObject relObj = ElectricObject.findByType("OBJ_D_SR_T_4_2");

         // Abhängigkeiten erzeugen
         //
         RelatedObject d_sr  = RelatedObject.createInstance(relObj               , eobj);
         RelatedObject volt5 = RelatedObject.createInstance(volt5Rel.getObject() , eobj);

         Connection.createInstance(d_sr , 1, volt5, 1);
         Connection.createInstance(d_sr , 4, volt5, 1);

         MacroPinMapping.createInstance(2, d_sr, 1, eobj);
         MacroPinMapping.createInstance(3, d_sr, 2, eobj);
         MacroPinMapping.createInstance(5, d_sr, 3, eobj);
         MacroPinMapping.createInstance(6, d_sr, 4, eobj);
      }

    /**
     *
     */
    private static void createOBJ_T_1_2()
    {
        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_T_1_2");
        ElectricObject jkObj = ElectricObject.findByType("OBJ_D_J!K_SR_T_5_2");

        // Abhängigkeiten erzeugen
        //
        RelatedObject jk    = RelatedObject.createInstance(jkObj               , eobj);
        RelatedObject volt5 = RelatedObject.createInstance(volt5Rel.getObject(), eobj);

        Connection.createInstance(volt5 , 1, jk, 1); // J auf High legen
        Connection.createInstance(volt5 , 2, jk, 4); // !K auf Low legen
        Connection.createInstance(volt5 , 1, jk, 1); // !Set auf High legen
        Connection.createInstance(volt5 , 1, jk, 5); // !Reset auf High legen

        MacroPinMapping.createInstance(3, jk  , 1, eobj); // C
        MacroPinMapping.createInstance(6, jk  , 4, eobj); // Q
        MacroPinMapping.createInstance(7, jk  , 5, eobj); // !Q
    }

    /**
     *
     */
    private static void createOBJ_TAKT_0_1()
    {
        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_TAKT_0_1");

        // Abhängigkeiten erzeugen
        //
        RelatedObject r1   = RelatedObject.createInstance(wider1000Rel.getObject(), eobj);
        RelatedObject r2   = RelatedObject.createInstance(trimmer100kRel.getObject(), eobj);
        RelatedObject r3   = RelatedObject.createInstance(wider1000Rel.getObject(), eobj);
        RelatedObject r4   = RelatedObject.createInstance(trimmer100kRel.getObject(), eobj);
        RelatedObject r5   = RelatedObject.createInstance(wider4700Rel.getObject(), eobj);

        RelatedObject d1   = RelatedObject.createInstance(diode1N914Rel.getObject(), eobj);
        RelatedObject d2   = RelatedObject.createInstance(diode1N914Rel.getObject(), eobj);

        RelatedObject c1   = RelatedObject.createInstance(kondensator10nRel.getObject(), eobj);
        RelatedObject c2   = RelatedObject.createInstance(kondensator10nRel.getObject(), eobj);

        RelatedObject ne   = RelatedObject.createInstance(ne555Rel.getObject(), eobj);

        RelatedObject volt5 = RelatedObject.createInstance(volt5Rel.getObject()    , eobj);

        Connection.createInstance(r5 ,  2, ne,    3);
        Connection.createInstance(r5,   1, volt5, 1);
        Connection.createInstance(ne,   8, volt5, 1);
        Connection.createInstance(ne,   4, volt5, 1);
        Connection.createInstance(ne,   1, volt5, 2);
        Connection.createInstance(ne,   5, c2   , 1);
        Connection.createInstance(c2,   2, volt5, 2);
        Connection.createInstance(c1,   1, ne   , 2);
        Connection.createInstance(c1,   2, c2   , 2);
        Connection.createInstance(ne,   2, ne   , 6);
        Connection.createInstance(d1,   2, ne   , 6);
        Connection.createInstance(r4,   3, d1   , 2);
        Connection.createInstance(r4,   2, r4   , 3);
        Connection.createInstance(r4,   1, r3   , 1);
        Connection.createInstance(r3,   2, d2   , 1);
        Connection.createInstance(d2,   2, ne   , 7);
        Connection.createInstance(d1,   1, ne   , 7);
        Connection.createInstance(r2,   2, ne   , 7);
        Connection.createInstance(r2,   3, ne   , 7);
        Connection.createInstance(r2,   1, r1   , 2);
        Connection.createInstance(r1,   1, ne   , 4);
        Connection.createInstance(r4,   3, r4   , 2);

        MacroPinMapping.createInstance(3, ne, 1, eobj);  // takt
    }

    /**
     *
     */
    private static void createOBJ_JK_T_3_2()
    {
        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_JK_T_3_2");
        ElectricObject jkObj = ElectricObject.findByType("OBJ_D_J!K_SR_T_5_2");
        ElectricObject notObj = ElectricObject.findByType("OBJ_NOT_1_1");

        // Abhängigkeiten erzeugen
        //
        RelatedObject jk    = RelatedObject.createInstance(jkObj               , eobj);
        RelatedObject not   = RelatedObject.createInstance(notObj              , eobj);
        RelatedObject volt5 = RelatedObject.createInstance(volt5Rel.getObject(), eobj);

        Connection.createInstance(jk , 4, not, 2);
        Connection.createInstance(volt5 , 1, jk, 1); // !Set auf High legen
        Connection.createInstance(volt5 , 1, jk, 5); // !Reset auf High legen

        MacroPinMapping.createInstance(2, jk  , 1, eobj); // J
        MacroPinMapping.createInstance(3, jk  , 2, eobj); // C
        MacroPinMapping.createInstance(1, not , 3, eobj); // K
        MacroPinMapping.createInstance(6, jk  , 4, eobj); // Q
        MacroPinMapping.createInstance(7, jk  , 5, eobj); // !Q
    }

    /**
     *
     */
    private static void createOBJ_JK_R_T_4_2()
    {
        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_JK_R_T_4_2");
        ElectricObject jkObj = ElectricObject.findByType("OBJ_D_J!K_SR_T_5_2");
        ElectricObject notObj = ElectricObject.findByType("OBJ_NOT_1_1");

        // Abhängigkeiten erzeugen
        //
        RelatedObject jk    = RelatedObject.createInstance(jkObj               , eobj);
        RelatedObject not   = RelatedObject.createInstance(notObj              , eobj);
        RelatedObject volt5 = RelatedObject.createInstance(volt5Rel.getObject(), eobj);

        Connection.createInstance(jk , 4, not, 2);
        Connection.createInstance(volt5 , 1, jk, 1); // !Set auf High legen

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
    private static void createOBJ_JK_SR_T_5_2()
    {
        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_JK_SR_T_5_2");
        ElectricObject jkObj = ElectricObject.findByType("OBJ_D_J!K_SR_T_5_2");
        ElectricObject notObj = ElectricObject.findByType("OBJ_NOT_1_1");

        // Abhängigkeiten erzeugen
        //
        RelatedObject jk    = RelatedObject.createInstance(jkObj               , eobj);
        RelatedObject not   = RelatedObject.createInstance(notObj              , eobj);

        Connection.createInstance(jk , 4, not, 2);

        MacroPinMapping.createInstance(1, jk  , 1, eobj);  // !Set
        MacroPinMapping.createInstance(2, jk  , 2, eobj);  // J
        MacroPinMapping.createInstance(3, jk  , 3, eobj);  // C
        MacroPinMapping.createInstance(1, not , 4, eobj);  // K
        MacroPinMapping.createInstance(5, jk  , 5, eobj);  // !Reset
        MacroPinMapping.createInstance(6, jk  , 6, eobj);  // Q
        MacroPinMapping.createInstance(7, jk  , 7, eobj);  // !Q
    }
    /**
     *            470 Ohm
     *           ______
     *  --------|______|-----
     *  pin 1             pin 2
     */
    private static void createResistor470()
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);

        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"470 OHM");
        ElectricCase   c    = ElectricCase.createInstance("Widerstand 470 Ohm","http://...",cl);
        wider470Rel = Object2Case.createInstance(c, eobj);

        // Objektlayout im Gehäuse erzeugen
        //
        ObjectPin    op11 = ObjectPin.createInstance(wider470Rel,"", 1,cp01);
        ObjectPin    op12 = ObjectPin.createInstance(wider470Rel,"", 2,cp02);

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
        CasePin     cp01  = CasePin.createInstance(0, "",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);

        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"SWITCH1XOFF");
        ElectricCase   c    = ElectricCase.createInstance("Schalter 1 x Aus","http://...",cl);
        schalter1XAusRel = Object2Case.createInstance(c, eobj);

        // Objektlayout im Gehäuse erzeugen
        //
        ObjectPin    op11 = ObjectPin.createInstance(schalter1XAusRel,"", 1,cp01);
        ObjectPin    op12 = ObjectPin.createInstance(schalter1XAusRel,"", 2,cp02);
    }

    /**
     *            3.3 kOhm
     *           ______
     *  --------|______|-----
     *  pin 1             pin 2
     */
    private static void createResistor3300()
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);

        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"3300 OHM");
        ElectricCase   c    = ElectricCase.createInstance("Widerstand 3.3 kOhm","http://...",cl);
        wider3300Rel = Object2Case.createInstance(c, eobj);

        // Objektlayout im Gehäuse erzeugen
        //
        ObjectPin    op11 = ObjectPin.createInstance(wider3300Rel,"", 1,cp01);
        ObjectPin    op12 = ObjectPin.createInstance(wider3300Rel,"", 2,cp02);

    }

    /**
     *            1.0 kOhm
     *           ______
     *  --------|______|-----
     *  pin 1             pin 2
     */
    private static void createResistor1000()
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);

        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"1000 OHM");
        ElectricCase   c    = ElectricCase.createInstance("Widerstand 1.0 kOhm","http://...",cl);
        wider1000Rel = Object2Case.createInstance(c, eobj);

        // Objektlayout im Gehäuse erzeugen
        //
        ObjectPin    op11 = ObjectPin.createInstance(wider1000Rel,"", 1,cp01);
        ObjectPin    op12 = ObjectPin.createInstance(wider1000Rel,"", 2,cp02);
    }

   /**
     *            4.7 kOhm
     *           ______
     *  --------|______|-----
     *  pin 1             pin 2
     */
    private static void createResistor4700()
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);

        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"4700 OHM");
        ElectricCase   c    = ElectricCase.createInstance("Widerstand 4.7 kOhm","http://...",cl);
        wider4700Rel = Object2Case.createInstance(c, eobj);

        // Objektlayout im Gehäuse erzeugen
        //
        ObjectPin    op11 = ObjectPin.createInstance(wider4700Rel,"", 1,cp01);
        ObjectPin    op12 = ObjectPin.createInstance(wider4700Rel,"", 2,cp02);
    }

   /**
     *     Kondensator 10 nF
     *
     *       ------||-----
     *  pin 1             pin 2
     */
    private static void createKondensator10n()
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "",2,cl,0);

        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"c10nF");
        ElectricCase   c    = ElectricCase.createInstance("Kondensator 10 nF","http://...",cl);
        kondensator10nRel = Object2Case.createInstance(c, eobj);

        // Objektlayout im Gehäuse erzeugen
        //
        ObjectPin    op11 = ObjectPin.createInstance(kondensator10nRel,"", 1,cp01);
        ObjectPin    op12 = ObjectPin.createInstance(kondensator10nRel,"", 2,cp02);
    }


   /**
     *    Diode 1N914
     *
     * (Anode)  |\     (Kathode)
     *    ______| \|______
     *          | /|
     *  pin 1   |/          pin 2
     */
    private static void createDiode1N914()
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "Anode",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "Kathode",2,cl,0);

        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"1N914");
        ElectricCase   c    = ElectricCase.createInstance("Diode 1N914","http://...",cl);
        diode1N914Rel = Object2Case.createInstance(c, eobj);

        // Objektlayout im Gehäuse erzeugen
        //
        ObjectPin    op11 = ObjectPin.createInstance(diode1N914Rel,"Anode"  , 1,cp01);
        ObjectPin    op12 = ObjectPin.createInstance(diode1N914Rel,"Kathode", 2,cp02);
    }

   /**
     *            4.7 kOhm
     *           ______
     *  --------|______|-----
     *  pin 1             pin 2
     */
    private static void createTrimmer100k()
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "Eingang" ,1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "Abnehmer",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "Eingang" ,3,cl,0);

        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"p100 kOHM");
        ElectricCase   c    = ElectricCase.createInstance("Trimmer 100 kOhm","http://...",cl);
        trimmer100kRel = Object2Case.createInstance(c, eobj);

        // Objektlayout im Gehäuse erzeugen
        //
        ObjectPin    op11 = ObjectPin.createInstance(trimmer100kRel,"Eingang", 1,cp01);
        ObjectPin    op12 = ObjectPin.createInstance(trimmer100kRel,"Abnehmer", 2,cp02);
        ObjectPin    op13 = ObjectPin.createInstance(trimmer100kRel,"Eingang", 3,cp03);
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
         CasePin     cp01  = CasePin.createInstance(0, "Pin 1" ,1,cl,0);
         CasePin     cp02  = CasePin.createInstance(0, "Pin 2" ,2,cl,0);
         CasePin     cp03  = CasePin.createInstance(0, "Pin 3" ,3,cl,0);
         CasePin     cp04  = CasePin.createInstance(0, "Pin 4" ,4,cl,0);
         CasePin     cp05  = CasePin.createInstance(0, "Pin 5" ,5,cl,0);
         CasePin     cp06  = CasePin.createInstance(0, "Pin 6" ,6,cl,0);
         CasePin     cp07  = CasePin.createInstance(0, "Pin 7" ,7,cl,0);
         CasePin     cp08  = CasePin.createInstance(0, "Pin 8" ,8,cl,0);

         // Objekt mit Gehäuse erzeugen
         //
         ElectricObject eobj = ElectricObject.createInstance(0,"O_INTERFACE_8_0");
         ElectricCase   c    = ElectricCase.createInstance("Steckleiste mit 8 Leitungen (Ausgang)","http://...",cl);
         Object2Case o2c = Object2Case.createInstance(c, eobj);

         // Objektlayout im Gehäuse erzeugen
         //
         ObjectPin.createInstance(o2c,"Pin 1", 1,cp01);
         ObjectPin.createInstance(o2c,"Pin 2", 2,cp02);
         ObjectPin.createInstance(o2c,"Pin 3", 3,cp03);
         ObjectPin.createInstance(o2c,"Pin 4", 4,cp04);
         ObjectPin.createInstance(o2c,"Pin 5", 5,cp05);
         ObjectPin.createInstance(o2c,"Pin 6", 6,cp06);
         ObjectPin.createInstance(o2c,"Pin 7", 7,cp07);
         ObjectPin.createInstance(o2c,"Pin 8", 8,cp08);
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
         CasePin     cp01  = CasePin.createInstance(0, "Pin 1" ,1,cl,0);
         CasePin     cp02  = CasePin.createInstance(0, "Pin 2" ,2,cl,0);
         CasePin     cp03  = CasePin.createInstance(0, "Pin 3" ,3,cl,0);
         CasePin     cp04  = CasePin.createInstance(0, "Pin 4" ,4,cl,0);
         CasePin     cp05  = CasePin.createInstance(0, "Pin 5" ,5,cl,0);
         CasePin     cp06  = CasePin.createInstance(0, "Pin 6" ,6,cl,0);
         CasePin     cp07  = CasePin.createInstance(0, "Pin 7" ,7,cl,0);
         CasePin     cp08  = CasePin.createInstance(0, "Pin 8" ,8,cl,0);

         // Objekt mit Gehäuse erzeugen
         //
         ElectricObject eobj = ElectricObject.createInstance(0,"I_INTERFACE_0_8");
         ElectricCase   c    = ElectricCase.createInstance("Steckleiste mit 8 Leitungen (Eingang)","http://...",cl);
         Object2Case o2c = Object2Case.createInstance(c, eobj);

         // Objektlayout im Gehäuse erzeugen
         //
         ObjectPin.createInstance(o2c,"Pin 1", 1,cp01);
         ObjectPin.createInstance(o2c,"Pin 2", 2,cp02);
         ObjectPin.createInstance(o2c,"Pin 3", 3,cp03);
         ObjectPin.createInstance(o2c,"Pin 4", 4,cp04);
         ObjectPin.createInstance(o2c,"Pin 5", 5,cp05);
         ObjectPin.createInstance(o2c,"Pin 6", 6,cp06);
         ObjectPin.createInstance(o2c,"Pin 7", 7,cp07);
         ObjectPin.createInstance(o2c,"Pin 8", 8,cp08);
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
    private static void createNE555()
    {
        // generate the Caselayout
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "GND",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "Trigger",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "Out",3,cl,0);
        CasePin     cp04  = CasePin.createInstance(0, "Reset",4,cl,0);
        CasePin     cp05  = CasePin.createInstance(0, "Steuerspannung",5,cl,0);
        CasePin     cp06  = CasePin.createInstance(0, "Schwelle",6,cl,0);
        CasePin     cp07  = CasePin.createInstance(0, "Entladung",7,cl,0);
        CasePin     cp08  = CasePin.createInstance(0, "VCC",8,cl,0);

        // generate the object and the case
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"NE555"); //
        ElectricCase   c     = ElectricCase.createInstance("Timmerbaustein NE555","http://www.e-online.de/public/schaerer/timer555.htm",cl);
        ne555Rel = Object2Case.createInstance(c, eobj);

        // generate the internal object layout
        //
        ObjectPin      op11 = ObjectPin.createInstance(ne555Rel, "GND"           ,1,cp01);
        ObjectPin      op12 = ObjectPin.createInstance(ne555Rel, "Trigger"       ,2,cp02);
        ObjectPin      op13 = ObjectPin.createInstance(ne555Rel, "Out"           ,3,cp03);
        ObjectPin      op14 = ObjectPin.createInstance(ne555Rel, "Reset"         ,4,cp04);
        ObjectPin      op15 = ObjectPin.createInstance(ne555Rel, "Steuerspannung",5,cp05);
        ObjectPin      op16 = ObjectPin.createInstance(ne555Rel, "Schwelle"      ,6,cp06);
        ObjectPin      op17 = ObjectPin.createInstance(ne555Rel, "Entladung"     ,7,cp07);
        ObjectPin      op18 = ObjectPin.createInstance(ne555Rel, "VCC"           ,8,cp08);
    }



   /**
     *        Leuchtdiode
     *
     * (Anode)  |\ //   (Kathode)
     *    ______| \|______
     *          | /|
     *  pin 1   |/          pin 2
     */
    private static void createLED()
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "Anode",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "Kathode",2,cl,0);

        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"LED");
        ElectricCase   c    = ElectricCase.createInstance("Leuchtdiode","http://...",cl);
        ledRel = Object2Case.createInstance(c, eobj);

        // Objektlayout im Gehäuse erzeugen
        //
        ObjectPin    op11 = ObjectPin.createInstance(ledRel,"Anode"  ,1,cp01);
        ObjectPin    op12 = ObjectPin.createInstance(ledRel,"Kathode",2,cp02);

    }


    /**
     *
     */
    private static void createOBJ_LED()
    {
        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_LED_1_0");

        // Abhängigkeiten erzeugen
        //
        RelatedObject r330 = RelatedObject.createInstance(wider3300Rel.getObject(), eobj);
        RelatedObject r470 = RelatedObject.createInstance(wider470Rel.getObject() , eobj);
        RelatedObject t107 = RelatedObject.createInstance(tBC107Rel.getObject()   , eobj);
        RelatedObject led = RelatedObject.createInstance(ledRel.getObject()      , eobj);
        RelatedObject volt5 = RelatedObject.createInstance(volt5Rel.getObject()    , eobj);

        Connection.createInstance(led , 2, volt5, 2);
        Connection.createInstance(r470, 1, volt5, 1);
        Connection.createInstance(r470, 2, t107,  2);
        Connection.createInstance(t107, 3, led,   1);
        Connection.createInstance(r330, 2, t107,  1);

        MacroPinMapping.createInstance(1, r330, 1, eobj);
    }

    private static void createOBJ_POWER()
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "Eingang 1 (VCC)",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "Eingang 2 (GND)",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "Ausgang"  ,3,cl,0);

        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_POWER_0_1");
        ElectricCase   c    = ElectricCase.createInstance("1 x Umschalter","http://...",cl);
        Object2Case c2o=Object2Case.createInstance(c, eobj);

        // Objektlayout im Gehäuse erzeugen
        //
        ObjectPin    op11 = ObjectPin.createInstance(c2o,"Ausgang"  , 1, cp03);
        ObjectPin    op12 = ObjectPin.createInstance(c2o,"Eingang 1 (VCC)", 2, cp01);
        ObjectPin    op13 = ObjectPin.createInstance(c2o,"Eingang 2 (GND)", 3, cp02);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(1));  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(2)); // Minuspool
    }

    private static void createOBJ_POWERTASTER0()
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "Eingang 1"                   ,1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "Eingang 2 (default Stellung)",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "Ausgang"                     ,3,cl,0);

        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_POWERTASTER0_0_1");
        ElectricCase   c    = ElectricCase.createInstance("1 x Um Taster (GND default)","http://...",cl);
        Object2Case c2o=Object2Case.createInstance(c, eobj);

        // Objektlayout im Gehäuse erzeugen
        //
        ObjectPin    op11 = ObjectPin.createInstance(c2o,"Eingang 1"                   , 1, cp03);
        ObjectPin    op12 = ObjectPin.createInstance(c2o,"Eingang 2 (default Stellung)", 2, cp02);
        ObjectPin    op13 = ObjectPin.createInstance(c2o,"Ausgang"                     , 3, cp01);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(1));
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(2));
    }

    private static void createOBJ_POWERTASTER1()
    {
        // Gehäuselayout erzeugen
        //
        CaseLayout    cl  = CaseLayout.createInstance();
        CasePin     cp01  = CasePin.createInstance(0, "Eingang 1",1,cl,0);
        CasePin     cp02  = CasePin.createInstance(0, "Eingang 2 (default Stellung)",2,cl,0);
        CasePin     cp03  = CasePin.createInstance(0, "Ausgang"  ,3,cl,0);

        // Objekt mit Gehäuse erzeugen
        //
        ElectricObject eobj = ElectricObject.createInstance(0,"OBJ_POWERTASTER1_0_1");
        ElectricCase   c    = ElectricCase.createInstance("1 x Um Taster (VCC default)","http://...",cl);
        Object2Case c2o=Object2Case.createInstance(c, eobj);

        // Objektlayout im Gehäuse erzeugen
        //
        ObjectPin    op11 = ObjectPin.createInstance(c2o,"Eingang 1", 1, cp01);
        ObjectPin    op12 = ObjectPin.createInstance(c2o,"Eingang 2 (default Stellung)", 2, cp02);
        ObjectPin    op13 = ObjectPin.createInstance(c2o,"Ausgang"  , 3, cp03);

        // Abhängigkeiten erzeugen
        //
        CaseDependency cd = CaseDependency.createInstance(c,volt5Rel.getObject());

        // +5 Volt an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(1),c.getPin(2));  // Pluspool
        // Masse an das Gehäuse legen
        DependencyPin.createInstance(cd,volt5Rel.getPin(2),c.getPin(1)); // Minuspool
    }
}

