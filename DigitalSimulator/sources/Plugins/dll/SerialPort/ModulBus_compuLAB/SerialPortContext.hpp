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
#ifndef ISERIALPORTNODE_HPP
#define ISERIALPORTNODE_HPP


#include "../IPluginInfo.h"
#include "../IInputContext.h"
#include "../IOutputContext.h"
#include "../SerialPort.h"

#define LINKAGE		__declspec(dllexport)

class SerialPortContext : IPluginInfo, IInputContext, IOutputContext{
public:
	SerialPortContext();

	virtual bool QueryInterface(const char *iid, IPluginBase **iface);
	virtual void Destroy(void);

	virtual int  write(char value);              // send one byte to the port
	virtual char read();                         // read one byte from port

	virtual void getKey(char * ,long);           // get the unique name of the Plugin
   virtual void getDeviceName(char * ,long);
   virtual void getProducerName(char * ,long);
   virtual void getProducerURL(char * ,long);
   virtual void getProgrammerName(char * ,long);
   virtual void getProgrammerURL(char * ,long);
   virtual void getVersion(char*, long);
   virtual void getLabel(char * ,long);         // gets the label for the GUI object (e.g. "SchmidtInterface at COM:1" )
   virtual int  getPort();                      // returns the COM-Port number
   virtual void Get(char * ,long);     // returns all parameters for save/load of the object
   virtual void Set(const char*);      // parse the required params from the CString

   virtual void DoOption();                     // start a dialog and configure this object


   virtual void onStart();                      // event before the simulation starts
   virtual void onStop();                       // event after the simulation ends

protected:
   void         Init(int );
   static CSerialPort* m_ports[10];
   static bool  m_isInit;
	int	    	 m_refCount;
   int          m_portNr;
   int          m_deviceNr;
   char         m_tmpParam[100];
};

#endif

