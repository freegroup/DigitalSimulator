package de.freegroup.digitalsimulator.test;

/**
 * Title:        JavaBridge for the DigitalSimulator
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:      FreeGroup
 * @author Andreas Herz
 * @version 1.0
 */
import Application;

public class UpdatePlugins {

    public static void main(String[] args)
    {
        System.getProperties().put( "proxySet", "true" );
        System.getProperties().put( "proxyHost", "proxy.wdf.sap-ag.de" );
        System.getProperties().put( "proxyPort", "8080" );

        Application.onUpdatePlugins();
    }
}