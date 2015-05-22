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

#ifndef _DRAGDROP_H_
#define _DRAGDROP_H_

#include <assert.h>

#include "Application\Debug\LogManager.h"
#include "Application\Debug\ExceptionStackTrace.h"

#ifndef TODO
   #define chSTR(x)  #x
   #define chSTR2(x) chSTR(x)
   #define TODO(desc) message( __FILE__"(" chSTR2(__LINE__) "): TODO => " #desc)
#endif


// the sides of a port...
enum PortSides {
        PSNone=1, 
        PSTop, 
        PSRight, 
        PSBottom, 
        PSLeft, 
        PortSidesLast};

// Handle stuff 

#define HANDLE_SIZE 9

enum Handles {
        NoHandle,   
        TopLeft, 
        TopMiddle, 
        TopRight, 
        SideRight, 
        BottomRight,
        BottomMiddle, 
        BottomLeft, 
        SideLeft,
        HandlesLast};

// Text Alignment

enum TextAlign {
        TextTopLeft=1, 
        TextTopMiddle, 
        TextTopRight,
        TextAlignLast};

// For UpdateAllViews Flag...

enum UpdateAllFlags {
        Update_Object=1,
        Refresh_Display,
        Update_Selection,
        Update_Serialize_Hook,
        Update_Delete,
        Update_ClearSelectionHandles,
        Update_RestoreSelectionHandles,
		  Update_New_Document_Size,
        Update_Window,
        Update_Last};                          

#ifndef STOCK_LAST
#define STOCK_LAST 16
#endif
const int DRAGDROP_STOCK_LAST = STOCK_LAST;                          
const int DragDropNoStock = DRAGDROP_STOCK_LAST+1;

// Drawing area parameters...

#define MIN_OBJECT_ON_RESIZE 60 // minimum size of an object in 0.1 mm
#define MIN_LINK_SEGMENT     12 // minimum length of Initial/final link segment
#define MAX_LINK_SEGMENT     45 // maximum length of Initial/final link segment
#define CALC_LINK_SEGMENT    3  // divisor to calculate Initial/final link segment

#endif
