#include "JStringHelperArray.h"
#include "JNIEnvHelper.h"

using namespace de::freegroup::jnipp;

JStringHelperArray::JStringHelperArray()
{
}

JStringHelperArray::JStringHelperArray(jobject obj)
{
}

JStringHelperArray::JStringHelperArray(jobjectArray nativeArray)
{
	jsize numElems = JNIEnvHelper::GetArrayLength( nativeArray );

	for ( int i = 0; i < numElems; ++i )
		stringVector.push_back( JStringHelper( JNIEnvHelper::GetObjectArrayElement( nativeArray, i ) ) );
}

JStringHelperArray::JStringHelperArray(const std::vector<std::string>& strVector)
{
	std::vector<std::string>::const_iterator it = strVector.begin();
	for ( ; it != strVector.end(); ++it )
		stringVector.push_back( it->c_str() );
}

JStringHelperArray::JStringHelperArray(int argc, char** args)
{
	for ( int i = 0; i < argc; ++i )
		stringVector.push_back( static_cast<const char *>(args[i]) );
}

JStringHelperArray::~JStringHelperArray()
{
}

void JStringHelperArray::addElement(const JStringHelper& newString)
{
	stringVector.push_back( newString );
}

void JStringHelperArray::addElement(const jstring newString)
{
	stringVector.push_back( newString );
}

JStringHelperArray& JStringHelperArray::operator=(JStringHelperArray& rhs)
{
	stringVector.clear();

	for ( std::vector<JStringHelper>::iterator it = rhs.stringVector.begin(); it != rhs.stringVector.end(); ++it )
		stringVector.push_back( *it );

	return *this;
}

JStringHelperArray& JStringHelperArray::operator=(const jobjectArray rhs)
{
	jsize numElems = JNIEnvHelper::GetArrayLength( rhs );

	for ( int i = 0; i < numElems; ++i )
		stringVector.push_back( JNIEnvHelper::GetObjectArrayElement( rhs, i ) );

	return *this;
}

JStringHelperArray::operator jobjectArray()
{
	jobjectArray retVal;
	jsize numElems = stringVector.size();

	if ( numElems == 0 )
		return NULL;

	// create new array, all NULLs by default
	retVal = JNIEnvHelper::NewObjectArray( numElems, JStringHelper::getClass(), NULL );

	// copy the elements of the vector into the newly-created array
	jsize index = 0;
	for ( std::vector<JStringHelper>::iterator it = stringVector.begin(); it != stringVector.end(); ++it, ++index )
		JNIEnvHelper::SetObjectArrayElement( retVal, index, *it );

	return retVal;
}
