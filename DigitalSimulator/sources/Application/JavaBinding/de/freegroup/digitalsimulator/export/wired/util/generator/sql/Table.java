package de.freegroup.digitalsimulator.export.wired.util.generator.sql;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */

/**
 * Title:        short-i
 * Description:  Information retrival System with human language interface
 * Copyright:    Copyright (c) 2001
 * Company:      short-i
 * @author Andreas Herz
 * @version 1.0
 */
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;

public class Table
{
    String  name ;
    String  primaryKey=null;
    HashMap  columns = new HashMap();

    /**
     *
     */
    public Table(String _name)
    {
        name = _name;
    }

    /**
     *
     */
    public void addColumn(String name, String type, int size)
    {
        columns.put(name, new TableColumn(name,type, size));
    }

    /**
     *
     */
    public void setPrimaryKey(String columnName)
    {
        TableColumn column =(TableColumn) columns.get(columnName);

        if(column != null)
        {
            primaryKey = columnName;
            column.setPrimaryKey(true);
        }
    }

    /**
     *
     */
    public void setUnique(String columnName)
    {
        TableColumn column =(TableColumn) columns.get(columnName);

        if(column != null)
            column.setUnique(true);
    }

    /**
     *
     */
    public String toString()
    {
        StringBuffer result = new StringBuffer(1024);
        result.append("\t\ttry {\n");
        result.append("\t\t\tstat.executeUpdate(\"DROP TABLE "+name+"\");\n");
        result.append("\t\t} catch(SQLException e) {}// Ignore Exception, because the table may not yet exist\n");

        Set propSet = columns.keySet();
        Iterator it = propSet.iterator();

        it = propSet.iterator();
        result.append("\t\tstat.execute(\"CREATE TABLE "+name+" (\"+\n");
        while(it.hasNext())
        {
            TableColumn column =(TableColumn) columns.get(it.next());
            result.append("\t\t\t\""+column.toString()+" , \"+\n");
        }
//        if(primaryKey !=null && !primaryKey.equals(""))
//            result.append("\t\t\t\"KEY    ("+primaryKey+") , \"+\n");

        // add the unique attributes
        //
        it = propSet.iterator();
        while(it.hasNext())
        {
            TableColumn column =(TableColumn) columns.get(it.next());
//            if(column.getUnique() && !column.getPrimaryKey())
//            {
//                result.append("\t\t\t\"UNIQUE ( ");
//                result.append(column.getName());
//                result.append("), \"+\n");
//            }
        }

        result.append("\t\t\t\"PRIMARY KEY    ("+primaryKey+"))\");\n");
        return result.toString();
    }
}