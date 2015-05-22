#include "stdafx.h"

#include "utils\autofont.h"
#include "Application\Debug\LogManager.h"
#include "DragDropApp.h"
//#include "DragDropClientapp.h"

#include "JNI_Painter.h"

/*
 * Class:     Painter
 * Method:    drawRect
 * Signature: (IIII)V
 */

CDC* javaPaintDC=0;

void JNICALL Java_Painter_drawLine(JNIEnv *, jclass, jint x1, jint y1, jint x2, jint y2)
{
	PROC_TRACE;

   if(javaPaintDC)
   {
      javaPaintDC->MoveTo(x1, y1);
      javaPaintDC->LineTo(x2, y2);
   }
}


void JNICALL Java_Painter_drawLineRGB(JNIEnv *, jclass, jint x1, jint y1, jint x2, jint y2, jint r, jint g, jint b)
{
	PROC_TRACE;

   if(javaPaintDC)
   {
      CPen pen;
      CPen *old;
      if (pen.CreatePen(PS_SOLID, 1,  RGB(r,g,b)))
         old=javaPaintDC->SelectObject(&pen);
      javaPaintDC->MoveTo(x1, y1);
      javaPaintDC->LineTo(x2, y2);
      javaPaintDC->SelectObject(old);
   }
}



/*
 * Class:     Painter
 * Method:    fillOval
 * Signature: (IIII)V
 */
void JNICALL Java_Painter_fillOval(JNIEnv *, jclass , jint x1, jint y1, jint x2, jint y2, jint r, jint g, jint b,jint borderSize, jint borderR, jint borderG, jint borderB)
{
	PROC_TRACE;

   if(javaPaintDC)
   {
	  CPen newPen(PS_SOLID, borderSize, RGB(borderR,borderG,borderB));
      CBrush brush(RGB(r,g,b));
      CBrush *old=NULL;
	  CPen   *oldPen = javaPaintDC->SelectObject(&newPen);
      old=javaPaintDC->SelectObject(&brush);
      javaPaintDC->Ellipse(x1, y1, x2, y2);
      javaPaintDC->SelectObject(old);
	  javaPaintDC->SelectObject(oldPen);
   }
}


/*
 * Class:     Painter
 * Method:    drawOval
 * Signature: (IIII)V
 */
void JNICALL Java_Painter_drawOval(JNIEnv *, jclass, jint x1, jint y1, jint x2, jint y2)
{
	PROC_TRACE;

   if(javaPaintDC)
   {
      javaPaintDC->Ellipse(x1, y1, x2, y2);
   }
}

/*
 * Class:     Painter
 * Method:    drawOval
 * Signature: (IIII)V
 */
void JNICALL Java_Painter_drawOvalRGB(JNIEnv *, jclass, jint x1, jint y1, jint x2, jint y2, jint r, jint g, jint b)
{
	PROC_TRACE;

   if(javaPaintDC)
   {
      CPen pen;
      CPen *old;
      if (pen.CreatePen(PS_SOLID, 1,  RGB(r,g,b)))
         old=javaPaintDC->SelectObject(&pen);
      javaPaintDC->Ellipse(x1, y1, x2, y2);
      javaPaintDC->SelectObject(old);
   }
}


/*
 * Class:     Painter
 * Method:    drawRect
 * Signature: (IIII)V
 */
void JNICALL Java_Painter_drawRect(JNIEnv *env, jclass clazz, jint x1, jint y1, jint x2, jint y2)
{
	PROC_TRACE;

   Java_Painter_drawRectRGB(env, clazz, x1, y1, x2, y2,0,0,0);
}


/*
 * Class:     Painter
 * Method:    drawRect
 * Signature: (IIIIIII)V
 */
void JNICALL Java_Painter_drawRectRGB(JNIEnv *, jclass, jint x1, jint y1, jint x2, jint y2, jint r, jint g, jint b)
{
	PROC_TRACE;

   if(javaPaintDC)
   {
      CPen pen;
      CPen *old;

      if (pen.CreatePen(PS_SOLID, 1,  RGB(r,g,b)))
         old=javaPaintDC->SelectObject(&pen);
      
      javaPaintDC->Rectangle(x1, y1, x2, y2);
      javaPaintDC->SelectObject(old);
   }
}



/*
 * Class:     Painter
 * Method:    drawRect
 * Signature: (IIII)V
 */
void JNICALL Java_Painter_fillRect(JNIEnv *, jclass , jint x1, jint y1, jint x2, jint y2, jint r, jint g, jint b,jint borderSize, jint borderR, jint borderG, jint borderB)
{
	PROC_TRACE;

   if(javaPaintDC)
   {
	  CPen newPen(PS_SOLID, borderSize, RGB(borderR,borderG,borderB));
      CBrush brush(RGB(r,g,b));
      CBrush *old=NULL;
	  CPen   *oldPen = javaPaintDC->SelectObject(&newPen);
      old=javaPaintDC->SelectObject(&brush);
      javaPaintDC->Rectangle(x1, y1, x2, y2);
      javaPaintDC->SelectObject(old);
	  javaPaintDC->SelectObject(oldPen);
   }
}


/*
 * Class:     Painter
 * Method:    drawString
 * Signature: (IIII)V
 */
void JNICALL Java_Painter_drawText(JNIEnv *env, jclass, jstring str, jint fontHeight, jint left, jint top)
{
	PROC_TRACE;

   static CAutoFont font;

   if(javaPaintDC)
   {
      const char * utf_string;
      jboolean isCopy;
      utf_string = env->GetStringUTFChars(str, &isCopy);
      font.SetDC((HDC)javaPaintDC);
      font.SetHeight(fontHeight);
      javaPaintDC->SelectObject(&font);
      javaPaintDC->TextOut( left,top , utf_string);

      if(isCopy== JNI_TRUE)
      {
         env->ReleaseStringUTFChars(str,utf_string);
      }
   }
}

/*
 * Class:     Painter
 * Method:    drawString
 * Signature: (IIII)V
 */
void JNICALL Java_Painter_drawTextRGB(JNIEnv *env, jclass clazz, jstring str, jint fontHeight, jint left, jint top, jint r, jint g, jint b)
{
	PROC_TRACE;

   if(javaPaintDC)
   {
      COLORREF oldColor =javaPaintDC->SetTextColor( RGB(r,g,b));

      Java_Painter_drawText(env, clazz,  str,  fontHeight,  left,  top);

      javaPaintDC->SetTextColor(oldColor);
   }
}
