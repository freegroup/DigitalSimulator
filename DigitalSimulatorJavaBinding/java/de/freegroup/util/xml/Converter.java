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
			"¡", "&#161;" }, // ¡ inverted exclamation
		{
			"¢", "&#162;" }, // ¢ cent sign
		{
			"£", "&#163;" }, // £ pound sterling
		{
			"¤", "&#164;" }, // ¤ general currency sign
		{
			"¥", "&#165;" }, // ¥ yen sign
		{
			"¦", "&#166;" }, // ¦ broken vertical bar
		{
			"§", "&#167;" }, // § section sign
		{
			"¨", "&#168;" }, // ¨ umlaut
		{
			"©", "&#169;" }, // © copyright
		{
			"ª", "&#170;" }, // ª feminine ordinal
		{
			"«", "&#171;" }, // « left angle quote
		{
			"¬", "&#172;" }, // ¬ not sign
		{
			"­", "&#173;" }, // ­ soft hyphen
		{
			"®", "&#174;" }, // ® registered trademark
		{
			"¯", "&#175;" }, // ¯ macron accent
		{
			"°", "&#176;" }, // ° degree sign
		{
			"±", "&#177;" }, //± plus or minus
		{
			"²", "&#178;" }, // ² superscript two
		{
			"³", "&#179;" }, // ³ superscript three
		{
			"´", "&#180;" }, //´ acute accent
		{
			"µ", "&#181;" }, // µ micro sign
		{
			"¶", "&#182;" }, // ¶ paragraph sign
		{
			"·", "&#183;" }, // · middle dot
		{
			"¸", "&#184;" }, // ¸ cedilla
		{
			"¹", "&#185;" }, // ¹ superscript one
		{
			"º", "&#186;" }, // º masculine ordinal
		{
			"»", "&#187;" }, // » right angle quote
		{
			"¼", "&#188;" }, // ¼ one-fourth
		{
			"½", " &#189;" }, // ½ one-half
		{
			"¾", "&#190;" }, // ¾ three-fourths
		{
			"¿", "&#191;" }, // ¿ inverted question mark
		{
			"À", "&#192;" }, // À uppercase A, grave accent
		{
			"Á", "&#193;" }, // Á uppercase A, acute accent
		{
			"Â", "&#194;" }, // Â uppercase A, circumflex accent
		{
			"Ã", "&#195;" }, // Ã uppercase A, tilde
		{
			"Ä", "&#196;" }, // Ä uppercase A, umlaut
		{
			"Å", "&#197;" }, // Å uppercase A, ring
		{
			"Æ", "&#198;" }, // Æ uppercase AE
		{
			"Ç", "&#199;" }, // Ç uppercase C, cedilla
		{
			"È", "&#200;" }, // È uppercase E, grave accent
		{
			"É", "&#201;" }, // É uppercase E, acute accent
		{
			"Ê", "&#202;" }, // Ê uppercase E, circumflex accent
		{
			"Ë", "&#203;" }, // Ë uppercase E, umlaut
		{
			"Ì", "&#204;" }, // Ì uppercase I, grave accent
		{
			"Í", "&#205;" }, // Í uppercase I, acute accent
		{
			"Î", "&#206;" }, // Î uppercase I, circumflex accent
		{
			"Ï", "&#207;" }, // Ï uppercase I, umlaut
		{
			"Ð", "&#208;" }, // Ð uppercase Eth, Icelandic
		{
			"Ñ", "&#209;" }, // Ñ uppercase N, tilde
		{
			"Ò", "&#210;" }, // Ò uppercase O, grave accent
		{
			"Ó", "&#211;" }, // Ó uppercase O, acute accent
		{
			"Ô", "&#212;" }, // Ô uppercase O, circumflex accent
		{
			"Õ", "&#213;" }, // Õ uppercase O, tilde
		{
			"Ö", "&#214;" }, // Ö uppercase O, umlaut
		{
			"×", "&#215;" }, // × multiplication sign
		{
			"Ø", "&#216;" }, // Ø uppercase O, slash
		{
			"Ù", "&#217;" }, // Ù uppercase U, grave accent
		{
			"Ú", "&#218;" }, // Ú uppercase U, acute accent
		{
			"Û", "&#219;" }, // Û uppercase U, circumflex accent
		{
			"Ü", "&#220;" }, // Ü uppercase U, umlaut
		{
			"Ý", "&#221;" }, // Ý uppercase Y, acute accent
		{
			"Þ", "&#222;" }, // Þ uppercase THORN, Icelandic
		{
			"ß", "&#223;" }, // ß lowercase sharps, German
		{
			"à", "&#224;" }, // à lowercase a, grave accent
		{
			"á", "&#225;" }, // á lowercase a, acute accent
		{
			"â", "&#226;" }, // â lowercase a, circumflex accent
		{
			"ã", "&#227;" }, // ã lowercase a, tilde
		{
			"ä", "&#228;" }, // ä lowercase a, umlaut
		{
			"å", "&#229;" }, // å lowercase a, ring
		{
			"æ", "&#230;" }, // æ lowercase ae
		{
			"ç", "&#231;" }, // ç lowercase c, cedilla
		{
			"è", "&#232;" }, // è lowercase e, grave accent
		{
			"é", "&#233;" }, // é lowercase e, acute accent
		{
			"ê", "&#234;" }, // ê lowercase e, circumflex accent
		{
			"ë", "&#235;" }, // ë lowercase e, umlaut
		{
			"ì", "&#236;" }, // ì lowercase i, grave accent
		{
			"í", "&#237;" }, // í lowercase i, acute accent
		{
			"î", "&#238;" }, // î lowercase i, circumflex accent
		{
			"ï", "&#239;" }, // ï lowercase i, umlaut
		{
			"ð", "&#240;" }, // ð lowercase eth, Icelandic
		{
			"ñ", "&#241;" }, // ñ lowercase n, tilde
		{
			"ò", "&#242;" }, // ò lowercase o, grave accent
		{
			"ó", "&#243;" }, // ó lowercase o, acute accent
		{
			"ô", "&#244;" }, // ô lowercase o, circumflex accent
		{
			"õ", "&#245;" }, // õ lowercase o, tilde
		{
			"ö", "&#246;" }, // ö lowercase o, umlaut
		{
			"÷", "&#247;" }, // ÷ division sign
		{
			"ø", "&#248;" }, // ø lowercase o, slash
		{
			"ù", "&#249;" }, // ù lowercase u, grave accent
		{
			"ú", "&#250;" }, // ú lowercase u, acute accent
		{
			"û", "&#251;" }, // û lowercase u, circumflex accent
		{
			"ü", "&#252;" }, // ü lowercase u, umlaut
		{
			"ý", "&#253;" }, // ý lowercase y, acute accent
		{
			"þ", "&#254;" }, // þ lowercase thorn, Icelandic
		{
			"ÿ", " &#255;" }, // ÿ lowercase y, umlaut
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
	* rendendola più generale.
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
