package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.util;


import javax.imageio.ImageWriter;
import javax.imageio.spi.IIORegistry;
import javax.imageio.spi.ImageReaderSpi;
import javax.imageio.spi.ImageWriterSpi;
import javax.swing.filechooser.FileFilter;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

/**
 * A FileFilter that is based on an ArrayList of file extension strings related to ImageIO. There are a few static
 * methods here for creating FileFilters based on what ImageIO will read or write. In some cases the
 * ImageIOFileFilter will be passes an ImageWriteSpi so you can get it later to use the correct writer
 * for the file type specified by the FileFilter.
 *
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class ImageIOFileFilter extends FileFilter {
   private String description;
   private ArrayList fileExtStrings;
   private ImageWriterSpi spi;
   private int biType;
   private boolean supportsAlpha;

   public ImageIOFileFilter(String description, ArrayList fileExtStrings, ImageWriterSpi spi) {
      this.description = description;
      this.fileExtStrings = fileExtStrings;
      this.spi = spi;
   }

   public boolean accept(File pathname) {
      if (pathname.exists() && pathname.isDirectory()) {
         return true;
      }
      for (int i = 0; i < fileExtStrings.size(); i++) {
         String ext = (String) fileExtStrings.get(i);
         if (pathname.exists() && pathname.isFile()) {
            String name = pathname.getName();
            String anExt = name.substring(name.indexOf(".") + 1);
            if (anExt.equalsIgnoreCase(ext)) {
               return true;
            }
         }
      }
      return false;
   }

   public ArrayList getFileExtStrings() {
      return fileExtStrings;
   }

   public String getPreferredExtString() {
      if (fileExtStrings.size() > 0) {
         return (String) fileExtStrings.get(0);
      }
      else {
         return null;
      }

   }

   public String getDescription() {
      return description;
   }

   public ImageWriter getImageWriter() {
      if (spi != null) {
         try {
            return spi.createWriterInstance();
         }
         catch (IOException e) {
            return null;
         }

      }
      return null;
   }

   public int getBiType() {
      return biType;
   }

   public void setBiType(int biType) {
      this.biType = biType;
   }

   public boolean isSupportsAlpha() {
      return supportsAlpha;
   }

   public void setSupportsAlpha(boolean supportsAlpha) {
      this.supportsAlpha = supportsAlpha;
   }

   public static ArrayList getImageWriterFilters() {
      ArrayList list = new ArrayList();
      Iterator iter = IIORegistry.getDefaultInstance().getServiceProviders(ImageWriterSpi.class, true);
      while (iter.hasNext()) {
         ImageWriterSpi spi = (ImageWriterSpi) iter.next();


         String name = spi.getDescription(null) + " (";

         String[] suf = spi.getFileSuffixes();
         ArrayList sufList = new ArrayList();
         for (int i = 0; i < suf.length; i++) {
            String s = suf[i].toLowerCase();

            if (!sufList.contains(s)) {
               sufList.add(s);
            }
            if (i < list.size() - 1) {
               name += "*." + s + ", ";
            }
            else {
               name += "*." + s;
            }

         }
         name += ")";
         ImageIOFileFilter filter = new ImageIOFileFilter(name, sufList, spi);


         //add to these tests as ImageIO is expanded
         if (spi.getFormatNames()[0].equalsIgnoreCase("wbmp")) {
            filter.setBiType(BufferedImage.TYPE_BYTE_BINARY);
            filter.setSupportsAlpha(false);
         }
         else if (spi.getFormatNames()[0].equalsIgnoreCase("bmp")) {
            filter.setBiType(BufferedImage.TYPE_INT_RGB);
            filter.setSupportsAlpha(false);
         }
         else if (spi.getFormatNames()[0].equalsIgnoreCase("png")) {
            filter.setBiType(BufferedImage.TYPE_INT_ARGB);
            filter.setSupportsAlpha(true);
         }
         else if (spi.getFormatNames()[0].equalsIgnoreCase("jpeg")) {
            filter.setBiType(BufferedImage.TYPE_INT_RGB);
            filter.setSupportsAlpha(false);
         }
         else {

            //some spi may not support this but try anyway
            filter.setBiType(BufferedImage.TYPE_INT_ARGB);
            filter.setSupportsAlpha(true);
         }

         list.add(filter);


      }
      return list;
   }

   public static FileFilter getImageReaderFilter() {
      ArrayList list = getImageIOReaderSuffix();
      String name = "Image Files (";
      for (int i = 0; i < list.size(); i++) {
         String s = (String) list.get(i);
         if (i < list.size() - 1) {
            name += "*." + s + ", ";
         }
         else {
            name += "*." + s;
         }

      }
      name += ")";
      return new ImageIOFileFilter(name, list, null);
   }

   public static ArrayList getImageIOReaderSuffix() {
      ArrayList list = new ArrayList();
      Iterator iter = IIORegistry.getDefaultInstance().getServiceProviders(ImageReaderSpi.class, true);
      while (iter.hasNext()) {
         ImageReaderSpi spi = ((ImageReaderSpi) iter.next());

         String[] suf = spi.getFileSuffixes();

         for (int i = 0; i < suf.length; i++) {
            String s = suf[i];
            list.add(s);

         }
      }
      return list;

   }

   public static void main(String[] args) {
      Iterator iter = IIORegistry.getDefaultInstance().getServiceProviders(ImageWriterSpi.class, true);
      while (iter.hasNext()) {
         ImageWriterSpi spi = (ImageWriterSpi) iter.next();
         System.out.println("spi " + spi.getFormatNames()[0]);

         for (int i = 1; i < 14; i++) {
            BufferedImage bi = new BufferedImage(2, 2, i);
            System.out.println(i + " " + spi.canEncodeImage(bi));
         }

      }
   }

}
