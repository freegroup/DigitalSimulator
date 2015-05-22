package de.freegroup.digitalsimulator.export.wired.util.generator.sql;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */

public class TableColumn
{
    String name;
    String type;
    int    size;
    boolean nullAble   = false;
    boolean primaryKey = false;
    boolean unique     = false;

    public TableColumn(String _name, String _type, int _size)
    {
        name  = _name;
        type  = _type;
        size  = _size>255?257:_size;
        if(type.equalsIgnoreCase("VARCHAR"))
            type = type+"("+size+")";
    }

    public void setNullAble(boolean _nullAble)
    {
        nullAble = _nullAble;
    }

    public void setPrimaryKey(boolean _primaryKey )
    {
        primaryKey = _primaryKey;
    }

    public boolean getPrimaryKey()
    {
        return primaryKey;
    }

    public void setUnique(boolean _unique )
    {
        unique = _unique;
    }


    public boolean getUnique()
    {
        return unique;
    }

    public String getName()
    {
        return name;
    }


    public String toString()
    {
        if(nullAble)
            return name + "  " + type ;

        return name + "  " + type + "  NOT NULL ";
    }
}