package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.objects;

import java.awt.*;
import java.awt.geom.GeneralPath;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;
import java.awt.geom.QuadCurve2D;
import java.util.ArrayList;

/**
 * Draws a "QuadArrow".
 * 
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class QuadArrowObject extends PaintObject {
   private Point2D locationStart;
   private Point2D locationEnd;
   private Point2D locationCtrl;
   private Point2D locStartDrag;
   private Point2D locEndDrag;
   private Point2D locCtrlDrag;
   private Point2D locHeadDrag;
   private double headMultDrag;

   private double endWidth;
   private double tipWidth;
   private double startWidth;
   private Stroke stroke;
   private GeneralPath arrow;
   private QuadCurve2D.Double quad;
   private ArrayList tempPoints;

   private Line2D.Double base;

   private QuadCurve2D.Double left;

   private Line2D.Double leftOut;

   private Line2D.Double leftTip;

   private Line2D.Double rightTip;

   private Line2D.Double rightOut;

   private QuadCurve2D.Double right;

   private double headMult;
   private Point2D headPoint;
   private Point2D endPoint;

   private Point2D tipPoint;
   private Point2D startPoint;
   private Point2D startPointDrag;
   private double startWidthDrag;
   private boolean filled;


   public QuadArrowObject(Color color, Point2D locationStart, Stroke stroke, boolean antialiased, boolean filled, float alpha) {
      super(color, null, antialiased, alpha);
      this.locationStart = locationStart;
      this.locationCtrl = locationStart;
      this.locationEnd = locationStart;
      this.stroke = stroke;
      this.filled = filled;
      this.init();


   }

   public QuadArrowObject(Color color, Point2D locationStart, Point2D locationEnd, Point2D locationCtrl, Stroke stroke, boolean antialiased, boolean filled, float alpha) {
      super(color, null, antialiased, alpha);
      this.locationStart = locationStart;
      this.locationEnd = locationEnd;
      this.locationCtrl = locationCtrl;
      this.stroke = stroke;
      this.init();


   }

   public void init() {
      tempPoints = new ArrayList();
      this.headMult = 0.8;
      this.endWidth = 10;
      this.tipWidth = 20;
      this.startWidth = 10;
      this.updateShape();

   }

   public boolean isFilled() {
      return filled;
   }

   public void setFilled(boolean filled) {
      this.filled = filled;
   }

   public void updateTempPoints(Point2D point) {
      if (!tempPoints.contains(point)) {
         tempPoints.add(point);
      }
      if (tempPoints.size() >= 5) {
         Point2D.Double mid = this.subPoint(new Line2D.Double(this.getLocationStart(), this.getLocationEnd()), 0.5);
         Point2D midDrag = (Point2D) (tempPoints.get((tempPoints.size() / 2) + 1));

         locationCtrl = new Point2D.Double((midDrag.getX() + midDrag.getX() - mid.x), (int) (midDrag.getY() + midDrag.getY() - mid.y));
         updateShape();

      }

   }

   public void updateHeadPoint(Point2D point) {
      double origDist = quad.getP2().distance(this.locHeadDrag);

      double currentDist = quad.getP2().distance(point);

      double newMult = 1.0 - (1.0 - headMultDrag) * currentDist / origDist;
      this.headMult = newMult;

   }

   public void updateEndPoint(Point2D point) {
      double dist = headPoint.distance(point);


      this.endWidth = dist;
   }

   public void updateTipPoint(Point2D point) {
      double dist = headPoint.distance(point);


      this.tipWidth = dist;
   }

   public void updateStartPoint(Point2D point) {
      double dist = quad.getP1().distance(point);

      double distStart = startPointDrag.distance(point);


      if (distStart > dist && distStart > startWidthDrag && startWidthDrag > 0) {
         dist = -dist;
      }
      else if (distStart < dist && distStart < startWidthDrag && startWidthDrag < 0) {
         dist = -dist;
      }
      this.startWidth = dist;
   }

   public void updateShape() {
      double x = locationEnd.getX() + (locationStart.getX() - locationEnd.getX()) / 2;
      double y = locationEnd.getY() + (locationStart.getY() - locationEnd.getY()) / 2;
      super.setLocation(new Point2D.Double(x, y));

      quad = new QuadCurve2D.Double(locationStart.getX(), locationStart.getY(), locationCtrl.getX(), locationCtrl.getY(), locationEnd.getX(), locationEnd.getY());
      Line2D.Double line = new Line2D.Double(locationStart, locationEnd);
      if (line.ptLineDist(locationCtrl) < Double.MIN_VALUE) {
         return;
      }

      QuadCurve2D.Double subCurve = this.getSubCurve(quad, headMult);
      Line2D.Double cLA = new Line2D.Double(subCurve.getCtrlPt(), subCurve.getP1());
      Line2D.Double cLB = new Line2D.Double(subCurve.getCtrlPt(), subCurve.getP2());
      this.headPoint = new Point2D.Double(subCurve.getX2(), subCurve.getY2());


      Point2D.Double endLeft = getTPoint(cLB, endWidth);
      Point2D.Double endLeftTip = getTPoint(cLB, tipWidth);
      Point2D.Double startLeft = getTPoint(cLA, -startWidth);

      Point2D.Double endRight = getTPoint(cLB, -endWidth);
      this.endPoint = new Point((int) endRight.getX(), (int) endRight.getY());
      Point2D.Double endRightTip = getTPoint(cLB, -tipWidth);
      this.tipPoint = new Point2D.Double((int) endRightTip.getX(), (int) endRightTip.getY());
      Point2D.Double startRight = getTPoint(cLA, startWidth);
      this.startPoint = new Point2D.Double((int) startRight.getX(), (int) startRight.getY());



      Point2D.Double leftCtrl = this.getIntersectionPoint(startLeft, this.getLineSlope(cLA), endLeft, this.getLineSlope(cLB));
      Point2D.Double rightCtrl = this.getIntersectionPoint(startRight, this.getLineSlope(cLA), endRight, this.getLineSlope(cLB));
      if (leftCtrl == null || rightCtrl == null) {
         return;
      }

      arrow = new GeneralPath();

      base = new Line2D.Double(startRight, startLeft);
      arrow.append(base, true);
      left = new QuadCurve2D.Double(startLeft.x, startLeft.y, leftCtrl.x, leftCtrl.y, endLeft.x, endLeft.y);
      arrow.append(left, true);
      leftOut = new Line2D.Double(endLeft, endLeftTip);
      arrow.append(leftOut, true);
      leftTip = new Line2D.Double(endLeftTip, quad.getP2());
      arrow.append(leftTip, true);
      rightTip = new Line2D.Double(quad.getP2(), endRightTip);
      arrow.append(rightTip, true);
      rightOut = new Line2D.Double(endRightTip, endRight);
      arrow.append(rightOut, true);
      right = new QuadCurve2D.Double(endRight.x, endRight.y, rightCtrl.x, rightCtrl.y, startRight.x, startRight.y);
      arrow.append(right, true);

   }


   public void addGraphics(Graphics2D g) {
      g.setStroke(stroke);
      g.setColor(this.getColor());
      if (arrow != null) {


         if (this.isFilled()) {
            g.fill(arrow);
         }
         else {
            g.draw(arrow);
         }


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

   public Point2D getLocationCtrl() {
      return locationCtrl;
   }

   public void setLocationCtrl(Point2D locationCtrl) {
      this.locationCtrl = new Point2D.Double(locationCtrl.getX(), locationCtrl.getY());
   }

   public void setLocationMiddle(Point2D point) {

      double xMove = point.getX() - this.getStartDragLoc().getX();
      double yMove = point.getY() - this.getStartDragLoc().getY();
      this.setLocationEnd(new Point2D.Double(locEndDrag.getX() + xMove, locEndDrag.getY() + yMove));
      this.setLocationStart(new Point2D.Double(locStartDrag.getX() + xMove, locStartDrag.getY() + yMove));
      this.setLocationCtrl(new Point2D.Double(locCtrlDrag.getX() + xMove, locCtrlDrag.getY() + yMove));
      this.updateShape();
   }

   public void setStartDragLocs() {

      this.locStartDrag = new Point2D.Double(this.locationStart.getX(), this.locationStart.getY());
      this.locEndDrag = new Point2D.Double(this.locationEnd.getX(), this.locationEnd.getY());
      this.locCtrlDrag = new Point2D.Double(this.locationCtrl.getX(), this.locationCtrl.getY());
      this.locHeadDrag = new Point2D.Double(this.headPoint.getX(), this.headPoint.getY());
      this.startPointDrag = new Point2D.Double(this.startPoint.getX(), this.startPoint.getY());
      this.headMultDrag = headMult;
      this.startWidthDrag = startWidth;

   }


   public void updateLocation(Point2D point) {

      if (this.getCurrentPointIndex() == 1) {
         this.setLocationStart(point);
         this.updateShape();
      }
      else if (this.getCurrentPointIndex() == 2) {
         this.setLocationEnd(point);
         this.updateShape();

      }
      else if (this.getCurrentPointIndex() == 3) {
         this.setLocationCtrl(point);
         this.updateShape();

      }
      else if (this.getCurrentPointIndex() == 4) {
         this.updateHeadPoint(point);
         this.updateShape();

      }
      else if (this.getCurrentPointIndex() == 5) {
         this.updateEndPoint(point);
         this.updateShape();

      }

      else if (this.getCurrentPointIndex() == 6) {
         this.updateTipPoint(point);
         this.updateShape();

      }
      else if (this.getCurrentPointIndex() == 7) {
         this.updateStartPoint(point);
         this.updateShape();

      }

      else if (this.getCurrentPointIndex() == 0) {

         this.setLocationMiddle(point);

      }
      else {
         this.setLocationEnd(point);
         this.updateTempPoints(point);
      }

   }

   public Stroke getStroke() {
      return stroke;
   }

   public void setStroke(Stroke stroke) {

      this.stroke = stroke;
   }

   public Point2D[] getHighlightPoints() {

      Point2D[] points = new Point2D[]{this.getLocation(),
                                       locationStart,
                                       locationEnd,
                                       locationCtrl,
                                       headPoint,
                                       endPoint,
                                       tipPoint,
                                       startPoint};


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
      if (tempPoints != null && tempPoints.size() < 5) {
         return false;
      }


      this.updateShape();
      tempPoints = null;
      return true;

   }

   public double[] getTranslation() {
      return new double[]{0.5, 0.5};
   }

   public PaintObject createCopy(int xOffset, int yOffset) {
      QuadArrowObject copy = new QuadArrowObject(this.getColor(), this.getLocationStart(), this.getStroke(), this.isAntialiased(), this.isFilled(), this.getAlpha());
      copy.locationEnd = new Point2D.Double(this.locationEnd.getX() + xOffset, this.locationEnd.getY() + yOffset);
      copy.locationStart = new Point2D.Double(this.locationStart.getX() + xOffset, this.locationStart.getY() + yOffset);
      copy.locationCtrl = new Point2D.Double(this.locationCtrl.getX() + xOffset, this.locationCtrl.getY() + yOffset);
      copy.headMult = headMult;
      copy.endWidth = endWidth;
      copy.tipWidth = tipWidth;
      copy.startWidth = startWidth;
      copy.tempPoints = null;
      copy.updateShape();

      return copy;
   }

   public Point2D.Double subPoint(Line2D.Double line, double t) {
      double midx = line.getX1() + (line.getX2() - line.getX1()) * t;
      double midy = line.getY1() + (line.getY2() - line.getY1()) * t;
      return new Point2D.Double(midx, midy);
   }

   public QuadCurve2D.Double getSubCurve(QuadCurve2D.Double quad, double t) {
      Line2D.Double lineA = new Line2D.Double(quad.getP1(), quad.getCtrlPt());
      Point2D.Double newCtrl = this.subPoint(lineA, t);
      Point2D.Double newEnd = this.pointOnQuad(quad, t);
      return new QuadCurve2D.Double(quad.getX1(), quad.getY1(), newCtrl.x, newCtrl.y, newEnd.x, newEnd.y);


   }

   public Point2D.Double pointOnQuad(QuadCurve2D.Double quad, double t) {
      double x = (1 - t) * (1 - t) * quad.getX1() + 2 * t * (1 - t) * quad.getCtrlX() + t * t * quad.getX2();
      double y = (1 - t) * (1 - t) * quad.getY1() + 2 * t * (1 - t) * quad.getCtrlY() + t * t * quad.getY2();
      return new Point2D.Double(x, y);

   }

   public Point2D.Double getTPoint(Line2D.Double line, double distance) {

      double slope = this.getLineSlope(line);

      double invSlope = -1.0 / slope;
      if (slope == 0) {
         invSlope = Double.MAX_VALUE;
      }
      double xDist = Math.sqrt(distance * distance / (invSlope * invSlope + 1));

      double yDist = invSlope * xDist;

      if (distance < 0) {
         if (line.getY2() < line.getY1()) {
            return new Point2D.Double(line.getX2() + xDist, line.getY2() + yDist);
         }
         else {
            return new Point2D.Double(line.getX2() - xDist, line.getY2() - yDist);
         }
      }
      else {
         if (line.getY2() > line.getY1()) {
            return new Point2D.Double(line.getX2() + xDist, line.getY2() + yDist);
         }
         else {
            return new Point2D.Double(line.getX2() - xDist, line.getY2() - yDist);
         }
      }
   }

   public Point2D.Double getIntersectionPoint(Point2D.Double pointA, double slopeA, Point2D.Double pointB, double slopeB) {

      if (pointA.equals(pointB)) {
         return pointA;
      }
      if (slopeA == slopeB || slopeA == -slopeB) {
         double slopeC = (pointB.y - pointA.y) / (pointB.x / pointB.x);
         if (slopeC == slopeA || slopeC == -slopeA) {
            return this.subPoint(new Line2D.Double(pointA, pointB), 0.5);
         }
         else {
            return null;
         }

      }
      double intA = pointA.y - pointA.x * slopeA;
      double intB = pointB.y - pointB.x * slopeB;

      double xPoint = (intB - intA) / (slopeA - slopeB);
      double yPoint = slopeA * xPoint + intA;

      return new Point2D.Double(xPoint, yPoint);
   }

   public double getLineSlope(Line2D.Double line) {
      if (line.getX2() - line.getX1() == 0.0) {
         return Double.MAX_VALUE;
      }
      return ((line.getY2() - line.getY1()) / (line.getX2() - line.getX1()));
   }
}
