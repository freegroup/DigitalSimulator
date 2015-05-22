// SimulationDocumentManager.h: interface for the SimulationDocumentManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMULATIONDOCUMENTMANAGER_H__02F90CF5_0D86_4A44_9B66_CC9C9A3D5C36__INCLUDED_)
#define AFX_SIMULATIONDOCUMENTMANAGER_H__02F90CF5_0D86_4A44_9B66_CC9C9A3D5C36__INCLUDED_
#include <jni.h>


class SimulationDocumentManager  
{
public:
	SimulationDocumentManager();
	virtual ~SimulationDocumentManager();

   static jint getDocumentWidth(JNIEnv *,  jobject);
   static jint getDocumentHeight(JNIEnv *, jobject);

};

#endif // !defined(AFX_SIMULATIONDOCUMENTMANAGER_H__02F90CF5_0D86_4A44_9B66_CC9C9A3D5C36__INCLUDED_)
