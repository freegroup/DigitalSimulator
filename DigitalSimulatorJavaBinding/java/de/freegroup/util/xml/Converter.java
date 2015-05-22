package de.freegroup.util.xml;
/**
 * Title: FWT-EAI
 * Description: EAI Integration Layer for FWT-SMC Portal
 * Copyright:    Copyright (c) 2003
 * Company: OneStepAhead
 * Created: Apr 7, 2003 4:01:54 PM
 * @author Andreas Herz
 * @version 1.0
 */
public class Converter
{
	// specialChar[x][0] contiene il carattere speciale, specialChar[x][1] contiene la traduzione xml
	public static final String[][] specialChar = {
		{   "&", "&amp;"  }, // &
		{
			"�", "&#161;" }, // � inverted exclamation
		{
			"�", "&#162;" }, // � cent sign
		{
			"�", "&#163;" }, // � pound sterling
		{
			"�", "&#164;" }, // � general currency sign
		{
			"�", "&#165;" }, // � yen sign
		{
			"�", "&#166;" }, // � broken vertical bar
		{
			"�", "&#167;" }, // � section sign
		{
			"�", "&#168;" }, // � umlaut
		{
			"�", "&#169;" }, // � copyright
		{
			"�", "&#170;" }, // � feminine ordinal
		{
			"�", "&#171;" }, // � left angle quote
		{
			"�", "&#172;" }, // � not sign
		{
			"�", "&#173;" }, // � soft hyphen
		{
			"�", "&#174;" }, // � registered trademark
		{
			"�", "&#175;" }, // � macron accent
		{
			"�", "&#176;" }, // � degree sign
		{
			"�", "&#177;" }, //� plus or minus
		{
			"�", "&#178;" }, // � superscript two
		{
			"�", "&#179;" }, // � superscript three
		{
			"�", "&#180;" }, //� acute accent
		{
			"�", "&#181;" }, // � micro sign
		{
			"�", "&#182;" }, // � paragraph sign
		{
			"�", "&#183;" }, // � middle dot
		{
			"�", "&#184;" }, // � cedilla
		{
			"�", "&#185;" }, // � superscript one
		{
			"�", "&#186;" }, // � masculine ordinal
		{
			"�", "&#187;" }, // � right angle quote
		{
			"�", "&#188;" }, // � one-fourth
		{
			"�", " &#189;" }, // � one-half
		{
			"�", "&#190;" }, // � three-fourths
		{
			"�", "&#191;" }, // � inverted question mark
		{
			"�", "&#192;" }, // � uppercase A, grave accent
		{
			"�", "&#193;" }, // � uppercase A, acute accent
		{
			"�", "&#194;" }, // � uppercase A, circumflex accent
		{
			"�", "&#195;" }, // � uppercase A, tilde
		{
			"�", "&#196;" }, // � uppercase A, umlaut
		{
			"�", "&#197;" }, // � uppercase A, ring
		{
			"�", "&#198;" }, // � uppercase AE
		{
			"�", "&#199;" }, // � uppercase C, cedilla
		{
			"�", "&#200;" }, // � uppercase E, grave accent
		{
			"�", "&#201;" }, // � uppercase E, acute accent
		{
			"�", "&#202;" }, // � uppercase E, circumflex accent
		{
			"�", "&#203;" }, // � uppercase E, umlaut
		{
			"�", "&#204;" }, // � uppercase I, grave accent
		{
			"�", "&#205;" }, // � uppercase I, acute accent
		{
			"�", "&#206;" }, // � uppercase I, circumflex accent
		{
			"�", "&#207;" }, // � uppercase I, umlaut
		{
			"�", "&#208;" }, // � uppercase Eth, Icelandic
		{
			"�", "&#209;" }, // � uppercase N, tilde
		{
			"�", "&#210;" }, // � uppercase O, grave accent
		{
			"�", "&#211;" }, // � uppercase O, acute accent
		{
			"�", "&#212;" }, // � uppercase O, circumflex accent
		{
			"�", "&#213;" }, // � uppercase O, tilde
		{
			"�", "&#214;" }, // � uppercase O, umlaut
		{
			"�", "&#215;" }, // � multiplication sign
		{
			"�", "&#216;" }, // � uppercase O, slash
		{
			"�", "&#217;" }, // � uppercase U, grave accent
		{
			"�", "&#218;" }, // � uppercase U, acute accent
		{
			"�", "&#219;" }, // � uppercase U, circumflex accent
		{
			"�", "&#220;" }, // � uppercase U, umlaut
		{
			"�", "&#221;" }, // � uppercase Y, acute accent
		{
			"�", "&#222;" }, // � uppercase THORN, Icelandic
		{
			"�", "&#223;" }, // � lowercase sharps, German
		{
			"�", "&#224;" }, // � lowercase a, grave accent
		{
			"�", "&#225;" }, // � lowercase a, acute accent
		{
			"�", "&#226;" }, // � lowercase a, circumflex accent
		{
			"�", "&#227;" }, // � lowercase a, tilde
		{
			"�", "&#228;" }, // � lowercase a, umlaut
		{
			"�", "&#229;" }, // � lowercase a, ring
		{
			"�", "&#230;" }, // � lowercase ae
		{
			"�", "&#231;" }, // � lowercase c, cedilla
		{
			"�", "&#232;" }, // � lowercase e, grave accent
		{
			"�", "&#233;" }, // � lowercase e, acute accent
		{
			"�", "&#234;" }, // � lowercase e, circumflex accent
		{
			"�", "&#235;" }, // � lowercase e, umlaut
		{
			"�", "&#236;" }, // � lowercase i, grave accent
		{
			"�", "&#237;" }, // � lowercase i, acute accent
		{
			"�", "&#238;" }, // � lowercase i, circumflex accent
		{
			"�", "&#239;" }, // � lowercase i, umlaut
		{
			"�", "&#240;" }, // � lowercase eth, Icelandic
		{
			"�", "&#241;" }, // � lowercase n, tilde
		{
			"�", "&#242;" }, // � lowercase o, grave accent
		{
			"�", "&#243;" }, // � lowercase o, acute accent
		{
			"�", "&#244;" }, // � lowercase o, circumflex accent
		{
			"�", "&#245;" }, // � lowercase o, tilde
		{
			"�", "&#246;" }, // � lowercase o, umlaut
		{
			"�", "&#247;" }, // � division sign
		{
			"�", "&#248;" }, // � lowercase o, slash
		{
			"�", "&#249;" }, // � lowercase u, grave accent
		{
			"�", "&#250;" }, // � lowercase u, acute accent
		{
			"�", "&#251;" }, // � lowercase u, circumflex accent
		{
			"�", "&#252;" }, // � lowercase u, umlaut
		{
			"�", "&#253;" }, // � lowercase y, acute accent
		{
			"�", "&#254;" }, // � lowercase thorn, Icelandic
		{
			"�", " &#255;" }, // � lowercase y, umlaut
		{
			"`", "&#96;" }, //
		{
			"<", "&lt;" }, //
		{
			">", "&gt;" } //
	};
	/**
	* Metodo che sostituisce alcuni caratteri speciali per la corretta visualizzazione dei testi negli XSL
	*
	* @param input la stringa in cui sostituire i caratteri
	* @return la stringa con le opportune sostituzioni
	*/
	public static String encode(String input)
	{
		for (int i = 0; i < specialChar.length; i++)
		{
			input = replaceString(input, specialChar[i][0], specialChar[i][1]);
		}
		return input;
	}
	/**
	* Metodo che sostituisce alcuni caratteri speciali per la corretta visualizzazione dei testi negli XSL
	*
	* @param input la stringa in cui sostituire i caratteri
	* @return la stringa con le opportune sostituzioni
	*/
	public static String decode(String input)
	{
		for (int i = 0; i < specialChar.length; i++)
		{
			input = replaceString(input, specialChar[i][1], specialChar[i][0]);
		}
		return input;
	}
	/**
	* Metodo che sostituisce nella stringa di input la sotto-stringa desiderata con una nuova sottostringa. Sostituisce la vecchia 'replaceVirg'
	* rendendola pi� generale.
	* Es. replaceString ("bla'bla'bla","'","''") --> "bla''bla''bla"
	*
	* @param la stringa in cui sostituire la 'oldString' con la 'newString'
	* @param la sotto-stringa da sostituire
	* @param la sotto-stringa sostituente
	* @return la stringa con le opportune sostituzioni
	*/
	public static synchronized String replaceString(	String input,String oldString,String newString)
	{
		StringBuffer out = new StringBuffer();
		int last = 0;
		while (input.indexOf(oldString) != -1)
		{
			String tok = input.substring(0, input.indexOf(oldString));
			last = input.indexOf(oldString) + oldString.length();
			input = input.substring(last, input.length());
			out.append(tok + newString);
		}
		out.append(input);
		return out.toString();
	}
}
