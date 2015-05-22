/*
 * This class was automatically generated with 
 * <a href="http://castor.exolab.org">Castor 0.9.2</a>, using an
 * XML Schema.
 * $Id: Author.java,v 1.4 2005/04/08 11:13:22 freegroup Exp $
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
public class Author implements java.io.Serializable {


      //--------------------------/
     //- Class/Member Variables -/
    //--------------------------/

    private java.lang.String _firstName;

    private java.lang.String _lastName;

    private java.lang.String _street;

    private java.lang.String _number;

    private java.lang.String _city;

    private java.lang.String _zipCode;

    private java.lang.String _eMail;


      //----------------/
     //- Constructors -/
    //----------------/

    public Author() {
        super();
    } //-- de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.Author()


      //-----------/
     //- Methods -/
    //-----------/

    /**
    **/
    public java.lang.String getCity()
    {
        return this._city;
    } //-- java.lang.String getCity() 

    /**
    **/
    public java.lang.String getEMail()
    {
        return this._eMail;
    } //-- java.lang.String getEMail() 

    /**
    **/
    public java.lang.String getFirstName()
    {
        return this._firstName;
    } //-- java.lang.String getFirstName() 

    /**
    **/
    public java.lang.String getLastName()
    {
        return this._lastName;
    } //-- java.lang.String getLastName() 

    /**
    **/
    public java.lang.String getNumber()
    {
        return this._number;
    } //-- java.lang.String getNumber() 

    /**
    **/
    public java.lang.String getStreet()
    {
        return this._street;
    } //-- java.lang.String getStreet() 

    /**
    **/
    public java.lang.String getZipCode()
    {
        return this._zipCode;
    } //-- java.lang.String getZipCode() 

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
     * @param city
    **/
    public void setCity(java.lang.String city)
    {
        this._city = city;
    } //-- void setCity(java.lang.String) 

    /**
     * 
     * @param eMail
    **/
    public void setEMail(java.lang.String eMail)
    {
        this._eMail = eMail;
    } //-- void setEMail(java.lang.String) 

    /**
     * 
     * @param firstName
    **/
    public void setFirstName(java.lang.String firstName)
    {
        this._firstName = firstName;
    } //-- void setFirstName(java.lang.String) 

    /**
     * 
     * @param lastName
    **/
    public void setLastName(java.lang.String lastName)
    {
        this._lastName = lastName;
    } //-- void setLastName(java.lang.String) 

    /**
     * 
     * @param number
    **/
    public void setNumber(java.lang.String number)
    {
        this._number = number;
    } //-- void setNumber(java.lang.String) 

    /**
     * 
     * @param street
    **/
    public void setStreet(java.lang.String street)
    {
        this._street = street;
    } //-- void setStreet(java.lang.String) 

    /**
     * 
     * @param zipCode
    **/
    public void setZipCode(java.lang.String zipCode)
    {
        this._zipCode = zipCode;
    } //-- void setZipCode(java.lang.String) 

    /**
     * 
     * @param reader
    **/
    public static de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.Author unmarshal(java.io.Reader reader)
        throws org.exolab.castor.xml.MarshalException, org.exolab.castor.xml.ValidationException
    {
        return (de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.Author) Unmarshaller.unmarshal(de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.Author.class, reader);
    } //-- de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.Author unmarshal(java.io.Reader) 

    /**
    **/
    public void validate()
        throws org.exolab.castor.xml.ValidationException
    {
        org.exolab.castor.xml.Validator validator = new org.exolab.castor.xml.Validator();
        validator.validate(this);
    } //-- void validate() 

}
