package de.freegroup.digitalsimulator.export.wired.util.generator.sql;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import java.io.*;
import java.util.*;
//import org.apache.oro.text.regex.*;
import java.io.*;
import java.lang.*;
import java.sql.*;
import de.freegroup.digitalsimulator.db.*;

public class Main
{
    final static String  OUT_PACKAGENAME = "de.freegroup.digitalsimulator.export.wired.util.db";
    final static String  OUT_DIRECTORY   = "D:\\FreeGroup\\DigitalSimulatorExports\\java";

    static HashMap       datatypes= null;

    static HashMap       tables         = null;

    static public void generate()
    {
        try
        {
//            String driver   = Config.getConfig("shorti").getProperty ("jdbc.driver.design");
//            String database = Config.getConfig("shorti").getProperty ("jdbc.database.design");
//            String user     = Config.getConfig("shorti").getProperty ("jdbc.user.design");
//            String password = Config.getConfig("shorti").getProperty ("jdbc.password.design");

            String driver          = "sun.jdbc.odbc.JdbcOdbcDriver";
            String database        = "jdbc:odbc:digital";
            String user            = "digital";
            String password        = "digital";

            System.out.println("--------------------------------------");
            System.out.println("initialize the ConnectionManager");
            System.out.println("--------------------------------------");
            System.out.println("   open connection to");
            System.out.println("   driver     :["+driver+"]");
            System.out.println("   database   :["+database+"]");
            System.out.println("   user       :["+user+"]");
            System.out.println("   password   :["+password+"]");

            java.lang.Class.forName( driver ).newInstance();
            SaveConnection cConn = new SaveConnection(DriverManager.getConnection( database, user , password ));

            SaveStatement stmt1 = cConn.createStatement("urgs");
            DatabaseMetaData dMeta = cConn.getMetaData ();
            dMeta=cConn.getMetaData();

            // retrieve all tables in the database
            //
            String usertables[]={"TABLE"};
            ResultSet result=dMeta.getTables(null,null,null,usertables);
            while(result.next())
            {
                String tableName = result.getString(3);
                if(!tableName.equals("dtproperties"))
                {
                    Table newClass = new Table(tableName);
                    tables.put(tableName,newClass);
                }
            }
            result.close();

            // generate all attributes for the classes
            //
            Iterator iter = tables.keySet().iterator();
            while(iter.hasNext())
            {
                String className = (String)iter.next();
                Table  outClass  = (Table)tables.get(className);
                ResultSet col=dMeta.getColumns(null,null,className,null);
                // properties
                //
                while(col.next())
                {
                    String  columnName   = col.getString("COLUMN_NAME");
                    String  type         = col.getString("TYPE_NAME");
                    int     datasize     = Integer.parseInt(col.getString("COLUMN_SIZE"));
                    String  digits       = col.getString("DECIMAL_DIGITS");
                    boolean nullable     = col.getInt(11)!=DatabaseMetaData.columnNoNulls;
                    StringTokenizer token = new StringTokenizer(type," ");
                    String propertyType = (String)datatypes.get(token.nextToken());
                    boolean isIdentity = false;

                    try
                    {
                        String identity = token.nextToken();
                        if(identity.equals("identity"))
                            isIdentity = true;
                    }
                    catch (Exception ex){}

                    if(propertyType==null)
                        System.out.println("unknown datatype:"+type);
                    outClass.addColumn(columnName, propertyType, datasize);
                }
                col.close();

                // primary keys
                //
                outClass.setPrimaryKey("id");

                // unique key
                //
                ResultSet ind=dMeta.getIndexInfo(null,null,className,false,false);
                while(ind.next())
                {
                    boolean unique = !ind.getBoolean(4);
                    String  iname  = ind.getString(6);
                    String  c      = ind.getString(9);
                    if((c!=null) && (unique==true) &&(!c.equalsIgnoreCase("id")))
                    {
                        outClass.setUnique(c);
                    }
                }
                ind.close();
            }

//            // forreign key
//            //
//            Iterator iterClass = tables.keySet().iterator();
//            while(iterClass.hasNext())
//            {
//                String name =(String) iterClass.next();
//                ResultSet r = dMeta.getExportedKeys( null, null, name ) ;
//                while(r.next())
//                {
//                    String fTable       = r.getString("FKTABLE_NAME");
//                    String fColumn      = r.getString("FKCOLUMN_NAME");
//                    Table  foreignClass = (Table) tables.get(fTable);
//
//                    foreignClass.setForeignKey(fColumn,name,"id");
//                }
//                r.close();
//            }


            // write output
            //
            writeCode();
        }
        catch(Exception exc)
        {
            System.out.println(exc);
        }
    }
    
    /**
     *
     */
    static String generateHeader()
    {
        StringBuffer classString = new StringBuffer(1024);
        java.sql.Date date = new java.sql.Date(System.currentTimeMillis());

        classString.append("package " + OUT_PACKAGENAME + ";\n");
        classString.append("\n");
        classString.append("/**\n");
        classString.append(" * short-i Class generated by automatic ClassGenerator\n");
        classString.append(" * Date: " +  date.toString() + "\n");
        classString.append(" */\n");
        classString.append("import java.util.ArrayList;\n");
        classString.append("import java.util.Iterator;\n");
        classString.append("import java.sql.*;\n\n");
        classString.append("import de.freegroup.digitalsimulator.db.*;\n\n");
        classString.append("public class CreateDB { \n");

        return classString.toString();
    }

    public static void writeCode() throws IOException
    {
        String fullPath = OUT_DIRECTORY ;

        fullPath.replace('/', '\\');
        if(!fullPath.endsWith("\\"))
        {
            fullPath += "\\";
        }
        fullPath += OUT_PACKAGENAME.replace('.', '\\');

        File dir = new File(fullPath);
        if (!dir.exists())
        {
            dir.mkdirs();
        }

        fullPath += "\\";
        fullPath += "CreateDB.java";

        File file = new File(fullPath);
        file.delete();
        FileWriter writer = new FileWriter(file);

        writer.write(generateHeader());
        writer.write("\tpublic static void main ( String[] args )\n");
        writer.write("\t{\n");
        writer.write("\t\ttry\n");
        writer.write("\t\t{\n");
        writer.write("\t\t\tSaveConnection conn=ConnectionManager.getValid();\n");
        writer.write("\t\t\tSaveStatement  stat=conn.createStatement(\"createDB\");\n");
        Iterator iter = tables.keySet().iterator();
        while(iter.hasNext())
        {
            Table outTable = (Table) tables.get(iter.next());
            writer.write(outTable.toString());
        }


        writer.write("\t\t\tstat.close();\n");
        writer.write("\t\t}\n");
        writer.write("\t\tcatch(Exception exc)\n");
        writer.write("\t\t{\n");
        writer.write("\t\t\tSystem.out.println(exc);\n");
        writer.write("\t\t\texc.printStackTrace();\n");
        writer.write("\t\t}\n");
        writer.write("\t}\n");
        writer.write("}\n");
        writer.flush();
        writer.close();
    }

    static
    {
        tables    = new HashMap();
        datatypes = new HashMap();
        datatypes.put("text"     , "VARCHAR");
        datatypes.put("varchar"  , "VARCHAR");
        datatypes.put("int"      , "int");
        datatypes.put("bigint"   , "long");
        datatypes.put("datetime" , "datetime");
        datatypes.put("bigint"   , "bigint");
        datatypes.put("float"    , "float");
        datatypes.put("bit"      , "int");
    }

    public static void main(String[] args)
    {
        generate();
    }
}