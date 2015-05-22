#ifndef ___ApplicationProxy_H
#define ___ApplicationProxy_H


#include <string>
#include "ProxyArray.h"
#include "PrimitiveArray.h"
#include "JStringHelper.h"
#include "JStringHelperArray.h"
using namespace de::freegroup::jnipp;

class ApplicationProxy
{
private:
	static std::string className;
	static jclass      objectClass;
	jobject peerObject;

	static jclass _getObjectClass();
protected:
	virtual jobject getPeerObject(){ return peerObject;};

public:
	virtual jclass  getObjectClass();
	operator jobject();
	// constructors
	ApplicationProxy(jobject obj);
	ApplicationProxy();

	// attribute getters

	// attribute setters

	// methods
	/*
	 * static void onInit();
	 */
	static void onInit();
	/*
	 * static void onExit();
	 */
	static void onExit();
	static void onHelpAbout();

	/*
	 * static void onExport(String);
	 */
	static void onExport(de::freegroup::jnipp::JStringHelper& p0);

	/*
	 * static void onToolCall(String);
	 */
	static void onToolCall(de::freegroup::jnipp::JStringHelper& p0);

	/*
	 * static void onDialogCall(String);
	 */
	static void onDialogCall(de::freegroup::jnipp::JStringHelper& p0);

   /*
	 * static void setProxy(String, int);
	 */
	static void setProxy(de::freegroup::jnipp::JStringHelper& p0, jint p1);

};


#endif
