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
// FOR DOKUMENTATION SEE IN Context.h !!!!!
//

#ifndef __IOBJECTWORKER_H_INCLUDED
#define __IOBJECTWORKER_H_INCLUDED

#include "../../IPluginBase.h"

interface IObjectWorker :IPluginBase{

public:
	virtual int  calculate(char *input ,char* lastInput,long inputCount, 
                          char* output, long outputCount,
                          char* param) = 0;
   virtual void onStartCalculate(char* param)=0;
   virtual void onStopCalculate(char* param)=0;
   virtual int  doConfigure(HWND view, char*  param) = 0;
   virtual void layoutOutput(long*  xPositions, 
                             long*  yPositions,
                             long   inputCount, 
                             long   outputCount,
                             char*  param) = 0;
   virtual void layoutInput(long*  xPositions, 
                            long*  yPositions,
                            long   inputCount, 
                            long   outputCount,
                            char*  param) = 0;
   virtual bool paint(CDC* pDC,
                     CPoint location, 
                     long   inputCount, 
                     long   outputCount, 
                     char*  param)=0;
   virtual void initParam(char* param)=0;
   virtual void cleanupParam(char* param)=0;
};

#endif
