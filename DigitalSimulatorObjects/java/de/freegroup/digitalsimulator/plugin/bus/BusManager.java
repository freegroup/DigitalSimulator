package de.freegroup.digitalsimulator.plugin.bus;

/**
 * Title:        DigitalSimulator java Pugins
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import java.util.*;
import de.freegroup.digitalsimulator.Trace;

public class BusManager
{
    private static HashMap busses = new HashMap();

    public static int[] getData(Integer busId)
    {
        try
        {
            if(busses.containsKey(busId))
                return (int[])busses.get(busId);
        }
        catch (Exception ex)
        {
            Trace.error("exception in getData:",ex);
        }
        return new int[8];
    }

    public static void setData(Integer busId, int[] data)
    {
        busses.put(busId, data);
    }
}