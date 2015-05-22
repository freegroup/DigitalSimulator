package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.objects;

import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Point2D;

/**
 *  Draws an Elipse2D.
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class OvalObject extends PaintObject {
   private Point2D locationStart;
   private Point2D locationEnd;
   private Point2D locStartDrag;
   private Point2D locEndDrag;
   private Stroke stroke;
   private boolean filled;


   public OvalObject(Color color, Point2D locationStart, Stroke stroke, boolean antialiased, boolean filled, float alpha) {
      super(color, null, antialiased, alpha);
      this.locationStart = locationStart;
      this.locationEnd = locationStart;

      this.filled = filled;
      this.stroke = stroke;
      this.updateMiddle();


   }

   public void updateMiddle() {
      double x = locationEnd.getX() + (locationStart.getX() - locationEnd.getX()) / 2;
      double y = locationEnd.getY() + (locationStart.getY() - locationEnd.getY()) / 2;

      super.setLocation(new Point2D.Double(x, y));

   }


   public void addGraphics(Graphics2D g) {
      g.setStroke(stroke);
      g.setColor(this.getColor());
      Point2D.Double s = new Point2D.Double(locationStart.getX(), locationStart.getY());
      Point2D.Double e = new Point2D.Double(locationEnd.getX(), locationEnd.getY());

      double width = locationEnd.getX() - locationStart.getX();
      double height = locationEnd.getY() - locationStart.getY();
      if (width < 0.0) {
         double t = e.x;
         e.x = s.x;
         s.x = t;
         width = -width;
      }
      if (height < 0.0) {
         double t = e.y;
         e.y = s.y;
         s.y = t;
         height = -height;

      }
      Ellipse2D.Double oval = new Ellipse2D.Double(s.x, s.y, width, height);
      if (this.isFilled()) {
         g.fill(oval);
      }
      else {
         g.draw(oval);
      }

   }

   public Point2D getLocationStart() {
      return locationStart;
   }

   public void setLocationStart(Point2D locationStart) {
      this.locationStart = new Point2D.Double(locationStart.getX(), locationStart.getY());
   }

   public Point2D getLocationEnd() {
      return locationEnd;
   }

   public void setLocationEnd(Point2D locationEnd) {
      this.locationEnd = new Point2D.Double(locationEnd.getX(), locationEnd.getY());

   }

   public void setLocationMiddle(Point2D point) {

      double xMove = point.getX() - this.getStartDragLoc().getX();
      double yMove = point.getY() - this.getStartDragLoc().getY();
      this.setLocationEnd(new Point2D.Double(locEndDrag.getX() + xMove, locEndDrag.getY() + yMove));
      this.setLocationStart(new Point2D.Double(locStartDrag.getX() + xMove, locStartDrag.getY() + yMove));
      this.updateMiddle();
   }

   public void setStartDragLocs() {

      this.locStartDrag = new Point2D.Double(this.locationStart.getX(), this.locationStart.getY());
      this.locEndDrag = new Point2D.Double(this.locationEnd.getX(), this.locationEnd.getY());

   }


   public void updateLocation(Point2D point) {

      if (this.getCurrentPointIndex() == 1) {
         this.setLocationStart(point);
         this.updateMiddle();
      }
      else if (this.getCurrentPointIndex() == 2) {
         this.setLocationEnd(point);
         this.updateMiddle();

      }
      else if (this.getCurrentPointIndex() == 3) {
         this.setLocationEnd(new Point2D.Double(locationEnd.getX(), point.getY()));
         this.setLocationStart(new Point2D.Double(point.getX(), locationStart.getY()));
         this.updateMiddle();

      }
      else if (this.getCurrentPointIndex() == 4) {
         this.setLocationEnd(new Point2D.Double(point.getX(), locationEnd.getY()));
         this.setLocationStart(new Point2D.Double(locationStart.getX(), point.getY()));
         this.updateMiddle();

      }

      else if (this.getCurrentPointIndex() == 5) {
         this.setLocationStart(new Point2D.Double(locationStart.getX(), point.getY()));
         this.updateMiddle();
      }
      else if (this.getCurrentPointIndex() == 6) {
         this.setLocationEnd(new Point2D.Double(locationEnd.getX(), point.getY()));
         this.updateMiddle();
      }
      else if (this.getCurrentPointIndex() == 7) {
         this.setLocationStart(new Point2D.Double(point.getX(), locationStart.getY()));
         this.updateMiddle();
      }
      else if (this.getCurrentPointIndex() == 8) {
         this.setLocationEnd(new Point2D.Double(point.getX(), locationEnd.getY()));
         this.updateMiddle();
      }

      else if (this.getCurrentPointIndex() == 0) {

         this.setLocationMiddle(point);

      }
      else {
         this.setLocationEnd(point);
         this.updateMiddle();
      }

   }

   public Stroke getStroke() {
      return stroke;
   }

   public void setStroke(Stroke stroke) {
      this.stroke = stroke;
   }

   public Point2D[] getHighlightPoints() {
      Point2D middle = this.getLocation();
      Point2D bottomLeft = new Point2D.Double(locationStart.getX(), locationEnd.getY());
      Point2D bottomRight = new Point2D.Double(locationEnd.getX(), locationStart.getY());
      Point2D middleTop = new Point2D.Double(middle.getX(), locationStart.getY());
      Point2D middleBottom = new Point2D.Double(middle.getX(), locationEnd.getY());
      Point2D middleLeft = new Point2D.Double(locationStart.getX(), middle.getY());
      Point2D middleRight = new Point2D.Double(locationEnd.getX(), middle.getY());


      Point2D[] points = new Point2D[]{middle, locationStart, locationEnd, bottomLeft, bottomRight, middleTop, middleBottom, middleLeft, middleRight};

      return points;
   }

   public boolean finished(Point2D point) {
      if (this.getCurrentPointIndex() < 0) {
         double dist = point.distance(this.locationStart);
         if (dist < 0.5) {
            return false;
         }
      }
      if (this.locationStart.equals(this.locationEnd)) {
         return false;
      }


      this.updateMiddle();
      return true;

   }

   public boolean isFilled() {
      return filled;
   }

   public void setFilled(boolean filled) {
      this.filled = filled;
   }


   public double[] getTranslation() {
      return new double[]{0.5, 0.5};
   }

   public PaintObject createCopy(int xOffset, int yOffset) {
      OvalObject copy = new OvalObject(this.getColor(), this.getLocationStart(), this.getStroke(), this.isAntialiased(), this.isFilled(), this.getAlpha());
      copy.locationEnd = new Point2D.Double(this.locationEnd.getX() + xOffset, this.locationEnd.getY() + yOffset);
      copy.locationStart = new Point2D.Double(this.locationStart.getX() + xOffset, this.locationStart.getY() + yOffset);
      copy.updateMiddle();
      return copy;
   }

}
