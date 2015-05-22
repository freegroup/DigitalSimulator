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

#if !defined(AFX_LOGICVALUE_H__CEDB51A1_6512_11D2_8912_004F49031E0C__INCLUDED_)
#define AFX_LOGICVALUE_H__CEDB51A1_6512_11D2_8912_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)

class CLogicValue 
{
public:
   enum state{
      High,
      Low
   };
	CLogicValue();
   CLogicValue(state s)
   {
      switch (s){
      case High:
         m_value = 5.0;
         break;
      case Low:
         m_value = 0.0;
         break;
      default:
         m_value = 5.0;
         break;
      }
   };
	virtual ~CLogicValue();

   const CLogicValue& operator=(const CLogicValue&);
   const bool        operator!=(const CLogicValue&) const ;
   const bool        operator==(const CLogicValue&) const ;
   const CLogicValue operator||(const CLogicValue&) const ;
   const CLogicValue operator&&(const CLogicValue&) const ;
   const CLogicValue operator!() const ;

   bool IsHigh() const ;
   bool IsLow() const ;

   virtual char * const GetClassName(){return "CLogicValue";};
protected:

private:
   double  m_value;

};

#endif // !defined(AFX_LOGICVALUE_H__CEDB51A1_6512_11D2_8912_004F49031E0C__INCLUDED_)

