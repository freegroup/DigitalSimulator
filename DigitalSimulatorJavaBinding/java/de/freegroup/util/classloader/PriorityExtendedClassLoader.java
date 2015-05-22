/*
 * SAPMarkets Copyright (c) 2001
 * All rights reserved
 *
 * @version $Id: PriorityExtendedClassLoader.java,v 1.1 2004/01/28 14:33:36 freegroup Exp $
 */

package de.freegroup.util.classloader;

//import com.sapmarkets.technology.tracing.*;

import java.io.*;
import java.net.*;
import java.security.*;
import java.util.*;

/**
 * Custom class loader.
 *
 * @created   26. April 2001
 */
public class PriorityExtendedClassLoader extends ExtendedClassLoader
{
    // Trace objcet
//    protected static Trace trace = new Trace( "$Class: com.sapmarkets.technology.classloader.PriorityExtendedClassLoader $$Id: PriorityExtendedClassLoader.java,v 1.1 2004/01/28 14:33:36 freegroup Exp $$DateTime: 2001/10/22 12:15:35 $$Change: 24501 $" );

    /**
     * Construct custom class loader.
     *
     * @param parentClassLoader  Parent class loader
     */
    public PriorityExtendedClassLoader( ClassLoader parentClassLoader )
    {
        // Call constructor of base class
        super( parentClassLoader );
    }

    /**
     * Get class path this class source references. Each entry including the last must be terminated
     * with a semicolon.
     *
     * @return   Class path this class source references
     */
    public String getClassPath()
    {
        StringBuffer result = new StringBuffer();
        synchronized( classSources )
        {
            for( Iterator iter = classSources.iterator(); iter.hasNext();  )
            {
                result.append( ( ( IClassSource )iter.next() ).getClassPath() );
            }
        }
        if( getParent() instanceof IClassSource )
        {
            result.append( ( ( IClassSource )getParent() ).getClassPath() );
        }
        return result.toString();
    }

    /**
     * Get library path this library source references. Each entry including the last must be
     * terminated with a semicolon.
     *
     * @return   Library path this library source references
     */
    public String getLibraryPath()
    {
        StringBuffer result = new StringBuffer();
        synchronized( librarySources )
        {
            for( Iterator iter = librarySources.iterator(); iter.hasNext();  )
            {
                result.append( ( ( ILibrarySource )iter.next() ).getLibraryPath() );
            }
        }
        if( getParent() instanceof ILibrarySource )
        {
            result.append( ( ( ILibrarySource )getParent() ).getLibraryPath() );
        }
        return result.toString();
    }

    /**
     * Get resource path this resource source references. Each entry including the last must be
     * terminated with a semicolon.
     *
     * @return   Resource path this resource source references
     */
    public String getResourcePath()
    {
        StringBuffer result = new StringBuffer();
        synchronized( resourceSources )
        {
            for( Iterator iter = resourceSources.iterator(); iter.hasNext();  )
            {
                result.append( ( ( IResourceSource )iter.next() ).getResourcePath() );
            }
        }
        if( getParent() instanceof IResourceSource )
        {
            result.append( ( ( IResourceSource )getParent() ).getResourcePath() );
        }
        return result.toString();
    }

    /**
     * Load a class, prioritizing the inner class path before the parent's one.
     *
     * @param name                        Name of class to be loaded
     * @param resolve                     If true, resolve, i.e. link loaded class
     * @return                            Class object of class to be loaded
     * @exception ClassNotFoundException  Exception thrown when class to be searched not found
     */
    protected Class loadClass( String name,
                               boolean resolve )
        throws ClassNotFoundException
    {
        // Safeguard operations
        try
        {
            synchronized( classSources )
            {
                // Protocol method entering
                // trace.entering( "loadClass(125)" );
                // trace.debugT( "loadClass(126)", "Trying to load" + ( resolve ? " and link " : " " ) + "class " + name );

                // Init class to null
                Class classObject = null;

                // Try to find class among loaded classes
                try
                {
                    // trace.debugT( "loadClass(134)", "Try to find class among loaded classes" );
                    classObject = findLoadedClass( name );
                }
                catch( Exception exception )
                {
                }
                if( classObject == null )
                {
                    // Try to find class in class path
                    try
                    {
                        // trace.debugT( "loadClass(145)", "Try to find class in class path" );
                        classObject = findClass( name );
                    }
                    catch( Exception exception )
                    {
                    }
                    if( classObject == null )
                    {
                        // Try to load class through the parent class loader
                        try
                        {
                            // trace.debugT( "loadClass(156)", "Try to load class through the parent class loader" );
                            classObject = super.loadClass( name, resolve );
                        }
                        catch( Exception exception )
                        {
                        }
                        if( classObject == null )
                        {
                            // trace.warningT( "loadClass(164)", "Throwing ClassNotFoundException() because class " + name + " couldn't be loaded" );
                            throw new ClassNotFoundException( name );
                        }
                    }
                }

                // Linking class
                if( resolve )
                {
                    // trace.debugT( "loadClass(173)", "Linking class " + classObject );
                    resolveClass( classObject );
                }

                // Returning class
                // trace.debugT( "loadClass(178)", "Returning loaded class " + classObject );
                return classObject;
            }
        }
        finally
        {
            // Protocol method exiting
            // trace.exiting( "loadClass(185)" );
        }
    }

    /**
     * Load a resource, prioritizing the inner resource path before the parent's one.
     *
     * @param name  Name of resource to be searched
     * @return      URL of resource
     */
    public URL getResource( String name )
    {
        // Safeguard operations
        try
        {
            synchronized( resourceSources )
            {
                // Protocol method entering
                // trace.entering( "getResource(203)" );
                // trace.debugT( "getResource(204)", "Trying to load resource " + name );

                // Init resource location to null
                URL resourceLocation = null;

                // Try to find resource in resource path
                // trace.debugT( "getResource(210)", "Try to find resource in resource path" );
                resourceLocation = findResource( name );
                if( resourceLocation == null )
                {
                    // Try to load resource through the parent class loader
                    // trace.debugT( "getResource(215)", "Try to load resource through the parent class loader" );
                    resourceLocation = super.getResource( name );
                }

                // Returning resource
                // trace.debugT( "getResource(220)", "Returning localized resource " + resourceLocation );
                return resourceLocation;
            }
        }
        finally
        {
            // Protocol method exiting
            // trace.exiting( "getResource(227)" );
        }
    }
}
