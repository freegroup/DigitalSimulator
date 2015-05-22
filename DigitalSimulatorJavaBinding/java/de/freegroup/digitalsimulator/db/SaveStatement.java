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

import de.freegroup.digitalsimulator.Trace;

public class SaveStatement
{

    private Statement      m_statement;
    private SaveConnection m_connection;
    private boolean        m_logging=true;
    private String         m_createLocation;

    public SaveStatement(SaveConnection con, Statement stm, String createLocation)
    {
        m_statement      = stm;
        m_connection     = con;
        m_createLocation = createLocation;
    }

    public ResultSet executeQuery(String sql) throws SQLException
    {
        log(sql);
        return m_statement.executeQuery(sql);
    }

    public int executeUpdate(String sql) throws SQLException
    {
        log(sql);
        return m_statement.executeUpdate(sql);
    }

    public void close()
    {
        try{ m_statement.close();}catch(SQLException exc){};

        m_connection.decrementStatements(m_createLocation);
        m_connection = null;
        m_statement  = null;
    }

    public int getMaxFieldSize() throws SQLException
    {
        return m_statement.getMaxFieldSize();
    }

    public void setMaxFieldSize(int max) throws SQLException
    {
        m_statement.setMaxFieldSize(max);
    }

    public int getMaxRows() throws SQLException
    {
        return m_statement.getMaxRows();
    }

    public void setMaxRows(int max) throws SQLException
    {
        m_statement.setMaxRows(max);
    }

    public void setEscapeProcessing(boolean enable) throws SQLException
    {
        m_statement.setEscapeProcessing(enable);
    }

    public int getQueryTimeout() throws SQLException
    {
        return m_statement.getQueryTimeout();
    }

    public void setQueryTimeout(int seconds) throws SQLException
    {
        m_statement.setQueryTimeout(seconds);
    }

    public void cancel() throws SQLException
    {
        m_statement.cancel();
    }

    public SQLWarning getWarnings() throws SQLException
    {
        return m_statement.getWarnings();
    }

    public void clearWarnings() throws SQLException
    {
        m_statement.clearWarnings();
    }

    public void setCursorName(String name) throws SQLException
    {
        m_statement.setCursorName(name );
    }

    public boolean execute(String sql) throws SQLException
    {
        log(sql);
        return m_statement.execute(sql);
    }

    public ResultSet getResultSet() throws SQLException
    {
        return m_statement.getResultSet();
    }

    public int getUpdateCount() throws SQLException
    {
        return m_statement.getUpdateCount();
    }

    public boolean getMoreResults() throws SQLException
    {
        return m_statement.getMoreResults();
    }

    public void setFetchDirection(int direction) throws SQLException
    {
        m_statement.setFetchDirection(direction);
    }

    public int getFetchDirection() throws SQLException
    {
        return m_statement.getFetchDirection();
    }

    public void setFetchSize(int rows) throws SQLException
    {
        m_statement.setFetchSize(rows);
    }

    public int getFetchSize() throws SQLException
    {
        return m_statement.getFetchSize();
    }

    public int getResultSetConcurrency() throws SQLException
    {
        return m_statement.getResultSetConcurrency();
    }

    public int getResultSetType() throws SQLException
    {
        return m_statement.getResultSetType();
    }

    public void addBatch(String sql) throws SQLException
    {
        log(sql);
        m_statement.addBatch(sql);
    }

    public void clearBatch() throws SQLException
    {
        m_statement.clearBatch();
    }


    public int[] executeBatch() throws SQLException
    {
        return m_statement.executeBatch();
    }


    public SaveConnection getConnection() throws SQLException
    {
        return m_connection;
    }

    private void log(String text)
    {
        if(m_logging==true)
            Trace.info(text);
    }
}