/*
 * This class was automatically generated with 
 * <a href="http://castor.exolab.org">Castor 0.9.2</a>, using an
 * XML Schema.
 * $Id: Update.java,v 1.4 2005/04/08 11:15:47 freegroup Exp $
 */

package de.freegroup.digitalsimulator.plugin.tool.LiveUpdate.castor;

  //---------------------------------/
 //- Imported classes and packages -/
//---------------------------------/

import java.io.Reader;
import java.io.Serializable;
import java.io.Writer;
import java.util.Enumeration;
import java.util.Vector;
import org.exolab.castor.xml.*;
import org.exolab.castor.xml.MarshalException;
import org.exolab.castor.xml.ValidationException;
import org.xml.sax.DocumentHandler;

/**
 * 
 * @version $Revision: 1.4 $ $Date: 2005/04/08 11:15:47 $
**/
public class Update implements java.io.Serializable {


      //--------------------------/
     //- Class/Member Variables -/
    //--------------------------/

    private java.util.Vector _updateFileList;


      //----------------/
     //- Constructors -/
    //----------------/

    public Update() {
        super();
        _updateFileList = new Vector();
    } //-- de.freegroup.digitalsimulator.plugin.tool.LiveUpdate.castor.Update()


      //-----------/
     //- Methods -/
    //-----------/

    /**
     * 
     * @param vUpdateFile
    **/
    public void addUpdateFile(UpdateFile vUpdateFile)
        throws java.lang.IndexOutOfBoundsException
    {
        _updateFileList.addElement(vUpdateFile);
    } //-- void addUpdateFile(UpdateFile) 

    /**
    **/
    public java.util.Enumeration enumerateUpdateFile()
    {
        return _updateFileList.elements();
    } //-- java.util.Enumeration enumerateUpdateFile() 

    /**
     * 
     * @param index
    **/
    public UpdateFile getUpdateFile(int index)
        throws java.lang.IndexOutOfBoundsException
    {
        //-- check bounds for index
        if ((index < 0) || (index > _updateFileList.size())) {
            throw new IndexOutOfBoundsException();
        }
        
        return (UpdateFile) _updateFileList.elementAt(index);
    } //-- UpdateFile getUpdateFile(int) 

    /**
    **/
    public UpdateFile[] getUpdateFile()
    {
        int size = _updateFileList.size();
        UpdateFile[] mArray = new UpdateFile[size];
        for (int index = 0; index < size; index++) {
            mArray[index] = (UpdateFile) _updateFileList.elementAt(index);
        }
        return mArray;
    } //-- UpdateFile[] getUpdateFile() 

    /**
    **/
    public int getUpdateFileCount()
    {
        return _updateFileList.size();
    } //-- int getUpdateFileCount() 

    /**
    **/
    public boolean isValid()
    {
        try {
            validate();
        }
        catch (org.exolab.castor.xml.ValidationException vex) {
            return false;
        }
        return true;
    } //-- boolean isValid() 

    /**
     * 
     * @param out
    **/
    public void marshal(java.io.Writer out)
        throws org.exolab.castor.xml.MarshalException, org.exolab.castor.xml.ValidationException
    {
        
        Marshaller.marshal(this, out);
    } //-- void marshal(java.io.Writer) 

    /**
     * 
     * @param handler
    **/
    public void marshal(org.xml.sax.DocumentHandler handler)
        throws org.exolab.castor.xml.MarshalException, org.exolab.castor.xml.ValidationException
    {
        
        Marshaller.marshal(this, handler);
    } //-- void marshal(org.xml.sax.DocumentHandler) 

    /**
    **/
    public void removeAllUpdateFile()
    {
        _updateFileList.removeAllElements();
    } //-- void removeAllUpdateFile() 

    /**
     * 
     * @param index
    **/
    public UpdateFile removeUpdateFile(int index)
    {
        Object obj = _updateFileList.elementAt(index);
        _updateFileList.removeElementAt(index);
        return (UpdateFile) obj;
    } //-- UpdateFile removeUpdateFile(int) 

    /**
     * 
     * @param index
     * @param vUpdateFile
    **/
    public void setUpdateFile(int index, UpdateFile vUpdateFile)
        throws java.lang.IndexOutOfBoundsException
    {
        //-- check bounds for index
        if ((index < 0) || (index > _updateFileList.size())) {
            throw new IndexOutOfBoundsException();
        }
        _updateFileList.setElementAt(vUpdateFile, index);
    } //-- void setUpdateFile(int, UpdateFile) 

    /**
     * 
     * @param updateFileArray
    **/
    public void setUpdateFile(UpdateFile[] updateFileArray)
    {
        //-- copy array
        _updateFileList.removeAllElements();
        for (int i = 0; i < updateFileArray.length; i++) {
            _updateFileList.addElement(updateFileArray[i]);
        }
    } //-- void setUpdateFile(UpdateFile) 

    /**
     * 
     * @param reader
    **/
    public static de.freegroup.digitalsimulator.plugin.tool.LiveUpdate.castor.Update unmarshal(java.io.Reader reader)
        throws org.exolab.castor.xml.MarshalException, org.exolab.castor.xml.ValidationException
    {
        return (de.freegroup.digitalsimulator.plugin.tool.LiveUpdate.castor.Update) Unmarshaller.unmarshal(de.freegroup.digitalsimulator.plugin.tool.LiveUpdate.castor.Update.class, reader);
    } //-- de.freegroup.digitalsimulator.plugin.tool.LiveUpdate.castor.Update unmarshal(java.io.Reader) 

    /**
    **/
    public void validate()
        throws org.exolab.castor.xml.ValidationException
    {
        org.exolab.castor.xml.Validator validator = new org.exolab.castor.xml.Validator();
        validator.validate(this);
    } //-- void validate() 

}
