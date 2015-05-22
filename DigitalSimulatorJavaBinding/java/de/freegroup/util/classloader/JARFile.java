/*
 * SAPMarkets Copyright (c) 2001
 * All rights reserved
 *
 * @version $Id: JARFile.java,v 1.1 2004/01/28 14:33:36 freegroup Exp $
 */

package de.freegroup.util.classloader;

import java.io.*;
import java.net.*;
import java.util.*;
import java.util.jar.*;

/**
 * Class source represented by a JAR file.
 *
 * @created   27. April 2001
 */
public class JARFile implements IClassSource, IResourceSource
{
    private File jarFile = null;

    /**
     * Construct JARFile object.
     *
     * @param jarFile                     JAR file
     * @exception ClassNotFoundException  Exception thrown when class source invalid
     */
    public JARFile( File jarFile )
        throws ClassNotFoundException
    {
        if( ( jarFile != null ) && ( jarFile.exists() ) && ( jarFile.isFile() ) )
        {
            this.jarFile = jarFile;
        }
        else
        {
            throw new ClassNotFoundException( "Failed to instantiate class source!" );
        }
    }

    /**
     * Get class defintion based on class name.
     *
     * @param name                        Name of class to be retrieved
     * @return                            Class defintion byte array of class to be retrieved
     * @exception ClassNotFoundException  Exception thrown when class to be retrieved not found
     */
    public byte[] getClassDefinition( String name )
        throws ClassNotFoundException
    {
        try
        {
            JarFile jarFile = new JarFile( this.jarFile );
            if( jarFile != null )
            {
                try
                {
                    JarEntry jarEntry = jarFile.getJarEntry( name.replace( '.', '/' ) + ".class" );
                    if( jarEntry != null )
                    {
                        int size = ( int )jarEntry.getSize();
                        byte[] temp = new byte[size];
                        byte[] classDefinition = new byte[size];
                        InputStream classStream = jarFile.getInputStream( jarEntry );
                        if( classStream != null )
                        {
                            try
                            {
                                int read = 0;

                                while( size > read )
                                {
                                    int l = classStream.read( temp );
                                    System.arraycopy( temp, 0, classDefinition, read, l );
                                    read += l;
                                }
                            }
                            finally
                            {
                                classStream.close();
                            }
                            return ( classDefinition );
                        }
                    }
                }
                finally
                {
                    jarFile.close();
                }
            }
        }
        catch( Exception exception )
        {
            // Do nothing since an exception will be thrown automatically
        }
        throw new ClassNotFoundException( name );
    }

    /**
     * Check if class definition can be found within class path.
     *
     * @param name  Name of class to be looked for
     * @return      flag indicating successful localization
     */
    public boolean hasClassDefinition( String name )
    {
        try
        {
            JarFile jarFile = new JarFile( this.jarFile );
            if( jarFile != null )
            {
                try
                {
                    JarEntry jarEntry = jarFile.getJarEntry( name.replace( '.', '/' ) + ".class" );
                    if( jarEntry != null )
                    {
                        return true;
                    }
                }
                finally
                {
                    jarFile.close();
                }
            }
        }
        catch( IOException e )
        {
        }
        return false;
    }

    /**
     * Get resource location based on resource name.
     *
     * @param name  Name of resource to be searched
     * @return      URL of resource
     */
    public URL getResourceLocation( String name )
    {
        try
        {
            while( name.startsWith( "/" ) )
            {
                name = name.substring( 1 );
            }
            JarFile jarFile = new JarFile( this.jarFile );
            if( jarFile != null )
            {
                try
                {
                    JarEntry jarEntry = jarFile.getJarEntry( name );
                    if( jarEntry != null )
                    {
                        return ( new URL( "jar:" + this.jarFile.toURL() + "!/" + name ) );
                    }
                }
                finally
                {
                    jarFile.close();
                }
            }
        }
        catch( Exception exception )
        {
            // Do nothing since null will be returned automatically
        }
        return null;
    }

    /**
     * Get resource locations based on resource name.
     *
     * @param name  Name of resources to be searched
     * @return      Enumeration of URLs of resources
     */
    public Enumeration getResourceLocations( String name )
    {
        URL url = getResourceLocation( name );
        if( url != null )
        {
            Vector vector = new Vector();
            vector.add( url );
            return vector.elements();
        }
        return null;
    }

    /**
     * Get class path this class source references. Each entry including the last must be terminated
     * with a semicolon.
     *
     * @return   Class path this class source references
     */
    public String getClassPath()
    {
        return jarFile.getPath() + ";";
    }

    /**
     * Get resource path this resource source references. Each entry including the last must be
     * terminated with a semicolon.
     *
     * @return   Resource path this resource source references
     */
    public String getResourcePath()
    {
        return getClassPath();
    }

    /**
     * Determine whether this and the other object are equal.
     *
     * @param otherObject  The other object
     * @return             Flag indicating whether or not this and the other object are equal
     */
    public boolean equals( Object otherObject )
    {
        if( otherObject instanceof JARFile )
        {
            return ( ( JARFile )otherObject ).getClassPath().equalsIgnoreCase( getClassPath() );
        }
        return false;
    }
}
