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
#pragma warning(disable : 4786)

#include <afxtempl.h>
#include <afxcoll.h>

class CSortableObArray : public CObArray{
    typedef CObArray inherited ;

public:
	void Sort(int(*CompareFunc)(CObject* pFirst, CObject* pSecond));
	void Sort(int iStartPos, int iElements, int(*CompareFunc)(CObject* pFirst, CObject* pSecond));
};


template< class TYPE >class CTypedSortableObArray : public CSortableObArray{
    typedef CSortableObArray inherited ;
public:
	// Accessing elements
	TYPE GetAt(int nIndex) const
	{ return (TYPE)inherited::GetAt(nIndex); }
	TYPE& ElementAt(int nIndex)
	{ return (TYPE&)inherited::ElementAt(nIndex); }
	void SetAt(int nIndex, TYPE ptr)
	{ inherited::SetAt(nIndex, ptr); }
	
	// Potentially growing the array
	void SetAtGrow(int nIndex, TYPE newElement)
	{ inherited::SetAtGrow(nIndex, newElement); }
	int Add(TYPE newElement)
	{ return inherited::Add(newElement); }
	int Append(const CTypedPtrArray< inherited, TYPE >& src)
	{ return inherited::Append(src); }
	void Copy(const CTypedPtrArray< inherited, TYPE >& src)
	{ inherited::Copy(src); }
	
	// Operations that move elements around
	void InsertAt(int nIndex, TYPE newElement, int nCount = 1)
	{ inherited::InsertAt(nIndex, newElement, nCount); }
	void InsertAt(int nStartIndex, CTypedSortableObArray< TYPE >* pNewArray)
	{ inherited::InsertAt(nStartIndex, pNewArray); }
	
	// overloaded operator helpers
	TYPE operator[](int nIndex) const
	{ return (TYPE)inherited::operator[](nIndex); }
	TYPE& operator[](int nIndex)
	{ return (TYPE&)inherited::operator[](nIndex); }
	
	void Sort( int(*CompareFunc)(TYPE pFirstObj, TYPE pSecondObj) )
	{ inherited::Sort((int(*)(CObject*,CObject*))CompareFunc); }
	void Sort( int iStartPos, int iElements, int(*CompareFunc)(TYPE pFirstObj, TYPE pSecondObj) )
	{ inherited::Sort(iStartPos, iElements, (int(*)(CObject*,CObject*))CompareFunc); }
};

