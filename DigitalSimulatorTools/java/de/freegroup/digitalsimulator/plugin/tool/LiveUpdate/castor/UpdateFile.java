/*
 * This class was automatically generated with 
 * <a href="http://castor.exolab.org">Castor 0.9.2</a>, using an
 * XML Schema.
 * $Id: UpdateFile.java,v 1.4 2005/04/08 11:15:47 freegroup Exp $
 */

package de.freegroup.digitalsimulator.plugin.tool.LiveUpdate.castor;

  //---------------------------------/
 //- Imported classes and packages -/
//---------------------------------/

import java.io.Reader;
import java.io.Serializable;
import java.io.Writer;
import org.exolab.castor.xml.*;
import org.exolab.castor.xml.MarshalException;
import org.exolab.castor.xml.ValidationException;
import org.xml.sax.DocumentHandler;

/**
 * 
 * @version $Revision: 1.4 $ $Date: 2005/04/08 11:15:47 $
**/
public class UpdateFile implements java.io.Serializable {


      //--------------------------/
     //- Class/Member Variables -/
    //--------------------------/

    private java.lang.String _relativePath;

    private long _version;

    /**
     * keeps track of state for field: _version
    **/
    private boolean _has_version;

    private java.lang.String _downloadUrl;

    private int _size;

    /**
     * keeps track of state for field: _size
    **/
    private boolean _has_size;


      //----------------/
     //- Constructors -/
    //----------------/

    public UpdateFile() {
        super();
    } //-- de.freegroup.digitalsimulator.plugin.tool.LiveUpdate.castor.UpdateFile()


      //-----------/
     //- Methods -/
    //-----------/

    /**
    **/
    public java.lang.String getDownloadUrl()
    {
        return this._downloadUrl;
    } //-- java.lang.String getDownloadUrl() 

    /**
    **/
    public java.lang.String getRelativePath()
    {
        return this._relativePath;
    } //-- java.lang.String getRelativePath() 

    /**
    **/
    public int getSize()
    {
        return this._size;
    } //-- int getSize() 

    /**
    **/
    public long getVersion()
    {
        return this._version;
    } //-- long getVersion() 

    /**
    **/
    public boolean hasSize()
    {
        return this._has_size;
    } //-- boolean hasSize() 

    /**
    **/
    public boolean hasVersion()
    {
        return this._has_version;
    } //-- boolean hasVersion() 

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
     * 
     * @param downloadUrl
    **/
    public void setDownloadUrl(java.lang.String downloadUrl)
    {
        this._downloadUrl = downloadUrl;
    } //-- void setDownloadUrl(java.lang.String) 

    /**
     * 
     * @param relativePath
    **/
    public void setRelativePath(java.lang.String relativePath)
    {
        this._relativePath = relativePath;
    } //-- void setRelativePath(java.lang.String) 

    /**
     * 
     * @param size
    **/
    public void setSize(int size)
    {
        this._size = size;
        this._has_size = true;
    } //-- void setSize(int) 

    /**
     * 
     * @param version
    **/
    public void setVersion(long version)
    {
        this._version = version;
        this._has_version = true;
    } //-- void setVersion(long) 

    /**
     * 
     * @param reader
    **/
    public static de.freegroup.digitalsimulator.plugin.tool.LiveUpdate.castor.UpdateFile unmarshal(java.io.Reader reader)
        throws org.exolab.castor.xml.MarshalException, org.exolab.castor.xml.ValidationException
    {
        return (de.freegroup.digitalsimulator.plugin.tool.LiveUpdate.castor.UpdateFile) Unmarshaller.unmarshal(de.freegroup.digitalsimulator.plugin.tool.LiveUpdate.castor.UpdateFile.class, reader);
    } //-- de.freegroup.digitalsimulator.plugin.tool.LiveUpdate.castor.UpdateFile unmarshal(java.io.Reader) 

    /**
    **/
    public void validate()
        throws org.exolab.castor.xml.ValidationException
    {
        org.exolab.castor.xml.Validator validator = new org.exolab.castor.xml.Validator();
        validator.validate(this);
    } //-- void validate() 

}
