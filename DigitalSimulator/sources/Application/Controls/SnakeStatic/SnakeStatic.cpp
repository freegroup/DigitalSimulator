//////
// EZSnakeCtrl - An Indefinite progressctrl like netscape's status bar progress
// Copyright V.Lakshmi Narasimhan,ezlux@Yahoo.com.
// Feel free to use,modify,twist,turn or even 
// digest the code for any non commercial purposes.
// I would appreciate constructive suggestions & bug reports.
// Please dont delete the above lines.
///////
// EZSnakeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "SnakeStatic.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEZSnakeCtrl

CEZSnakeCtrl::CEZSnakeCtrl()
{
	PROC_TRACE;

	m_bReverse=FALSE;
	m_bTimeForTail=FALSE;
	m_nMax=100;
	m_clrBk=RGB(255,255,255);
	m_nSize=40;
	m_clrEnd=RGB(0,255,255);
	m_clrStart=RGB(255,0,0);
	m_nStep=1;
	m_nPos=0;
	m_nTail=0;
}

CEZSnakeCtrl::~CEZSnakeCtrl()
{
	PROC_TRACE;

}


BEGIN_MESSAGE_MAP(CEZSnakeCtrl, CStatic)
	//{{AFX_MSG_MAP(CEZSnakeCtrl)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEZSnakeCtrl message handlers

void CEZSnakeCtrl::SetSize(int nSize)
{
	PROC_TRACE;

	m_nSize=nSize;
}


void CEZSnakeCtrl::SetBkColor(COLORREF clrFG)
{
	PROC_TRACE;


	m_clrBk=clrFG;
}


void CEZSnakeCtrl::SetGradientFill(COLORREF clrStart, COLORREF clrEnd)
{
	PROC_TRACE;

	m_clrCurStart=m_clrStart=clrStart;
	m_clrCurEnd=m_clrEnd=clrEnd;
}


void CEZSnakeCtrl::SetStep(int nStep)
{
	PROC_TRACE;

	m_nStep=nStep;

}


void CEZSnakeCtrl::SetMax(int nMax)
{
	PROC_TRACE;

    m_nMax=nMax;
}

int CEZSnakeCtrl::GetPos()
{
	PROC_TRACE;

	return m_nPos;

}

int CEZSnakeCtrl::GetStep()
{
	PROC_TRACE;

	return m_nStep;

}

int CEZSnakeCtrl::GetSize()
{
	PROC_TRACE;

	return m_nSize;

}


COLORREF CEZSnakeCtrl::GetBkColor()
{
	PROC_TRACE;

	return m_clrBk;

}


COLORREF CEZSnakeCtrl::GetGradientStartColor()
{
	PROC_TRACE;

	return m_clrStart;

}


COLORREF CEZSnakeCtrl::GetGradientEndColor()
{
	PROC_TRACE;

   return m_clrEnd;
}

int CEZSnakeCtrl::GetTail()
{
	PROC_TRACE;

	return m_nTail;
}

BOOL CEZSnakeCtrl::IsReverse()
{
	PROC_TRACE;

  return m_bReverse;
}


int CEZSnakeCtrl::StepIt()
{
	PROC_TRACE;

   if(!m_bReverse)
   {
	   if(m_nPos>=m_nMax)
	   {
		   m_nPos=m_nMax;
		   if(!m_bTimeForTail) m_bTimeForTail=TRUE;
		   else if(m_nTail>=m_nMax)
		   {
			   m_bTimeForTail=FALSE;
			   m_nPos=m_nMax-m_nStep;
			   m_nTail=m_nMax;
               m_bReverse=TRUE;
			   m_clrCurStart=m_clrEnd;
			   m_clrCurEnd=m_clrStart;
		   }
           else SafeStepTail();
		   		   
	   }
	   else
	   {
	       SafeStepHead();
		   SafeStepTail();
	   }

   }
   else
   {
	   if(m_nPos<=0)
	   {
		   m_nPos=0;
		   if(!m_bTimeForTail) m_bTimeForTail=TRUE;
		   else if(m_nTail<=0)
		   {
			   m_bTimeForTail=FALSE;
			   m_nPos=m_nStep;
			   m_nTail=0;
			   m_bReverse=FALSE;
			   m_clrCurStart=m_clrStart;
			   m_clrCurEnd=m_clrEnd;
		   }
		   else
			   SafeStepTail();

	   }
	   else
	   {
		   SafeStepHead();
		   SafeStepTail();
	   }
   }

   InvalidateRect(NULL);
   return m_nPos;
}



void CEZSnakeCtrl::OnPaint() 
{
	PROC_TRACE;

	CPaintDC dc(this);
	CDC *pdc;
   pdc = &dc;
	CRect rect,rcLeft,rcRight,rcSnake;
	GetClientRect(&rect);

	rcLeft.CopyRect(&rect);
	rcRight.CopyRect(&rect);
	rcSnake.CopyRect(&rect); 

	float nTailpos=(float)m_nTail/(float)m_nMax*(float)rect.right;
	float nHeadpos=(float)m_nPos/(float)m_nMax*(float)rect.right;
	

	rcSnake.left=(long)(m_bReverse?nHeadpos:nTailpos);
	rcSnake.right=(long)(m_bReverse?nTailpos:nHeadpos);

	rcLeft.right=rcSnake.left;
	rcRight.left=rcSnake.right;

   DrawGradient(pdc,rcSnake);

	CBrush brush;
	VERIFY(brush.CreateSolidBrush(m_clrBk));
	pdc->FillRect(&rcLeft, &brush);
	pdc->FillRect(&rcRight,&brush);
	VERIFY(brush.DeleteObject());
	// Do not call CStatic::OnPaint() for painting messages
}

/***********************************************************
//////////Modified DrawGradient from CGradientProgressControl
//////////Thanks::matt weagle (mweagle@redrose.net)
//////////This is the code that actually draws the snake 
*************************************************************/
void CEZSnakeCtrl::DrawGradient(CDC *pDC, CRect rcGrad)
{
	PROC_TRACE;

	
	RECT rectFill;			   // Rectangle for filling band
	float fStep;              // How wide is each band?
	CBrush brush;			// Brush to fill in the bar	
	
	
	//CMemDC memDC(pDC);
	CDC* memDC=pDC;
	
	// First find out the largest color distance between the start and end colors.  This distance
	// will determine how many steps we use to carve up the client region and the size of each
	// gradient rect.
	int r, g, b;							// First distance, then starting value
	float rStep, gStep, bStep;		// Step size for each color
	
	// Get the color differences
	r = (GetRValue(m_clrCurEnd) - GetRValue(m_clrCurStart));
	g = (GetGValue(m_clrCurEnd) - GetGValue(m_clrCurStart));
	b =  (GetBValue(m_clrCurEnd) - GetBValue(m_clrCurStart));
	
	
	// Make the number of steps equal to the greatest distance
	int nSteps = max(abs(r), max(abs(g), abs(b)));
	
	// Determine how large each band should be in order to cover the
	// client with nSteps bands (one for every color intensity level)
	fStep = ((float)abs(rcGrad.right-rcGrad.left)) / (float)nSteps;
	
	// Calculate the step size for each color
	rStep = r/(float)nSteps;
	gStep = g/(float)nSteps;
	bStep = b/(float)nSteps;
	
	// Reset the colors to the starting position
	r = GetRValue(m_clrCurStart);
	g = GetGValue(m_clrCurStart);
	b = GetBValue(m_clrCurStart);
	
	
	// Start filling bands
	for (int iOnBand = 0; iOnBand < nSteps; iOnBand++) 
	{
		
		::SetRect(&rectFill,
			(int)(rcGrad.left+iOnBand * fStep),       // Upper left X
			rcGrad.top,									 // Upper left Y
			rcGrad.left+(int)((iOnBand+1) * fStep),          // Lower right X
			rcGrad.bottom);			// Lower right Y

		if(rectFill.left<rcGrad.left || rectFill.right>rcGrad.right)
		return;
		// CDC::FillSolidRect is faster, but it does not handle 8-bit color depth
		VERIFY(brush.CreateSolidBrush(RGB(r+rStep*iOnBand, g + gStep*iOnBand, b + bStep *iOnBand)));
		memDC->FillRect(&rectFill,&brush);
		VERIFY(brush.DeleteObject());
			


	}
	
	
}

int CEZSnakeCtrl::SafeStepHead()
{
	PROC_TRACE;

   int nStep;
   if(m_bReverse)
   {
	  nStep=m_nPos-m_nStep;
	  if(nStep>0)
	  {
		  m_nPos-=m_nStep;
		  nStep=m_nStep;
	  }
	  else
	  {
		  nStep=m_nPos;
		  m_nPos=0;
	  }
   }
   else
   {
	  nStep=m_nPos+m_nStep;
	  if(nStep<m_nMax)
	  {
		  m_nPos+=m_nStep;
		  nStep=m_nStep;
	  }
	  else
	  {
		  nStep=m_nMax-m_nPos;
		  m_nPos=m_nMax;
	  }

   }

  return nStep;
}

int CEZSnakeCtrl::SafeStepTail()
{
	PROC_TRACE;

if(!m_bTimeForTail && ((m_bReverse && m_nMax-m_nPos<m_nSize) || (!m_bReverse && m_nPos<m_nSize)))
  return 0;

   int nStep;
   if(m_bReverse)
   {
	  nStep=m_nTail-m_nStep;
	  if(nStep>0)
	  {
		  m_nTail-=m_nStep;
		  nStep=m_nStep;
	  }
	  else
	  {
		  nStep=m_nTail;
		  m_nTail=0;
	  }
   }
   else
   {
	  nStep=m_nTail+m_nStep;
	  if(nStep<m_nMax)
	  {
		  m_nTail+=m_nStep;
		  nStep=m_nStep;
	  }
	  else
	  {
		  nStep=m_nMax-m_nTail;
		  m_nTail=m_nMax;
	  }

   }

  return nStep;
}

void CEZSnakeCtrl::ResetProgress()
{
	PROC_TRACE;

	m_bReverse=FALSE;
	m_nTail=m_nPos=0;


}

int CEZSnakeCtrl::GetMax()
{
	PROC_TRACE;

  return m_nMax;
}
