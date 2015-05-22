/*
 * Created on Jan 27, 2004
 * 
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.test;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Enumeration;
import javax.comm.*;
import javax.comm.ParallelPort;

public class CommTest
{
	public static void main(String[] args)
	{
    		CommPortIdentifier portId;
				try
				{
          portId = (CommPortIdentifier)CommPortIdentifier.getPortIdentifier("LPT1");
          ParallelPort port = (ParallelPort) portId.open("DigitalSimulator", 3000);
          port.setMode(ParallelPort.LPT_MODE_SPP);
          
          DataOutputStream  stream = new DataOutputStream(port.getOutputStream());
          
          for(int i =0;i<256;i++)
          {
            stream.write(i); //------- Statement 1
            System.out.println(i);
            Thread.sleep(100);
            if(i==255)i=0;
          }
        }
				catch (Exception e)
				{
					e.printStackTrace();
				}
	}
}
