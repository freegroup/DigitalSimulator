package de.freegroup.test;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import de.freegroup.util.CallStack;
public class CallStackTest {

    public static void main(String[] args)
    {
        CallStack cs = new CallStack();

        new Exception();
        System.out.println(cs.getCurrentMethod());
    }
}