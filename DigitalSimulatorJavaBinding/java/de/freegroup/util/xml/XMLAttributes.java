/*
 * Copyright (c) 2000 Statistisches Bundesamt
 *
 * Datei: XMLAttributes.java
 *
 * Änderungshistorie:
 *
 * Nr ! Datum    ! Name            ! Änderungsgrund
 * -----------------------------------------------------------------------------
 *  1 ! 27.10.00 ! Herz            ! neu erstellt
 *
 */

package de.freegroup.util.xml;

import org.xml.sax.helpers.AttributesImpl;

/**
 * Diese Klasse <code>XMLAttributes</code> implementiert das einfache 
 * Setzen und Auslesen von Attributen eines XML-Elements. Diese
 * Klasse wird von {@link XMLWriter} zum Schreiben benutzt. Es soll die jeweilige
 * benutzte SAX-Version verschleiern, da es verschiedene Implementierungen
 * mit dem Namen dieser Klasse gibt.
 * <p>
 * Weiterhin soll diese Klasse eine einfach Migration von 
 * <code>java.util.jar.Attributes</code> nach <code>org.xml.sax.Attributes</code>
 * ermöglichen.
**/
public class XMLAttributes extends AttributesImpl
    {
    /**
     * Konstruktur, erzeugt eine Menge von XML-Attributen, die 
     * für ein XML-Element gesetzt werden kann.
    **/
    public XMLAttributes()
        {
        super();
        }

    /**
     * Konstruktur, erzeugt eine Menge von XML-Attributen, die 
     * für ein XML-Element gesetzt werden kann.
     *
     * @deprecated Die Anzahl der Attributmenge braucht nicht mehr angegeben zu werden.
    **/
    public XMLAttributes( int size )
        {
        super();
        }

    /**
     * Ruft {@link #add(String, String} auf.
     *
     * @deprecated Bitte {@link #add(String, String} aufrufen.
    **/
    public void putValue( String key, String value )
        {
        add( key, value );
        }

    /**
     * Fügt ein Attribute in diese Menge hinzu.
    **/
    public void add( String key, String value )
        {
        addAttribute( /* uri       */ null, 
                      /* localName */ null, 
                      /* qName     */ key, 
                      /* type      */ "CDATA", 
                      value );
        }
    }  //End of class
