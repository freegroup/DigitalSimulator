package de.freegroup.test;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import java.net.URL;

public class URLPerformanceTest
{
    final static int ITERATION_COUNT = 1000000;

    public static void main(String[] args)
    {
        long start1 =System.currentTimeMillis();
        for(int i = 0; i<ITERATION_COUNT; i++)
        {
            try {
                new URL("http://" + "www.urgs.de");

            }
            catch (Exception ex)
            {
                System.out.println("ERROR: "+ex);
            }
        }
        long end1 = System.currentTimeMillis();
        System.out.println("duration :"+((end1-start1)/1000.0));

        long start2 =System.currentTimeMillis();
        for(int i = 0; i<ITERATION_COUNT; i++)
        {
            try {
                new URL("http", "www.urgs.de",80,"/");

            }
            catch (Exception ex)
            {
                System.out.println("ERROR: "+ex);
            }
        }
        long end2 = System.currentTimeMillis();
        System.out.println("duration :"+((end2-start2)/1000.0));
    }
}