package de.freegroup.digitalsimulator.db;
/**
 * Title:        short-i
 * Description:  Information retrival System with human language interface
 * Copyright:    Copyright (c) 2001
 * Company:      short-i
 * @author David Sommer & Andreas Herz
 * @version 1.0
 */

import java.sql.*;
import java.util.Map;
import java.util.*;

import de.freegroup.digitalsimulator.Trace;

public class SaveConnection
{
    private Connection m_connection;
    private HashMap    m_openStatements = new HashMap();

    public SaveConnection(Connection con)
    {
        m_connection = con;
    }

    public SaveStatement createStatement(String createLocation) throws SQLException
    {
        SaveStatement s=new SaveStatement(this, m_connection.createStatement(),createLocation);
        incrementStatements(createLocation);
        return s;
    }

    public PreparedStatement prepareStatement(String sql) throws SQLException
    {
        return m_connection.prepareStatement(sql);
    }

    public CallableStatement prepareCall(String sql) throws SQLException
    {
        return m_connection.prepareCall(sql);
    }

    public String nativeSQL(String sql) throws SQLException
    {
        return m_connection.nativeSQL(sql);
    }

    public void setAutoCommit(boolean autoCommit) throws SQLException
    {
        m_connection.setAutoCommit(autoCommit);
    }

    public boolean getAutoCommit() throws SQLException
    {
        return m_connection.getAutoCommit();
    }

    public void commit() throws SQLException
    {
        m_connection.commit();
    }

    public void rollback() throws SQLException
    {
        m_connection.rollback();
    }

    public void close() throws SQLException
    {
        m_connection.close();
        m_connection = null;
    }

    public boolean isClosed() throws SQLException
    {
        return m_connection.isClosed();
    }

    public DatabaseMetaData getMetaData() throws SQLException
    {
        return m_connection.getMetaData();
    }

    public void setReadOnly(boolean readOnly) throws SQLException
    {
        m_connection.setReadOnly( readOnly);
    }

    public boolean isReadOnly() throws SQLException
    {
        return m_connection.isReadOnly();
    }

    public void setCatalog(String catalog) throws SQLException
    {
        m_connection.setCatalog( catalog);
    }

    public String getCatalog() throws SQLException
    {
        return m_connection.getCatalog();
    }

    public void setTransactionIsolation(int level) throws SQLException
    {
        m_connection.setTransactionIsolation( level);
    }

    public int getTransactionIsolation() throws SQLException
    {
        return m_connection.getTransactionIsolation();
    }

    public SQLWarning getWarnings() throws SQLException
    {
        return m_connection.getWarnings();
    }

    public void clearWarnings() throws SQLException
    {
        m_connection.clearWarnings();
    }

    public SaveStatement createStatement(int resultSetType, int resultSetConcurrency, String createLocation) throws SQLException
    {
        SaveStatement s= new SaveStatement(this, m_connection.createStatement(resultSetType, resultSetConcurrency), createLocation);
        incrementStatements(createLocation);
        return s;
    }

    public PreparedStatement prepareStatement(String sql, int resultSetType, int resultSetConcurrency) throws SQLException
    {
        return m_connection.prepareStatement( sql,  resultSetType,  resultSetConcurrency);
    }

    public CallableStatement prepareCall(String sql, int resultSetType, int resultSetConcurrency) throws SQLException
    {
        return m_connection.prepareCall( sql,  resultSetType,  resultSetConcurrency);
    }

    public Map getTypeMap() throws SQLException
    {
        return m_connection.getTypeMap();
    }

    public void setTypeMap(Map map) throws SQLException
    {
        m_connection.setTypeMap(map);
    }

    public void incrementStatements(String createLocation)
    {
        Integer counter;
        if(m_openStatements.containsKey(createLocation))
        {
            counter = (Integer)m_openStatements.get(createLocation);
            counter = new Integer(counter.intValue()+1);
        }
        else
        {
            counter = new Integer(1);
        }

        m_openStatements.put(createLocation,counter);
    }

    public void decrementStatements(String createLocation)
    {
        Integer counter;
        if(m_openStatements.containsKey(createLocation))
        {
            counter = (Integer)m_openStatements.get(createLocation);
            counter = new Integer(counter.intValue()-1);
        }
        else
        {
            counter = new Integer(1);
        }
        if(counter.intValue()!=0)
            m_openStatements.put(createLocation,counter);
        else
            m_openStatements.remove(createLocation);
    }
}