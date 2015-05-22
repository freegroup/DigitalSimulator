/*
 * SAPMarkets Copyright (c) 2001
 * All rights reserved
 *
 * @version $Id: IResourceSource.java,v 1.1 2004/01/28 14:33:36 freegroup Exp $
 */

package de.freegroup.util.classloader;

import java.net.*;
import java.util.*;

/**
 * Interface describing a resource source.
 *
 * @created   27. April 2001
 */
public interface IResourceSource
{
    /**
     * Get resource location based on resource name.
     *
     * @param name  Name of resource to be searched
     * @return      URL of resource
     */
    public URL getResourceLocation( String name );

    /**
     * Get resource locations based on resource name.
     *
     * @param name  Name of resources to be searched
     * @return      Enumeration of URLs of resources
     */
    public Enumeration getResourceLocations( String name );

    /**
     * Get resource path this resource source references. Each entry including the last must be
     * terminated with a semicolon.
     *
     * @return   Resource path this resource source references
     */
    public String getResourcePath();
}
