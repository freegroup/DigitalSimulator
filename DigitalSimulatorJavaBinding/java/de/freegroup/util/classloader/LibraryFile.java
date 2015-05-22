/*
 * SAPMarkets Copyright (c) 2001
 * All rights reserved
 *
 * @version $Id: LibraryFile.java,v 1.1 2004/01/28 14:33:36 freegroup Exp $
 */

package de.freegroup.util.classloader;

import java.io.*;
import java.net.*;

/**
 * Library source represented by a library file.
 *
 * @created   27. April 2001
 */
public class LibraryFile implements ILibrarySource
{
    private File libraryFile = null;

    /**
     * Construct LibraryFile object.
     *
     * @param libraryFile                Library file
     * @exception ClassNotFoundException  Exception thrown when library source invalid
     */
    public LibraryFile( File libraryFile )
        throws ClassNotFoundException
    {
        if( ( libraryFile != null ) && ( libraryFile.exists() ) && ( libraryFile.isFile() ) )
        {
            this.libraryFile = libraryFile;
        }
        else
        {
            throw new ClassNotFoundException( "Failed to instantiate library source!" );
        }
    }

    /**
     * Get library location based on library name.
     *
     * @param name  Name of library to be searched
     * @return      Absolute path name of native library
     */
    public String getLibraryLocation( String name )
    {
        String libraryFileName = libraryFile.getName() + ".";
        String wantedFileName = name + ".";
        if( libraryFileName.toUpperCase().startsWith( wantedFileName.toUpperCase() ) )
        {
            return libraryFile.getAbsolutePath();
        }
        return null;
    }

    /**
     * Get library path this library source references. Each entry including the last must be
     * terminated with a semicolon.
     *
     * @return   Library path this library source references
     */
    public String getLibraryPath()
    {
        return libraryFile.getPath() + ";";
    }
}
