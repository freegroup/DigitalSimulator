package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.objects;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.geom.Point2D;

/**
 * An object used to hold infomation about something to draw on a Graphics2D object. It includes information
 * about the color, location, antialiasing, and alpha. Subclasses get to specify a bunch of methods.  
 * See LineObject and others for a concrete example.
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public abstract class PaintObject 
{

   private Color color;
   private Point2D location;
   private boolean selected;
   private int currentPointIndex = -1;
   private Point2D startDrag;
   private boolean antialiased;
   private float alpha;


   public PaintObject(Color color) 
   {
      this(color, null, false);
   }

   public PaintObject(Color color, Point2D location) 
   {
      this(color, location, false);
   }

   public PaintObject(Color color, Point2D location, boolean antialiased) 
   {
      this(color, location, antialiased, 1.0f);

   }

   public PaintObject(Color color, Point2D location, boolean antialiased, float alpha) 
   {

      this.color = color;
      this.location = location;
      this.antialiased = antialiased;
      selected = false;
      this.alpha = alpha;

   }


   public Color getColor() 
   {
      return color;
   }

   public void setColor(Color color) 
   {
      this.color = color;
   }

   public Point2D getLocation() 
   {
      return location;
   }

   public void setLocation(Point2D location) 
   {
      this.location = location;
   }

   public float getAlpha() 
   {
      return alpha;
   }

   public void setAlpha(float alpha) 
   {
      this.alpha = alpha;
   }

   public boolean isSelected() 
   {
      return selected;
   }

   public void setSelected(boolean selected) 
   {
      this.selected = selected;
   }

   public int getCurrentPointIndex() 
   {
      return currentPointIndex;
   }

   public void setCurrentPointIndex(int currentPointIndex) 
   {
      this.currentPointIndex = currentPointIndex;
   }


   public void setStartDragLoc(Point2D point) 
   {
      this.startDrag = point;
      this.setStartDragLocs();


   }

   public Point2D getStartDragLoc() 
   {
      return startDrag;
   }


   public Graphics2D addToGraphics(Graphics2D g) 
   {
      g.translate(this.getTranslation()[0], this.getTranslation()[1]);
      if (this.isAntialiased()) 
      {
         g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
      }
      else 
      {
         g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_OFF);
      }
      float startAlpha = ((AlphaComposite) g.getComposite()).getAlpha();
      g.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, alpha));
      this.addGraphics(g);
      g.translate(-this.getTranslation()[0], -this.getTranslation()[1]);
      g.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, startAlpha));
      return g;

   }

   public boolean isAntialiased() 
   {
      return antialiased;
   }

   public void setAntialiased(boolean antialiased) 
   {
      this.antialiased = antialiased;
   }


   public void keyPressed(KeyEvent e) 
   {

   }

   protected abstract void setStartDragLocs();

   public abstract void addGraphics(Graphics2D g2);

   public abstract Point2D[] getHighlightPoints();

   public abstract void updateLocation(Point2D point);

   public abstract boolean finished(Point2D point);

   public abstract double[] getTranslation();

   public abstract PaintObject createCopy(int xOffset, int yOffset);


}
