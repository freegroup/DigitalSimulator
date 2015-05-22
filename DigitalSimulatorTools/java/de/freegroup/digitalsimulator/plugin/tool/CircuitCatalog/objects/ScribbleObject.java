package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.objects;

import java.awt.*;
import java.awt.geom.GeneralPath;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.Iterator;

/**
 * Draws a polyline. 
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class ScribbleObject extends PaintObject {

   private ArrayList points;
   private ArrayList dragPoints;
   private Stroke stroke;
   private boolean filled;

   public ScribbleObject(Color color, Point2D locationStart, Stroke stroke, boolean antialiased, boolean filled, float alpha) {
      super(color, null, antialiased, alpha);
      points = new ArrayList();
      points.add(locationStart);


      this.stroke = stroke;
      this.filled = filled;

      this.updateMiddle();


   }

   public void updateMiddle() {
      Point2D locationStart = (Point2D) points.get(0);
      Point2D locationEnd = (Point2D) points.get(points.size() - 1);
      double x = locationEnd.getX() + (locationStart.getX() - locationEnd.getX()) / 2;
      double y = locationEnd.getY() + (locationStart.getY() - locationEnd.getY()) / 2;
      super.setLocation(new Point2D.Double(x, y));

   }


   public void addGraphics(Graphics2D g) {
      g.setColor(this.getColor());
      g.setStroke(stroke);
      int[] x = new int[points.size()];
      int[] y = new int[points.size()];
      Point2D current = (Point2D) points.get(0);
      GeneralPath poly = new GeneralPath();

      for (int i = 1; i < points.size(); i++) {
         Point2D next = (Point2D) (points.get(i));
         Line2D line = new Line2D.Double(current, next);
         poly.append(line, true);
         current = next;

      }
      if (filled) {
         g.fill(poly);
      }
      else {
         g.draw(poly);
      }


   }

   public boolean isFilled() {
      return filled;
   }

   public void setFilled(boolean filled) {
      this.filled = filled;
   }

   public void move(Point2D point) {
      double xMove = point.getX() - this.getStartDragLoc().getX();
      double yMove = point.getY() - this.getStartDragLoc().getY();
      points.clear();
      for (Iterator iterator = dragPoints.iterator(); iterator.hasNext();) {
         Point2D point1 = (Point2D) iterator.next();
         addPoint(new Point2D.Double(point1.getX() + xMove, point1.getY() + yMove));
      }

      this.updateMiddle();

   }

   public void addPoint(Point2D point) {

      if (!points.contains(point)) {
         points.add(point);
      }


   }

   public void updateLocation(Point2D point) {

      if (this.getCurrentPointIndex() >= 0) {
         this.move(point);

      }

      else {

         this.addPoint(point);

      }

   }

   public Stroke getStroke() {
      return stroke;
   }

   public void setStroke(Stroke stroke) {
      this.stroke = stroke;
   }

   public Point2D[] getHighlightPoints() {
      Point2D[] pointArray = new Point2D[]{(Point2D) points.get(0), (Point2D) points.get(points.size() - 1)};

      return pointArray;
   }

   public boolean finished(Point2D point) {
      if (this.getCurrentPointIndex() < 0) {
         this.updateMiddle();
         this.addPoint(point);
         return true;
      }

      this.updateMiddle();
      return true;
   }

   public double[] getTranslation() {
      return new double[]{0.5, 0.5};
   }

   public void setStartDragLocs() {
      dragPoints = new ArrayList();
      for (Iterator iterator = points.iterator(); iterator.hasNext();) {
         Point2D point = (Point2D) iterator.next();
         dragPoints.add(new Point2D.Double(point.getX(), point.getY()));
      }
   }

   public PaintObject createCopy(int xOffset, int yOffset) {
      Point2D first = (Point2D) points.get(0);

      ScribbleObject copy = new ScribbleObject(this.getColor(), new Point2D.Double(first.getX() + xOffset, first.getY() + yOffset), this.getStroke(), this.isAntialiased(), this.isFilled(), this.getAlpha());
      for (Iterator iterator = points.iterator(); iterator.hasNext();) {
         Point2D point = (Point2D) iterator.next();
         copy.addPoint(new Point2D.Double(point.getX() + xOffset, point.getY() + yOffset));
      }
      return copy;
   }


}
