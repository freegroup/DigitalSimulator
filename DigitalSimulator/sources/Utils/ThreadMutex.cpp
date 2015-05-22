/* NO WARRANTY
 *
 *    BECAUSE THE PROGRAM IS IN THE PUBLIC DOMAIN, THERE IS NO
 *    WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE
 *    LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE AUTHORS
 *    AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT
 *    WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *    BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 *    AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS TO
 *    THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD
 *    THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL
 *    NECESSARY SERVICING, REPAIR OR CORRECTION.
 *
 *    IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN
 *    WRITING WILL ANY AUTHOR, OR ANY OTHER PARTY WHO MAY MODIFY
 *    AND/OR REDISTRIBUTE THE PROGRAM, BE LIABLE TO YOU FOR DAMAGES,
 *    INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL
 *    DAMAGES ARISING OUT OF THE USE OR INABILITY TO USE THE PROGRAM
 *    (INCLUDING BUT NOT LIMITED TO LOSS OF DATA OR DATA BEING
 *    RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES
 *    OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER
 *    PROGRAMS), EVEN IF SUCH AUTHOR OR OTHER PARTY HAS BEEN ADVISED
 *    OF THE POSSIBILITY OF SUCH DAMAGES.
 */
#include "stdafx.h"
#include "Application\Debug\LogManager.h"
#include "ThreadMutex.h"

//----------------------------------------------------------------------------
ThreadMutex::ThreadMutex(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    // auf KEINEN Fall WindowsNT Mutex Objekte verwenden
    // Der Thread welcher das Mutex Objekt mit WaitForSingleObject
    // erhalten hat MUSS DIESE AUCH WIEDER FREIGENEN. Kein anderer
    // Thread kann mit ReleaseObject das Mutex Object freieben.
    // Das hat zur Folge, das Lock und UnLock immer im selben Thread
    // stattfinden muss - sehr unflexibel fuer manche Anwendungen.
	 // Besser mit Semaphoren - ist aber viel langsamer.

    hSema = CreateSemaphore (NULL,1,1,NULL);
    if (!hSema)
    {
        exit(1);
    }

}


//----------------------------------------------------------------------------
ThreadMutex::~ThreadMutex(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (hSema)
   {
		CloseHandle(hSema);
   }
}


//----------------------------------------------------------------------------
BOOL ThreadMutex::lock(long TimeOut){
//----------------------------------------------------------------------------
	PROC_TRACE;

  if(TimeOut == -1)
  {
	  WaitForSingleObject(hSema,INFINITE);
     return TRUE;
  }
  else
  {
	  return( ((WaitForSingleObject(hSema,TimeOut*1000)==WAIT_TIMEOUT) ? FALSE: TRUE));
  }
}


//----------------------------------------------------------------------------
BOOL ThreadMutex::unlock(){
//----------------------------------------------------------------------------
	PROC_TRACE;

  ReleaseSemaphore(hSema,1,NULL);
  // only for the compatibility to the UNIX-Version of ThreadMutex
  return TRUE;
}
