#ifndef ___ApplicationProxy_H
#define ___ApplicationProxy_H


#include <string>
#include "ProxyArray.h"
#include "PrimitiveArray.h"
#include "JStringHelper.h"
#include "JStringHelperArray.h"
using namespace de::freegroup::jnipp;

class I18NProxy
{
private:
	static std::string className;
	static jclass      objectClass;
//	jobject peerObject;

	static jclass _getObjectClass();
protected:
//	virtual jobject getPeerObject(){ return peerObject;};

public:
//	virtual jclass  getObjectClass();
//	operator jobject();
	// constructors
//	I18NProxy(jobject obj);
//	I18NProxy();


	/*
	 * static String get(String);
	 */
	static CString get(CString p0);
};


#endif
