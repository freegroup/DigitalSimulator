/*
 * Copyright (c) 2003 JGoodies Karsten Lentzsch. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 *  o Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *     
 *  o Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution. 
 *     
 *  o Neither the name of JGoodies Karsten Lentzsch nor the names of 
 *    its contributors may be used to endorse or promote products derived 
 *    from this software without specific prior written permission. 
 *     
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

package com.jgoodies.animation.examples.intro;

import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

import com.jgoodies.animation.AnimationUtils;
import com.jgoodies.animation.Animator;

/** 
 * A test class for a bunch of animations.
 * 
 * @author Karsten Lentzsch
 * @version $Revision: 1.1 $
 */
public final class Intro {
	
    private static final int DEFAULT_FRAME_RATE = 30;
    
    private IntroPage introPage;
    
    
    public static void main(String[] args) {
        // Try to get the framerate from the command-line.
        int fps = DEFAULT_FRAME_RATE;
        if (args.length > 0) {
            try {
                fps = Integer.parseInt(args[0]);
            } catch (NumberFormatException e) {
                System.out.println("Could not parse the custom frame rate: " + args[0]);
            }
        }
        System.out.println("The desired framerate is " + fps + '.');    
        new Intro(fps);
    }
    
    
    /**
     * Constructs an animation demo using the specified frame rate.
     * 
     * @param fps   the animation's frame rate
     */
    private Intro(int fps) {
        buildFrame();

        Runnable runnable = new Runnable() {
            public void run() {
                JOptionPane.showMessageDialog(null, "The End.");
            }
        };
        
        AnimationUtils.invokeOnStop(introPage.animation(), runnable);
        Animator animator = new Animator(introPage.animation(), fps);
        animator.start();
    }


    // Building ***************************************************************
    
    /**
     * Builds and opens the demo frame.
     */ 
    private void buildFrame() {
        JFrame frame = new JFrame();
        frame.setContentPane(buildContent());
        frame.setSize(350, 150);
        frame.setTitle("JGoodies Animation :: Intro");
        frame.setDefaultCloseOperation(3); // EXIT_ON_CLOSE
        locateOnScreenCenter(frame);
        frame.setVisible(true);
    }
    

    /**
     * Builds and answers the frame's content pane.
     * 
     * @return the frame's content pane
     */
    private Container buildContent() {
        introPage = new IntroPage();
        return introPage.build();
    }


    // Helper Code ***********************************************************
    
    /**
     * Locates the given component on the screen's center.
     * 
     * @param component   the component to be centered
     */
    private void locateOnScreenCenter(Component component) {
        Dimension paneSize = component.getSize();
        Dimension screenSize = component.getToolkit().getScreenSize();
        component.setLocation(
            (screenSize.width  - paneSize.width)  / 2,
            (screenSize.height - paneSize.height) / 2);
    }


}