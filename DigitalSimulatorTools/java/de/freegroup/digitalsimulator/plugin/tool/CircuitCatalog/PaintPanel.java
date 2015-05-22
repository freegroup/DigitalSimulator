package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog;

import de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.objects.*;
import de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.util.*;

import javax.imageio.ImageIO;
import javax.imageio.ImageWriter;
import javax.imageio.stream.FileImageOutputStream;
import javax.imageio.stream.ImageOutputStream;
import javax.swing.*;
import java.awt.*;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.event.*;
import java.awt.geom.Point2D;
import java.awt.geom.RoundRectangle2D;
import java.awt.image.BufferedImage;
import java.awt.image.WritableRaster;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Properties;

/**
 * The core of the jimgpnt package. This is the do-everything class that everything else is based on
 * This panel is designed to go in a JScrollPane and you should set one using setScrollPane().
 *
 * The panel consists of a background color, an image that has a tranparent chanel (BufferedImage.TYPE_INT_ARGB),
 * some JImagePaintObjects that hover over the image until they are "incorporated", and selected and temporary objects
 *
 * The panel has a notion of the current drawing mode and is sensitive to MouseEvents. It also retains
 * information about various options for createing new JImagePaintObjects.
 *
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class PaintPanel extends JPanel implements MouseListener, MouseMotionListener, MouseWheelListener, KeyListener 
{


   public static final int MODE_LINE = 0;
   public static final int MODE_SCRIBBLE = 1;
   public static final int MODE_RECT = 2;
   public static final int MODE_OVAL = 3;
   public static final int MODE_TEXT = 4;
   public static final int MODE_SELECT = 5;
   public static final int MODE_ERASE = 6;
   public static final int MODE_FLOOD = 7;
   public static final int MODE_POINT = 8;
   public static final int MODE_QUADARROW = 9;
   public static final int MODE_COLORPICK = 10;

   private BufferedImage img;
   private int currentMode;
   private int oldMode;
   private int zoom;

   private Color bgColor;
   private Color drawColor;
   private boolean antialiased;
   private int arcWidth;
   private int arcHeight;
   private boolean filled;
   private Stroke stroke;
   private float alpha;


   private ArrayList paintObjects;
   private ArrayList selectedObjects;
   private ArrayList tempObjects;
   private ArrayList displayObjects;


   private JScrollPane scroll;

   private Point mousePoint;
   private int eraseRad;
   private File currentFile;

   private LocationPanel locationPanel;

   private Point dragDown;

   private Cursor preCursor;

   private JFileChooser saveChooser;

   private Clipboard clip;

   private Properties properties;


   /**
    *
    * @param fileToLoad
    * An File objected representing an image that ImageIO can read. The image is set to the
    * @param properties
    * A properties object in which to create and load properties
    */
   public PaintPanel(File fileToLoad, Properties properties) 
   {
      this.properties = properties;
      this.currentFile = fileToLoad;


      if (fileToLoad != null && fileToLoad.isFile()) 
      {
         try 
         {
            img = ImageIO.read(fileToLoad);
         }
         catch (Exception e) 
         {
            e.printStackTrace();  //To change body of catch statement use Options | File Templates.
         }
      }

      if (img != null) {
         img = BufferedImageTool.copy(img);
      }

      this.init();


   }

   /**
    *
    * @param img
    * A bufferedImage that will
    * @param properties
    * A properties object in which to create and load properties
    */
   public PaintPanel(BufferedImage img, Properties properties) 
   {
      this.properties = properties;
      if (img != null) 
      {
         img = BufferedImageTool.copy(img);
      }

      this.init();
   }

   /**
    * Creates a new image
    * @param properties
    * A properties object in which to create and load properties
    */
   public PaintPanel(Properties properties) 
   {
      this.properties = properties;
      this.init();
   }

   private void init() 
   {
      clip = Toolkit.getDefaultToolkit().getSystemClipboard();
      this.zoom = 1;

      paintObjects = new ArrayList();
      tempObjects = new ArrayList();
      selectedObjects = new ArrayList();
      displayObjects = new ArrayList();

      String width = properties.getProperty("width");
      if (width == null) 
      {
         width = "256";
      }

      String height = properties.getProperty("height");
      if (height == null) 
      {
         height = "256";
      }
      if (img == null) 
      {
         this.setImageSize(Integer.parseInt(width), Integer.parseInt(height), false);
      }
      else 
      {
         properties.setProperty("width", "" + img.getWidth());
         properties.setProperty("height", "" + img.getHeight());
      }

      String bgcolor = properties.getProperty("bgcolor");
      if (bgcolor == null) {
         bgcolor = "" + new Color(255, 255, 175).getRGB();
      }
      this.setBgColor(new Color(Integer.parseInt(bgcolor)));

      String fgcolor = properties.getProperty("drawcolor");
      if (fgcolor == null) {
         fgcolor = "" + Color.black.getRGB();
      }
      this.setDrawColor(new Color(Integer.parseInt(fgcolor)));


      String fontName = properties.getProperty("fontname");
      if (fontName == null) 
      {
         fontName = "Serif";
      }

      String fonttype = properties.getProperty("fonttype");
      if (fonttype == null) 
      {
         fonttype = "1";
      }

      String fontsize = properties.getProperty("fontsize");
      if (fontsize == null) 
      {
         fontsize = "22";
      }
      this.setFont(new Font(fontName, Integer.parseInt(fonttype), Integer.parseInt(fontsize)));

      String filled = properties.getProperty("filled");
      if (filled == null) 
      {
         filled = "fasle";
      }
      this.setFilled(Boolean.valueOf(filled).booleanValue());

      String strokewidth = properties.getProperty("strokewidth");
      if (strokewidth == null) {
         strokewidth = "1.0";
      }
      this.setStroke(new BasicStroke(Float.parseFloat(strokewidth)));

      String alpha = properties.getProperty("alpha");
      if (alpha == null) {
         alpha = "1.0";
      }
      this.setAlpha(Float.parseFloat(alpha));

      String antialiased = properties.getProperty("antialiased");
      if (antialiased == null) {
         antialiased = "1.0";
      }
      this.setAntialiased(Boolean.valueOf(antialiased).booleanValue());

//     properties.setProperty("arcwidth", "0.0");
//      properties.setProperty("archeight","0.0");
//
//      properties.setProperty("eraserad","3");
      String eraserad = properties.getProperty("eraserad");
      if (eraserad == null) {
         eraserad = "3";
      }
      eraseRad = Integer.parseInt(eraserad);

      this.setPreferredSize(new Dimension(img.getWidth() * zoom, img.getHeight() * zoom));


      this.addMouseListener(this);
      this.addMouseMotionListener(this);
      this.addMouseWheelListener(this);
      this.addKeyListener(this);


   }

   private void setImageSize(int width, int height, boolean copyOld) {
      BufferedImage old = img;
      properties.setProperty("width", "" + width);
      properties.setProperty("height", "" + height);
      img = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
      if (old != null && copyOld) {
         Graphics g = img.getGraphics();
         g.drawImage(old, 0, 0, null);
      }


   }

   public LocationPanel getLocationPanel() {
      return locationPanel;
   }

   public void setLocationPanel(LocationPanel panel) {
      this.locationPanel = panel;
   }

   public Color getBgColor() {
      return bgColor;
   }

   public void setBgColor(Color bgColor) {
      this.bgColor = bgColor;
      properties.setProperty("bgcolor", "" + bgColor.getRGB());
   }

   public void createNewFile() {

      this.setImageSize(Integer.parseInt(properties.getProperty("width")), Integer.parseInt(properties.getProperty("height")), false);
      this.zoom = 1;
      this.setPreferredSize(new Dimension(img.getWidth() * zoom, img.getHeight() * zoom));

      paintObjects = new ArrayList();
      tempObjects = new ArrayList();
      selectedObjects = new ArrayList();
      this.updatePanel();

   }

   public void openImageFile() {
      File loadFile = currentFile;
      if (loadFile != null && loadFile.isFile()) {
         loadFile = new File(loadFile.getParent());
      }
      JFileChooser chooser = new JFileChooser(loadFile);
      chooser.addChoosableFileFilter(ImageIOFileFilter.getImageReaderFilter());
      chooser.setAcceptAllFileFilterUsed(false);
      int ret = chooser.showOpenDialog(this);
      if (ret == JFileChooser.APPROVE_OPTION) {
         File file = chooser.getSelectedFile();
         if (file != null) {
            this.currentFile = file;
            try {
               img = ImageIO.read(file);
               if (img != null) {
                  img = BufferedImageTool.copy(img);
                  this.zoom = 1;
                  this.setPreferredSize(new Dimension(img.getWidth() * zoom, img.getHeight() * zoom));
                  paintObjects = new ArrayList();
                  tempObjects = new ArrayList();
                  selectedObjects = new ArrayList();
               }
            }
            catch (Exception e) {
            }
         }
      }
      this.updatePanel();
   }

   public BufferedImage getImage() {
      return img;
   }

   private void updatePanel() {
      if (scroll != null) {
         this.revalidate();
         scroll.repaint();
      }
      else {
         this.repaint();
      }

   }

   public void appendImageFile(int x, int y) {
      File loadFile = currentFile;
      if (loadFile != null && loadFile.isFile()) {
         loadFile = new File(loadFile.getParent());
      }
      JFileChooser chooser = new JFileChooser(loadFile);
      chooser.addChoosableFileFilter(ImageIOFileFilter.getImageReaderFilter());
      chooser.setAcceptAllFileFilterUsed(false);
      int ret = chooser.showOpenDialog(this);
      if (ret == JFileChooser.APPROVE_OPTION) {
         File file = chooser.getSelectedFile();
         if (file != null) {
            this.currentFile = file;
            try {
               BufferedImage nimg = ImageIO.read(file);
               if (nimg != null) {
                  nimg = BufferedImageTool.copy(nimg);
                  img.getGraphics().drawImage(nimg, x, y, null);
               }
            }
            catch (Exception e) {

            }
         }
      }
      this.updatePanel();
   }

   public boolean saveImageFile() {

      if (saveChooser == null) {
         saveChooser = new JFileChooser();
         ArrayList filters = ImageIOFileFilter.getImageWriterFilters();
         ImageIOFileFilter png = null;
         for (int i = 0; i < filters.size(); i++) {
            ImageIOFileFilter filter = (ImageIOFileFilter) filters.get(i);
            if (filter.getPreferredExtString().equalsIgnoreCase("png")) {
               png = filter;
            }
            saveChooser.addChoosableFileFilter(filter);
            saveChooser.setAcceptAllFileFilterUsed(false);

         }
         if (png != null) {
            saveChooser.setFileFilter(png);
         }
      }
      File loadFile = currentFile;
      if (loadFile != null && loadFile.isFile()) {
         loadFile = new File(loadFile.getParent());
      }
      saveChooser.setCurrentDirectory(loadFile);


      int ret = saveChooser.showSaveDialog(this);
      if (ret == JFileChooser.APPROVE_OPTION) {
         File file = saveChooser.getSelectedFile();
         if (file != null && file.getName().length() > 0) {
            ImageIOFileFilter filter = (ImageIOFileFilter) saveChooser.getFileFilter();
            ImageWriter writer = filter.getImageWriter();
            if (!file.getPath().endsWith("." + filter.getPreferredExtString())) {
               file = new File(file.getPath() + "." + filter.getPreferredExtString());
            }
            this.currentFile = file;
            for (Iterator iterator = selectedObjects.iterator(); iterator.hasNext();) {
               PaintObject paintObject = (PaintObject) iterator.next();
               paintObject.setSelected(false);
            }
            selectedObjects.clear();
            BufferedImage save = new BufferedImage(img.getWidth(), img.getHeight(), filter.getBiType());
            Graphics2D g = (Graphics2D) save.getGraphics();
            if (!filter.isSupportsAlpha()) {
               g.setColor(this.bgColor);
               g.fillRect(0, 0, img.getWidth(), img.getHeight());
            }
            g.drawImage(img, 0, 0, null);

            g.drawImage(this.getObjectsImage(paintObjects), 0, 0, null);
            if (file.exists()) {
               int retOK = JOptionPane.showConfirmDialog(this, "File " + file.getName() + " exists. Do you want to overwrite?");
               if (retOK == JOptionPane.OK_OPTION) {
                  try {
                     ImageOutputStream stream = new FileImageOutputStream(file);
                     writer.setOutput(stream);
                     writer.write(save);
                     stream.close();

                     this.updatePanel();
                     return true;
                  }
                  catch (IOException e) {
                     e.printStackTrace();
                     this.updatePanel();
                     return false;

                  }
               }
               else {
                  this.updatePanel();
                  return false;

               }
            }
            else {
               try {
                  ImageOutputStream stream = new FileImageOutputStream(file);
                  writer.setOutput(stream);
                  writer.write(save);
                  stream.close();
                  this.updatePanel();
                  return true;
               }
               catch (IOException e) {

                  e.printStackTrace();
                  this.updatePanel();
                  return false;
               }
            }

         }
      }
      else {
         return false;
      }
      return false;
   }

   public float getAlpha() {
      return alpha;
   }

   public void setAlpha(float alpha) {
      this.alpha = alpha;
      properties.setProperty("alpha", "" + alpha);
      if (selectedObjects != null) {
         for (Iterator iterator = selectedObjects.iterator(); iterator.hasNext();) {
            PaintObject paintObject = (PaintObject) iterator.next();
            paintObject.setAlpha(this.alpha);

         }
         this.updatePanel();
      }
   }

   public Stroke getStroke() {
      return stroke;
   }

   public void setStroke(Stroke stroke) {
      this.stroke = stroke;
      properties.setProperty("stroke", "" + ((BasicStroke) stroke).getLineWidth());
      if (selectedObjects != null) {
         for (Iterator iterator = selectedObjects.iterator(); iterator.hasNext();) {
            PaintObject paintObject = (PaintObject) iterator.next();
            if (paintObject instanceof RectObject) {
               ((RectObject) paintObject).setStroke(stroke);
            }
            if (paintObject instanceof OvalObject) {
               ((OvalObject) paintObject).setStroke(stroke);
            }
            if (paintObject instanceof ScribbleObject) {
               ((ScribbleObject) paintObject).setStroke(stroke);
            }
            if (paintObject instanceof LineObject) {
               ((LineObject) paintObject).setStroke(stroke);
            }
            if (paintObject instanceof QuadArrowObject) {
               ((QuadArrowObject) paintObject).setStroke(stroke);
            }

         }
         this.updatePanel();
      }
   }

   public void setFont(Font font) {
      super.setFont(font);
      if (properties != null) {
         properties.setProperty("fontname", font.getName());
         properties.setProperty("fonttype", "" + font.getStyle());
         properties.setProperty("fontsize", "" + font.getSize());
      }

      if (selectedObjects != null) {
         for (Iterator iterator = selectedObjects.iterator(); iterator.hasNext();) {
            PaintObject paintObject = (PaintObject) iterator.next();
            if (paintObject instanceof TextObject) {
               ((TextObject) paintObject).setFont(font);
            }

         }
         this.updatePanel();
      }

   }


   public int getCurrentMode() {
      return currentMode;
   }

   public void setCurrentMode(int currentmode) {
      oldMode = currentMode;
      this.currentMode = currentmode;
      this.firePropertyChange("mode", new Integer(oldMode), new Integer(currentMode));
      for (Iterator iterator = selectedObjects.iterator(); iterator.hasNext();) {
         PaintObject paintObject = (PaintObject) iterator.next();
         if (paintObject instanceof TextObject) {
            if (((TextObject) paintObject).getText().trim().length() > 0) {
               paintObjects.add(paintObject);
            }

         }
         else {
            paintObjects.add(paintObject);
         }
      }
      selectedObjects = new ArrayList();
      if (currentMode == PaintPanel.MODE_LINE ||
          currentMode == PaintPanel.MODE_OVAL ||
          currentMode == PaintPanel.MODE_RECT ||
          currentmode == PaintPanel.MODE_SCRIBBLE ||
          currentmode == PaintPanel.MODE_FLOOD ||
          currentmode == PaintPanel.MODE_COLORPICK) {
         this.setCursor(new Cursor(Cursor.CROSSHAIR_CURSOR));
      }
      else if (currentMode == PaintPanel.MODE_TEXT) {
         this.setCursor(new Cursor(Cursor.TEXT_CURSOR));

      }
      else if (currentMode == PaintPanel.MODE_SELECT ||
          currentMode == PaintPanel.MODE_QUADARROW) {
         this.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
      }
      else if (currentMode == PaintPanel.MODE_ERASE ||
          currentMode == PaintPanel.MODE_POINT) {
         this.setCursor(new Cursor(Cursor.CROSSHAIR_CURSOR));

      }

      this.updatePanel();
   }

   public JScrollPane getScroll() {
      return scroll;
   }

   public void setScroll(JScrollPane scroll) {
      this.scroll = scroll;
      scroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
      scroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);


   }

   public boolean isAntialiased() {
      return antialiased;
   }

   public void setAntialiased(boolean antialiased) {
      this.antialiased = antialiased;
      properties.setProperty("antialiased", "" + antialiased);
      for (Iterator iterator = selectedObjects.iterator(); iterator.hasNext();) {
         PaintObject paintObject = (PaintObject) iterator.next();
         paintObject.setAntialiased(antialiased);
      }
      this.updatePanel();
   }

   public Color getDrawColor() {
      return drawColor;
   }

   public int getArcWidth() {
      return arcWidth;
   }

   public void setArcWidth(int arcWidth) {
      this.arcWidth = arcWidth;
      for (Iterator iterator = selectedObjects.iterator(); iterator.hasNext();) {
         PaintObject paintObject = (PaintObject) iterator.next();
         if (paintObject instanceof RectObject) {
            ((RectObject) paintObject).setArcWidth(arcWidth);
         }

      }
      this.updatePanel();
   }

   public int getArcHeight() {
      return arcHeight;

   }

   public void setArcHeight(int arcHeight) {
      this.arcHeight = arcHeight;
      for (Iterator iterator = selectedObjects.iterator(); iterator.hasNext();) {
         PaintObject paintObject = (PaintObject) iterator.next();
         if (paintObject instanceof RectObject) {
            ((RectObject) paintObject).setArcHeight(arcHeight);
         }

      }
      this.updatePanel();
   }

   public void setDrawColor(Color drawColor) {
      this.drawColor = drawColor;
      properties.setProperty("drawcolor", "" + drawColor.getRGB());
      for (Iterator iterator = selectedObjects.iterator(); iterator.hasNext();) {
         PaintObject paintObject = (PaintObject) iterator.next();
         paintObject.setColor(drawColor);
      }
      this.updatePanel();
   }

   public void imageChanged() {
      this.setPreferredSize(new Dimension(img.getWidth(), img.getHeight()));
      this.zoom = 1;
      paintObjects = new ArrayList();
   }


   public void paintComponent(Graphics g) {
      super.paintComponent(g);

      Graphics2D g2 = (Graphics2D) g;


      //zoomed bits

      g2.scale((double) zoom, (double) zoom);
      g2.setColor(bgColor);
      g2.fillRect(0, 0, img.getWidth(), img.getHeight());



      //unzoomded bits

      g2.drawImage(img, 0, 0, null);

      if (currentMode == PaintPanel.MODE_ERASE && mousePoint != null) {
         g2.setColor(Color.red);
         Composite old = g2.getComposite();
         g2.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 0.7f));
         g2.fillRect(mousePoint.x - (eraseRad - 1) / 2, mousePoint.y - (eraseRad - 1) / 2, eraseRad, eraseRad);
         g2.setComposite(old);
      }

      if (currentMode == PaintPanel.MODE_POINT && mousePoint != null) {
         g2.setColor(this.getDrawColor());
         g2.fillRect(mousePoint.x - (eraseRad - 1) / 2, mousePoint.y - (eraseRad - 1) / 2, eraseRad, eraseRad);
      }

      if (zoom >= 5) {
         g2.scale(1.0 / (double) zoom, 1.0 / (double) zoom);
         for (int x = 0; x < img.getWidth() * zoom; x += zoom) {
            g2.setColor(Color.lightGray);
            g2.drawLine(x, 0, x, img.getHeight() * zoom);
         }
         for (int y = 0; y < img.getHeight() * zoom; y += zoom) {
            g2.setColor(Color.lightGray);
            g2.drawLine(0, y, img.getWidth() * zoom, y);
         }
         g2.scale(zoom, zoom);
      }

      //displayObjects

      for (int i = 0; i < displayObjects.size(); i++) {
         PaintObject paintObject = (PaintObject) displayObjects.get(i);
         paintObject.addToGraphics(g2);
      }

      //paint objects
      g2.drawImage(getObjectsImage(paintObjects), 0, 0, null);

      g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
      //paint highlight points for those objects selected
      if (currentMode == PaintPanel.MODE_SELECT) {
         for (int o = 0; o < selectedObjects.size(); o++) {
            g2.setColor(Color.magenta);
            PaintObject paintObject = (PaintObject) selectedObjects.get(o);
            Point2D[] points = paintObject.getHighlightPoints();
            for (int i = 0; i < points.length; i++) {
               Point2D point = points[i];
               g2.translate(paintObject.getTranslation()[0], paintObject.getTranslation()[1]);
               g2.setStroke(new BasicStroke((float) (1.0 / zoom)));
               RoundRectangle2D.Double rect = new RoundRectangle2D.Double((point.getX() - 2), (point.getY() - 2), 5, 5, 2, 2);
               g2.draw(rect);
               g2.translate(-paintObject.getTranslation()[0], -paintObject.getTranslation()[1]);
            }


         }

      }

      //paint temp objects &  hightliged points
      for (int t = 0; t < tempObjects.size(); t++) {
         PaintObject tempObject = (PaintObject) tempObjects.get(t);
         g2.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER, 0.5f));
         tempObject.addToGraphics(g2);
         if (tempObject.isSelected() && currentMode == PaintPanel.MODE_SELECT) {
            Point2D[] points = tempObject.getHighlightPoints();
            for (int i = 0; i < points.length; i++) {
               Point2D point = points[i];
               g2.setColor(Color.magenta);
               g2.translate(tempObject.getTranslation()[0], tempObject.getTranslation()[1]);

               g2.setStroke(new BasicStroke((float) (1.0 / zoom)));
               RoundRectangle2D.Double rect = new RoundRectangle2D.Double((point.getX() - 2), (point.getY() - 2), 5, 5, 2, 2);
               g2.draw(rect);
               int index = tempObject.getCurrentPointIndex();
               if (index == i) {

                  g2.fill(rect);

               }

               g2.translate(-tempObject.getTranslation()[0], -tempObject.getTranslation()[1]);
            }
         }
      }


   }

   public boolean isFilled() {
      return filled;
   }

   public void setFilled(boolean filled) {
      this.filled = filled;
      properties.setProperty("filled", "" + filled);
      if (selectedObjects != null) {
         for (Iterator iterator = selectedObjects.iterator(); iterator.hasNext();) {
            PaintObject paintObject = (PaintObject) iterator.next();
            if (paintObject instanceof RectObject) {
               ((RectObject) paintObject).setFilled(filled);
            }
            if (paintObject instanceof OvalObject) {
               ((OvalObject) paintObject).setFilled(filled);
            }
            if (paintObject instanceof QuadArrowObject) {
               ((QuadArrowObject) paintObject).setFilled(filled);
            }

            if (paintObject instanceof ScribbleObject) {
               ((ScribbleObject) paintObject).setFilled(filled);
            }

         }
         this.updatePanel();
      }
   }

   public ArrayList getPaintObjects() {
      return paintObjects;
   }

   public BufferedImage getObjectsImage(ArrayList list) {
      BufferedImage temp = new BufferedImage(img.getWidth(), img.getHeight(), BufferedImage.TYPE_INT_ARGB);
      Graphics2D g2 = (Graphics2D) temp.getGraphics();


      for (Iterator iterator = list.iterator(); iterator.hasNext();) {
         PaintObject paintObject = (PaintObject) iterator.next();
         paintObject.addToGraphics(g2);
      }

      return temp;
   }

   public ArrayList getDisplayObjects() {
      return displayObjects;
   }


   public void setDisplayObjects(ArrayList displayObjects) {
      this.displayObjects = displayObjects;
   }

   private void flood(Point initPoint, int rgb, int newRGB) {
      ArrayList queue = new ArrayList();
      boolean[][] seen = new boolean[img.getWidth()][img.getHeight()];

      queue.add(initPoint);
      while (queue.size() > 0) {
         Point p = (Point) queue.remove(0);
         int i = p.x;
         int j = p.y;
         if (seen[i][j]) {
            continue;
         }
         seen[i][j] = true;

         if (img.getRGB(i, j) == rgb) {
            img.setRGB(i, j, newRGB);
            img.getRaster().setSample(i, j, 3, 255);

            if (i > 0 && !seen[i - 1][j]) {
               queue.add(new Point(i - 1, j));
            }
            if (i < img.getWidth() - 1 && !seen[i + 1][j]) {
               queue.add(new Point(i + 1, j));
            }
            if (j > 0 && !seen[i][j - 1]) {
               queue.add(new Point(i, j - 1));
            }
            if (j < img.getHeight() - 1 && !seen[i][j + 1]) {
               queue.add(new Point(i, j + 1));
            }
         }
      }
   }

   public void copyImageToClipboard() {

      BufferedImage img = this.getImage();
      BufferedImage save = new BufferedImage(img.getWidth(), img.getHeight(), BufferedImage.TYPE_INT_ARGB);
      Graphics2D g = (Graphics2D) save.getGraphics();
      g.drawImage(img, 0, 0, null);
      g.drawImage(this.getObjectsImage(paintObjects), 0, 0, null);

      TransferableImage trans = new TransferableImage(save);

      clip.setContents(trans, null);
   }

   public void copyImageToClipboardwBG() {

      BufferedImage img = this.getImage();
      BufferedImage save = new BufferedImage(img.getWidth(), img.getHeight(), BufferedImage.TYPE_INT_ARGB);
      Graphics2D g = (Graphics2D) save.getGraphics();
      g.setColor(this.getBackground());
      g.fillRect(0, 0, save.getWidth(), save.getHeight());
      g.drawImage(img, 0, 0, null);
      g.drawImage(this.getObjectsImage(paintObjects), 0, 0, null);

      TransferableImage trans = new TransferableImage(save);

      clip.setContents(trans, null);
   }

   public void pasteImageFromClipboard(Point2D clickPoint) {
      if (clip != null) {
         Transferable trans = clip.getContents(this);
         if (trans != null && trans.isDataFlavorSupported(DataFlavor.imageFlavor)) {

            try {
               Image clipImage = (Image) trans.getTransferData(DataFlavor.imageFlavor);

               paintObjects.add(new ImageObject(clipImage, clickPoint, alpha));
               this.repaint();
            }
            catch (UnsupportedFlavorException e1) {
               e1.printStackTrace();
            }
            catch (IOException e1) {
               e1.printStackTrace();
            }
         }
      }
   }

   public void mouseClicked(MouseEvent e) {


      if (currentMode == PaintPanel.MODE_SELECT && e.getButton() == MouseEvent.BUTTON1) {
         boolean ctrl = (e.getModifiers() & MouseEvent.CTRL_MASK) == MouseEvent.CTRL_MASK;
         if (!ctrl) {
            selectedObjects = new ArrayList();
         }
         PaintObject closest = null;

         double closestDist = Double.MAX_VALUE;

         for (Iterator iterator = paintObjects.iterator(); iterator.hasNext();) {
            PaintObject paintObject = (PaintObject) iterator.next();
            if (!ctrl) {
               paintObject.setSelected(false);
            }

            Point2D[] points = paintObject.getHighlightPoints();
            for (int i = 0; i < points.length; i++) {
               Point2D point = points[i];
               double dist = point.distance(new Point2D.Double(e.getPoint().getX() / zoom, e.getPoint().getY() / zoom));
               if (dist < closestDist) {
                  closest = paintObject;
                  closestDist = dist;
               }
            }
         }
         if (closest != null) {
            if (closest.isSelected()) {
               closest.setSelected(false);
               selectedObjects.remove(closest);

            }
            else {
               closest.setSelected(true);

               selectedObjects.add(closest);
               this.firePropertyChange("selection", null, selectedObjects);
            }

         }


      }
      else if (currentMode == PaintPanel.MODE_COLORPICK) {
         Color color = new Color(img.getRGB(e.getPoint().x / zoom, e.getPoint().y / zoom));

         this.firePropertyChange("pickcolor", this.drawColor, color);
         this.setDrawColor(color);
         this.setCurrentMode(oldMode);

      }
      this.updatePanel();
   }

   public void mousePressed(MouseEvent e) {
      this.requestFocus();
      if ((e.getModifiersEx() & MouseEvent.BUTTON3_DOWN_MASK) == MouseEvent.BUTTON3_DOWN_MASK) {
         dragDown = e.getPoint();
         this.preCursor = this.getCursor();
         this.setCursor(new Cursor(Cursor.HAND_CURSOR));
      }
      else if ((e.getModifiersEx() & MouseEvent.BUTTON1_DOWN_MASK) == MouseEvent.BUTTON1_DOWN_MASK) {
         if (currentMode == PaintPanel.MODE_FLOOD) {
            int rgb = img.getRGB(e.getPoint().x / zoom, e.getPoint().y / zoom);

            this.flood(new Point(e.getPoint().x / zoom, e.getPoint().y / zoom), rgb, this.getDrawColor().getRGB());
            this.updatePanel();
         }
         else if (currentMode == PaintPanel.MODE_OVAL) {
            tempObjects.add(new OvalObject(this.drawColor, new Point(e.getPoint().x / zoom, e.getPoint().y / zoom), this.getStroke(), antialiased, filled, alpha));
         }
         else if (currentMode == PaintPanel.MODE_RECT) {
            tempObjects.add(new RectObject(this.drawColor, new Point(e.getPoint().x / zoom, e.getPoint().y / zoom), this.getStroke(), antialiased, filled, arcWidth, arcHeight, alpha));
         }
         else if (currentMode == PaintPanel.MODE_LINE) {
            tempObjects.add(new LineObject(this.drawColor, new Point(e.getPoint().x / zoom, e.getPoint().y / zoom), this.getStroke(), antialiased, alpha));
         }

         else if (currentMode == PaintPanel.MODE_QUADARROW) {
            tempObjects.add(new QuadArrowObject(this.drawColor, new Point(e.getPoint().x / zoom, e.getPoint().y / zoom), this.getStroke(), antialiased, filled, alpha));
         }
         else if (currentMode == PaintPanel.MODE_SCRIBBLE) {
            tempObjects.add(new ScribbleObject(this.drawColor, new Point(e.getPoint().x / zoom, e.getPoint().y / zoom), this.getStroke(), antialiased, filled, alpha));
         }
         else if (currentMode == PaintPanel.MODE_TEXT) {

            TextObject text = new TextObject(this.getFont(), this.drawColor, new Point(e.getPoint().x / zoom, e.getPoint().y / zoom), " ", antialiased);
            text.setPanel(this);
            tempObjects.add(text);
            this.setCurrentMode(PaintPanel.MODE_SELECT);
            selectedObjects.add(text);

         }

         else if (currentMode == PaintPanel.MODE_SELECT) {
            double closestDist = Double.MAX_VALUE;
            if (selectedObjects.size() == 1) {
               PaintObject selectedObject = (PaintObject) selectedObjects.get(0);
               selectedObject.setCurrentPointIndex(-1);
               Point2D[] points = selectedObject.getHighlightPoints();
               for (int i = 0; i < points.length; i++) {
                  Point2D point = points[i];
                  double dist = point.distance(new Point2D.Double(e.getPoint().getX() / zoom, e.getPoint().getY() / zoom));
                  if (dist < closestDist) {
                     selectedObject.setCurrentPointIndex(i);
                     closestDist = dist;
                  }
               }
               if (closestDist < 5.0) {

                  paintObjects.remove(selectedObject);
                  tempObjects.add(selectedObject);
               }
               else {
                  selectedObject.setCurrentPointIndex(-1);
               }

            }
            else {

               for (Iterator iterator = selectedObjects.iterator(); iterator.hasNext();) {
                  PaintObject paintObject = (PaintObject) iterator.next();
                  paintObject.setCurrentPointIndex(-1);
                  Point2D[] points = paintObject.getHighlightPoints();
                  for (int i = 0; i < points.length; i++) {
                     Point2D point = points[i];
                     double dist = point.distance(new Point2D.Double(e.getPoint().getX() / zoom, e.getPoint().getY() / zoom));
                     if (dist < closestDist) {
                        closestDist = dist;
                     }
                  }
               }

               if (closestDist < 5.0) {
                  for (Iterator iterator = selectedObjects.iterator(); iterator.hasNext();) {
                     PaintObject paintObject = (PaintObject) iterator.next();

                     paintObject.setCurrentPointIndex(0);
                     paintObjects.remove(paintObject);
                     tempObjects.add(paintObject);
                  }
               }

            }


         }
         else if (currentMode == PaintPanel.MODE_ERASE) {
            Point loc = new Point(e.getPoint().x / zoom, e.getPoint().y / zoom);
            int startX = loc.x - (eraseRad - 1) / 2;
            int startY = loc.y - (eraseRad - 1) / 2;
            int endX = loc.x + (eraseRad - 1) / 2;
            int endY = loc.y + (eraseRad - 1) / 2;
            if (startX < 0) {
               startX = 0;
            }
            if (startY < 0) {
               startY = 0;
            }
            if (endX > img.getWidth() - 1) {
               endX = img.getWidth() - 1;
            }
            if (endY > img.getHeight() - 1) {
               endY = img.getHeight() - 1;
            }

            WritableRaster raster = img.getRaster();
            for (int x = startX; x <= endX; x++) {
               for (int y = startY; y <= endY; y++) {
                  raster.setSample(x, y, 3, 0);
               }
            }
         }
         else if (currentMode == PaintPanel.MODE_POINT) {
            Point loc = new Point(e.getPoint().x / zoom, e.getPoint().y / zoom);
            int startX = loc.x - (eraseRad - 1) / 2;
            int startY = loc.y - (eraseRad - 1) / 2;
            int endX = loc.x + (eraseRad - 1) / 2;
            int endY = loc.y + (eraseRad - 1) / 2;
            if (startX < 0) {
               startX = 0;
            }
            if (startY < 0) {
               startY = 0;
            }
            if (endX > img.getWidth() - 1) {
               endX = img.getWidth() - 1;
            }
            if (endY > img.getHeight() - 1) {
               endY = img.getHeight() - 1;
            }

            WritableRaster raster = img.getRaster();
            for (int x = startX; x <= endX; x++) {
               for (int y = startY; y <= endY; y++) {

                  img.setRGB(x, y, this.getDrawColor().getRGB());
                  raster.setSample(x, y, 3, (int)(255 * this.getAlpha()));

               }
            }
         }
      }

      this.updatePanel();
   }

   public void mouseReleased(MouseEvent e) {

      if (currentMode == PaintPanel.MODE_ERASE || currentMode == PaintPanel.MODE_POINT) {
         mousePoint = new Point(e.getX() / zoom, e.getY() / zoom);

      }

      if (preCursor != null) {
         this.setCursor(preCursor);
         preCursor = null;
      }
      dragDown = null;


      for (Iterator iterator = tempObjects.iterator(); iterator.hasNext();) {
         PaintObject tempObject = (PaintObject) iterator.next();

         if (tempObject.finished(new Point(e.getPoint().x / zoom, e.getPoint().y / zoom))) {
            paintObjects.add(tempObject);
         }
         tempObject.setStartDragLoc(null);
         tempObject.setCurrentPointIndex(-1);
      }

      for (Iterator iterator = selectedObjects.iterator(); iterator.hasNext();) {
         PaintObject selObject = (PaintObject) iterator.next();
         selObject.setCurrentPointIndex(-1);
      }

      tempObjects = new ArrayList();


      this.updatePanel();
   }

   public void mouseEntered(MouseEvent e) {
      if (locationPanel != null) {
         int x = e.getX() / zoom;
         int y = e.getY() / zoom;
         if (x >= 0 && x < img.getWidth() && y >= 0 && y < img.getHeight()) {
            locationPanel.updateLocation(new Point(x, y));
         }
         else {
            locationPanel.updateLocation(null);
         }

         locationPanel.repaint();
      }
      if (currentMode == PaintPanel.MODE_ERASE || currentMode == PaintPanel.MODE_POINT) {
         mousePoint = new Point(e.getX() / zoom, e.getY() / zoom);
         this.updatePanel();
      }

   }


   public void mouseExited(MouseEvent e) {
      if (locationPanel != null) {
         locationPanel.updateLocation(null);
         locationPanel.repaint();
      }
      if (currentMode == PaintPanel.MODE_ERASE || currentMode == PaintPanel.MODE_POINT) {
         mousePoint = null;
         this.repaint();
      }
   }

   public void mouseDragged(MouseEvent e) {

      if ((e.getModifiersEx() & MouseEvent.BUTTON3_DOWN_MASK) == MouseEvent.BUTTON3_DOWN_MASK) {
         if (scroll != null) {
            Point current = e.getPoint();
            int xMove = current.x - dragDown.x;
            int yMove = current.y - dragDown.y;

            Point origin = scroll.getViewport().getViewPosition();
            int newX = origin.x - xMove;
            int newY = origin.y - yMove;
            int xMax = this.getWidth() - scroll.getViewport().getWidth();
            int yMax = this.getHeight() - scroll.getViewport().getHeight();
            if (newX < 0) {
               newX = 0;
            }
            if (newY < 0) {
               newY = 0;
            }
            if (newX > xMax) {
               newX = xMax;
            }
            if (newY > yMax) {
               newY = yMax;
            }
            scroll.getViewport().setViewPosition(new Point(newX, newY));


         }

      }
      else if ((e.getModifiersEx() & MouseEvent.BUTTON1_DOWN_MASK) == MouseEvent.BUTTON1_DOWN_MASK) {

         if (locationPanel != null) {
            int x = e.getX() / zoom;
            int y = e.getY() / zoom;
            if (x >= 0 && x < img.getWidth() && y >= 0 && y < img.getHeight()) {
               locationPanel.updateLocation(new Point(x, y));
            }
            else {
               locationPanel.updateLocation(null);
            }

            locationPanel.repaint();
         }
         if (currentMode == PaintPanel.MODE_ERASE) {
            mousePoint = null;
            Point loc = new Point(e.getPoint().x / zoom, e.getPoint().y / zoom);
            int startX = loc.x - (eraseRad - 1) / 2;
            int startY = loc.y - (eraseRad - 1) / 2;
            int endX = loc.x + (eraseRad - 1) / 2;
            int endY = loc.y + (eraseRad - 1) / 2;
            if (startX < 0) {
               startX = 0;
            }
            if (startY < 0) {
               startY = 0;
            }
            if (endX > img.getWidth() - 1) {
               endX = img.getWidth() - 1;
            }
            if (endY > img.getHeight() - 1) {
               endY = img.getHeight() - 1;
            }
            WritableRaster raster = img.getRaster();
            for (int x = startX; x <= endX; x++) {
               for (int y = startY; y <= endY; y++) {
                  //          img.setRGB(x,y,bgColor.getRGB());
                  raster.setSample(x, y, 3, 0);
               }
            }
         }
         else if (currentMode == PaintPanel.MODE_POINT) {
            Point loc = new Point(e.getPoint().x / zoom, e.getPoint().y / zoom);
            int startX = loc.x - (eraseRad - 1) / 2;
            int startY = loc.y - (eraseRad - 1) / 2;
            int endX = loc.x + (eraseRad - 1) / 2;
            int endY = loc.y + (eraseRad - 1) / 2;
            if (startX < 0) {
               startX = 0;
            }
            if (startY < 0) {
               startY = 0;
            }
            if (endX > img.getWidth() - 1) {
               endX = img.getWidth() - 1;
            }
            if (endY > img.getHeight() - 1) {
               endY = img.getHeight() - 1;
            }

            WritableRaster raster = img.getRaster();
            for (int x = startX; x <= endX; x++) {
               for (int y = startY; y <= endY; y++) {

                  img.setRGB(x, y, this.getDrawColor().getRGB());
                  raster.setSample(x, y, 3, (int)(255 * this.getAlpha()));
               }
            }
         }
         else {
            for (Iterator iterator = tempObjects.iterator(); iterator.hasNext();) {
               int x = e.getX();
               int y = e.getY();
               if (x < 0) {
                  x = 0;
               }
               if (y < 0) {
                  y = 0;
               }
               if (x > this.getPreferredSize().width) {
                  x = this.getPreferredSize().width;
               }
               if (y > this.getPreferredSize().height) {
                  y = this.getPreferredSize().height;
               }
               PaintObject tempObject = (PaintObject) iterator.next();
               if (tempObject.getStartDragLoc() == null) {
                  tempObject.setStartDragLoc(new Point(x / zoom, y / zoom));
               }

               tempObject.updateLocation(new Point(x / zoom, y / zoom));

            }
         }
      }


      this.updatePanel();
   }

   public void mouseMoved(MouseEvent e) {
      if (locationPanel != null) {
         int x = e.getX() / zoom;
         int y = e.getY() / zoom;
         if (x >= 0 && x < img.getWidth() && y >= 0 && y < img.getHeight()) {
            locationPanel.updateLocation(new Point(x, y));
         }
         else {
            locationPanel.updateLocation(null);
         }
         locationPanel.repaint();
      }
      if (currentMode == PaintPanel.MODE_ERASE || currentMode == PaintPanel.MODE_POINT) {
         mousePoint = new Point(e.getX() / zoom, e.getY() / zoom);
         this.updatePanel();
      }

   }

   public void mouseWheelMoved(MouseWheelEvent e) {

      if (currentMode == PaintPanel.MODE_ERASE || currentMode == PaintPanel.MODE_POINT) {
         mousePoint = new Point(e.getX() / zoom, e.getY() / zoom);

      }
      boolean ctrl = (e.getModifiers() & MouseEvent.CTRL_MASK) == MouseEvent.CTRL_MASK;
      if (currentMode == PaintPanel.MODE_ERASE && ctrl || currentMode == PaintPanel.MODE_POINT && ctrl) {
         if (e.getWheelRotation() > 0) {
            eraseRad -= 2;
            if (eraseRad < 1) {
               eraseRad = 1;
            }
         }
         if (e.getWheelRotation() < 0) {
            eraseRad += 2;
         }
         this.updatePanel();
      }
      else {
         if (e.getWheelRotation() > 0) {
            zoom--;
            if (zoom < 1) {
               zoom = 1;
            }
         }
         if (e.getWheelRotation() < 0) {
            zoom++;
         }
         this.zoomed(e.getPoint());
      }


   }

   public void zoomed(Point center) {
      Dimension newSize = new Dimension(img.getWidth() * zoom, img.getHeight() * zoom);


      if (scroll != null) {
         Dimension currentSize = this.getPreferredSize();
         double ratio = (double) newSize.getHeight() / (double) currentSize.getHeight();

         Point currentLoc = scroll.getViewport().getViewPosition();

         Dimension viewSize = scroll.getViewport().getExtentSize();
         int xOff = center.x - currentLoc.x;

         int yOff = center.y - currentLoc.y;

         Point newCent = new Point((int) (center.x * ratio), (int) (center.y * ratio));

         int newXLoc = newCent.x - xOff;
         int newYLoc = newCent.y - yOff;
         if (newXLoc > newSize.getWidth() - viewSize.getWidth()) {
            newXLoc = (int) newSize.getWidth() - (int) viewSize.getWidth();

         }
         if (newXLoc < 0) {
            newXLoc = 0;
         }
         if (newYLoc > newSize.getHeight() - viewSize.getHeight()) {
            newYLoc = (int) newSize.getHeight() - (int) viewSize.getHeight();

         }
         if (newYLoc < 0) {
            newYLoc = 0;
         }
         Point newLoc = new Point(newXLoc, newYLoc);


         this.setPreferredSize(newSize);
         this.revalidate();
         scroll.getViewport().setViewPosition(newLoc);


         if (locationPanel != null) {
            int x = (int) (center.getX() / zoom);
            int y = (int) (center.getY() / zoom);
            if (x >= 0 && x < img.getWidth() && y >= 0 && y < img.getHeight()) {
               locationPanel.updateLocation(new Point(x, y));
            }
            else {
               locationPanel.updateLocation(null);
            }
            locationPanel.repaint();
         }


      }
      else {
         this.setPreferredSize(newSize);
         this.revalidate();
         this.updatePanel();
      }

   }


   public void deleteSelected() {
      ArrayList toDelete = new ArrayList();
      for (Iterator iterator = selectedObjects.iterator(); iterator.hasNext();) {
         PaintObject paintObject = (PaintObject) iterator.next();
         toDelete.add(paintObject);

      }
      for (Iterator iterator = toDelete.iterator(); iterator.hasNext();) {
         PaintObject object = (PaintObject) iterator.next();
         paintObjects.remove(object);
         selectedObjects.remove(object);

      }
      this.updatePanel();
   }

   public void copySelected() {
      ArrayList toCopy = new ArrayList();
      for (Iterator iterator = selectedObjects.iterator(); iterator.hasNext();) {
         PaintObject paintObject = (PaintObject) iterator.next();
         PaintObject copy = paintObject.createCopy(20, 20);
         toCopy.add(copy);
      }

      for (Iterator iterator = toCopy.iterator(); iterator.hasNext();) {
         PaintObject object = (PaintObject) iterator.next();
         paintObjects.add(object);
         selectedObjects.add(object);
      }
      this.updatePanel();
   }

   public void selectAll() {
      this.setCurrentMode(PaintPanel.MODE_SELECT);
      for (Iterator iterator = paintObjects.iterator(); iterator.hasNext();) {
         PaintObject paintObject = (PaintObject) iterator.next();
         paintObject.setSelected(true);
         selectedObjects.add(paintObject);
         this.firePropertyChange("selection", null, selectedObjects);
      }
      this.updatePanel();
   }

   public void incorporateSelected() {
      ArrayList toInc = new ArrayList();

      for (Iterator iterator = selectedObjects.iterator(); iterator.hasNext();) {
         PaintObject paintObject = (PaintObject) iterator.next();
         paintObject.setSelected(false);
         toInc.add(paintObject);
      }

      Graphics2D g = (Graphics2D) img.getGraphics();
      g.drawImage(this.getObjectsImage(selectedObjects), 0, 0, null);

      for (Iterator iterator = toInc.iterator(); iterator.hasNext();) {
         PaintObject object = (PaintObject) iterator.next();
         paintObjects.remove(object);
         selectedObjects.remove(object);
      }
      this.updatePanel();
   }


   public void keyTyped(KeyEvent e) {

   }

   /**
    * route the key pressed event to all selected objects
    * 
    */
   public void keyPressed(KeyEvent e) 
   {
      for (int i = 0; i < selectedObjects.size(); i++) 
      {
         PaintObject paintObject = (PaintObject) selectedObjects.get(i);
         paintObject.keyPressed(e);
      }
      this.updatePanel();
   }

   public void keyReleased(KeyEvent e) 
   {

   }

   public void textFinished(TextObject textObject) {
      if (textObject.getText().trim().length() <= 0) {
         paintObjects.remove(textObject);
      }
      selectedObjects.remove(textObject);
      textObject.setSelected(false);
   }


}
