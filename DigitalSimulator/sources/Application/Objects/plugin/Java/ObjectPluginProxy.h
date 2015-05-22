#ifndef ___ObjectPluginProxy_H
#define ___ObjectPluginProxy_H


#include <string>
#include "ProxyArray.h"
#include "PrimitiveArray.h"
#include "JStringHelper.h"
#include "JStringHelperArray.h"
using namespace de::freegroup::jnipp;

class ObjectPluginProxy
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
	ObjectPluginProxy(jobject obj);
	ObjectPluginProxy();

	// attribute getters

	// attribute setters

	// methods
	/*
	 * String getName();
	 */
	de::freegroup::jnipp::JStringHelper getName();
	/*
	 * void init();
	 */
	void init(PrimitiveArray< jbyte >& p0);
	/*
	 * void init();
	 */
	void init();
	/*
	 * String getKey();
	 */
	de::freegroup::jnipp::JStringHelper getKey();
	/*
	 *  getSize(long, long);
	 */
	PrimitiveArray< jint > getSize(jlong p0, jlong p1);
	/*
	 * String getVersion();
	 */
	jint getVersion();
	/*
	 * int doConfigure();
	 */
	jboolean doConfigure(PrimitiveArray< jbyte >& p0);
	/*
	 * String getProgrammerName();
	 */
	de::freegroup::jnipp::JStringHelper getProgrammerName();
	/*
	 * String getProgrammerURL();
	 */
	de::freegroup::jnipp::JStringHelper getProgrammerURL();
	/*
	 * String getProgrammerMail();
	 */
	de::freegroup::jnipp::JStringHelper getProgrammerMail();
	/*
	 * String getLabel();
	 */
	de::freegroup::jnipp::JStringHelper getLabel();
	/*
	 * int getParamCount();
	 */
	jint getParamCount();
	/*
	 *  getInputCountRange();
	 */
	PrimitiveArray< jint > getInputCountRange();
	/*
	 *  getOutputCountRange();
	 */
	PrimitiveArray< jint > getOutputCountRange();
	/*
	 * String getDescription();
	 */
	de::freegroup::jnipp::JStringHelper getDescription();
	/*
	 * String getGroup();
	 */
	de::freegroup::jnipp::JStringHelper getGroup();
	/*
	 * int calculate(, , , );
	 */
	jboolean calculate(PrimitiveArray< jint >& p0, PrimitiveArray< jint >& p1, PrimitiveArray< jint >& p2, PrimitiveArray< jbyte >& p3);
	/*
	 * void paint(int, int, );
	 */
	void paint(jint p0, jint p1, PrimitiveArray< jbyte >& p2);
	/*
	 * void onStartCalculate();
	 */
	void onStartCalculate(PrimitiveArray< jbyte >& p0);
	/*
	 * void onStopCalculate();
	 */
	void onStopCalculate(PrimitiveArray< jbyte >& p0);
	/*
	 * boolean onButtonClick();
	 */
	jboolean onButtonClick(jint p0, jint p1, PrimitiveArray< jbyte >& p2);
	/*
	 * boolean onMouseOverStart();
	 */
	jboolean onMouseOverStart(jint p0, jint p1, PrimitiveArray< jbyte >& p2);
	/*
	 * boolean onMouseOver();
	 */
	jboolean onMouseOver(jint p0, jint p1, PrimitiveArray< jbyte >& p2);
	/*
	 * boolean onMouseOverEnd();
	 */
	jboolean onMouseOverEnd(jint p0, jint p1, PrimitiveArray< jbyte >& p2);
	/*
	 * boolean onButtonDblClick();
	 */
	jboolean onButtonDblClick(jint p0, jint p1, PrimitiveArray< jbyte >& p2);
	/*
	 * boolean onButtonDown();
	 */
	jboolean onButtonDown(jint p0, jint p1, PrimitiveArray< jbyte >& p2);
	/*
	 * boolean onButtonUp();
	 */
	jboolean onButtonUp(jint p0, jint p1, PrimitiveArray< jbyte >& p2);
	/*
	 *  layoutOutput(int, int, );
	 */
	PrimitiveArray< jint > layoutOutput(jint p0, jint p1, PrimitiveArray< jbyte >& p2);
	/*
	 *  layoutInput(int, int, );
	 */
	PrimitiveArray< jint > layoutInput(jint p0, jint p1, PrimitiveArray< jbyte >& p2);
	/*
	 * void invertInput(int, boolean);
	 */
	void invertInput(jint p0, jboolean p1);
	/*
	 * void invertOutput(int, boolean);
	 */
	void invertOutput(jint p0, jboolean p1);

};


#endif
