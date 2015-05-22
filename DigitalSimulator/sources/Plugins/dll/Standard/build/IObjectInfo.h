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
// This is a part of the base class for the plugin architecture
// for the DigitalSimulator
//
// DON`T CHANGE THIS FILE
//
// FOR DOKUMENTATION SEE IN Context.h !!!
//


#ifndef __IOBJECTINFO_H_INCLUDED
#define __IOBJECTINFO_H_INCLUDED

#include "../../IPluginBase.h"

interface IObjectInfo :IPluginBase{

public:
	virtual char * getKey()           = 0;
   virtual char * getName()          = 0;
   virtual char * getProgrammerName()= 0;
   virtual char * getProgrammerURL() = 0;
   virtual char * getProgrammerMail()= 0;
   virtual char * getVersion()       = 0;
   virtual char * getLabel()         = 0;
   virtual char * getDescription()   = 0;
   virtual char * getGroup()         = 0;
   virtual char * getBuildDate()     = 0;

   virtual CSize getInputCountRange()          = 0;
   virtual CSize getOutputCountRange()         = 0;
   virtual CSize getSize(long inputCount, long outputCount) = 0;
   virtual long  getParamCount()               = 0;
};

#endif
