package de.freegroup.util.clazz;

import java.util.List;
import java.util.ArrayList;
import java.util.StringTokenizer;
import java.lang.Package;
import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.lang.ClassNotFoundException;
import java.util.Iterator;
import java.util.Map;
import java.util.HashMap;
import java.lang.reflect.Field;
import java.util.Properties;

/**
 * Node to represent data for a class or interface.
 *
 * This class contains data for a given Java class or interface that assists the
 * various code generators.
 *
 * @author Philllip E. Trewhella
 * @version 1.0
 */

public class ClassNode
{
	private String fullyQualifiedClassName = "";
	private String className = "";
	private String packageName = "";
	private String namespace = "";
	private List namespaceElements = new ArrayList();
	private boolean intfc = false;
	private boolean primitive = false;
	private List ctors = new ArrayList();
	private List methods = new ArrayList();
	private List fields = new ArrayList();
	private List innerClasses = new ArrayList();
	private static Map loadedClassNodes = new HashMap();
	private String jniString = "";
	private int arrayDims = 0;
	private List dependencyList = new ArrayList();
	private ClassNode componentType = null;
	private String jniTypeName = "";
	private boolean willGenerateProxy = false;
	private static Properties props = new Properties();

	/**
	 * Factory method for ClassNode objects.
	 *
	 * The <code> loadedClassNodes </code> map contains all of the ClassNode objects that
	 * have been loaded as part of the traversal.  This map is subsequently used by the
	 * code generating phase as a list of all classes for which code needs to be generated.
	 *
	 * If the ClassNode already exists, it is found and returned.  If not, then the ClassNode
	 * is created, added to the map and returned.
	 *
	 * @param fullyQualifiedClassName The fully qualified class name of the ClassNode object
	 * @return The ClassNode specified by the <code> fullyQualifiedClassName </code> parameter
	 * @exception ClassNotFoundException
	 * @see loadedClassNodes
	 * @see getClassNodes
	 */
	public static ClassNode getClassNode(String fullyQualifiedClassName)
		throws ClassNotFoundException
	{
		ClassNode node = (ClassNode) loadedClassNodes.get( fullyQualifiedClassName );
		if ( node == null )
		{
			node = new ClassNode( fullyQualifiedClassName );
			loadedClassNodes.put( fullyQualifiedClassName, node );
			node.init();
		}

		return node;
	}

	/**
	 * Accessor for loaded ClassNode objects.
	 *
	 * At the end of the initial analysis phase, the <code> loadedClassNodes </code> map will
	 * contain ClassNode object instances for all classes for which code needs to be generated.
	 * This map is used by the code generation phase as a reference for all dependencies.
	 *
	 * @return The map of loaded ClassNode instances
	 * @see loadedClassNodes
	 * @see getClassNode
	 */
	public static Map getClassNodes()
	{
		return loadedClassNodes;
	}

	private static boolean isTypePrimitive(String type)
	{
		if ( type.length() > 8 || type.indexOf( '.' ) != -1 )
			return false;

		return ( type.equals( "boolean" ) ||
					type.equals( "byte" ) ||
					type.equals( "char" ) ||
					type.equals( "short" ) ||
					type.equals( "int" ) ||
					type.equals( "long" ) ||
					type.equals( "float" ) ||
					type.equals( "double" ) ||
					type.equals( "void" ) );
	}

	private static boolean shouldGenerateProxy(String type)
	{
		if ( type.equals( "java.lang.String" ) == true )
			return false;
		
		/*
		 * Check the "ignore" list and return false if found.
		 */
		if ( props.getProperty( "ignore." + type ) != null )
		{
			return false;
		}
			
		return true;
	}
	
	public static void setProperties(Properties props)
	{
		ClassNode.props = props;
	}

	/**
	 * Class constructor.
	 *
	 * The class constructor accepts a string representation of the fully qualified
	 * class name.  This is utilized to obtain data about the class through Java's introspection
	 * API.  The queried data is utilized to build a data structure that assists the
	 * various code generators.
	 *
	 * @param fullyQualifiedClassName The fully qualifed name of the class
	 * @exception ClassNotFoundException
	 */
	private ClassNode(String fullyQualifiedClassName)
	{
		this.fullyQualifiedClassName = fullyQualifiedClassName;
	}

	public void init()throws ClassNotFoundException
	{
 		if ( isTypePrimitive( fullyQualifiedClassName ) == true )
		{
			primitive = true;
			className = fullyQualifiedClassName;
		}
		else
		{
			Class theClass = Class.forName( fullyQualifiedClassName );
			intfc = theClass.isInterface();

			if ( theClass.isArray() == true )
			{
				componentType = ClassNode.getClassNode( theClass.getComponentType().getName() );
        className = componentType.getClassName();
        for ( arrayDims = 0;   theClass != null && theClass.isArray() == true;)
         {
           ++arrayDims;
           theClass = theClass.getComponentType() ;
           className+="[]";
         }
	 				;
        
			}
			else
			{
				int pkgEnd = fullyQualifiedClassName.lastIndexOf( "." ) + 1;
				className = fullyQualifiedClassName.substring( pkgEnd );

				if ( pkgEnd > 0 )
  					packageName = fullyQualifiedClassName.substring( 0, pkgEnd - 1 );

				StringTokenizer st = new StringTokenizer( packageName, "." );
				while ( st.hasMoreTokens() == true )
				{
					String next = st.nextToken();
					namespaceElements.add( next );
					namespace += next;
					if ( st.hasMoreTokens() == true )
						namespace += "::";
				}

				String typeName = fullyQualifiedClassName;

				if ( arrayDims > 0 )
					typeName = componentType.fullyQualifiedClassName;


				willGenerateProxy = shouldGenerateProxy( typeName );
				if ( willGenerateProxy == false )
					return;

				Constructor[] declaredCtors = theClass.getDeclaredConstructors();
				for ( int i = 0; i < declaredCtors.length; ++i )
					ctors.add( new MethodNode( declaredCtors[i] ) );

				Method[] declaredMethods = theClass.getDeclaredMethods();
				for ( int i = 0; i < declaredMethods.length; ++i )
					methods.add( new MethodNode( declaredMethods[i] ) );

				Class[] declaredClasses = theClass.getDeclaredClasses();
				for ( int i = 0; i < declaredClasses.length; ++i )
					innerClasses.add( getClassNode( declaredClasses[i].getName() ) );

				Field[] declaredFields = theClass.getDeclaredFields();
				for ( int i = 0; i < declaredFields.length; ++i )
					fields.add( new FieldNode( declaredFields[i] ) );
				generateDependencyList();
			}    
		}
	}
	
	private void generateDependencyList()
		throws ClassNotFoundException
	{

		Iterator ctorIter = ctors.iterator();
		while ( ctorIter.hasNext() == true )
		{
			Iterator paramIter = ((MethodNode) ctorIter.next()).getParameterList();
			while ( paramIter.hasNext() == true )
			{
				ClassNode current = (ClassNode) paramIter.next();

				if ( current.isArray() == true )
					current = current.getComponentType();

				String fullyQualifiedName = current.getPackageName() + "." + current.getClassName();

				if ( current.isPrimitive() == false &&
					  fullyQualifiedName.equals( "java.lang.String" ) == false &&
					  dependencyList.contains( current ) == false )
					dependencyList.add( current );
			}
		}

		Iterator methodIter = methods.iterator();
		while ( methodIter.hasNext() == true )
		{
			MethodNode methodNode = (MethodNode) methodIter.next();
			Iterator paramIter = methodNode.getParameterList();
			while ( paramIter.hasNext() == true )
			{
				ClassNode current = (ClassNode) paramIter.next();

				if ( current.isArray() == true )
					current = current.getComponentType();

				String fullyQualifiedName = current.getPackageName() + "." + current.getClassName();

				if ( current.isPrimitive() == false &&
					  fullyQualifiedName.equals( "java.lang.String" ) == false &&
					  dependencyList.contains( current ) == false )
					dependencyList.add( current );
			}

			ClassNode current = methodNode.getReturnType();

			if ( current.isArray() == true )
				current = current.getComponentType();

			String fullyQualifiedName = current.getPackageName() + "." + current.getClassName();

			if ( current.isPrimitive() == false &&
				  fullyQualifiedName.equals( "java.lang.String" ) == false &&
				  dependencyList.contains( current ) == false )
				dependencyList.add( current );
		}

		Iterator fieldIter = fields.iterator();
		while ( fieldIter.hasNext() == true )
		{
			ClassNode current = ((FieldNode) fieldIter.next()).getType();

			if ( current.isArray() == true )
				current = current.getComponentType();

			String fullyQualifiedName = current.getPackageName() + "." + current.getClassName();

			if ( current.isPrimitive() == false &&
			     fullyQualifiedName.equals( "java.lang.String" ) == false &&
				  dependencyList.contains( current ) == false )
				dependencyList.add( current );
		}

		if ( dependencyList.contains( this ) == true )
			dependencyList.remove( this );
	}
    
	public boolean isInterface()
	{
		return intfc;
	}

	public boolean isPrimitive()
	{
		return primitive;
	}

	public boolean isArray()
	{
		return arrayDims != 0;
	}

	public String getClassName()
	{
		return className;
	}
	
	public String getCPPClassName()
	{
		String cppName = Util.getCPPIdentifier( className );
		return cppName.replace( '$', '_' );
	}

	public String getPackageName()
	{
		return packageName;
	}

	public String getNamespace()
	{
		return namespace;
	}

	public Iterator getNamespaceElements()
	{
		return namespaceElements.iterator();
	}

	public Iterator getConstructors()
	{
		return ctors.iterator();
	}

	public Iterator getMethods()
	{
		return methods.iterator();
	}

	public Iterator getFields()
	{
		return fields.iterator();
	}

	public Iterator getInnerClasses()
	{
		return innerClasses.iterator();
	}

	public ClassNode getComponentType()
	{
		return componentType;
	}

	public int getArrayDims()
	{
		return arrayDims;
	}

	public String getJNIString()
	{
		if ( jniString.equals( "" ) == false )
			return jniString;

		if ( fullyQualifiedClassName.equals( "void" ) == true )
			jniString = "V";
		else
		if ( arrayDims > 0 )
		{
			jniString = "[" + componentType.getJNIString();
		}
		else
		if ( primitive == true )
		{
			if ( fullyQualifiedClassName.equals( "boolean" ) == true )
				jniString = "Z";
			else
			if ( fullyQualifiedClassName.equals( "long" ) == true )
				jniString = "J";
			else
				jniString += Character.toUpperCase( fullyQualifiedClassName.charAt( 0 ) );
		}
		else
		{
			jniString = "L" + fullyQualifiedClassName.replace( '.', '/' ) + ";";
		}

		return jniString;
	}

	public Iterator getDependencies()
	{
		return dependencyList.iterator();
	}

	public String getJNITypeName(boolean includeNamespace)
	{
		jniTypeName = "";

		if ( arrayDims > 0 )
		{
			if ( includeNamespace == true && willGenerateProxy == true )
				jniTypeName = "net::sourceforge::jnipp::";

			if ( componentType.isPrimitive() == true )
			{
				jniTypeName += "PrimitiveArray< ";
				jniTypeName += componentType.getJNITypeName( includeNamespace );
				jniTypeName += " >";
			}
			else
			if ( componentType.getPackageName().equals( "java.lang" ) == true &&
				  componentType.getClassName().equals( "String" ) == true )
				jniTypeName += "JStringHelperArray";
			else
			if ( willGenerateProxy == true )
			{
				jniTypeName += "ProxyArray< ";
				if ( componentType.arrayDims > 0 )
					jniTypeName += (includeNamespace == true ? "java::lang::ObjectProxy" : "ObjectProxy");
				else
					jniTypeName += componentType.getJNITypeName( includeNamespace );
				jniTypeName += " >";
			}
			else
				jniTypeName = "jobjectArray";
		}
		else
		if ( className.equals( "void" ) == true )
			jniTypeName += "void";
		else
		if ( primitive == true )
			jniTypeName += "j" + className;
		else
		if ( packageName.equals( "java.lang" ) == true && className.equals( "String" ) == true )
			jniTypeName += (includeNamespace == true ? "net::sourceforge::jnipp::JStringHelper" : "JStringHelper" );
		else
		if ( willGenerateProxy == true )
			jniTypeName += namespace + "::" + getCPPClassName() + "Proxy";
		else
			jniTypeName += "jobject";

		return jniTypeName;
	}

	public boolean needsProxy()
	{
		return willGenerateProxy;
	}
}
