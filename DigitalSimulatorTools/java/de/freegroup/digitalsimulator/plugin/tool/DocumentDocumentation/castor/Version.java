/*
 * This class was automatically generated with 
 * <a href="http://castor.exolab.org">Castor 0.9.2</a>, using an
 * XML Schema.
 * $Id: Version.java,v 1.4 2005/04/08 11:13:22 freegroup Exp $
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
public class Version implements java.io.Serializable {


      //--------------------------/
     //- Class/Member Variables -/
    //--------------------------/

    private V01x00 _v01x00;


      //----------------/
     //- Constructors -/
    //----------------/

    public Version() {
        super();
    } //-- de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.Version()


      //-----------/
     //- Methods -/
    //-----------/

    /**
    **/
    public V01x00 getV01x00()
    {
        return this._v01x00;
    } //-- V01x00 getV01x00() 

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
     * @param v01x00
    **/
    public void setV01x00(V01x00 v01x00)
    {
        this._v01x00 = v01x00;
    } //-- void setV01x00(V01x00) 

    /**
     * 
     * @param reader
    **/
    public static de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.Version unmarshal(java.io.Reader reader)
        throws org.exolab.castor.xml.MarshalException, org.exolab.castor.xml.ValidationException
    {
        return (de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.Version) Unmarshaller.unmarshal(de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.Version.class, reader);
    } //-- de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.Version unmarshal(java.io.Reader) 

    /**
    **/
    public void validate()
        throws org.exolab.castor.xml.ValidationException
    {
        org.exolab.castor.xml.Validator validator = new org.exolab.castor.xml.Validator();
        validator.validate(this);
    } //-- void validate() 

}
