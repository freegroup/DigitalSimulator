/*
 * SAPMarkets Copyright (c) 2001
 * All rights reserved
 *
 * @version $Id: ResourceDirectory.java,v 1.1 2004/01/28 14:33:36 freegroup Exp $
 */

package de.freegroup.util.classloader;

import java.io.*;
import java.net.*;
import java.util.*;

/**
 * Resource source represented by a resource directory.
 *
 * @created   27. April 2001
 */
public class ResourceDirectory implements IResourceSource
{
    private File resourceDirectory = null;

    /**
     * Construct ResourceDirectory object.
     *
     * @param resourceDirectory          Resource directory
     * @exception ClassNotFoundException  Exception thrown when resource source invalid
     */
    public ResourceDirectory( File resourceDirectory )
        throws ClassNotFoundException
    {
        if( ( resourceDirectory != null ) && ( resourceDirectory.isDirectory() ) )
        {
            this.resourceDirectory = resourceDirectory;
        }
        else
        {
            throw new ClassNotFoundException( "Failed to instantiate resource source!" );
        }
    }

    /**
     * Get resource location based on resource name.
     *
     * @param name  Name of resource to be searched
     * @return      URL of resource
     */
    public URL getResourceLocation( String name )
    {
        File resourceFile = new File( resourceDirectory, name.replace( '/', File.separatorChar ) );
        if( ( resourceFile != null ) && ( resourceFile.exists() ) && ( resourceFile.isFile() ) )
        {
            try
            {
                return resourceFile.toURL();
            }
            catch( Exception exception )
            {
            }
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
     * Get resource path this resource source references. Each entry including the last must be
     * terminated with a semicolon.
     *
     * @return   Resource path this resource source references
     */
    public String getResourcePath()
    {
        return resourceDirectory.getPath() + ";";
    }
}
