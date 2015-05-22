package de.freegroup.digitalsimulator.export.wired.db;

/**
 * Class generated by automatic ClassGenerator
 * Date: Mon Feb 02 16:30:54 CET 2004
 */
import de.freegroup.digitalsimulator.db.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.sql.*;
import de.freegroup.digitalsimulator.Trace;

class _dbDependencyPin extends dbObject 
{

	String    casePin_id;	// Foreign Key pointing to Table [CasePin], Field [id]
	String    caseDependency_id;	// Foreign Key pointing to Table [CaseDependency], Field [id]
	String    objectPin2CasePin_id;	// Foreign Key pointing to Table [ObjectPin2CasePin], Field [id]
	String    id;	// Key


	/**
	 * destroy a object in the database
	 */
	public boolean destroy()
	{
		boolean result = false;
		String    _key   = id;
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbDependencyPin.destroyInstance");
			try
			{
					stmt.executeUpdate( "DELETE FROM DependencyPin WHERE id='"+_key+"'");
					result = true;
					id     = null;
			}
			catch(Exception exc)
			{
				Trace.error(exc);
			}
			stmt.close();
		
		}
		catch (Exception ex)
		{
			Trace.error(ex);
		}
		return result;
	}



	/**
	 * Method:      getId()
	 * Description: 
	 * Returns:     String
	 */
	public String getId()
	{
		return id;
	}

	/**
	 * Method:      getCasePin()
	 * Description: 
	 * Returns:     CasePin
	 */
	public CasePin getCasePin()
	{
		return CasePin.findById(casePin_id);
	}

	/**
	 * Method:      setCasePin()
	 * Description: 
	 * Returns:     void
	 */
	public void setCasePin(CasePin _foreigner, boolean _autocommit)
	{
		casePin_id= _foreigner.getId();
		if (_autocommit == true)
			commit();
	}

	/**
	 * Method:      getCaseDependency()
	 * Description: 
	 * Returns:     CaseDependency
	 */
	public CaseDependency getCaseDependency()
	{
		return CaseDependency.findById(caseDependency_id);
	}

	/**
	 * Method:      setCaseDependency()
	 * Description: 
	 * Returns:     void
	 */
	public void setCaseDependency(CaseDependency _foreigner, boolean _autocommit)
	{
		caseDependency_id= _foreigner.getId();
		if (_autocommit == true)
			commit();
	}

	/**
	 * Method:      getObjectPin2CasePin()
	 * Description: 
	 * Returns:     ObjectPin2CasePin
	 */
	public ObjectPin2CasePin getObjectPin2CasePin()
	{
		return ObjectPin2CasePin.findById(objectPin2CasePin_id);
	}

	/**
	 * Method:      setObjectPin2CasePin()
	 * Description: 
	 * Returns:     void
	 */
	public void setObjectPin2CasePin(ObjectPin2CasePin _foreigner, boolean _autocommit)
	{
		objectPin2CasePin_id= _foreigner.getId();
		if (_autocommit == true)
			commit();
	}

	/**
	 *  Method:      findByCasePin(_dbCasePin _casePin)
	 *  Description: 
	 *  Returns:     ArrayList<DependencyPin>
	 */
	public static ArrayList findByCasePin(_dbCasePin _casePin)
	{
		ArrayList result = new ArrayList();
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbDependencyPin.findByCasePin");
			try
			{
				ResultSet s = stmt.executeQuery( "SELECT casePin_id, caseDependency_id, objectPin2CasePin_id, id FROM DependencyPin WHERE casePin_id='"+toSQL(((_casePin==null)?"":_casePin.getId()))+"'");
				while(s.next())
				{
					DependencyPin newObject = new DependencyPin();
					newObject.casePin_id=s.getString(1);
					newObject.caseDependency_id=s.getString(2);
					newObject.objectPin2CasePin_id=s.getString(3);
					newObject.id=s.getString(4);
					result.add(newObject);
				}
			}
			catch(Exception exc)
			{
				Trace.error(exc);
			}
			stmt.close();
		
		}
		catch (Exception ex)
		{
			Trace.error(ex);
		}
		return result;
	}

	/**
	 *  Method:      findByCaseDependency(_dbCaseDependency _caseDependency)
	 *  Description: 
	 *  Returns:     ArrayList<DependencyPin>
	 */
	public static ArrayList findByCaseDependency(_dbCaseDependency _caseDependency)
	{
		ArrayList result = new ArrayList();
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbDependencyPin.findByCaseDependency");
			try
			{
				ResultSet s = stmt.executeQuery( "SELECT casePin_id, caseDependency_id, objectPin2CasePin_id, id FROM DependencyPin WHERE caseDependency_id='"+toSQL(((_caseDependency==null)?"":_caseDependency.getId()))+"'");
				while(s.next())
				{
					DependencyPin newObject = new DependencyPin();
					newObject.casePin_id=s.getString(1);
					newObject.caseDependency_id=s.getString(2);
					newObject.objectPin2CasePin_id=s.getString(3);
					newObject.id=s.getString(4);
					result.add(newObject);
				}
			}
			catch(Exception exc)
			{
				Trace.error(exc);
			}
			stmt.close();
		
		}
		catch (Exception ex)
		{
			Trace.error(ex);
		}
		return result;
	}

	/**
	 *  Method:      findByObjectPin2CasePin(_dbObjectPin2CasePin _objectPin2CasePin)
	 *  Description: 
	 *  Returns:     ArrayList<DependencyPin>
	 */
	public static ArrayList findByObjectPin2CasePin(_dbObjectPin2CasePin _objectPin2CasePin)
	{
		ArrayList result = new ArrayList();
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbDependencyPin.findByObjectPin2CasePin");
			try
			{
				ResultSet s = stmt.executeQuery( "SELECT casePin_id, caseDependency_id, objectPin2CasePin_id, id FROM DependencyPin WHERE objectPin2CasePin_id='"+toSQL(((_objectPin2CasePin==null)?"":_objectPin2CasePin.getId()))+"'");
				while(s.next())
				{
					DependencyPin newObject = new DependencyPin();
					newObject.casePin_id=s.getString(1);
					newObject.caseDependency_id=s.getString(2);
					newObject.objectPin2CasePin_id=s.getString(3);
					newObject.id=s.getString(4);
					result.add(newObject);
				}
			}
			catch(Exception exc)
			{
				Trace.error(exc);
			}
			stmt.close();
		
		}
		catch (Exception ex)
		{
			Trace.error(ex);
		}
		return result;
	}

	/**
	 *  Method:      findById(String _id)
	 *  Description: 
	 *  Returns:     DependencyPin
	 */
	public static DependencyPin findById(String _id)
	{
		DependencyPin result = null;
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbDependencyPin.findById");
			try
			{
				ResultSet s = stmt.executeQuery( "SELECT casePin_id, caseDependency_id, objectPin2CasePin_id, id FROM DependencyPin WHERE id='"+toSQL(_id)+"'");
				if(s.next())
				{
					result = new DependencyPin();
					result.casePin_id= s.getString(1);
					result.caseDependency_id= s.getString(2);
					result.objectPin2CasePin_id= s.getString(3);
					result.id= s.getString(4);
				}
			}
			catch(Exception exc)
			{
				Trace.error(exc);
			}
			stmt.close();
		
		}
		catch (Exception ex)
		{
			Trace.error(ex);
		}
		return result;
	}

	/**
	 * returns boolean
	 */
	public boolean commit()
	{
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbDependencyPin.commit");
			try
			{
				stmt.executeUpdate( "UPDATE DependencyPin set casePin_id= '"+toSQL(casePin_id)+"', caseDependency_id= '"+toSQL(caseDependency_id)+"', objectPin2CasePin_id= '"+toSQL(objectPin2CasePin_id)+"' WHERE id='"+id+"'");
			}
			catch(Exception exc)
			{
				Trace.error(exc);
			}
			stmt.close();
		
		}
		catch (Exception ex)
		{
			Trace.error(ex);
		}
		return true;
	}


	/**
	 * returns ArrayList<DependencyPin>
	 */
	public static ArrayList getAll()
	{
		ArrayList result = new ArrayList();
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbDependencyPin.getAll");
			try
			{
				ResultSet s = stmt.executeQuery( "SELECT casePin_id, caseDependency_id, objectPin2CasePin_id, id FROM DependencyPin");
				while(s.next())
				{
					DependencyPin newObject = new DependencyPin();
					newObject.casePin_id=s.getString(1);
					newObject.caseDependency_id=s.getString(2);
					newObject.objectPin2CasePin_id=s.getString(3);
					newObject.id=s.getString(4);
					result.add(newObject);
				}
			}
			catch(Exception exc)
			{
				Trace.error(exc);
			}
			stmt.close();
		
		}
		catch (Exception ex)
		{
			Trace.error(ex);
		}
		return result;
	}


	/**
	 * create a new object in the database
	 */
	static public DependencyPin createInstance( _dbCasePin _casePin, _dbCaseDependency _caseDependency, _dbObjectPin2CasePin _objectPin2CasePin )
	{
		DependencyPin result = null;
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbDependencyPin.createInstance");
			try
			{
				String nextGUID = new java.rmi.server.UID().toString();
				stmt.executeUpdate( "INSERT INTO DependencyPin ( casePin_id, caseDependency_id, objectPin2CasePin_id, id) VALUES ( '"+((_casePin==null)?"":_casePin.getId())+"',  '"+((_caseDependency==null)?"":_caseDependency.getId())+"',  '"+((_objectPin2CasePin==null)?"":_objectPin2CasePin.getId())+"', '"+nextGUID+"')");
				result = new DependencyPin();
				result.casePin_id= (_casePin==null)?"":_casePin.getId();
				result.caseDependency_id= (_caseDependency==null)?"":_caseDependency.getId();
				result.objectPin2CasePin_id= (_objectPin2CasePin==null)?"":_objectPin2CasePin.getId();
				result.id= nextGUID;
			}
			catch(Exception exc)
			{
				Trace.error(exc);
			}
			stmt.close();
		
		}
		catch (Exception ex)
		{
			Trace.error(ex);
		}
		return result;
	}


	/**
	 * create a new object in the database
	 */
	static public void newInstance( _dbCasePin _casePin, _dbCaseDependency _caseDependency, _dbObjectPin2CasePin _objectPin2CasePin )
	{
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbDependencyPin.newInstance");
			try
			{
				String nextGUID = new java.rmi.server.UID().toString();
				stmt.executeUpdate( "INSERT INTO DependencyPin ( casePin_id, caseDependency_id, objectPin2CasePin_id, id) VALUES ( '"+((_casePin==null)?"":_casePin.getId())+"',  '"+((_caseDependency==null)?"":_caseDependency.getId())+"',  '"+((_objectPin2CasePin==null)?"":_objectPin2CasePin.getId())+"', '"+nextGUID+"')");
			}
			catch(Exception exc)
			{
				Trace.error(exc);
			}
			stmt.close();
		
		}
		catch (Exception ex)
		{
			Trace.error(ex);
		}
	}


	/**
	 * destroy a object in the database
	 */
	static public boolean destroyInstance( String  _key)
	{
		boolean result = false;
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbDependencyPin.destroyInstance");
			try
			{
					stmt.executeUpdate( "DELETE FROM DependencyPin WHERE id='"+_key+"'");
					result = true;
			}
			catch(Exception exc)
			{
				Trace.error(exc);
			}
			stmt.close();
		
		}
		catch (Exception ex)
		{
			Trace.error(ex);
		}
		return result;
	}


	/**
	 * destroy ALL objects in the database
	 */
	static public boolean destroyAll()
	{
		boolean result = false;
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbDependencyPin.destroyAll");
			try
			{
					stmt.executeUpdate("DELETE from DependencyPin" );
					result = true;
			}
			catch(Exception exc)
			{
				Trace.error(exc);
			}
			stmt.close();
		
		}
		catch (Exception ex)
		{
			Trace.error(ex);
		}
		return result;
	}


	/**
	 */
	public String toString()
	{
		StringBuffer result = new StringBuffer(1024);
		result.append(casePin_id);
		result.append("|");
		result.append(caseDependency_id);
		result.append("|");
		result.append(objectPin2CasePin_id);
		result.append("|");
		result.append(id);
		return result.toString();
	}


	/**
	 * init the class
	 */
	static
	{
	}


}