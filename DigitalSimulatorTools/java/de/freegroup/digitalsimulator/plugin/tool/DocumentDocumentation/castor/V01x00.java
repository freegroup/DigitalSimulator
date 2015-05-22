/*
 * This class was automatically generated with 
 * <a href="http://castor.exolab.org">Castor 0.9.2</a>, using an
 * XML Schema.
 * $Id: V01x00.java,v 1.4 2005/04/08 11:13:22 freegroup Exp $
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
public class V01x00 implements java.io.Serializable {


      //--------------------------/
     //- Class/Member Variables -/
    //--------------------------/

    private Author _author;

    private Circuit _circuit;


      //----------------/
     //- Constructors -/
    //----------------/

    public V01x00() {
        super();
    } //-- de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.V01x00()


      //-----------/
     //- Methods -/
    //-----------/

    /**
    **/
    public Author getAuthor()
    {
        return this._author;
    } //-- Author getAuthor() 

    /**
    **/
    public Circuit getCircuit()
    {
        return this._circuit;
    } //-- Circuit getCircuit() 

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
     * @param author
    **/
    public void setAuthor(Author author)
    {
        this._author = author;
    } //-- void setAuthor(Author) 

    /**
     * 
     * @param circuit
    **/
    public void setCircuit(Circuit circuit)
    {
        this._circuit = circuit;
    } //-- void setCircuit(Circuit) 

    /**
     * 
     * @param reader
    **/
    public static de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.V01x00 unmarshal(java.io.Reader reader)
        throws org.exolab.castor.xml.MarshalException, org.exolab.castor.xml.ValidationException
    {
        return (de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.V01x00) Unmarshaller.unmarshal(de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.V01x00.class, reader);
    } //-- de.freegroup.digitalsimulator.plugin.tool.DocumentDocumentation.castor.V01x00 unmarshal(java.io.Reader) 

    /**
    **/
    public void validate()
        throws org.exolab.castor.xml.ValidationException
    {
        org.exolab.castor.xml.Validator validator = new org.exolab.castor.xml.Validator();
        validator.validate(this);
    } //-- void validate() 

}
