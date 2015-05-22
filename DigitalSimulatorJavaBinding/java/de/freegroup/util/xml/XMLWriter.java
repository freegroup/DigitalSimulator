/*
 * Copyright (c) 2000 Statistisches Bundesamt
 *
 * Datei: XMLWriter.java
 *
 * Änderungshistorie:
 *
 * Nr ! Datum    ! Name            ! Änderungsgrund
 * -----------------------------------------------------------------------------
 *  1 ! 20.02.01 ! Herz            ! neu erstellt
 *
 */
package de.freegroup.util.xml;
import java.io.IOException;
import java.io.InputStream;
import java.io.StringWriter;
import java.io.Writer;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.Map;
import java.util.Stack;

import javax.swing.text.AttributeSet;

import org.xml.sax.Attributes;
/**
 * Diese Klasse ist eine Hilfsklasse zur Erstellung eines 
 * XML Stroms. Sie bietet Methoden an, um Elemente und 
 * Attribute zu schreiben.
**/
public class XMLWriter
{
	/**
	 * Schreibe in diesen Strom
	**/
	private Writer myWriter;
	/**
	 * Merke die Tags auf einem Stack
	**/
	private Stack myTagStack = new Stack();
	/**
	 * XML Konstante
	**/
	private static final String head =
		"<?xml version=\"1.0\" encoding=\"ISO-8859-1\" standalone=\"yes\" ?>\n";
	/**
	 * XML Konstante
	**/
	private static final String beginTag = "<";
	/**
	 * XML Konstante
	**/
	private static final String endTag = ">";
	/**
	 * XML Konstante
	**/
	private static final String endTagEmpty = "/>";
	/**
	 * XML Konstante
	**/
	private static final String beginTagSingle = "</";
	/**
	 * XML Konstante
	**/
	private static final String space = " ";
	/**
	 * XML Konstante
	**/
	private static final String beginAssign = "=\"";
	/**
	 * XML Konstante
	**/
	private static final String endAssign = "\"";
	/**
	 * Initiiere diesen Strom mit dem Writer-Objekt. Es wird
	 * der Standard-XML-Kopf an den Anfang gestellt.
	**/
	public XMLWriter(Writer writer) throws IOException
	{
		this(writer, true);
	}
	/**
	 * Initiiere diesen Strom mit dem Writer-Objekt. Mit dem Parameter
	 * XMLhead kann der Standard-XML-Kopf an den Anfang gestellt werden.
	**/
	public XMLWriter(Writer writer, boolean XMLhead) throws IOException
	{
		myWriter = writer;
		if (XMLhead)
			myWriter.write(head);
	}
	/**
	 * Schreibe ein leeres Tag (Tag mit leerem Wert ) in den XML Strom.
	**/
	public void element(String tag) throws IOException
	{
		myWriter.write(beginTag + tag + endTagEmpty);
	}
	/**
	 * Schreibe ein vollständiges Element mit Tag und Wert in diesen Strom.
	**/
	public void element(String tag, String value) throws IOException
	{
		if (value == null || value.length() == 0)
			element(tag);
		else
			myWriter.write(
				beginTag
					+ tag
					+ endTag
					+ valueToXML(value)
					+ beginTagSingle
					+ tag
					+ endTag);
	}
	/**
	 * Schreibt ein vollständiges Element mit Tag und Wert in diesen Strom.
	**/
	public void element(String tag, long value) throws IOException
	{
		element(tag, String.valueOf(value));
	}
	/**
	 * Schreibe ein vollständiges Element mit Tag und Wert in diesen Strom.
	**/
	public void element(
		String tag,
		String value,
		String attributeTag,
		String attributeValue)
		throws IOException
	{
		if (value == null || value.length() == 0)
			myWriter.write(
				beginTag
					+ tag
					+ space
					+ attributeTag
					+ beginAssign
					+ valueToXML(attributeValue)
					+ endAssign
					+ endTagEmpty);
		else
			myWriter.write(
				beginTag
					+ tag
					+ space
					+ attributeTag
					+ beginAssign
					+ valueToXML(attributeValue)
					+ endAssign
					+ endTag
					+ valueToXML(value)
					+ beginTagSingle
					+ tag
					+ endTag);
	}
	/**
	 * Schreibe ein vollständiges Element mit Tag und Wert in diesen Strom.
	**/
	public void element(
		String tag,
		String value,
		String attributeTag,
		int attributeValue)
		throws IOException
	{
		element(tag, value, attributeTag, String.valueOf(attributeValue));
	}
	/**
	 * Es wird ein einzelnes Element (ohne Wert) und seinen Attributen in den
	 * XML Strom geschrieben.
	**/
	public void element(String tag, AttributeSet attributeList)
		throws IOException
	{
		myWriter.write(beginTag + tag);
		for (Enumeration e = attributeList.getAttributeNames();
			e.hasMoreElements();
			)
		{
			Object key = e.nextElement();
			String val = (String) attributeList.getAttribute(key);
			myWriter.write(
				space + key + beginAssign + valueToXML(val) + endAssign);
		}
		myWriter.write(endTagEmpty);
	}
	/**
	 * Es wird ein einzelnes Element mit Wert und seinen Attributen in den
	 * XML Strom geschrieben.
	**/
	public void element(String tag, String value, AttributeSet attributeList)
		throws IOException
	{
		myWriter.write(beginTag + tag);
		for (Enumeration e = attributeList.getAttributeNames();
			e.hasMoreElements();
			)
		{
			Object key = e.nextElement();
			String val = (String) attributeList.getAttribute(key);
			myWriter.write(
				space + key + beginAssign + valueToXML(val) + endAssign);
		}
		myWriter.write(
			endTag + valueToXML(value) + beginTagSingle + tag + endTag);
	}
	/**
	 * Schreibt ein Tag mit folgenden Attributen aus der Attribut-Liste
	 * in diesem XML Strom.
	 * Die Attribute-Liste besteht aus einer Menge von Keys mit Werten.
	 * <br>
	 * Die Attribute-Liste kann wie folgt erzeugt werden: <br>
	 * <code>
	 * Attributes a = new Attributes( 2 );
	 * a.putValue( "mark", r.getMark() );
	 * a.putValue( "requestindex", String.valueOf( i + 1 ) );
	 * </code>
	**/
	public void element(String tag, Attributes attributes) throws IOException
	{
		myWriter.write(beginTag + tag);
		if (attributes != null)
		{
			for (int i = 0; i < attributes.getLength(); i++)
			{
				String key = attributes.getQName(i);
				String val = attributes.getValue(i);
				myWriter.write(
					space + key + beginAssign + valueToXML(val) + endAssign);
			}
		}
		myWriter.write(endTagEmpty);
	}
	/**
	 * Schreibt ein Tag mit folgenden Attributen aus der Attribut-Liste
	 * und dem Wert in diesem XML Strom.
	 * Die Attribute-Liste besteht aus einer Menge von Keys mit Werten.
	 * <br>
	 * Die Attribute-Liste kann wie folgt erzeugt werden: <br>
	 * <code>
	 * Attributes a = new Attributes( 2 );
	 * a.putValue( "mark", r.getMark() );
	 * a.putValue( "requestindex", String.valueOf( i + 1 ) );
	 * </code>
	**/
	public void element(String tag, org.xml.sax.Attributes attributes, String value)
		throws IOException
	{
		elementBegin(tag, attributes);
		elementValue(value);
		elementEnd();
	}
	
	/**
	 * Schreibt nur einen Wert. Das Tag muss schon vorher durch den Methodenaufrufe 
	 * {@link #elementBegin(String)} gesetzt sein,
	**/
	public void elementValue(String value) throws IOException
	{
		myWriter.write(valueToXML(value));
	}
	/**
	 * Schreibe ein Tag in den Strom. Es beginnt eine geschachtelte Struktur.
	 * Das Ende der Struktur mit dem Tag wird durch die Methode 
	 * {@link #elementEnd()} gesetzt.
	**/
	public void elementBegin(String tag) throws IOException
	{
		myWriter.write(beginTag + tag + endTag);
		myTagStack.push(tag);
	}
	/**
	 * Schreibe ein Tag in den Strom. Es beginnt eine geschachtelte Struktur.
	 * Das Ende der Struktur mit dem Tag wird durch die Methode 
	 * {@link #elementEnd()} gesetzt. Bei diesem Tag muss ein Attribut gesetzt
	 * werden.
	**/
	public void elementBegin(
		String tag,
		String attributeTag,
		int attributeValue)
		throws IOException
	{
		elementBegin(tag, attributeTag, String.valueOf(attributeValue));
	}
	/**
	 * Schreibe ein Tag in den Strom. Es beginnt eine geschachtelte Struktur.
	 * Das Ende der Struktur mit dem Tag wird durch die Methode 
	 * {@link #elementEnd()} gesetzt. Bei diesem Tag muss ein Attribut gesetzt
	 * werden.
	**/
	public void elementBegin(
		String tag,
		String attributeTag,
		String attributeValue)
		throws IOException
	{
		myWriter.write(
			beginTag
				+ tag
				+ space
				+ attributeTag
				+ beginAssign
				+ valueToXML(attributeValue)
				+ endAssign
				+ endTag);
		myTagStack.push(tag);
	}
	/**
	 * Schreibt ein Tag mit folgenden Attributen aus der Attribut-Liste
	 * in diesem XML Strom.
	 * Die Attribute-Liste besteht aus einer Menge von Keys mit Werten.
	 * <br>
	 * Die Attribute-Liste kann wie folgt erzeugt werden: <br>
	 * <pre>
	 * Attributes a = new Attributes( 2 );
	 * a.putValue( "mark", r.getMark() );
	 * a.putValue( "requestindex", String.valueOf( i + 1 ) );
	 * </pre>
	 * Das Ende der Struktur von diesem Tag muss durch die Methode 
	 * {@link #elementEnd()} gesetzt.
	**/
	public void elementBegin(String tag, java.util.jar.Attributes attributes)
		throws IOException
	{
		myWriter.write(beginTag + tag);
		if (attributes != null)
		{
			Iterator iter = attributes.entrySet().iterator();
			while (iter.hasNext())
			{
				Map.Entry element = (Map.Entry) iter.next();
				myWriter.write(
					space
						+ element.getKey()
						+ beginAssign
						+ valueToXML((String) element.getValue())
						+ endAssign);
			}
		}
		myWriter.write(endTag);
		myTagStack.push(tag);
	}
	
	

	/**
	 * Schreibt ein Tag mit folgenden Attributen aus der Attribut-Liste
	 * in diesem XML Strom.
	 * Die Attribute-Liste besteht aus einer Menge von Keys mit Werten.
	 * <br>
	 * Die Attribute-Liste kann wie folgt erzeugt werden: <br>
	 * <pre>
	 * Attributes a = new Attributes( 2 );
	 * a.putValue( "mark", r.getMark() );
	 * a.putValue( "requestindex", String.valueOf( i + 1 ) );
	 * </pre>
	 * Das Ende der Struktur von diesem Tag muss durch die Methode 
	 * {@link #elementEnd()} gesetzt.
	**/
	public void elementBegin( String tag, org.xml.sax.Attributes attributes )
		throws IOException
		{
		myWriter.write( beginTag + tag ); 

		if ( attributes != null )
			{
			for ( int i = 0; i < attributes.getLength(); i++ )
				{
				String key = attributes.getQName( i );
				String val = attributes.getValue( i );
                
				myWriter.write( space + key + beginAssign + valueToXML( val ) + endAssign );
				}
			}        

		myWriter.write( endTag );
        
		myTagStack.push( tag );
		}
	
	/**
	 * Schreibt ein Tag mit folgenden Attributen aus der Attribut-Liste
	 * in diesem XML Strom.
	 * Die Attribute-Liste besteht aus einer Menge von Keys mit Werten.
	 * <br>
	 * Das Ende der Struktur von diesem Tag wird durch die Methode 
	 * {@link #elementEnd()} gesetzt.
	**/
	public void elementBegin(String tag, AttributeSet attributeList)
		throws IOException
	{
		myWriter.write(beginTag + tag);
		for (Enumeration e = attributeList.getAttributeNames();
			e.hasMoreElements();
			)
		{
			Object key = e.nextElement();
			String val = (String) attributeList.getAttribute(key);
			myWriter.write(
				space + key + beginAssign + valueToXML(val) + endAssign);
		}
		myWriter.write(endTag);
		myTagStack.push(tag);
	}
	/**
	 * Beende eine Struktur, die mit {@link #elementBegin(String)} 
	 * eingeleitet worden ist.
	**/
	public void elementEnd() throws IOException
	{
		myWriter.write(beginTagSingle + (String) myTagStack.pop() + endTag);
	}
	/**
	 * Schliesst alle Elemente mit {@link #elementEnd()}, bis nur noch eine
	 * bestimmte Anzahl (level) vorhanden sind.
	 *
	 * @param level Anzahl, die übrig bleiben sollen
	**/
	private void elementEndUntil(int level) throws IOException
	{
		while (myTagStack.size() > level)
		{
			elementEnd();
		}
	}
	/**
	 * Schlieest alle Elemente mit {@link #elementEnd()}, bis nur noch eins,
	 * das Oberste, übrig ist.
	**/
	public void elementEndUntilTop() throws IOException
	{
		elementEndUntil(1);
	}
	/**
	 * Schlieest alle Elemente mit {@link #elementEnd()}.
	**/
	public void elementEndAll() throws IOException
	{
		elementEndUntil(0);
	}
	/**
	 * Schreibe den Inhalt von <code>value</code> in den Writer.
	**/
	public void element(String tag, InputStream value) throws IOException
	{
		elementBegin(tag);
		char[] s = new char[1];
		int c = value.read();
		while (c > -1)
		{
			s[0] = (char) c;
			elementValue(new String(s));
			//myWriter.write( c );
			c = value.read();
		}
		elementEnd();
	}
	/**
	 * Liefert TRUE zurück, falls kein Element mehr offen ist.
	**/
	public boolean isAllElementClosed()
	{
		return myTagStack.empty();
	}
	/**
	 * Schreiben einen Kommentar in den XML Strom.
	**/
	public void comment(String s) throws IOException
	{
		myWriter.write("<!-- " + s + " -->");
	}
	/**
	 * Gebe das Writer-Objekt zurück.
	**/
	public Writer getWriter()
	{
		return myWriter;
	}
	/**
	 * Gebe den XML Strom als String zurück.
	**/
	public String toString()
	{
		return ((StringWriter) getWriter()).toString();
	}
	/**
	 * Schliesse den XML-Datenstrom
	**/
	public void close() throws IOException
	{
		getWriter().close();
	}
	/**
	 * Liefert den Stack der aktuellen schachtelten XML-Tags.
	**/
	protected Stack getTagStack()
	{
		return myTagStack;
	}
	/**
	 * Liefert die Anzahl der aktuellen schachtelten XML-Tags.
	**/
	protected int getTagLevel()
	{
		return myTagStack.size();
	}
	/**
	 * Ersetze alle 'normalen' Zeichen im String <code>value</code>
	 * durch XML Zeichen.
	**/
	public static String valueToXML(String value)
	{
		value = valueToXML(value, '&', "&#038;"); //Als erstes !
		value = valueToXML(value, '<', "&lt;"); // &#060; oder &lt;
		value = valueToXML(value, '>', "&gt;"); // &#062; oder &gt;
		value = valueToXML(value, 'ä', "&#228;");
		value = valueToXML(value, 'ö', "&#246;");
		value = valueToXML(value, 'ü', "&#252;");
		value = valueToXML(value, 'Ä', "&#196;");
		value = valueToXML(value, 'Ö', "&#214;");
		value = valueToXML(value, 'Ü', "&#220;");
		value = valueToXML(value, 'ß', "&#223;");
		value = valueToXML(value, 1, ";");
		return value;
	}
	/**
	 * Ersetzt das Zeichen <code>ch</code> im String <code>value</code>
	 * mit dem String <code>replaceWith</code>.
	**/
	private static String valueToXML(String value, int ch, String replaceWith)
	{
		if (value == null)
			return null;
		int i = value.indexOf(ch);
		if (i < 0)
			return value;
		if (i == 0)			//erstes Zeichen
			return replaceWith
				+ valueToXML(value.substring(1), ch, replaceWith);
		else
			if (i + 1 == value.length())				//letztes Zeichen
				return value.substring(0, value.length() - 1) + replaceWith;
			else				//in der Mitte
				return value.substring(0, i)
					+ replaceWith
					+ valueToXML(value.substring(i + 1), ch, replaceWith);
	}
	/**
	 * Testfunktion
	**/
	public static void main(String[] s)
	{
		System.out.println(valueToXML(s[0]));
	}
} //END CLASS
