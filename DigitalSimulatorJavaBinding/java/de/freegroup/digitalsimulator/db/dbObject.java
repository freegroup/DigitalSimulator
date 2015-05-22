package de.freegroup.digitalsimulator.db;

import java.util.*;

public class dbObject
{
	protected static String toSQL(String input)
	{
        if(input==null)
        {
            return "";
        }
		StringBuffer erg = new StringBuffer(input);
		int pos = 0;
		while(pos < erg.length())
		{
			if(erg.charAt(pos) == '\'')
			{
				if(((pos+1)==erg.length()) || erg.charAt(pos+1) != '\'')
				{
					erg.insert(pos+1, '\'');
				}
				pos++;
			}
			pos++;
		}
		return erg.toString();
	}

	protected static String toSQL(java.sql.Date input)
	{
        if(input==null)
        {
            return "";
        }

        return input.toString();
	}

	protected static String toSQL(boolean input)
	{
        if(input)
            return "1";

        return "0";
	}
}
