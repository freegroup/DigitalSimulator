package de.freegroup.util.dbgenerator;
/**
 * Title:        short-i
 * Description:  Information retrival System with human language interface
 * Copyright:    Copyright (c) 2001
 * Company:      short-i
 * @author David Sommer & Andreas Herz
 * @version 1.0
 */

public class ReversePropertyClass
{
    String  reverseClass;
    String  reverseProperty;
    boolean unique     = false;

    public ReversePropertyClass(String _reverseClass, String _reverseProperty, boolean isUnique)
    {
        reverseClass    = _reverseClass;
        reverseProperty = _reverseProperty;
        unique          = isUnique;
    }

    public boolean getUnique()
    {
        return unique;
    }

    public String getReverseClass()
    {
        return reverseClass;
    }

    public String getReverseProperty()
    {
        return reverseProperty;
    }
}