package de.freegroup.util.dbgenerator;

/**
 * Title:        short-i
 * Description:  Information retrival System with human language interface
 * Copyright:    Copyright (c) 2001
 * Company:      short-i
 * @author Andreas Herz
 * @version 1.0
 */
import java.io.*;
import java.util.*;
import java.sql.*;

public class Main
{
    static HashMap       datatypes= null;
    static HashMap       classes  = null;

    /**
     *
     */
    public static void generate( String outDirectory, String outPackage, String driver, String database, String user, String password)
    {
        generateClasses(outDirectory, outPackage, driver, database, user, password);
    }


    /**
     *
     */
    static void generateClasses(String outDirectory, String outPackage, String driver, String database, String user, String password)
    {
        try
        {
            System.out.println("--------------------------------------");
            System.out.println("initialize the ConnectionManager");
            System.out.println("--------------------------------------");
            System.out.println("   open connection to");
            System.out.println("   driver     :["+driver+"]");
            System.out.println("   database   :["+database+"]");
            System.out.println("   user       :["+user+"]");
            System.out.println("   password   :["+password+"]");

            java.lang.Class.forName( driver ).newInstance();
            Connection cConn = DriverManager.getConnection( database, user , password );
            Statement  stmt1 = cConn.createStatement();
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
                    Class newClass = new Class(tableName,outPackage);
                    classes.put(tableName,newClass);
                }
            }
            result.close();

            // generate all attributes for the classes
            //
            Iterator iter = classes.keySet().iterator();
            while(iter.hasNext())
            {
                String className = (String)iter.next();
                Class  outClass  = (Class) classes.get(className);
                ResultSet col=dMeta.getColumns(null,null,className,null);
                // properties
                //
                while(col.next())
                {
//                    dumpResultSetMetaInformation(col);
                    String  columnName   = col.getString("COLUMN_NAME");
                    String  type         = col.getString("TYPE_NAME");
                    String  datasize     = col.getString("COLUMN_SIZE");
                    String  digits       = col.getString("DECIMAL_DIGITS");
                    boolean nullable     = col.getInt(11)!=DatabaseMetaData.columnNoNulls;
                    String  propertyType = "";
                    boolean isIdentity   = false;
                    StringTokenizer token = new StringTokenizer(type," ");
                    propertyType = (String)datatypes.get(token.nextToken());

                    try
                    {
                        String identity = token.nextToken();
                        if(identity.equals("identity"))
                            isIdentity = true;
                    }
                    catch (Exception ex){}

                    outClass.addProperty(columnName, propertyType, isIdentity);
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
                    if((c!=null) && (unique==true))
                    {
                        outClass.setUnique(c);
                    }
                }
                ind.close();
            }

            // forreign key
            //
            System.out.println("checking foreign keys...");
            Iterator iterClass = classes.keySet().iterator();
            while(iterClass.hasNext())
            {
                String name =(String) iterClass.next();
                System.out.println("  checking:"+name);
                ResultSet r = dMeta.getExportedKeys( null, null, name ) ;
                while(r.next())
                {
                    String fTable       = r.getString("FKTABLE_NAME");
                    String fColumn      = r.getString("FKCOLUMN_NAME");
                    Class  foreignClass = (Class) classes.get(fTable);
                    Class  currentClass = (Class) classes.get(name);
                    boolean unique      = foreignClass.isUnique(fColumn);

                    currentClass.addReverseRelation(fTable,fColumn,unique);
                    foreignClass.setForeignKey(fColumn,name,"id");
                }
                r.close();
            }

            iterClass = classes.keySet().iterator();
            while(iterClass.hasNext())
            {
                Class outClass = (Class) classes.get(iterClass.next());
                outClass.writeDBCode(outDirectory);
                outClass.writeCode(outDirectory);
            }
        }
        catch(Exception exc)
        {
            System.err.println(exc);
            System.exit(1);
        }
    }

    static void dumpResultSetMetaInformation(ResultSet r)
    {
        try
        {
            ResultSetMetaData md= r.getMetaData();
            int count =md.getColumnCount();
            for(int i=1; i<=count; i++)
            {
                System.out.println("Name:"+ md.getColumnName(i)+"   Type:"+md.getColumnTypeName(i));

            }
            System.out.println("========================================");
        }
        catch (Exception ex)
        {
        }
    }


    static
    {
        classes   = new HashMap();
        datatypes = new HashMap();
        datatypes.put("text"     , "String");
        datatypes.put("varchar"  , "String");
        datatypes.put("char"     , "String");
        datatypes.put("int"      , "int");
        datatypes.put("datetime" , "Date");
        datatypes.put("bigint"   , "long");
        datatypes.put("float"    , "double");
        datatypes.put("bit"      , "int");
    }

    public static void main(String[] args)
    {
        String outPackage      = args[0];//"com.sapmarkets.db.test";
        String outDirectory    = args[1];//"C:/Users/herz/Projects/dbGeneratorTest/java";
        String driver          = args[2];//"sun.jdbc.odbc.JdbcOdbcDriver";
        String database        = args[3];//"jdbc:odbc:calendar";
        String user            = args[4];//"calendar";
        String password        = args[5];//"calendar";

        Main.generate(outDirectory, outPackage, driver, database, user, password);
    }
}