package de.freegroup.digitalsimulator.export.wired.db;

/**
 * Class generated by automatic ClassGenerator
 * Date: Fri Oct 04 16:35:32 GMT+02:00 2002
 */
import de.freegroup.digitalsimulator.db.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.sql.*;
import Trace;

class _dbObjectPin extends dbObject 
{

	String    object2Case_id;	// Foreign Key pointing to Table [Object2Case], Field [id]
	String    description;
	long      number;
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
			stmt  = ConnectionManager.getValid().createStatement("_dbObjectPin.destroyInstance");
			try
			{
					stmt.executeUpdate( "DELETE FROM ObjectPin WHERE id='"+_key+"'");
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
	 * Method:      getDescription()
	 * Description: 
	 * Returns:     String
	 */
	public String getDescription()
	{
		return description;
	}

	/**
	 * Method:      setDescription(String _description, boolean _autoCommit)
	 * Description: 
	 * Returns:     void
	 */
	public void setDescription(String _description, boolean _autoCommit)
	{
		description=_description;
		if(_autoCommit)
		{
			commit();
		}
	}

	/**
	 * Method:      getNumber()
	 * Description: 
	 * Returns:     long
	 */
	public long getNumber()
	{
		return number;
	}

	/**
	 * Method:      setNumber(long _number, boolean _autoCommit)
	 * Description: 
	 * Returns:     void
	 */
	public void setNumber(long _number, boolean _autoCommit)
	{
		number=_number;
		if(_autoCommit)
		{
			commit();
		}
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
	 * Method:      getObject2Case()
	 * Description: 
	 * Returns:     Object2Case
	 */
	public Object2Case getObject2Case()
	{
		return Object2Case.findById(object2Case_id);
	}

	/**
	 * Method:      setObject2Case()
	 * Description: 
	 * Returns:     void
	 */
	public void setObject2Case(Object2Case _foreigner, boolean _autocommit)
	{
		object2Case_id= _foreigner.getId();
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
	 *  Method:      getDependencyPins()
	 *  Description:                              
	 *  Returns:     ArrayList<DependencyPin>
	 */
	public ArrayList getDependencyPins()
	{
		return _dbDependencyPin.findByObjectPin(this);
	}


	/**
	 *  Method:      findByObject2Case(_dbObject2Case _object2Case)
	 *  Description: 
	 *  Returns:     ArrayList<ObjectPin>
	 */
	public static ArrayList findByObject2Case(_dbObject2Case _object2Case)
	{
		ArrayList result = new ArrayList();
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbObjectPin.findByObject2Case");
			try
			{
				ResultSet s = stmt.executeQuery( "SELECT object2Case_id, description, number, casePin_id, id FROM ObjectPin WHERE object2Case_id='"+toSQL(((_object2Case==null)?"":_object2Case.getId()))+"'");
				while(s.next())
				{
					ObjectPin newObject = new ObjectPin();
					newObject.object2Case_id=s.getString(1);
					newObject.description=s.getString(2);
					newObject.number=s.getLong(3);
					newObject.casePin_id=s.getString(4);
					newObject.id=s.getString(5);
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
	 *  Method:      findByDescription(String _description)
	 *  Description: 
	 *  Returns:     ArrayList<ObjectPin>
	 */
	public static ArrayList findByDescription(String _description)
	{
		ArrayList result = new ArrayList();
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbObjectPin.findByDescription");
			try
			{
				ResultSet s = stmt.executeQuery( "SELECT object2Case_id, description, number, casePin_id, id FROM ObjectPin WHERE description='"+toSQL(_description)+"'");
				while(s.next())
				{
					ObjectPin newObject = new ObjectPin();
					newObject.object2Case_id=s.getString(1);
					newObject.description=s.getString(2);
					newObject.number=s.getLong(3);
					newObject.casePin_id=s.getString(4);
					newObject.id=s.getString(5);
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
	 *  Method:      findByNumber(long _number)
	 *  Description: 
	 *  Returns:     ArrayList<ObjectPin>
	 */
	public static ArrayList findByNumber(long _number)
	{
		ArrayList result = new ArrayList();
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbObjectPin.findByNumber");
			try
			{
				ResultSet s = stmt.executeQuery( "SELECT object2Case_id, description, number, casePin_id, id FROM ObjectPin WHERE number="+_number);
				while(s.next())
				{
					ObjectPin newObject = new ObjectPin();
					newObject.object2Case_id=s.getString(1);
					newObject.description=s.getString(2);
					newObject.number=s.getLong(3);
					newObject.casePin_id=s.getString(4);
					newObject.id=s.getString(5);
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
	 *  Returns:     ArrayList<ObjectPin>
	 */
	public static ArrayList findByCasePin(_dbCasePin _casePin)
	{
		ArrayList result = new ArrayList();
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbObjectPin.findByCasePin");
			try
			{
				ResultSet s = stmt.executeQuery( "SELECT object2Case_id, description, number, casePin_id, id FROM ObjectPin WHERE casePin_id='"+toSQL(((_casePin==null)?"":_casePin.getId()))+"'");
				while(s.next())
				{
					ObjectPin newObject = new ObjectPin();
					newObject.object2Case_id=s.getString(1);
					newObject.description=s.getString(2);
					newObject.number=s.getLong(3);
					newObject.casePin_id=s.getString(4);
					newObject.id=s.getString(5);
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
	 *  Returns:     ObjectPin
	 */
	public static ObjectPin findById(String _id)
	{
		ObjectPin result = null;
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbObjectPin.findById");
			try
			{
				ResultSet s = stmt.executeQuery( "SELECT object2Case_id, description, number, casePin_id, id FROM ObjectPin WHERE id='"+toSQL(_id)+"'");
				if(s.next())
				{
					result = new ObjectPin();
					result.object2Case_id= s.getString(1);
					result.description= s.getString(2);
					result.number= s.getLong(3);
					result.casePin_id= s.getString(4);
					result.id= s.getString(5);
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
			stmt  = ConnectionManager.getValid().createStatement("_dbObjectPin.commit");
			try
			{
				stmt.executeUpdate( "UPDATE ObjectPin set object2Case_id= '"+toSQL(object2Case_id)+"', description= '"+toSQL(description)+"', number= "+number+", casePin_id= '"+toSQL(casePin_id)+"' WHERE id='"+id+"'");
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
	 * returns ArrayList<ObjectPin>
	 */
	public static ArrayList getAll()
	{
		ArrayList result = new ArrayList();
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbObjectPin.getAll");
			try
			{
				ResultSet s = stmt.executeQuery( "SELECT object2Case_id, description, number, casePin_id, id FROM ObjectPin");
				while(s.next())
				{
					ObjectPin newObject = new ObjectPin();
					newObject.object2Case_id=s.getString(1);
					newObject.description=s.getString(2);
					newObject.number=s.getLong(3);
					newObject.casePin_id=s.getString(4);
					newObject.id=s.getString(5);
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
	static public ObjectPin createInstance( _dbObject2Case _object2Case, String  _description, long  _number, _dbCasePin _casePin )
	{
		ObjectPin result = null;
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbObjectPin.createInstance");
			try
			{
				String nextGUID = new java.rmi.server.UID().toString();
				stmt.executeUpdate( "INSERT INTO ObjectPin ( object2Case_id, description, number, casePin_id, id) VALUES ( '"+((_object2Case==null)?"":_object2Case.getId())+"',  '"+toSQL(_description)+"', "+_number+",  '"+((_casePin==null)?"":_casePin.getId())+"', '"+nextGUID+"')");
				result = new ObjectPin();
				result.object2Case_id= (_object2Case==null)?"":_object2Case.getId();
				result.description= _description;
				result.number= _number;
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
	static public void newInstance( _dbObject2Case _object2Case, String  _description, long  _number, _dbCasePin _casePin )
	{
		SaveStatement  stmt;

		try
		{
			stmt  = ConnectionManager.getValid().createStatement("_dbObjectPin.newInstance");
			try
			{
				String nextGUID = new java.rmi.server.UID().toString();
				stmt.executeUpdate( "INSERT INTO ObjectPin ( object2Case_id, description, number, casePin_id, id) VALUES ( '"+((_object2Case==null)?"":_object2Case.getId())+"',  '"+toSQL(_description)+"', "+_number+",  '"+((_casePin==null)?"":_casePin.getId())+"', '"+nextGUID+"')");
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
			stmt  = ConnectionManager.getValid().createStatement("_dbObjectPin.destroyInstance");
			try
			{
					stmt.executeUpdate( "DELETE FROM ObjectPin WHERE id='"+_key+"'");
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
			stmt  = ConnectionManager.getValid().createStatement("_dbObjectPin.destroyAll");
			try
			{
					stmt.executeUpdate("DELETE from ObjectPin" );
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
		result.append(object2Case_id);
		result.append("|");
		result.append(description);
		result.append("|");
		result.append(number);
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