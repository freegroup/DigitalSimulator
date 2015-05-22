/*
 * SAPMarkets Copyright (c) 2001
 * All rights reserved
 *
 * @version $Id: LibraryDirectory.java,v 1.1 2004/01/28 14:33:36 freegroup Exp $
 */

package de.freegroup.util.classloader;

import java.io.*;
import java.net.*;

/**
 * Library source represented by a library directory.
 *
 * @created   27. April 2001
 */
public class LibraryDirectory implements ILibrarySource
{
    private File libraryDirectory = null;

    /**
     * Construct LibraryDirectory object.
     *
     * @param libraryDirectory           Library directory
     * @exception ClassNotFoundException  Exception thrown when library source invalid
     */
    public LibraryDirectory( File libraryDirectory )
        throws ClassNotFoundException
    {
        if( ( libraryDirectory != null ) && ( libraryDirectory.isDirectory() ) )
        {
            this.libraryDirectory = libraryDirectory;
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
        String libraryFileName;
        String wantedFileName = name + ".";
        File libraryFile;
        File[] libraryFilesArray = libraryDirectory.listFiles();
        if( libraryFilesArray != null )
        {
            for( int i = 0; i < libraryFilesArray.length; i++ )
            {
                libraryFile = libraryFilesArray[i];
                if( libraryFile.isFile() )
                {
                    libraryFileName = libraryFile.getName() + ".";
                    if( libraryFileName.toUpperCase().startsWith( wantedFileName.toUpperCase() ) )
                    {
                        return libraryFile.getAbsolutePath();
                    }
                }
            }
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
        return libraryDirectory.getPath() + ";";
    }
}
