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
#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__

#include "queue"
using namespace std ;

class CSerialPort{

public:
	// contruction and destruction
	CSerialPort();
	virtual		~CSerialPort();

	BOOL		Init(UINT portnr=1, UINT baud=19200, char parity='N', UINT databits = 8, UINT stopsbits = 1, DWORD dwCommEvents=EV_RXCHAR|EV_CTS, UINT nBufferSize=512);

	BOOL		startMonitoring();
	BOOL		restartMonitoring();
	BOOL		stopMonitoring();

   int      getPort(){return m_nPortNr;};
	void		write(char* buffer,long size);
	bool		read(char& buffer );

protected:
	
	void        processErrorMessage(char* ErrorText);
	static UINT	commThread(LPVOID pParam);
	static void	receiveChar(CSerialPort* port, COMSTAT comstat);
	static void	writeChar(CSerialPort* port);

	// synchronisation objects
	UINT			      m_nPortNr;
	HANDLE  				m_hComm;

	OVERLAPPED			m_ov;

	HANDLE				m_hWriteEvent;
	HANDLE				m_hShutdownEvent;
	char             *m_szWriteBuffer;
	CWinThread       *m_Thread;
	BOOL   				m_bThreadAlive;

   CRITICAL_SECTION	m_csCommunicationSync;
	HANDLE				m_hEventArray[3];

	COMMTIMEOUTS		m_CommTimeouts;
	DCB					m_dcb;

	DWORD             m_nWriteSize;
	DWORD		  		   m_dwCommEvents;
	DWORD				   m_nWriteBufferSize;
   queue<char>       m_readQueue;
};

#endif __SERIALPORT_H__


