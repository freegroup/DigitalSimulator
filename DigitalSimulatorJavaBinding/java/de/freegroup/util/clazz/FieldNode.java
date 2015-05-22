package de.freegroup.util.clazz;

import java.lang.reflect.Field;
import java.lang.reflect.Modifier;

/**
 * @author Philllip E. Trewhella
 * @version 1.0
 */

public class FieldNode
{
	private String name = "";
	private String jniGetFieldCall = null;
	private String jniSetFieldCall = null;
	private ClassNode type = null;
	private boolean staticField = false;

	public FieldNode(Field field)
		throws ClassNotFoundException
	{
		name = field.getName();
		type = ClassNode.getClassNode( field.getType().getName() );
		staticField = Modifier.isStatic( field.getModifiers() );
		buildJNIGetFieldCall();
		buildJNISetFieldCall();
	}
	
	private void buildJNIGetFieldCall()
	{
		if ( type.isPrimitive() == false )
		{
			jniGetFieldCall = "return JNIEnvHelper::Get";
			jniGetFieldCall += (staticField == true ? "StaticObjectField(" : "ObjectField(");
		}
		else
		{
			jniGetFieldCall = "return JNIEnvHelper::Get";
			if ( staticField == true )
				jniGetFieldCall += "Static";
			jniGetFieldCall += Character.toUpperCase( type.getClassName().charAt( 0 ) ) + type.getClassName().substring( 1 );
			jniGetFieldCall += "Field(";
		}
	}

	private void buildJNISetFieldCall()
	{
		if ( type.isPrimitive() == false )
		{
			jniSetFieldCall = "JNIEnvHelper::Set";
			jniSetFieldCall += (staticField == true ? "StaticObjectField(" : "ObjectField(");
		}
		else
		{
			jniSetFieldCall = "JNIEnvHelper::Set";
			if ( staticField == true )
				jniSetFieldCall += "Static";
			jniSetFieldCall += Character.toUpperCase( type.getClassName().charAt( 0 ) ) + type.getClassName().substring( 1 );
			jniSetFieldCall += "Field(";
		}
	}

	public String getName()
	{
		return name;
	}

	public String getCPPName()
	{
		return Util.getCPPIdentifier( name );
	}
	
	public ClassNode getType()
	{
		return type;
	}

	public String getJNIGetFieldCall()
	{
		return jniGetFieldCall;
	}

	public String getJNISetFieldCall()
	{
		return jniSetFieldCall;
	}
	
	public boolean isStatic()
	{
		return staticField;
	}
}
