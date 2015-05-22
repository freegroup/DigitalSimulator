// Decompiled by Jad v1.5.8e2. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://kpdus.tripod.com/jad.html
// Decompiler options: packimports(3) 

package de.freegroup.digitalsimulator.plugin.rs232;

import de.freegroup.digitalsimulator.Painter;
import de.freegroup.digitalsimulator.Trace;
import de.freegroup.digitalsimulator.dialogs.GenericDialog;
import de.freegroup.digitalsimulator.plugin.object.ObjectPlugin;
import de.freegroup.digitalsimulator.update.ILiveUpdateObject;
import java.io.DataOutputStream;
import java.io.FilterOutputStream;
import javax.comm.*;

// Referenced classes of package de.freegroup.digitalsimulator.plugin.rs232:
//            RS232Dialog

public class Output extends ObjectPlugin  implements ILiveUpdateObject
{
  static final int INPUT_COUNT = 8;
  static final int OUTPUT_COUNT = 0;
  static final int PARAM_COUNT = 1;
  static final int WIDTH = 150;
  static final int HEIGHT = 400;
  static DataOutputStream stream[] = new DataOutputStream[5];
  static ParallelPort port[] = new ParallelPort[5];
  static int openCount[] = new int[5];

  public boolean calculate(int ai[], int ai1[], int ai2[], byte abyte0[])
	{
		try
		{
			int i = (ai[0] <= 0 ? 0 : 1) + (ai[1] <= 0 ? 0 : 2) + (ai[2] <= 0 ? 0 : 4) + (ai[3] <= 0 ? 0 : 8) + (ai[4] <= 0 ? 0 : 16) + (ai[5] <= 0 ? 0 : 32) + (ai[6] <= 0 ? 0 : 64) + (ai[7] <= 0 ? 0 : 128);
			stream[abyte0[0]].write(i);
		}
		catch (Exception exception)
		{
			Trace.error(exception);
		}
		return false;
	}

  public boolean doConfigure(byte abyte0[])
	{
		try
		{
			RS232Dialog rs232dialog = new RS232Dialog(abyte0[0]);
			if (rs232dialog.isOk())
			{
				abyte0[0] = rs232dialog.getPortId();
				return true;
			}
		}
		catch (Throwable e)
		{
			Trace.error(e);
		}
		return false;
	}

    public String getDescription()
    {
        return "8-bit data bus\r\nselect the number of the bus to with you want connect\r\nThe information from the corresponding bus will be display\r\nat this output element.\r\nWith this object it is possible to avoid the wide range\r\nconnector over the circuit.";
    }

    public String getGroup()
    {
        return "OBJECTGROUP.BUS";
    }

    public int[] getInputCountRange()
    {
        int ai[] = new int[2];
        ai[0] = 8;
        ai[1] = 8;
        return ai;
    }

    public String getKey()
    {
        return "RS232 (output)";
    }

    public String getName()
    {
        return "OBJECT.RS232";
    }

    public int[] getOutputCountRange()
    {
        int ai[] = new int[2];
        ai[0] = 0;
        ai[1] = 0;
        return ai;
    }

    public int getParamCount()
    {
        return 1;
    }

    public String getProgrammerMail()
    {
        return "A.Herz@FreeGroup.de";
    }

    public String getProgrammerName()
    {
        return "Andreas Herz";
    }

    public String getProgrammerURL()
    {
        return "http://www.FreeGroup.de";
    }

    public int[] getSize(long l, long l1)
    {
        int ai[] = new int[2];
        ai[0] = 150;
        ai[1] = 400;
        return ai;
    }

    public int getVersion()
    {
        return 1;
    }

    public void init(byte abyte0[])
    {
        Trace.info("init1 id:" + abyte0[0]);
        Trace.info("init2 id:" + abyte0[0]);
    }

    public int[] layoutInput(int i, int j, byte abyte0[])
    {
        int ai[] = new int[2 * i];
        float f = 400F / (float)(i + 1);
        for(int k = 0; k < i * 2; k += 2)
        {
            ai[k] = 0;
            ai[k + 1] = -(int)(f + f * (float)(k / 2));
        }

        return ai;
    }

    public int[] layoutOutput(int i, int j, byte abyte0[])
    {
        int ai[] = new int[2 * j];
        float f = 400F / (float)(j + 1);
        for(int k = 0; k < j * 2; k += 2)
        {
            ai[k] = 150;
            ai[k + 1] = -(int)(f + f * (float)(k / 2));
        }

        return ai;
    }

    public boolean onButtonDblClick(int i, int j, byte abyte0[])
    {
        return doConfigure(abyte0);
    }

    public void onStartCalculate(byte abyte0[])
    {
        try
        {
            synchronized(openCount)
            {
                if(openCount[abyte0[0]] == 0)
                {
                    CommPortIdentifier commportidentifier = CommPortIdentifier.getPortIdentifier("LPT" + abyte0[0]);
                    port[abyte0[0]] = (ParallelPort)commportidentifier.open("DigitalSimulator", 3000);
                    port[abyte0[0]].setMode(1);
                    stream[abyte0[0]] = new DataOutputStream(port[abyte0[0]].getOutputStream());
                }
                openCount[abyte0[0]]++;
            }
        }
        catch(Exception exception)
        {
            Trace.error(exception);
        }
    }

    public void onStopCalculate(byte abyte0[])
    {
        try
        {
            synchronized(openCount)
            {
                openCount[abyte0[0]]--;
                if(openCount[abyte0[0]] == 0)
                {
                    port[abyte0[0]].close();
                    port[abyte0[0]] = null;
                    stream[abyte0[0]].close();
                    stream[abyte0[0]] = null;
                }
            }
        }
        catch(Throwable throwable)
        {
            Trace.error(throwable);
        }
    }

    public void paint(int x, int y, byte param[])
    {
        Painter.drawRect(x, y, x + 150, y - 400);
        Painter.drawText("Parallel", 55, x + 5, y - 50);
        Painter.drawText("Port", 55, x + 30, y - 100);
        Painter.drawText("LPT" + param[0], 45, x + 30, y - 190);
    }
}
