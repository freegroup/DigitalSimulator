package de.freegroup.util.clazz;

import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.lang.reflect.Method;
import java.lang.reflect.Constructor;
import java.lang.reflect.Modifier;

/**
 * Node representing a method of a Java interface or class.
 *
 * @author Philllip E. Trewhella
 * @version 1.0
 */

public class MethodNode
{
	private String methodName = "";
	private String jniName = "";
	private List parameterList = new ArrayList();
	private ClassNode returnType = null;
	private boolean ctor = false;
	private String jniSignature = "";
	private String jniMethodCall = "";
	private boolean staticMethod = false;

	public MethodNode(Constructor ctor)		throws ClassNotFoundException
	{
		this.ctor = true;
		int lastDot = ctor.getName().lastIndexOf( '.' ) + 1;
		methodName = ctor.getName().substring( lastDot );
		jniName = "<init>";

		Class[] parameterTypes = ctor.getParameterTypes();
		for ( int i = 0; i < parameterTypes.length; ++i )
			parameterList.add( ClassNode.getClassNode( parameterTypes[i].getName() ) );

		buildJNISignature();
		buildJNIMethodCall();
	}

	public MethodNode(Method method)	throws ClassNotFoundException
	{
		methodName = method.getName();
		jniName = methodName;
		staticMethod = Modifier.isStatic( method.getModifiers() );
		returnType = ClassNode.getClassNode( method.getReturnType().getName() );
		Class[] parameterTypes = method.getParameterTypes();
		for ( int i = 0; i < parameterTypes.length; ++i )
			parameterList.add( ClassNode.getClassNode( parameterTypes[i].getName() ) );

		buildJNISignature();
		buildJNIMethodCall();
	}

	private void buildJNISignature()
	{
		jniSignature = "(";
		Iterator it = parameterList.iterator();
		while ( it.hasNext() == true )
			jniSignature += ((ClassNode) it.next()).getJNIString();
		jniSignature += ")" + (returnType == null ? "V" : returnType.getJNIString() );
	}

	private void buildJNIMethodCall()
	{
		if ( returnType == null || returnType.getClassName().equals( "void" ) == true )
		{
			jniMethodCall = "JNIEnvHelper::Call";
			jniMethodCall += (staticMethod == true ? "StaticVoidMethod(" : "VoidMethod(");
		}
		else
		if ( returnType.isPrimitive() == false )
		{
			jniMethodCall = "return JNIEnvHelper::Call";
			jniMethodCall += (staticMethod == true ? "StaticObjectMethod(" : "ObjectMethod(");
		}
		else
		{
			jniMethodCall = "return JNIEnvHelper::Call";
			if ( staticMethod == true )
				jniMethodCall += "Static";
			jniMethodCall += Character.toUpperCase( returnType.getClassName().charAt( 0 ) ) + returnType.getClassName().substring( 1 );
			jniMethodCall += "Method(";
		}
	}

	public String getName()
	{
		return methodName;
	}
	
	public String getCPPName()
	{
		return Util.getCPPIdentifier( methodName );
	}

	public String getJNIName()
	{
		return jniName;
	}

	public String getJNISignature()
	{
		return jniSignature;
	}

	public Iterator getParameterList()
	{
		return parameterList.iterator();
	}

	public ClassNode getReturnType()
	{
		return returnType;
	}

	public String getJNIMethodCall()
	{
		return jniMethodCall;
	}

	public boolean isStatic()
	{
		return staticMethod;
	}
	
	public String getJavaSignature()
	{
		String signature = "";
		if ( returnType != null )
			signature += returnType.getClassName() + " ";
		else
		if ( ctor == false )
			signature += "void ";
		signature += methodName + "(";
		Iterator it = parameterList.iterator();
		while ( it.hasNext() == true )
    {
      ClassNode node =((ClassNode) it.next());
			signature +=  node.getClassName()+ (it.hasNext() == true ? ", " : "");
    }
		signature += ");";
		return signature;
	}
}
