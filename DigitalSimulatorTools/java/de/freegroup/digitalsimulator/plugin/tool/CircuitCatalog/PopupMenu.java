package de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog;

import de.freegroup.digitalsimulator.plugin.tool.CircuitCatalog.util.*;

import javax.swing.*;
import java.awt.*;
import java.awt.datatransfer.Clipboard;
import java.awt.event.*;
import java.awt.geom.Point2D;

/**
 * A JPopupMenu for a PaintPanel to do all of the edit stuff.
 *
 * <p>Copyright (c) 2004 Alistair Dickie. All Rights Reserved.
 * See alistairdickie.com for contact details
 * See licence.txt for licence infomation</p>
 */
public class PopupMenu extends JPopupMenu implements MouseListener, MouseMotionListener, ActionListener {
   private PaintPanel panel;
   private boolean drag;
   private JMenuItem pasteImage;

   private Clipboard clip;

   private Point2D clickPoint;


   public PopupMenu(PaintPanel panel) {
      clip = Toolkit.getDefaultToolkit().getSystemClipboard();

      this.panel = panel;
      panel.addMouseListener(this);
      panel.addMouseMotionListener(this);

      JMenuItem copy = new JMenuItem("Copy Objects");
      copy.addActionListener(this);
      copy.setActionCommand("copy");
      this.add(copy);

      JMenuItem delete = new JMenuItem("Delete Objects ");
      delete.addActionListener(this);
      delete.setActionCommand("delete");
      this.add(delete);

      JMenuItem inc = new JMenuItem("Incorporate Objects");
      inc.addActionListener(this);
      inc.setActionCommand("inc");
      this.add(inc);

      this.addSeparator();

      JMenuItem selAll = new JMenuItem("Select All Objects");
      selAll.addActionListener(this);
      selAll.setActionCommand("selall");
      this.add(selAll);

      JMenuItem incAll = new JMenuItem("Incorporate All Objects");
      incAll.addActionListener(this);
      incAll.setActionCommand("incall");
      this.add(incAll);

      this.addSeparator();

      JMenuItem copyImage = new JMenuItem("Copy Image To Clipboard");
      copyImage.addActionListener(this);
      copyImage.setActionCommand("copyimage");
      this.add(copyImage);

      JMenuItem copyImageBG = new JMenuItem("Copy Image with Background");
      copyImageBG.addActionListener(this);
      copyImageBG.setActionCommand("copyimagebg");
      this.add(copyImageBG);

      pasteImage = new JMenuItem("Paste Image from Clipboard");
      pasteImage.addActionListener(this);
      pasteImage.setActionCommand("pasteimage");
      this.add(pasteImage);


   }

   public void actionPerformed(ActionEvent e) {
      if (e.getActionCommand().equals("copy")) {
         panel.copySelected();
      }
      if (e.getActionCommand().equals("delete")) {
         panel.deleteSelected();
      }
      if (e.getActionCommand().equals("inc")) {
         panel.incorporateSelected();
      }

      if (e.getActionCommand().equals("selall")) {
         panel.selectAll();
      }

      if (e.getActionCommand().equals("incall")) {
         panel.selectAll();
         panel.incorporateSelected();
      }
      if (e.getActionCommand().equals("copyimage")) {
         panel.copyImageToClipboard();

      }
      if (e.getActionCommand().equals("copyimagebg")) {
         panel.copyImageToClipboardwBG();
      }

      if (e.getActionCommand().equals("pasteimage")) {
         panel.pasteImageFromClipboard(clickPoint);


      }


   }

   public void mouseClicked(MouseEvent e) {

   }

   public void mousePressed(MouseEvent e) {
      drag = false;
      if (e.isPopupTrigger() & !drag) {
         if (!BufferedImageTool.clipboardHasImage(clip)) {
            pasteImage.setEnabled(false);
         }
         else {
            pasteImage.setEnabled(true);
         }
         clickPoint = e.getPoint();

         this.show((Component) e.getSource(), e.getX(), e.getY());
      }
   }

   public void mouseReleased(MouseEvent e) {
      if (e.isPopupTrigger() & !drag) {
         if (!BufferedImageTool.clipboardHasImage(clip)) {
            pasteImage.setEnabled(false);
         }
         else {
            pasteImage.setEnabled(true);
         }
         clickPoint = e.getPoint();

         this.show((Component) e.getSource(), e.getX(), e.getY());
      }
   }

   public void mouseEntered(MouseEvent e) {
      //To change body of implemented methods use File | Settings | File Templates.
   }

   public void mouseExited(MouseEvent e) {
      //To change body of implemented methods use File | Settings | File Templates.
   }

   public void mouseDragged(MouseEvent e) {
      drag = true;
   }

   public void mouseMoved(MouseEvent e) {
      //To change body of implemented methods use File | Settings | File Templates.
   }


}
