/*
 * SAPMarkets Copyright (c) 2001
 * All rights reserved
 *
 * @version $Id: JavaDirectory.java,v 1.1 2004/01/28 14:33:36 freegroup Exp $
 */

package de.freegroup.util.classloader;

import java.io.*;
import java.util.*;

/**
 * Class source represented by a java directory.
 *
 * @created   27. April 2001
 */
public class JavaDirectory implements IClassSource
{
    private File javaDirectory = null;
    private String classPath = null;
    private Map javaFiles = null;

    /**
     * Construct JavaDirectory object.
     *
     * @param javaDirectory               Java directory
     * @exception ClassNotFoundException  Exception thrown when class source invalid
     */
    public JavaDirectory( File javaDirectory )
        throws ClassNotFoundException
    {
        if( ( javaDirectory != null ) && ( javaDirectory.isDirectory() ) )
        {
            this.javaDirectory = javaDirectory;
            this.javaFiles = new HashMap();
        }
        else
        {
            throw new ClassNotFoundException( "Failed to instantiate class source!" );
        }
    }

    /**
     * Construct JavaDirectory object.
     *
     * @param javaDirectory               Java directory
     * @param classPath                   Class path which should be used for compilation
     * @exception ClassNotFoundException  Exception thrown when class source invalid
     */
    public JavaDirectory( File javaDirectory, String classPath )
        throws ClassNotFoundException
    {
        if( ( javaDirectory != null ) && ( javaDirectory.isDirectory() ) )
        {
            this.javaDirectory = javaDirectory;
            this.classPath = classPath;
            this.javaFiles = new HashMap();
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
            // Check known class files
            JavaFile javaFile = ( JavaFile )javaFiles.get( name );
            if( javaFile == null )
            {
                javaFile = new JavaFile( new File( javaDirectory.getPath() + File.separatorChar + name.replace( '.', File.separatorChar ) + ".java" ), classPath );
                javaFiles.put( name, javaFile );
            }
            return javaFile.getClassDefinition( name );
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
            // Check known class files
            JavaFile javaFile = ( JavaFile )javaFiles.get( name );
            if( javaFile == null )
            {
                javaFile = new JavaFile( new File( javaDirectory.getPath() + File.separatorChar + name.replace( '.', File.separatorChar ) + ".java" ), classPath );
                javaFiles.put( name, javaFile );
            }
            return javaFile.hasClassDefinition( name );
        }
        catch( Exception exception )
        {
            // Do nothing since an exception will be thrown automatically
        }
        return false;
    }

    /**
     * Get class path this class source references. Each entry including the last must be terminated
     * with a semicolon.
     *
     * @return   Class path this class source references
     */
    public String getClassPath()
    {
        return javaDirectory.getPath() + ";";
    }
}
