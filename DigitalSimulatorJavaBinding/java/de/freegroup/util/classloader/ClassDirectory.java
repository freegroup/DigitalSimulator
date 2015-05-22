/*
 * SAPMarkets Copyright (c) 2001
 * All rights reserved
 *
 * @version $Id: ClassDirectory.java,v 1.1 2004/01/28 14:33:36 freegroup Exp $
 */

package de.freegroup.util.classloader;

import java.io.*;

/**
 * Class source represented by a class directory.
 *
 * @created   27. April 2001
 */
public class ClassDirectory implements IClassSource
{
    private File classDirectory = null;

    /**
     * Construct ClassDirectory object.
     *
     * @param classDirectory              Class directory
     * @exception ClassNotFoundException  Exception thrown when class source invalid
     */
    public ClassDirectory( File classDirectory )
        throws ClassNotFoundException
    {
        if( ( classDirectory != null ) && ( classDirectory.isDirectory() ) )
        {
            this.classDirectory = classDirectory;
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
            File classFile = new File( classDirectory, name.replace( '.', File.separatorChar ) + ".class" );
            if( ( classFile != null ) && ( classFile.exists() ) && ( classFile.isFile() ) )
            {
                byte[] classDefintion = new byte[( int )classFile.length()];
                InputStream classStream = new FileInputStream( classFile );
                if( classStream != null )
                {
                    try
                    {
                        classStream.read( classDefintion );
                    }
                    finally
                    {
                        classStream.close();
                    }
                    return ( classDefintion );
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
        File classFile = new File( classDirectory, name.replace( '.', File.separatorChar ) + ".class" );
        if( ( classFile != null ) && ( classFile.exists() ) && ( classFile.isFile() ) )
        {
            return true;
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
        return classDirectory.getPath() + ";";
    }
}
