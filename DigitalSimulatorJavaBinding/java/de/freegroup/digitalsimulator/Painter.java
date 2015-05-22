package de.freegroup.digitalsimulator;
import java.util.*;
import java.awt.Color;

public class Painter
{
   private static native void n_drawLine(int x1, int y1, int x2, int y2);
   private static native void n_drawLine(int x1, int y1, int x2, int y2, int red, int green, int blue);
   public static void drawLine(int x1, int y1, int x2, int y2)
   {
     if(Application.isRunningInDigiSim())
      n_drawLine( x1,  y1,  x2,  y2);
   }
   public static void drawLine(int x1, int y1, int x2, int y2, int red, int green, int blue)
   {
     if(Application.isRunningInDigiSim())
      n_drawLine( x1,  y1,  x2,  y2,  red,  green,  blue);
   }
   public static void drawLine(int x1, int y1, int x2, int y2, Color color)
   {
        drawLine(x1,y1,x2,y2,color.getRed(), color.getGreen(), color.getBlue());
   }

   /**
    * filled oval methods
    *
    *
    */
   private static native void n_fillOval(int x1, int y1, int x2, int y2, int red, int green, int blue, int borderSize, int borderR,int borderG, int borderB);
   public static void fillOval(int x1, int y1, int x2, int y2, int red, int green, int blue, int borderSize, int borderR,int borderG, int borderB)
   {
     if(Application.isRunningInDigiSim())
      n_fillOval(x1, y1, x2, y2, red, green, blue, borderSize, borderR,borderG, borderB);
   }
   public static void fillOval(int x1, int y1, int x2, int y2, Color fill, int borderSize, Color border)
   {
        fillOval(x1,y1,x2,y2,fill.getRed(), fill.getGreen(), fill.getBlue(),borderSize,border.getRed(), border.getGreen(), border.getBlue());
   }
   public static void fillOval(int x1, int y1, int x2, int y2, int red, int green, int blue)
   {
        fillOval(x1,y1,x2,y2,red, green,blue,1,red, green,blue);
   }
   public static void fillOval(int x1, int y1, int x2, int y2, Color color)
   {
        fillOval(x1,y1,x2,y2,color.getRed(), color.getGreen(), color.getBlue(),1,color.getRed(), color.getGreen(), color.getBlue());
   }
   public static void fillOval(int x1, int y1, int x2, int y2)
   {
        fillOval(x1,y1,x2,y2,0, 0,0,0,0,0,0);
   }


   private static native void n_drawOval(int x1, int y1, int x2, int y2);
   private static native void n_drawOval(int x1, int y1, int x2, int y2, int red, int green, int blue);
   public static void drawOval(int x1, int y1, int x2, int y2)
   {
     if(Application.isRunningInDigiSim())
      n_drawOval(x1, y1, x2, y2);
   }
   public static void drawOval(int x1, int y1, int x2, int y2, int red, int green, int blue)
   {
     if(Application.isRunningInDigiSim())
      n_drawOval(x1, y1, x2, y2, red, green, blue);
   }
   public static void drawOval(int x1, int y1, int x2, int y2, Color color)
   {
        drawOval(x1,y1,x2,y2,color.getRed(), color.getGreen(), color.getBlue());
   }

   private static native void n_drawRect(int x1, int y1, int x2, int y2);
   private static native void n_drawRect(int x1, int y1, int x2, int y2, int red, int green, int blue);
   public static void drawRect(int x1, int y1, int x2, int y2)
   {
     if(Application.isRunningInDigiSim())
      n_drawRect(x1, y1, x2, y2);
   }
   public static void drawRect(int x1, int y1, int x2, int y2, int red, int green, int blue)
   {
     if(Application.isRunningInDigiSim())
        n_drawRect(x1, y1, x2, y2, red, green, blue);
   }
   public static void drawRect(int x1, int y1, int x2, int y2, Color color)
   {
        drawRect(x1,y1,x2,y2,color.getRed(), color.getGreen(), color.getBlue());
   }

   /**
    *
    */
   private static native void n_fillRect(int x1, int y1, int x2, int y2, int red, int green, int blue, int borderSize, int borderR,int borderG, int borderB);
   public static void fillRect(int x1, int y1, int x2, int y2, int red, int green, int blue, int borderSize, int borderR,int borderG, int borderB)
   {
     if(Application.isRunningInDigiSim())
        n_fillRect(x1, y1, x2, y2, red, green, blue, borderSize, borderR,borderG, borderB);
   }
   public static void fillRect(int x1, int y1, int x2, int y2, Color fill, int borderSize, Color border)
   {
        fillRect(x1,y1,x2,y2,fill.getRed(), fill.getGreen(), fill.getBlue(),borderSize,border.getRed(), border.getGreen(), border.getBlue());
   }
   public static void fillRect(int x1, int y1, int x2, int y2, int red, int green, int blue)
   {
        fillRect(x1,y1,x2,y2,red, green,blue,1,red, green,blue);
   }
   public static void fillRect(int x1, int y1, int x2, int y2, Color color)
   {
        fillRect(x1,y1,x2,y2,color.getRed(), color.getGreen(), color.getBlue(),1,color.getRed(), color.getGreen(), color.getBlue());
   }
   public static void fillRect(int x1, int y1, int x2, int y2)
   {
        fillRect(x1,y1,x2,y2,0, 0,0,0,0,0,0);
   }

   private static native void n_drawText(String str , int fontHeight, int left, int top);
   private static native void n_drawText(String str , int fontHeight, int left, int top, int red, int green, int blue);
   public static void drawText(String str , int fontHeight, int left, int top)
   {
     if(Application.isRunningInDigiSim())
      n_drawText(str , fontHeight, left, top);
   }
   public static void drawText(String str , int fontHeight, int left, int top, int red, int green, int blue)
   {
     if(Application.isRunningInDigiSim())
       n_drawText(str , fontHeight, left, top,  red,  green,  blue) ;    
   }
   public static void drawText(String str , int fontHeight, int left, int top, Color color)
   {
        drawText(str , fontHeight, left, top, color.getRed(), color.getGreen(), color.getBlue());
   }
}
