/*
 * Created on Jan 16, 2004
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.util.file;

import java.io.*;

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class Stream
{
  public static void copyStream(InputStream in, OutputStream out) throws IOException
  {
    synchronized(in)
    {
      synchronized(out)
      {
        byte[] buffer = new byte[256];
        while(true)
        {
          int bytesRead = in.read(buffer);
          if(bytesRead == -1)
            break;
          out.write(buffer, 0, bytesRead);
        }
      }
    }
  }
}