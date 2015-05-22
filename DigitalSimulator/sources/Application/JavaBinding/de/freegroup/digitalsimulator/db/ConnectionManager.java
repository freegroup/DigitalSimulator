package de.freegroup.digitalsimulator.db;
/**
 * Title:        short-i
 * Description:  Information retrival System with human language interface
 * Copyright:    Copyright (c) 2001
 * Company:      short-i
 * @author Andreas Herz
 * @version 1.0
 */
import java.io.*;
import java.sql.*;
import java.text.*;
import java.util.*;
import javax.swing.*;
import Trace;
import Configuration;

public class ConnectionManager
{
   private static String  m_user;
   private static String  m_password;
   private static String  m_database;
   private static String  m_driver;
   private static ArrayList  m_connections;

   /**
    * Init the Database with the hands over JDBC driver and the database, user, password.
    *
    */
   public static void init(String jdbcDriver,  String database, String user, String password )
   {
      // Find and load the JDBC driver in the DriverManager
      // Safeguard operations
      try
      {
         //
         Trace.info("--------------------------------------");
         Trace.info("initialize the ConnectionManager");
         Trace.info("--------------------------------------");
         Trace.info("   open connection to");
         Trace.info("   driver     :["+jdbcDriver+"]");
         Trace.info("   database   :["+database+"]");
         Trace.info("   user       :["+user+"]");
         Trace.info("   password   :["+password+"]");
         Class.forName ( jdbcDriver ).newInstance();
         m_driver      = jdbcDriver;
         m_database    = database;
         m_user        = user;
         m_password    = password;
         m_connections = new ArrayList();
         m_connections.add(0,new SaveConnection(DriverManager.getConnection( database, user , password )));
         Trace.info("--------------------------------------\n");
      }
      catch ( Exception exc )
      {
         Trace.error("unable to open db-connection", exc );
      }
   }

   /**
   * Return a valid JDBC connection.
   */
   public static synchronized SaveConnection getValid()
   {
      // Safeguard operations
      try
      {
         // prüfen ob connection noch gülig ist
         //
         if(m_connections==null)
         {
            // object not initialized.....try to get the params from the config object
            // and read the jdbc informations
//            String driver          = "sun.jdbc.odbc.JdbcOdbcDriver";
//            String database        = "jdbc:odbc:digital";
//            String user            = "digital";
//            String password        = "digital";

            String appPath = Configuration.getString(Configuration.APPLICATION_PATH);
            String driver          = "org.hsql.jdbcDriver";
            String database        = "jdbc:HypersonicSQL:"+appPath+"database\\exportWired";
            String user            = "sa";
            String password        = "";

            init(driver,database,user,password );
            return getValid();
         }
         else
         {
            SaveConnection con = (SaveConnection)m_connections.get(0);
            if(con.isClosed())
            {
               m_connections.add(0, new SaveConnection(DriverManager.getConnection( m_database, m_user , m_password )));
            }
         }
      }
      catch ( Exception exc )
      {
         Trace.error("unable to read and open db",exc);
      }
      // return a valid connection
      //
      return (SaveConnection)m_connections.get(0);
   }
}