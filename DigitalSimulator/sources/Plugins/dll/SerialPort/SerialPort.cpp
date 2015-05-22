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
#include "SerialPort.h"

#include <assert.h>
 
//----------------------------------------------------------------------------
CSerialPort::CSerialPort(){
//----------------------------------------------------------------------------

	m_hComm         = NULL;
   m_nPortNr       = -1;

	m_ov.Offset     = 0;
	m_ov.OffsetHigh = 0;
	m_ov.hEvent      = NULL;

	m_hWriteEvent    = NULL;
	m_hShutdownEvent = NULL;
	m_szWriteBuffer  = NULL;
	m_Thread         = NULL;
	m_bThreadAlive   = FALSE;
   m_hEventArray[0] = NULL;
   m_hEventArray[1] = NULL;
   m_hEventArray[2] = NULL;
   m_nWriteSize     = 0;
   /*m_dwCommEvents   = urgs;*/
   m_nWriteBufferSize=0;

   // Initialize critical section
   //
	InitializeCriticalSection(&m_csCommunicationSync);
}

//----------------------------------------------------------------------------
CSerialPort::~CSerialPort(){
//----------------------------------------------------------------------------

   SetEvent(m_hShutdownEvent);
   SetEvent(m_hShutdownEvent);

   if(m_szWriteBuffer!=NULL){
	   delete [] m_szWriteBuffer;
      m_szWriteBuffer = NULL;
   }

   if (m_ov.hEvent != NULL){
		CloseHandle(m_ov.hEvent);
      m_ov.hEvent = NULL;
   }

	if (m_hWriteEvent != NULL){
		CloseHandle(m_hWriteEvent);
      m_hWriteEvent = NULL;
   }
	
	if (m_hShutdownEvent != NULL){
		CloseHandle(m_hShutdownEvent);
      m_hShutdownEvent = NULL;
   }

	if (m_hComm != INVALID_HANDLE_VALUE && m_hComm!=NULL){
      CloseHandle(m_hComm);
      m_hComm = NULL;
	}

	DeleteCriticalSection(&m_csCommunicationSync);
}

//----------------------------------------------------------------------------
BOOL CSerialPort::Init(	   UINT  portnr,		// portnumber (1..4)
						   UINT  baud,		    	   // baudrate
						   char  parity,		      // parity 
						   UINT  databits,		   // databits 
						   UINT  stopbits,		   // stopbits 
						   DWORD dwCommEvents,	   // EV_RXCHAR, EV_CTS etc
						   UINT  writebuffersize)	// size to the writebuffer
{
//----------------------------------------------------------------------------
	assert(portnr > 0 && portnr < 5);

	BOOL bResult = FALSE;
	char szPort[50];
	char szBaud[50];

	// if the thread is alive: Kill
   while (m_bThreadAlive){
		SetEvent(m_hShutdownEvent);
	}

	// create events
	//
	if (m_ov.hEvent != NULL)
		CloseHandle(m_ov.hEvent);
	m_ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (m_hWriteEvent != NULL)
		CloseHandle(m_hWriteEvent);
	m_hWriteEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	
	if (m_hShutdownEvent != NULL)
		CloseHandle(m_hShutdownEvent);
	m_hShutdownEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	m_hEventArray[0] = m_hShutdownEvent;	// highest priority
	m_hEventArray[1] = m_ov.hEvent;
	m_hEventArray[2] = m_hWriteEvent;


	
	if (m_szWriteBuffer != NULL)
		delete [] m_szWriteBuffer;
	m_szWriteBuffer = new char[writebuffersize];


	m_nWriteBufferSize = writebuffersize;
	m_dwCommEvents = dwCommEvents;


	// now it critical!
	EnterCriticalSection(&m_csCommunicationSync);

	// if the port is already opened: close it
	if (m_hComm != NULL){
		CloseHandle(m_hComm);
		m_hComm = NULL;
	}

	// prepare port CStrings
	sprintf(szPort, "COM%d", portnr);
	sprintf(szBaud, "baud=%d parity=%c data=%d stop=%d", baud, parity, databits, stopbits);

	// get a handle to the port
	m_hComm = CreateFile(szPort,					  	   // communication port CString (COMX)
					     GENERIC_READ | GENERIC_WRITE,	// read/write types
					     0,								      // comm devices must be opened with exclusive access
					     NULL,							      // no security attributes
					     OPEN_EXISTING,					   // comm devices must use OPEN_EXISTING
					     FILE_FLAG_OVERLAPPED,			   // Async I/O
					     0);							         // template must be 0 for comm devices

	if (m_hComm == INVALID_HANDLE_VALUE){
		return FALSE;
   }

	// set the timeout values
	m_CommTimeouts.ReadIntervalTimeout         = 1000;
	m_CommTimeouts.ReadTotalTimeoutMultiplier  = 1000;
	m_CommTimeouts.ReadTotalTimeoutConstant    = 1000;
	m_CommTimeouts.WriteTotalTimeoutMultiplier = 1000;
	m_CommTimeouts.WriteTotalTimeoutConstant   = 1000;

	// configure
	if (SetCommTimeouts(m_hComm, &m_CommTimeouts)){						   
		if (SetCommMask(m_hComm, dwCommEvents))	{
			if (GetCommState(m_hComm, &m_dcb)){
				m_dcb.fRtsControl = RTS_CONTROL_ENABLE;		// set RTS bit high!
				if (BuildCommDCB(szBaud, &m_dcb)){
					if (SetCommState(m_hComm, &m_dcb)){
						// normal operation... continue
					}
					else{
						processErrorMessage("SetCommState()");
					}
				}
				else{
					processErrorMessage("BuildCommDCB()");
				}
			}
			else{
				processErrorMessage("GetCommState()");
			}
		}
		else{
			processErrorMessage("SetCommMask()");
		}
	}
	else{
		processErrorMessage("SetCommTimeouts()");
	}

	// flush the port
	PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	m_nPortNr = portnr;

	LeaveCriticalSection(&m_csCommunicationSync);

	return TRUE;
}


//----------------------------------------------------------------------------
void CSerialPort::write(char* buffer, long size){		
//----------------------------------------------------------------------------

	assert(m_hComm != 0);

	memcpy(m_szWriteBuffer, buffer, size);
	m_nWriteSize = size;

	// set event for write
	//
	SetEvent(m_hWriteEvent);
}

//----------------------------------------------------------------------------
bool CSerialPort::read(char& buffer){		
//----------------------------------------------------------------------------

	assert(m_hComm != 0);

    
   if(!m_readQueue.empty()) {
        buffer = m_readQueue.front();
        m_readQueue.pop();
        return true;
   }

   return false;
}



//----------------------------------------------------------------------------
BOOL CSerialPort::startMonitoring(){
//----------------------------------------------------------------------------

	if (!(m_Thread = AfxBeginThread(commThread, this)))
		return FALSE;
	return TRUE;	
}

//----------------------------------------------------------------------------
BOOL CSerialPort::restartMonitoring(){
//----------------------------------------------------------------------------
	if(m_Thread!=NULL)
		m_Thread->ResumeThread();
	return TRUE;	
}


//----------------------------------------------------------------------------
BOOL CSerialPort::stopMonitoring(){
//----------------------------------------------------------------------------

	if(m_Thread!=NULL)
		m_Thread->SuspendThread(); 
	return TRUE;	
}


//----------------------------------------------------------------------------
void CSerialPort::processErrorMessage(char* ErrorText){
//----------------------------------------------------------------------------

	char *Temp = new char[200];
	
	LPVOID lpMsgBuf;

	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);

	sprintf(Temp, "WARNING:  %s Failed with the following error: \n%s\nPort: %d\n", (char*)ErrorText, lpMsgBuf, m_nPortNr); 
	MessageBox(NULL, Temp, "Application Error", MB_ICONSTOP);

	LocalFree(lpMsgBuf);
	delete[] Temp;
}

//----------------------------------------------------------------------------
/* static */ UINT CSerialPort::commThread(LPVOID pParam){
//----------------------------------------------------------------------------

	// Cast the void pointer passed to the thread back to
	// a pointer of CSerialPort class
	CSerialPort *port = (CSerialPort*)pParam;
	
	// Set the status variable in the dialog class to
	// TRUE to indicate the thread is running.
	port->m_bThreadAlive = TRUE;	
		
	// Misc. variables
	DWORD BytesTransfered = 0; 
	DWORD Event           = 0;
	DWORD CommEvent       = 0;
	DWORD dwError         = 0;
	BOOL  bResult         = TRUE;
	COMSTAT comstat;
		
	// Clear comm buffers at startup
	if (port->m_hComm)		// check if the port is opened
		PurgeComm(port->m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	// begin forever loop.  This loop will run as long as the thread is alive.
	for (;;) { 

		// Make a call to WaitCommEvent().  This call will return immediatly
		// because our port was created as an async port (FILE_FLAG_OVERLAPPED
		// and an m_OverlappedStructerlapped structure specified).  This call will cause the 
		// m_OverlappedStructerlapped element m_OverlappedStruct.hEvent, which is part of the m_hEventArray to 
		// be placed in a non-signeled state if there are no bytes available to be read,
		// or to a signeled state if there are bytes available.  If this event handle 
		// is set to the non-signeled state, it will be set to signeled when a 
		// character arrives at the port.

		// we do this for each port!

		bResult = WaitCommEvent(port->m_hComm, &Event, &port->m_ov);

		if (!bResult)  { 
			// If WaitCommEvent() returns FALSE, process the last error to determin
			// the reason..
			switch (dwError = GetLastError()){ 
			case ERROR_IO_PENDING: 	
					// This is a normal return value if there are no bytes
					// to read at the port.
					// Do nothing and continue
					break;
			case 87:
					// Under Windows NT, this value is returned for some reason.
					// I have not investigated why, but it is also a valid reply
					// Also do nothing and continue.
					break;
			default:
					// All other error codes indicate a serious error has
					// occured.  Process this error.
//					port->processErrorMessage("WaitCommEvent()");
					break;
			}
		}
		else{
			// If WaitCommEvent() returns TRUE, check to be sure there are
			// actually bytes in the buffer to read.  
			//
			// If you are reading more than one byte at a time from the buffer 
			// (which this program does not do) you will have the situation occur 
			// where the first byte to arrive will cause the WaitForMultipleObjects() 
			// function to stop waiting.  The WaitForMultipleObjects() function 
			// resets the event handle in m_OverlappedStruct.hEvent to the non-signelead state
			// as it returns.  
			//
			// If in the time between the reset of this event and the call to 
			// ReadFile() more bytes arrive, the m_OverlappedStruct.hEvent handle will be set again
			// to the signeled state. When the call to ReadFile() occurs, it will 
			// read all of the bytes from the buffer, and the program will
			// loop back around to WaitCommEvent().
			// 
			// At this point you will be in the situation where m_OverlappedStruct.hEvent is set,
			// but there are no bytes available to read.  If you proceed and call
			// ReadFile(), it will return immediatly due to the async port setup, but
			// GetOverlappedResults() will not return until the next character arrives.
			//
			// It is not desirable for the GetOverlappedResults() function to be in 
			// this state.  The thread shutdown event (event 0) and the WriteFile()
			// event (Event2) will not DoCalculate if the thread is blocked by GetOverlappedResults().
			//
			// The solution to this is to check the buffer with a call to ClearCommError().
			// This call will reset the event handle, and if there are no bytes to read
			// we can loop back through WaitCommEvent() again, then proceed.
			// If there are really bytes to read, do nothing and proceed.
			bResult = ClearCommError(port->m_hComm, &dwError, &comstat);

			if (comstat.cbInQue == 0)
				continue;
		}	// end if bResult

		// Main wait function.  This function will normally block the thread
		// until one of three events occur that require action.
		Event = WaitForMultipleObjects(3, port->m_hEventArray, FALSE, INFINITE);

		switch (Event){
		case 0:
				// Shutdown event.  This is event zero so it will be
				// the higest priority and be serviced first.
			 	port->m_bThreadAlive = FALSE;
				// Kill this thread.  break is not needed, but makes me feel better.
				AfxEndThread(100);
				// never reached
				break;
		case 1:	// read event
				GetCommMask(port->m_hComm, &CommEvent);
				if (CommEvent & EV_CTS){
				}
				if (CommEvent & EV_RXFLAG){
				}
				if (CommEvent & EV_BREAK){
				}
				if (CommEvent & EV_ERR){
				}
				if (CommEvent & EV_RING){
				}
				if (CommEvent & EV_RXCHAR){
					// Receive character event from port.
					receiveChar(port, comstat);
				}
					
				break;
		case 2: // write event
				// Write character event from port
				writeChar(port);
				break;

		} // end switch

	} // close forever loop

	return 0;
}


//----------------------------------------------------------------------------
/* static */ void CSerialPort::writeChar(CSerialPort* port){
//----------------------------------------------------------------------------

	BOOL bWrite  = TRUE;
	BOOL bResult = TRUE;

	DWORD BytesSent = 0;

	ResetEvent(port->m_hWriteEvent);

	EnterCriticalSection(&port->m_csCommunicationSync);

	if (bWrite){
		port->m_ov.Offset = 0;
		port->m_ov.OffsetHigh = 0;

		// Clear buffer
		PurgeComm(port->m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

		bResult = WriteFile(port->m_hComm,					// Handle to COMM Port
							port->m_szWriteBuffer,				// Pointer to message buffer in calling finction
							port->m_nWriteSize,              // Length of message to send
							&BytesSent,								// Where to store the number of bytes sent
							&port->m_ov);							// Overlapped structure

		// deal with any error codes
		if (!bResult) {
			DWORD dwError = GetLastError();
			switch (dwError){
				case ERROR_IO_PENDING:
						BytesSent = 0;
						bWrite = FALSE;
						break;
				default:
						// all other error codes
						port->processErrorMessage("WriteFile()");
			}
		} 
		else{
			LeaveCriticalSection(&port->m_csCommunicationSync);
		}
	} 

	if (!bWrite){
		bWrite = TRUE;
		bResult = GetOverlappedResult(port->m_hComm, &port->m_ov, &BytesSent,  TRUE); 		

		LeaveCriticalSection(&port->m_csCommunicationSync);

		if (!bResult){
			port->processErrorMessage("GetOverlappedResults() in WriteFile()");
		}	
	} 
	if (BytesSent != port->m_nWriteSize){
		TRACE("WARNING: WriteFile() error.. Bytes Sent: %d; Message Length: %d\n", BytesSent, port->m_nWriteSize);
	}
}

//----------------------------------------------------------------------------
/* static */ void CSerialPort::receiveChar(CSerialPort* port, COMSTAT comstat){
//----------------------------------------------------------------------------
	BOOL  bRead = TRUE; 
	BOOL  bResult = TRUE;
	DWORD dwError = 0;
	DWORD BytesRead = 0;
	unsigned char RXBuff;

	for (;;) 	{ 
		// Gain ownership of the comm port critical section.
		// This process guarantees no other part of this program 
		// is using the port object. 
		
		EnterCriticalSection(&port->m_csCommunicationSync);

		// ClearCommError() will update the COMSTAT structure and
		// clear any other errors.
		
		bResult = ClearCommError(port->m_hComm, &dwError, &comstat);

		LeaveCriticalSection(&port->m_csCommunicationSync);

		// start forever loop.  I use this type of loop because I
		// do not know at runtime how many loops this will have to
		// run. My solution is to start a forever loop and to
		// break out of it when I have processed all of the
		// data available.  Be careful with this approach and
		// be sure your loop will exit.
		// My reasons for this are not as clear in this sample 
		// as it is in my production code, but I have found this 
		// solutiion to be the most efficient way to do this.
		
		if (comstat.cbInQue == 0){
			// break out when all bytes have been read
			break;
		}
						
		EnterCriticalSection(&port->m_csCommunicationSync);

		if (bRead){
			bResult = ReadFile(port->m_hComm,		// Handle to COMM port 
							   &RXBuff,				// RX Buffer Pointer
							   1,					// Read one byte
							   &BytesRead,			// Stores number of bytes read
							   &port->m_ov);		// pointer to the m_ov structure
			// deal with the error code 
			if (!bResult){ 
				switch (dwError = GetLastError()){ 
					case ERROR_IO_PENDING: 	
						// asynchronous i/o is still in progress 
						// Proceed on to GetOverlappedResults();
						bRead = FALSE;
						break;
					default:
						// Another error has occured.  Process this error.
						port->processErrorMessage("ReadFile()");
						break;
				}
			}
			else{
				// ReadFile() returned complete. It is not necessary to call GetOverlappedResults()
				bRead = TRUE;
			}
		}  // close if (bRead)

		if (!bRead)	{
			bRead = TRUE;
			bResult = GetOverlappedResult(port->m_hComm,	// Handle to COMM port 
										  &port->m_ov,		// Overlapped structure
										  &BytesRead,		// Stores number of bytes read
										  TRUE); 			// Wait flag

			// deal with the error code 
			if (!bResult){
				port->processErrorMessage("GetOverlappedResults() in ReadFile()");
			}	
		}  // close if (!bRead)
				
      port->m_readQueue.push(RXBuff);
		LeaveCriticalSection(&port->m_csCommunicationSync);
		// notify parent that a byte was received
   } // end forever loop

}

