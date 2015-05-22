package de.freegroup.digitalsimulator.export.wired.db;

/**
 * Class generated by automatic ClassGenerator
 * Date: Fri Oct 04 16:35:33 GMT+02:00 2002
 */
import de.freegroup.digitalsimulator.db.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.sql.*;
import Trace;

class _dbDependencyPin extends dbObject 
{

	String    caseDependency_id;	// Foreign Key pointing to Table [CaseDependency], Field [id]
	String    objectPin_id;	// Foreign Key pointing to Table [ObjectPin], Field [id]
	String    casePin_id;	// Foreign Key pointing to Table [CasePin], Field [id]
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
	 * Method:      getObjectPin()
	 * Description: 
	 * Returns:     ObjectPin
	 */
	public ObjectPin getObjectPin()
	{
		return ObjectPin.findById(objectPin_id);
	}

	/**
	 * Method:      setObjectPin()
	 * Description: 
	 * Returns:     void
	 */
	public void setObjectPin(ObjectPin _foreigner, boolean _autocommit)
	{
		objectPin_id= _foreigner.getId();
		if (_autocommit == true)
			commit();
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
				ResultSet s = stmt.executeQuery( "SELECT caseDependency_id, objectPin_id, casePin_id, id FROM DependencyPin WHERE caseDependency_id='"+toSQL(((_caseDependency==null)?"":_caseDependency.getId()))+"'");
				while(s.next())
				{
					DependencyPin newObject = new DependencyPin();
					newObject.caseDependency_id=s.getString(1);
					newObject.objectPin_id=s.getString(2);
					newObject.casePin_id=s.getString(3);
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
	 *  Method:      findByObjectPin(_dbObjectPin _objectPin)
	 *  Description: 
	 *  Returns:     ArrayList<DependencyPin>
	 */
	public static ArrayList findByObjectPin(_dbObjectPin _objectPin)
	{
		ArrayList result = new ArrayList();
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbDependencyPin.findByObjectPin");
			try
			{
				ResultSet s = stmt.executeQuery( "SELECT caseDependency_id, objectPin_id, casePin_id, id FROM DependencyPin WHERE objectPin_id='"+toSQL(((_objectPin==null)?"":_objectPin.getId()))+"'");
				while(s.next())
				{
					DependencyPin newObject = new DependencyPin();
					newObject.caseDependency_id=s.getString(1);
					newObject.objectPin_id=s.getString(2);
					newObject.casePin_id=s.getString(3);
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
				ResultSet s = stmt.executeQuery( "SELECT caseDependency_id, objectPin_id, casePin_id, id FROM DependencyPin WHERE casePin_id='"+toSQL(((_casePin==null)?"":_casePin.getId()))+"'");
				while(s.next())
				{
					DependencyPin newObject = new DependencyPin();
					newObject.caseDependency_id=s.getString(1);
					newObject.objectPin_id=s.getString(2);
					newObject.casePin_id=s.getString(3);
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
				ResultSet s = stmt.executeQuery( "SELECT caseDependency_id, objectPin_id, casePin_id, id FROM DependencyPin WHERE id='"+toSQL(_id)+"'");
				if(s.next())
				{
					result = new DependencyPin();
					result.caseDependency_id= s.getString(1);
					result.objectPin_id= s.getString(2);
					result.casePin_id= s.getString(3);
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
				stmt.executeUpdate( "UPDATE DependencyPin set caseDependency_id= '"+toSQL(caseDependency_id)+"', objectPin_id= '"+toSQL(objectPin_id)+"', casePin_id= '"+toSQL(casePin_id)+"' WHERE id='"+id+"'");
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
				ResultSet s = stmt.executeQuery( "SELECT caseDependency_id, objectPin_id, casePin_id, id FROM DependencyPin");
				while(s.next())
				{
					DependencyPin newObject = new DependencyPin();
					newObject.caseDependency_id=s.getString(1);
					newObject.objectPin_id=s.getString(2);
					newObject.casePin_id=s.getString(3);
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
	static public DependencyPin createInstance( _dbCaseDependency _caseDependency, _dbObjectPin _objectPin, _dbCasePin _casePin )
	{
		DependencyPin result = null;
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbDependencyPin.createInstance");
			try
			{
				String nextGUID = new java.rmi.server.UID().toString();
				stmt.executeUpdate( "INSERT INTO DependencyPin ( caseDependency_id, objectPin_id, casePin_id, id) VALUES ( '"+((_caseDependency==null)?"":_caseDependency.getId())+"',  '"+((_objectPin==null)?"":_objectPin.getId())+"',  '"+((_casePin==null)?"":_casePin.getId())+"', '"+nextGUID+"')");
				result = new DependencyPin();
				result.caseDependency_id= (_caseDependency==null)?"":_caseDependency.getId();
				result.objectPin_id= (_objectPin==null)?"":_objectPin.getId();
				result.casePin_id= (_casePin==null)?"":_casePin.getId();
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
	static public void newInstance( _dbCaseDependency _caseDependency, _dbObjectPin _objectPin, _dbCasePin _casePin )
	{
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbDependencyPin.newInstance");
			try
			{
				String nextGUID = new java.rmi.server.UID().toString();
				stmt.executeUpdate( "INSERT INTO DependencyPin ( caseDependency_id, objectPin_id, casePin_id, id) VALUES ( '"+((_caseDependency==null)?"":_caseDependency.getId())+"',  '"+((_objectPin==null)?"":_objectPin.getId())+"',  '"+((_casePin==null)?"":_casePin.getId())+"', '"+nextGUID+"')");
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
		result.append(caseDependency_id);
		result.append("|");
		result.append(objectPin_id);
		result.append("|");
		result.append(casePin_id);
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