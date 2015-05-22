package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.util;

import java.awt.*;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.image.BufferedImage;
import java.awt.image.WritableRaster;

/**
 * A collection of static methods to fool with BufferedImages.
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */


public class BufferedImageTool {
   /**
    * Turns any fully transparent pixel to the Color of color using the setRGB(x,y, int RGB) method. Note that it
    * is assumed that in is an ARGB Buffered Image, or that band index 3 of its raster is the tranparent one
    * @param in
    * An intARBG BufferedImage
    * @param color
    * The color to replace with
    * @return
    * The modified in
    */
   public static BufferedImage makeTransBGColor(BufferedImage in, Color color) {
      WritableRaster raster = in.getRaster();
      for (int x = 0; x < in.getWidth(); x++) {
         for (int y = 0; y < in.getHeight(); y++) {

            if (raster.getSample(x, y, 3) == 0) {
               in.setRGB(x, y, color.getRGB());
            }
         }
      }
      return in;

   }


   /**
    * Creates a copy of in and returns a BufferedImage of biType
    *
    * @param in
    * An Image
    * @param biType
    * A BufferedImage type
    * @return
    * A new BufferedImage
    */

   public static BufferedImage copy(Image in, int biType) {
      BufferedImage out = new BufferedImage(in.getWidth(null), in.getHeight(null), biType);
      out.getGraphics().drawImage(in, 0, 0, null);
      return out;
   }


   /**
    * A returns copy(in, BufferedImage.TYPE_INT_ARGB)
    * @param in
    * An Image
    * @return
    * A new BufferedImage
    */
   public static BufferedImage copy(Image in) {
      return copy(in, BufferedImage.TYPE_INT_ARGB);
   }

   /**
    * Determines if aClip has a Tranferable with a DataFlavor of DataFlavor.imageFlavor
    * @param aClip
    * A Clipboard
    * @return
    * true if the Clipboard has a Tranferable with a DataFlavor of DataFlavor.imageFlavor
    */
   public static boolean clipboardHasImage(Clipboard aClip) {
      if (aClip == null) {
         return false;
      }
      Transferable trans = aClip.getContents(null);
      if (trans == null) {
         return false;
      }
      else {
         DataFlavor[] flavors = trans.getTransferDataFlavors();
         for (int i = 0; i < flavors.length; i++) {
            DataFlavor flavor = flavors[i];
            if (flavor.equals(DataFlavor.imageFlavor)) {
               return true;
            }
         }
      }
      return false;
   }


  /**
   * Returns clipboardHasImage(Toolkit.getDefaultToolkit().getSystemClipboard())
   * @return
   * true if the System Clipboard has a Tranferable with a DataFlavor of DataFlavor.imageFlavor
   */
   public static boolean clipboardHasImage() {
      return clipboardHasImage(Toolkit.getDefaultToolkit().getSystemClipboard());
   }

}
