package de.freegroup.util.clazz;

import java.util.HashMap;

public class Util
{
	private static HashMap keywordMap = new HashMap();
	
	static
	{
		keywordMap.put( "asm", "_asm" );
		keywordMap.put( "auto", "_auto" );
		keywordMap.put( "bool", "_bool" );
		keywordMap.put( "break", "_break" );
		keywordMap.put( "case", "_case" );
		keywordMap.put( "catch", "_catch" );
		keywordMap.put( "char", "_char" );
		keywordMap.put( "class", "_class" );
		keywordMap.put( "const", "_const" );
		keywordMap.put( "const_cast", "_const_cast" );
		keywordMap.put( "continue", "_continue" );
		keywordMap.put( "default", "_default" );
		keywordMap.put( "delete", "_delete" );
		keywordMap.put( "do", "_do" );
		keywordMap.put( "double", "_double" );
		keywordMap.put( "dynamic_cast", "_dynamic_cast" );
		keywordMap.put( "else", "_else" );
		keywordMap.put( "enum", "_enum" );
		keywordMap.put( "explicit", "_explicit" );
		keywordMap.put( "export", "_export" );
		keywordMap.put( "extern", "_extern" );
		keywordMap.put( "false", "_false" );
		keywordMap.put( "float", "_float" );
		keywordMap.put( "for", "_for" );
		keywordMap.put( "friend", "_friend" );
		keywordMap.put( "goto", "_goto" );
		keywordMap.put( "if", "_if" );
		keywordMap.put( "inline", "_inline" );
		keywordMap.put( "int", "_int" );
		keywordMap.put( "long", "_long" );
		keywordMap.put( "mutable", "_mutable" );
		keywordMap.put( "namespace", "_namespace" );
		keywordMap.put( "new", "_new" );
		keywordMap.put( "operator", "_operator" );
		keywordMap.put( "private", "_private" );
		keywordMap.put( "protected", "_protected" );
		keywordMap.put( "public", "_public" );
		keywordMap.put( "register", "_register" );
		keywordMap.put( "reinterpret_cast", "_reinterpret_cast" );
		keywordMap.put( "return", "_return" );
		keywordMap.put( "short", "_short" );
		keywordMap.put( "signed", "_signed" );
		keywordMap.put( "sizeof", "_sizeof" );
		keywordMap.put( "static", "_static" );
		keywordMap.put( "static_cast", "_static_cast" );
		keywordMap.put( "struct", "_struct" );
		keywordMap.put( "switch", "_switch" );
		keywordMap.put( "template", "_template" );
		keywordMap.put( "this", "_this" );
		keywordMap.put( "throw", "_throw" );
		keywordMap.put( "true", "_true" );
		keywordMap.put( "try", "_try" );
		keywordMap.put( "typedef", "_typedef" );
		keywordMap.put( "typeid", "_typeid" );
		keywordMap.put( "typename", "_typename" );
		keywordMap.put( "union", "_union" );
		keywordMap.put( "unsigned", "_unsigned" );
		keywordMap.put( "using", "_using" );
		keywordMap.put( "virtual", "_virtual" );
		keywordMap.put( "void", "_void" );
		keywordMap.put( "volatile", "_volatile" );
		keywordMap.put( "wchar_t", "_wchar_t" );
		keywordMap.put( "while", "_while" );
		
		// reserved words
		keywordMap.put( "and", "_and" );
		keywordMap.put( "and_eq", "_and_eq" );
		keywordMap.put( "bitand", "_bitand" );
		keywordMap.put( "compl", "_compl" );
		keywordMap.put( "not", "_not" );
		keywordMap.put( "not_eq", "_not_eq" );
		keywordMap.put( "or", "_or" );
		keywordMap.put( "or_eq", "_or_eq" );
		keywordMap.put( "xor", "_xor" );
		keywordMap.put( "xor_eq", "_xor_eq" );
	}
	
	public static String getCPPIdentifier(String identifier)
	{
		if ( keywordMap.containsKey( identifier ) )
			return (String) keywordMap.get( identifier );
		
		return identifier;
	}
}
