/*
 * SAPMarkets Copyright (c) 2001
 * All rights reserved
 *
 * @version $Id: ILibrarySource.java,v 1.1 2004/01/28 14:33:36 freegroup Exp $
 */

package de.freegroup.util.classloader;

/**
 * Interface describing a library source.
 *
 * @created   27. April 2001
 */
public interface ILibrarySource
{
    /**
     * Get library location based on library name.
     *
     * @param name  Name of library to be searched
     * @return      Absolute path name of native library
     */
    public String getLibraryLocation( String name );

    /**
     * Get library path this library source references. Each entry including the last must be
     * terminated with a semicolon.
     *
     * @return   Library path this library source references
     */
    public String getLibraryPath();
}
