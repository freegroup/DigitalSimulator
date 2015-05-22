#include "JVM.h"
#include "JStringHelper.h"
#include "JNIEnvHelper.h"

using namespace de::freegroup::jnipp;

jclass JStringHelper::stringClass=NULL;

JStringHelper::JStringHelper()
	: str( "" )
{
   /*
   if(stringClass==NULL)
   	stringClass = reinterpret_cast<jclass>( JNIEnvHelper::NewGlobalRef( JNIEnvHelper::FindClass( "java/lang/String" ) ) );
*/
}

JStringHelper::JStringHelper(const JStringHelper &rhs)
	: str( rhs.str )
{
//	stringClass = rhs.stringClass;
}

JStringHelper::JStringHelper(const char *p)
{
	str = (p == NULL ? "" : p);
   /*
   if(stringClass==NULL)
   	stringClass = reinterpret_cast<jclass>( JNIEnvHelper::NewGlobalRef( JNIEnvHelper::FindClass( "java/lang/String" ) ) );
*/
}

JStringHelper::JStringHelper(jobject obj)
{
   /*
   if(stringClass==NULL)
   	stringClass = reinterpret_cast<jclass>( JNIEnvHelper::NewGlobalRef( JNIEnvHelper::FindClass( "java/lang/String" ) ) );
*/
	if ( obj != NULL )
	{
		const char *p = static_cast<const char *>( JNIEnvHelper::GetStringUTFChars( reinterpret_cast<jstring>(obj), NULL ) );
		str = (p == NULL ? "" : p);
		if ( p != NULL )
			JNIEnvHelper::ReleaseStringUTFChars( reinterpret_cast<jstring>(obj), p );
	}
	else
		str = "";
}

JStringHelper& JStringHelper::operator=(const JStringHelper &rhs)
{
	str = rhs.str;
	return *this;
}

JStringHelper& JStringHelper::operator=(const char *rhs)
{
	str = (rhs == NULL ? "" : rhs);
	return *this;
}

JStringHelper& JStringHelper::operator=(jobject rhs)
{
	const char *p = static_cast<const char *>( JNIEnvHelper::GetStringUTFChars( reinterpret_cast<jstring>(rhs), NULL ) );
	str = (p == NULL ? "" : p);
	JNIEnvHelper::ReleaseStringUTFChars( reinterpret_cast<jstring>(rhs), p );
	return *this;
}

JStringHelper::~JStringHelper()
{
}

JStringHelper::operator jstring() const
{
	return JNIEnvHelper::NewStringUTF( str.c_str() );
}

JStringHelper::operator jobject() const
{
	return static_cast<jobject>( static_cast<jstring>(*this) );
}

JStringHelper::operator const char*() const
{
	return str.c_str();
}

jclass JStringHelper::getClass()
{
   if(stringClass==NULL)
   	stringClass = reinterpret_cast<jclass>( JNIEnvHelper::NewGlobalRef( JNIEnvHelper::FindClass( "java/lang/String" ) ) );
	return stringClass;
}
