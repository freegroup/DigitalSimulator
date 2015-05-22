package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.util;

import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.image.BufferedImage;
import java.io.IOException;

/**
 * A tranferable object that holds a BufferedImage.
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class TransferableImage implements Transferable {
   public BufferedImage img;

   public TransferableImage(BufferedImage img) {
      this.img = img;
   }

   public DataFlavor[] getTransferDataFlavors() {
      return new DataFlavor[]{DataFlavor.imageFlavor};
   }

   public boolean isDataFlavorSupported(DataFlavor flavor) {
      if (flavor.equals(DataFlavor.imageFlavor)) {
         return true;
      }
      return false;
   }

   public Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException, IOException {
      return img;
   }
}
