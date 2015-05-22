#include "stdafx.h"

#include "Application\Objects\plugin\java\JavaPluginManager.h"

#include "ApplicationProxyWrapper.h"

using namespace de::freegroup::jnipp;

//----------------------------------------------------------------------------
void ApplicationProxyWrapper::onInit()
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   if(JavaPluginManager::isOk())
      ApplicationProxy::onInit();
}

//----------------------------------------------------------------------------
void ApplicationProxyWrapper::onExit()
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   if(JavaPluginManager::isOk())
      ApplicationProxy::onExit();
}

//----------------------------------------------------------------------------
void ApplicationProxyWrapper::onHelpAbout()
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   if(JavaPluginManager::isOk())
      ApplicationProxy::onHelpAbout();
}

//----------------------------------------------------------------------------
void ApplicationProxyWrapper::onExport(JStringHelper& p0)
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   if(JavaPluginManager::isOk())
      ApplicationProxy::onExport(p0);
}


//----------------------------------------------------------------------------
void ApplicationProxyWrapper::onToolCall(CString p0)
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   if(JavaPluginManager::isOk())
      ApplicationProxy::onToolCall(JStringHelper((LPCSTR)p0));
}



//----------------------------------------------------------------------------
void ApplicationProxyWrapper::onDialogCall(CString p0)
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   if(JavaPluginManager::isOk())
      ApplicationProxy::onDialogCall(JStringHelper((LPCSTR)p0));
}


//----------------------------------------------------------------------------
void ApplicationProxyWrapper::setProxy(JStringHelper& proxy, jint port)
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   if(JavaPluginManager::isOk())
      ApplicationProxy::setProxy(proxy,port);
}
