/*
 * This class was automatically generated with 
 * <a href="http://castor.exolab.org">Castor 0.9.2</a>, using an
 * XML Schema.
 * $Id: Circuit.java,v 1.4 2005/04/08 11:13:22 freegroup Exp $
 */

package de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor;

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
 * @version $Revision: 1.4 $ $Date: 2005/04/08 11:13:22 $
**/
public class Circuit implements java.io.Serializable {


      //--------------------------/
     //- Class/Member Variables -/
    //--------------------------/

    private java.lang.String _name;

    private java.lang.String _shortDescription;

    private java.lang.String _longDescription;

    private java.lang.String _version;


      //----------------/
     //- Constructors -/
    //----------------/

    public Circuit() {
        super();
    } //-- de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.Circuit()


      //-----------/
     //- Methods -/
    //-----------/

    /**
    **/
    public java.lang.String getLongDescription()
    {
        return this._longDescription;
    } //-- java.lang.String getLongDescription() 

    /**
    **/
    public java.lang.String getName()
    {
        return this._name;
    } //-- java.lang.String getName() 

    /**
    **/
    public java.lang.String getShortDescription()
    {
        return this._shortDescription;
    } //-- java.lang.String getShortDescription() 

    /**
    **/
    public java.lang.String getVersion()
    {
        return this._version;
    } //-- java.lang.String getVersion() 

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
     * @param longDescription
    **/
    public void setLongDescription(java.lang.String longDescription)
    {
        this._longDescription = longDescription;
    } //-- void setLongDescription(java.lang.String) 

    /**
     * 
     * @param name
    **/
    public void setName(java.lang.String name)
    {
        this._name = name;
    } //-- void setName(java.lang.String) 

    /**
     * 
     * @param shortDescription
    **/
    public void setShortDescription(java.lang.String shortDescription)
    {
        this._shortDescription = shortDescription;
    } //-- void setShortDescription(java.lang.String) 

    /**
     * 
     * @param version
    **/
    public void setVersion(java.lang.String version)
    {
        this._version = version;
    } //-- void setVersion(java.lang.String) 

    /**
     * 
     * @param reader
    **/
    public static de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.Circuit unmarshal(java.io.Reader reader)
        throws org.exolab.castor.xml.MarshalException, org.exolab.castor.xml.ValidationException
    {
        return (de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.Circuit) Unmarshaller.unmarshal(de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.Circuit.class, reader);
    } //-- de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.Circuit unmarshal(java.io.Reader) 

    /**
    **/
    public void validate()
        throws org.exolab.castor.xml.ValidationException
    {
        org.exolab.castor.xml.Validator validator = new org.exolab.castor.xml.Validator();
        validator.validate(this);
    } //-- void validate() 

}
