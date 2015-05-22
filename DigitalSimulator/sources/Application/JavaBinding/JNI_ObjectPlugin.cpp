#include "stdafx.h"
#include "JNI_ObjectPlugin.h"
#include "Application\Configuration\ParameterManager.h"
#include "Application\Debug\LogManager.h"
#include "Application\Objects\buildin\Digital\ElectricNodeContext.h"
#include "Application\Objects\plugin\Java\JavaPluginManager.h"
#include "Application\Objects\plugin\DLL\SimpleType\ObjectPluginManager.h"

static CElectricNode::CElectricNodeDokument* currentObjectData=NULL;

void setCurrentObjectData(CElectricNode::CElectricNodeDokument* _data)
{
	PROC_TRACE;

   currentObjectData = _data;
}

/*
 * Class:     ObjectPlugin
 * Method:    invertInput
 * Signature: (IZ)V
 */
void  JNICALL Java_ObjectPlugin_invertInput(JNIEnv *, jobject jobj, jint index, jboolean inverted)
{
	PROC_TRACE;

   if(currentObjectData!=NULL)
   {
      if((index<currentObjectData->inCount)&& (index>=0))
         currentObjectData->inPorts[index]->SetInverter(inverted==JNI_TRUE?true:false);
      else
         LogManager::log(LogManager::error ,"out of index in method 'Java_ObjectPlugin_invertInput' Action will be ingnored.");
   }
}

/*
 * Class:     ObjectPlugin
 * Method:    invertOutput
 * Signature: (IZ)V
 */
void  JNICALL Java_ObjectPlugin_invertOutput(JNIEnv *, jobject jobj, jint index, jboolean inverted)
{
	PROC_TRACE;

   if(currentObjectData!=NULL)
   {
      if((index<currentObjectData->outCount)&& (index>=0))
         currentObjectData->outPorts[index]->SetInverter(inverted==JNI_TRUE?true:false);
      else
         LogManager::log(LogManager::error ,"out of index in method 'Java_ObjectPlugin_invertOutput' Action will be ingnored.");
   }
}


/*
 * Class:     ObjectPlugin
 * Method:    invertOutput
 * Signature: (IZ)V
 */
jboolean  JNICALL Java_ObjectPlugin_isObjectNameFree(JNIEnv *env, jclass, jstring name)
{
	PROC_TRACE;

	const char * utf_string;
	jboolean isCopy;
    jboolean result = false;

	utf_string = env->GetStringUTFChars(name, &isCopy);
//	LogManager::log(LogManager::debug1 ,"isObjectNameFree with [%s] called",utf_string);

	try
	{
		result = ObjectPluginManager::isObjectNameFree(CString(utf_string))?JNI_TRUE:JNI_FALSE;
	}
	catch(...)
	{
	}
	if(isCopy== JNI_TRUE)
	{
		env->ReleaseStringUTFChars(name,utf_string);
	}
	return result;
}
