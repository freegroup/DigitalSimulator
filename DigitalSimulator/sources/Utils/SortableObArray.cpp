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

#include "SortableObArray.h"
#include "Application\Debug\LogManager.h" 

#define STRIDE_FACTOR 3

//----------------------------------------------------------------------------
void CSortableObArray::Sort(int(*CompareFunc)(CObject* pFirst, CObject* pSecond)){
//----------------------------------------------------------------------------
	PROC_TRACE;

	// CompareFunc is expected to return a positive integer if pFirstObj
	// should follow pSecondObj (is greater than)
	
	// Uses Shell Sort
	
	// Basically it does a bunch of smaller insertion sorts than insertion sorts the
	//  whole thing.  Insertion sorting is much faster on a list that is already
	//  mostly sorted.
	
	// ** NOTE:  Because GetSize() is called to retrieve the number of elements, you should
	//            call SetSize() with the number of valid elements.  An alternative is
	//            shown in the sort function below.
	
	ASSERT_VALID(this);
	
	BOOL bFound;
	int iElements = GetSize();
	int iInner,iOuter,iStride = 1;
	CObject *pTmp;
	
	while (iStride <= iElements)
		iStride = iStride * STRIDE_FACTOR + 1;
	
	while (iStride > (STRIDE_FACTOR - 1))
	{
		iStride = iStride / STRIDE_FACTOR;
		for (iOuter = iStride; iOuter < iElements; iOuter++)
		{
			bFound = 0;
			iInner = iOuter - iStride;
			while ((iInner >= 0) && !bFound)
			{
				if (CompareFunc(m_pData[iInner+iStride],m_pData[iInner]) < 0)
				{
					pTmp = m_pData[iInner+iStride];
					m_pData[iInner+iStride] = m_pData[iInner];
					m_pData[iInner] = pTmp;
					iInner -= iStride;
				}
				else
					bFound = 1;
			}
		}
	}
}

//----------------------------------------------------------------------------
void CSortableObArray::Sort(int iStartPos, int iElements, int(*CompareFunc)(CObject* pFirst, CObject* pSecond)){
//----------------------------------------------------------------------------
	PROC_TRACE;

	// This variation allows you to sort only a portion of the array
	
	ASSERT_VALID(this);
	ASSERT( iStartPos >= 0 && iStartPos <= GetUpperBound() );
	ASSERT( GetSize() - iStartPos >= iElements );
	
	BOOL bFound;
	int iInner,iOuter,iStride = 1;
	CObject *pTmp;
	CObject **pData = &m_pData[iStartPos];
	
	while (iStride <= iElements)
		iStride = iStride * STRIDE_FACTOR + 1;
	
	while (iStride > (STRIDE_FACTOR - 1))
	{
		iStride = iStride / STRIDE_FACTOR;
		for (iOuter = iStride; iOuter < iElements; iOuter++)
		{
			bFound = 0;
			iInner = iOuter - iStride;
			while ((iInner >= 0) && !bFound)
			{
				if (CompareFunc(pData[iInner+iStride],pData[iInner]) < 0)
				{
					pTmp = pData[iInner+iStride];
					pData[iInner+iStride] = pData[iInner];
					pData[iInner] = pTmp;
					iInner -= iStride;
				}
				else
					bFound = 1;
			}
		}
	}
}




/* USAGE

// Create a CObject based class
//
class CMyObject : public CObject
{
public:
    CString name;
    static int CompBackward(CMyObject* pFirstObj, CMyObject* pSecondObj)
    {
        return -lstrcmp((LPCTSTR)pFirstObj->name,(LPCTSTR)pSecondObj->name);
    }
};


// Create an array object
//
CTypedSortableObArray< CMyObject* > array;

array.SetSize(10);

// Fill the array with a bunch of objects
for (int i=0; i < 10; i++)
{
	CMyObject * pObj = new CMyObject;
	pObj->name.Format("Object #%d",i);
	array[i] = pObj;
}

// Sort the array
//
array.Sort(CMyObject::CompBackward);

// Display the contents of the now sorted array
for (int i=0; i < 10; i++)
{
	TRACE1("%s\n",array[i]->name);
}


*/