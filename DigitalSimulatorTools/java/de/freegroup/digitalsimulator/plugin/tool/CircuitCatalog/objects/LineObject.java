package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.objects;

import java.awt.*;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;

/**
 * Draws a Line2D.
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class LineObject extends PaintObject {
   private Point2D locationStart;
   private Point2D locationEnd;
   private Point2D locStartDrag;
   private Point2D locEndDrag;
   private Stroke stroke;

   public LineObject(Color color, Point2D locationStart, Stroke stroke, boolean antialiased, float alpha) 
   {
      super(color, null, antialiased, alpha);
      this.locationStart = locationStart;
      this.locationEnd = locationStart;
      this.stroke = stroke;

      this.updateMiddle();
   }

   public LineObject(Color color, Point2D locationStart, Point2D locationEnd, Stroke stroke, boolean antialiased, float alpha) 
   {
      super(color, null, antialiased, alpha);
      this.locationStart = locationStart;
      this.locationEnd = locationEnd;
      this.stroke = stroke;

      this.updateMiddle();
   }

   public void updateMiddle() 
   {
      double x = locationEnd.getX() + (locationStart.getX() - locationEnd.getX()) / 2.0;
      double y = locationEnd.getY() + (locationStart.getY() - locationEnd.getY()) / 2.0;

      super.setLocation(new Point2D.Double(x, y));
   }


   public void addGraphics(Graphics2D g) 
   {
      g.setStroke(stroke);
      g.setColor(this.getColor());
      Line2D line = new Line2D.Double(locationStart.getX(), locationStart.getY(), locationEnd.getX(), locationEnd.getY());
      g.draw(line);
   }

   public Point2D getLocationStart() 
   {
      return locationStart;
   }

   public void setLocationStart(Point2D locationStart) 
   {
      this.locationStart = new Point2D.Double(locationStart.getX(), locationStart.getY());
   }

   public Point2D getLocationEnd() 
   {
      return locationEnd;
   }

   public void setLocationEnd(Point2D locationEnd) 
   {
      this.locationEnd = new Point2D.Double(locationEnd.getX(), locationEnd.getY());
   }

   public void setLocationMiddle(Point2D point) 
   {
      double xMove = point.getX() - this.getStartDragLoc().getX();
      double yMove = point.getY() - this.getStartDragLoc().getY();
      this.setLocationEnd(new Point2D.Double(locEndDrag.getX() + xMove, locEndDrag.getY() + yMove));
      this.setLocationStart(new Point2D.Double(locStartDrag.getX() + xMove, locStartDrag.getY() + yMove));
      this.updateMiddle();
   }

   public void setStartDragLocs() 
   {
      this.locStartDrag = new Point2D.Double(this.locationStart.getX(), this.locationStart.getY());
      this.locEndDrag = new Point2D.Double(this.locationEnd.getX(), this.locationEnd.getY());
   }


   public void updateLocation(Point2D point) 
   {
      if (this.getCurrentPointIndex() == 1) 
      {
         this.setLocationStart(point);
         this.updateMiddle();
      }
      else if (this.getCurrentPointIndex() == 2) 
      {
         this.setLocationEnd(point);
         this.updateMiddle();
      }
      else if (this.getCurrentPointIndex() == 0) 
      {
         this.setLocationMiddle(point);
      }
      else 
      {
         this.setLocationEnd(point);
         this.updateMiddle();
      }
   }

   public Stroke getStroke() 
   {
      return stroke;
   }

   public void setStroke(Stroke stroke) 
   {
      this.stroke = stroke;
   }

   public Point2D[] getHighlightPoints() 
   {
      Point2D[] points = new Point2D[]{this.getLocation(), locationStart, locationEnd};

      return points;
   }

   public boolean finished(Point2D point) 
   {
      if (this.getCurrentPointIndex() < 0) 
      {
         double dist = point.distance(this.locationStart);
         if (dist < 0.5) {
            return false;
         }
      }
      if (this.locationStart.equals(this.locationEnd)) 
      {
         return false;
      }


      this.updateMiddle();
      return true;

   }

   public double[] getTranslation() 
   {
      return new double[]{0.5, 0.5};
   }

   public PaintObject createCopy(int xOffset, int yOffset) 
   {
      LineObject copy = new LineObject(this.getColor(), this.getLocationStart(), this.getStroke(), this.isAntialiased(), this.getAlpha());
      copy.locationEnd = new Point2D.Double(this.locationEnd.getX() + xOffset, this.locationEnd.getY() + yOffset);
      copy.locationStart = new Point2D.Double(this.locationStart.getX() + xOffset, this.locationStart.getY() + yOffset);
      copy.updateMiddle();
      
      return copy;
   }
}
