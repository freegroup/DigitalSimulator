package de.freegroup.util.clazz;

import java.util.*;

public class CommandLineParser
{
	private Map paramMap = new HashMap();

	public CommandLineParser(String[] args)
	{
		String currentArg = null, currentSwitch = null;
		char c = 0;
		boolean hasEntry = false;

		for ( int i = 0; i < args.length; ++i )
		{
			currentArg = args[i];
			c = currentArg.charAt( 0 );

			if ( (c == '-') || (c == '/') )
			{
				// put an empty string in for value of previous switch if there were no other values
				if ( (currentSwitch != null) && (hasEntry == false) )
				{
					paramMap.put( currentSwitch, "" );
					currentSwitch = null;
				}

				int eq = currentArg.indexOf( "=", 0 );
				if ( eq != -1 )
				{
					paramMap.put( currentArg.substring( 1, eq ), currentArg.substring( eq + 1 ) );
					currentSwitch = null;
				}
				else
				{
					currentSwitch = currentArg.substring( 1 );
					hasEntry = false;
				}
			}
			else
			{
				// hit a value with no matching switch
				if ( currentSwitch == null )
				; // throw

				// put the switch/value combination in the map
				paramMap.put( currentSwitch, currentArg );
				hasEntry = true;
			}

			if ( currentSwitch != null )
			if ( hasEntry == false )
			paramMap.put( currentSwitch, "" );
		}
	}

	public String getParamValue(String paramName)
	{
		return (String) paramMap.get( paramName );
	}

	public String toString()
	{
		return paramMap.toString();
	}
}
