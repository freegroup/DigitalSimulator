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

import java.awt.Color;
import java.awt.Font;

import javax.swing.JPanel;

import com.jgoodies.animation.Animation;
import com.jgoodies.animation.Animations;
import com.jgoodies.animation.animations.BasicTextAnimation;
import com.jgoodies.animation.animations.BasicTextAnimations;
import com.jgoodies.animation.components.BasicTextLabel;

/**
 * This is the main panel of the Forms Demo application.
 * It creates the navigator, design view and status bar.
 *
 * @author Karsten Lentzsch
 * @version $Revision: 1.1 $
 */

public final class IntroPage {

    private BasicTextLabel label1;
    private BasicTextLabel label2;
    private Animation      animation;


    // API ******************************************************************

    /**
     * Returns the intro animation.
     * 
     * @return the intro animation
     */
    public Animation animation() {
        return animation;
    }
    

    // Building *************************************************************

    /**
     * Creates and configures the UI components.
     */
    private void initComponents() {
        Font font = getAnimationFont();
        label1 = new BasicTextLabel(" ");
        label1.setFont(font);
        label1.setBounds(0, 0, 350, 100);
        label1.setOpaque(false);

        label2 = new BasicTextLabel(" ");
        label2.setFont(font);
        label2.setBounds(0, 0, 350, 100);
        label2.setOpaque(false);
    }
    
    /**
     * Builds this intro panel with two overlayed labels in the center.
     * 
     * @return the panel that contains the two overlayed labels
     */
    public JPanel build() {
        initComponents();
        animation = createAnimation();
        
        JPanel panel = new JPanel(null);
        panel.setBounds(0, 0, 350, 100);
        panel.setBackground(Color.white);
        
        panel.add(label1);
        panel.add(label2); 

        return panel;
    }

    // Animation Creation ***************************************************

    /**
     * Creates and answers a composed animation for the intro.
     * 
     * @return the composed animation
     */
    private Animation createAnimation() {
        Animation welcome =
            BasicTextAnimation.defaultFade(
                label1,
                2500,
                "Welcome To",
                Color.darkGray);

        Animation theJGoodiesAnimation =
            BasicTextAnimation.defaultFade(
                label1,
                3000,
                "The JGoodies Animation",
                Color.darkGray);

        Animation description =
            BasicTextAnimations.defaultFade(
                label1,
                label2,
                2000,
                -100,
                "An open source framework|" +
                "for time-based|real-time animations|in Java.",
                Color.darkGray);

        Animation features =
            BasicTextAnimations.defaultFade(
                label1,
                label2,
                3000,
                500,
                "Main Features:",
                Color.darkGray);

        Animation featureList =
            BasicTextAnimations.defaultFade(
                label1,
                label2,
                1750,
                0,
                "Seemless|flexible|and powerful integration|with Java.|" +
                "small library size",
                Color.darkGray);

        Animation all =
            Animations.sequential(
                new Animation[] {
                    Animations.pause(1000),
                    welcome,
                    Animations.pause(1000),
                    theJGoodiesAnimation,
                    Animations.pause(1000),
                    description,
                    Animations.pause(1000),
                    features,
                    Animations.pause(1000),
                    featureList,
                    Animations.pause(1500),
                    });

        return all;
    }
    
    // Helper Code **********************************************************
    
    /**
     * Looks up and answer a <code>Font</code> used for the animations.
     * Tries to get a bold <i>Tahoma</i> on Windows.
     * 
     * @return the font used for the animation
     */
    private Font getAnimationFont() {
        return new Font("Tahoma", Font.BOLD, 18);
    }

}