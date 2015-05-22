/*
 * SAPMarkets Copyright (c) 2001
 * All rights reserved
 *
 * @version $Id: IClassSource.java,v 1.1 2004/01/28 14:33:36 freegroup Exp $
 */

package de.freegroup.util.classloader;

/**
 * Interface describing a class source.
 *
 * @created   27. April 2001
 */
public interface IClassSource
{
    /**
     * Get class defintion based on class name.
     *
     * @param name                        Name of class to be retrieved
     * @return                            Class defintion byte array of class to be retrieved
     * @exception ClassNotFoundException  Exception thrown when class to be retrieved not found
     */
    public byte[] getClassDefinition( String name )
        throws ClassNotFoundException;

    /**
     * Check if class definition can be found within class path.
     *
     * @param name  Name of class to be looked for
     * @return      flag indicating successful localization
     */
    public boolean hasClassDefinition( String name );

    /**
     * Get class path this class source references. Each entry including the last must be terminated
     * with a semicolon.
     *
     * @return   Class path this class source references
     */
    public String getClassPath();
}
