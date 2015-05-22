package de.freegroup.util.clazz;

import java.io.*;

public class FormattedFileWriter
{
	private String fileName = null;
	private FileWriter writer = null;
	private int tabLevel = 0;
	private boolean needsTabs = true;

   public FormattedFileWriter(String fileName)
		throws IOException
   {
		this.fileName = fileName;
		writer = new FileWriter( fileName );
   }

	public void flush()
		throws IOException
	{
		writer.flush();
	}

	public void close()
		throws IOException
	{
		writer.close();
	}

	public void incTabLevel()
	{
		++tabLevel;
	}

	public void decTabLevel()
	{
		--tabLevel;
	}

	public void output(String line)
		throws IOException
	{
		if ( needsTabs == true )
		{
			for ( int i = tabLevel; i > 0; --i )
	   		writer.write( "\t" );
			needsTabs = false;
		}

		writer.write( line );
	}

	public void outputLine(String line)
		throws IOException
	{
		output( line );
		writer.write( "\n" );
		needsTabs = true;
	}

	public void newLine(int numLines)
		throws IOException
	{
		for ( int i = numLines; i > 0; --i )
			writer.write( "\n" );
		needsTabs = true;
	}
}