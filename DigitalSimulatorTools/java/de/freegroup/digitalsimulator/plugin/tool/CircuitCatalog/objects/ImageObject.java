package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.objects;


import java.awt.*;
import java.awt.geom.Point2D;
import java.awt.image.BufferedImage;

import de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.util.BufferedImageTool;

/**
 * Holds a BufferedImage.
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class ImageObject extends PaintObject 
{
   private BufferedImage img;
   private Point2D bottomRight;


   public ImageObject(Image image, Point2D location, float alpha) 
   {
      super(null, new Point((int) (location.getX()), (int) (location.getY())), false, alpha);
      img = BufferedImageTool.copy(image);
      bottomRight = new Point2D.Double(this.getLocation().getX() + img.getWidth(), this.getLocation().getY() + img.getHeight());
   }


   public void addGraphics(Graphics2D g) 
   {
      int width = (int) (bottomRight.getX() - this.getLocation().getX());
      int height = (int) (bottomRight.getY() - this.getLocation().getY());
      Image sub = img.getScaledInstance(width, height, BufferedImage.SCALE_SMOOTH);

      g.drawImage(sub, (int) (this.getLocation().getX()), (int) (this.getLocation().getY()), null);
   }

   public void setBottomRightLocation(Point2D point) 
   {
      double threshold = 3.0;
      double newX = point.getX();
      double newY = point.getY();
      if (newX < this.getLocation().getX() + threshold) 
      {
         newX = this.getLocation().getX() + threshold;
      }
      if (newY < this.getLocation().getY() + threshold) 
      {
         newY = this.getLocation().getY() + threshold;
      }
      this.bottomRight = new Point2D.Double(newX, newY);

   }

   public void setLocation(Point2D point) 
   {
      double xDiff = point.getX() - this.getLocation().getX();
      double yDiff = point.getY() - this.getLocation().getY();
      super.setLocation(point);
      this.bottomRight = new Point2D.Double(bottomRight.getX() + xDiff, bottomRight.getY() + yDiff);
   }


   public void setStartDragLocs() 
   {

   }


   public void updateLocation(Point2D point) 
   {
      if (this.getCurrentPointIndex() == 1) 
      {
         this.setBottomRightLocation(point);
      }
      else if (this.getCurrentPointIndex() == 0) 
      {
         this.setLocation(point);
      }
   }


   public BufferedImage getImage() 
   {
      return img;
   }


   public Point2D[] getHighlightPoints() 
   {
      Point2D[] points = new Point2D[]{this.getLocation(), new Point((int) bottomRight.getX(), (int) (bottomRight.getY()))};
      return points;
   }

   public boolean finished(Point2D point) 
   {
      return true;
   }

   public double[] getTranslation() 
   {
      return new double[]{0.0, 0.0};
   }

   public PaintObject createCopy(int xOffset, int yOffset) 
   {
      ImageObject copy = new ImageObject(this.getImage(), this.getLocation(), this.getAlpha());
//    copy.locationEnd = new Point(this.locationEnd.x + xOffset, this.locationEnd.y + yOffset);
//    copy.locationStart = new Point(this.locationStart.x + xOffset, this.locationStart.y + yOffset);
//    copy.updateMiddle();
      return this;
   }
}
