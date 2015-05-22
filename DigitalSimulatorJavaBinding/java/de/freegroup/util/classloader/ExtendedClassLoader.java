/*
 * SAPMarkets Copyright (c) 2001
 * All rights reserved
 *
 * @version $Id: ExtendedClassLoader.java,v 1.1 2004/01/28 14:33:36 freegroup Exp $
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
public class ExtendedClassLoader extends ClassLoader implements IClassSource, ILibrarySource, IResourceSource
{
    // Sources
    protected Vector classSources;
    protected Vector librarySources;
    protected Vector resourceSources;

    // Security access control context
    protected AccessControlContext accessControlContext;

    // Trace objcet
//    protected static Trace trace = new Trace( "$Class: com.sapmarkets.technology.classloader.ExtendedClassLoader $$Id: ExtendedClassLoader.java,v 1.1 2004/01/28 14:33:36 freegroup Exp $$DateTime: 2001/10/22 12:15:35 $$Change: 24501 $" );

    /**
     * Construct custom class loader.
     *
     * @param parentClassLoader  Parent class loader
     */
    public ExtendedClassLoader( ClassLoader parentClassLoader )
    {
        // Call constructor of base class
        super( parentClassLoader );
       // // trace.debugT( "ExtendedClassLoader(44)", "Constructed " + identity() + " using parent " + parentClassLoader );

        // Instantiate private members
        classSources = new Vector();
        librarySources = new Vector();
        resourceSources = new Vector();
        accessControlContext = AccessController.getContext();
    }

    /**
     * TBD: Description of the Method.
     *
     * @return   TBD: Description of the outgoing return value
     */
    public String identity()
    {
        return super.toString();
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
        if( getParent() instanceof IClassSource )
        {
            result.append( ( ( IClassSource )getParent() ).getClassPath() );
        }
        synchronized( classSources )
        {
            for( Iterator iter = classSources.iterator(); iter.hasNext();  )
            {
                result.append( ( ( IClassSource )iter.next() ).getClassPath() );
            }
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
        if( getParent() instanceof ILibrarySource )
        {
            result.append( ( ( ILibrarySource )getParent() ).getLibraryPath() );
        }
        synchronized( librarySources )
        {
            for( Iterator iter = librarySources.iterator(); iter.hasNext();  )
            {
                result.append( ( ( ILibrarySource )iter.next() ).getLibraryPath() );
            }
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
        if( getParent() instanceof IResourceSource )
        {
            result.append( ( ( IResourceSource )getParent() ).getResourcePath() );
        }
        synchronized( resourceSources )
        {
            for( Iterator iter = resourceSources.iterator(); iter.hasNext();  )
            {
                result.append( ( ( IResourceSource )iter.next() ).getResourcePath() );
            }
        }
        return result.toString();
    }

    /**
     * Append class source to the current class sources (at the end). Side effect: The class source
     * will also be added to the resource sources if possible.
     *
     * @param classSource                 Class source to be added
     * @exception ClassNotFoundException  Exception thrown when class source invalid
     */
    public void appendClassSource( IClassSource classSource )
        throws ClassNotFoundException
    {
        // trace.infoT( "appendClassSource(142)", "Appending class source " + classSource );
        if( classSource != null )
        {
            synchronized( classSources )
            {
                classSources.add( classSource );

                if( classSource instanceof JARFile )
                {
                    appendResourceSource( ( JARFile )classSource );
                }
                if( classSource instanceof JARDirectory )
                {
                    appendResourceSource( ( JARDirectory )classSource );
                }
                if( ( classSource instanceof ClassDirectory ) ||
                    ( classSource instanceof JavaDirectory ) )
                {
                    try
                    {
                        String filePath = classSource.getClassPath();
                        while( filePath.endsWith( ";" ) )
                        {
                            filePath = filePath.substring( 0, filePath.length() - 1 );
                        }
                        appendResourceSource( new ResourceDirectory( new File( filePath ) ) );
                    }
                    catch( Exception exception )
                    {
                        // trace.warningT( "appendClassSource(171)", "Failed to add class source " + classSource.getClassPath() + " as resource source: ", exception );
                    }
                }
            }
        }
        else
        {
            throw new ClassNotFoundException( "Failed to append class source!" );
        }
    }

    /**
     * Insert class source into the current class sources (at the beginning). Side effect: The class
     * source will also be added to the resource sources if possible.
     *
     * @param classSource                 Class source to be inserted
     * @exception ClassNotFoundException  Exception thrown when class source invalid
     */
    public void insertClassSource( IClassSource classSource )
        throws ClassNotFoundException
    {
        // trace.infoT( "insertClassSource(192)", "Inserting class source " + classSource );
        if( classSource != null )
        {
            synchronized( classSources )
            {
                classSources.insertElementAt( classSource, 0 );

                if( classSource instanceof JARFile )
                {
                    insertResourceSource( ( JARFile )classSource );
                }
                if( classSource instanceof JARDirectory )
                {
                    insertResourceSource( ( JARDirectory )classSource );
                }
                if( ( classSource instanceof ClassDirectory ) ||
                    ( classSource instanceof JavaDirectory ) )
                {
                    try
                    {
                        String filePath = classSource.getClassPath();
                        while( filePath.endsWith( ";" ) )
                        {
                            filePath = filePath.substring( 0, filePath.length() - 1 );
                        }
                        insertResourceSource( new ResourceDirectory( new File( filePath ) ) );
                    }
                    catch( Exception exception )
                    {
                        // trace.warningT( "insertClassSource(221)", "Failed to add class source " + classSource.getClassPath() + " as resource source: ", exception );
                    }
                }
            }
        }
        else
        {
            throw new ClassNotFoundException( "Failed to insert class source!" );
        }
    }

    /**
     * Remove class source from the current class sources.
     *
     * @param classSource                 Class source to be removed
     * @exception ClassNotFoundException  Exception thrown when class source invalid
     */
    public void removeClassSource( IClassSource classSource )
        throws ClassNotFoundException
    {
        // trace.infoT( "removeClassSource(241)", "Removing class source " + classSource );
        if( classSource != null )
        {
            synchronized( classSources )
            {
                classSources.remove( classSource );
            }
        }
        else
        {
            throw new ClassNotFoundException( "Failed to remove class source!" );
        }
    }

    /**
     * Remove all class sources from the current class sources.
     */
    public void removeAllClassSources()
    {
        // trace.infoT( "removeAllClassSources(260)", "Removing all class sources" );
        synchronized( classSources )
        {
            classSources.clear();
        }
    }

    /**
     * Append library source to the current library sources (at the end).
     *
     * @param librarySource               library source to be added
     * @exception ClassNotFoundException  Exception thrown when library source invalid
     */
    public void appendLibrarySource( ILibrarySource librarySource )
        throws ClassNotFoundException
    {
        // trace.infoT( "appendLibrarySource(276)", "Appending library source " + librarySource );
        if( librarySource != null )
        {
            synchronized( librarySources )
            {
                librarySources.add( librarySource );
            }
        }
        else
        {
            throw new ClassNotFoundException( "Failed to append library source!" );
        }
    }

    /**
     * Insert library source into the current library sources (at the beginning).
     *
     * @param librarySource               library source to be inserted
     * @exception ClassNotFoundException  Exception thrown when library source invalid
     */
    public void insertLibrarySource( ILibrarySource librarySource )
        throws ClassNotFoundException
    {
        // trace.infoT( "insertLibrarySource(299)", "Inserting library source " + librarySource );
        if( librarySource != null )
        {
            synchronized( librarySources )
            {
                librarySources.insertElementAt( librarySource, 0 );
            }
        }
        else
        {
            throw new ClassNotFoundException( "Failed to insert library source!" );
        }
    }

    /**
     * Remove library source from the current library sources.
     *
     * @param librarySource               library source to be removed
     * @exception ClassNotFoundException  Exception thrown when library source invalid
     */
    public void removeLibrarySource( ILibrarySource librarySource )
        throws ClassNotFoundException
    {
        // trace.infoT( "removeLibrarySource(322)", "Removing library source " + librarySource );
        if( librarySource != null )
        {
            synchronized( librarySources )
            {
                librarySources.remove( librarySource );
            }
        }
        else
        {
            throw new ClassNotFoundException( "Failed to remove library source!" );
        }
    }

    /**
     * Remove all library sources from the current library sources.
     */
    public void removeAllLibrarySources()
    {
        // trace.infoT( "removeAllLibrarySources(341)", "Removing all library sources" );
        synchronized( librarySources )
        {
            librarySources.clear();
        }
    }

    /**
     * Append resource source to the current resource sources (at the end).
     *
     * @param resourceSource              resource source to be added
     * @exception ClassNotFoundException  Exception thrown when resource source invalid
     */
    public void appendResourceSource( IResourceSource resourceSource )
        throws ClassNotFoundException
    {
        // trace.infoT( "appendResourceSource(357)", "Appending resource source " + resourceSource );
        if( resourceSource != null )
        {
            synchronized( resourceSources )
            {
                resourceSources.add( resourceSource );
            }
        }
        else
        {
            throw new ClassNotFoundException( "Failed to append resource source!" );
        }
    }

    /**
     * Insert resource source into the current resource sources (at the beginning).
     *
     * @param resourceSource              resource source to be inserted
     * @exception ClassNotFoundException  Exception thrown when resource source invalid
     */
    public void insertResourceSource( IResourceSource resourceSource )
        throws ClassNotFoundException
    {
        // trace.infoT( "insertResourceSource(380)", "Inserting resource source " + resourceSource );
        if( resourceSource != null )
        {
            synchronized( resourceSources )
            {
                resourceSources.insertElementAt( resourceSource, 0 );
            }
        }
        else
        {
            throw new ClassNotFoundException( "Failed to insert resource source!" );
        }
    }

    /**
     * Remove resource source from the current resource sources.
     *
     * @param resourceSource              resource source to be removed
     * @exception ClassNotFoundException  Exception thrown when resource source invalid
     */
    public void removeResourceSource( IResourceSource resourceSource )
        throws ClassNotFoundException
    {
        // trace.infoT( "removeResourceSource(403)", "Removing resource source " + resourceSource );
        if( resourceSource != null )
        {
            synchronized( resourceSources )
            {
                resourceSources.remove( resourceSource );
            }
        }
        else
        {
            throw new ClassNotFoundException( "Failed to remove resource source!" );
        }
    }

    /**
     * Remove all resource sources from the current resource sources.
     */
    public void removeAllResourceSources()
    {
        // trace.infoT( "removeAllResourceSources(422)", "Removing all resource sources" );
        synchronized( resourceSources )
        {
            resourceSources.clear();
        }
    }

    /**
     * Suggest class source based on file.
     *
     * @param classSourceFile             file to be used to suggest class source
     * @return                            suggested class source
     * @exception ClassNotFoundException  Exception raised in failure situation
     */
    public IClassSource suggestClassSource( File classSourceFile )
        throws ClassNotFoundException
    {
        // trace.infoT( "suggestClassSource(439)", "Trying to suggest class source for file " + classSourceFile );
        if( classSourceFile.exists() )
        {
            // Check for directory
            if( classSourceFile.isDirectory() )
            {
                if( classSourceFile.getName().startsWith( "class" ) )
                {
                    return new ClassDirectory( classSourceFile );
                }
                if( classSourceFile.getName().startsWith( "lib" ) )
                {
                    return new JARDirectory( classSourceFile );
                }
                if( ( classSourceFile.getName().startsWith( "java" ) ) ||
                    ( classSourceFile.getName().startsWith( "source" ) ) ||
                    ( classSourceFile.getName().startsWith( "src" ) ) )
                {
                    return new JavaDirectory( classSourceFile );
                }
            }

            // Check for file
            if( classSourceFile.isFile() )
            {
                if( classSourceFile.getName().endsWith( ".class" ) )
                {
                    return new ClassFile( classSourceFile );
                }
                if( classSourceFile.getName().endsWith( ".jar" ) )
                {
                    return new JARFile( classSourceFile );
                }
                if( classSourceFile.getName().endsWith( ".java" ) )
                {
                    return new JavaFile( classSourceFile );
                }
            }

            // Nothing matched
            // trace.warningT( "suggestClassSource(479)", "Failed to suggest class source" );
            throw new ClassNotFoundException( "Failed to suggest class source" );
        }
        else
        {
            // trace.warningT( "suggestClassSource(484)", "File doesn't exist; can't suggest class source" );
            throw new ClassNotFoundException( "File doesn't exist; can't suggest class source" );
        }
    }

    /**
     * Suggest library source based on file.
     *
     * @param librarySourceFile           file to be used to suggest library source
     * @return                            suggested library source
     * @exception ClassNotFoundException  Exception raised in failure situation
     */
    public ILibrarySource suggestLibrarySource( File librarySourceFile )
        throws ClassNotFoundException
    {
        // trace.infoT( "suggestLibrarySource(499)", "Trying to suggest library source for file " + librarySourceFile );
        if( librarySourceFile.exists() )
        {
            // Check for directory
            if( librarySourceFile.isDirectory() )
            {
                return new LibraryDirectory( librarySourceFile );
            }

            // Check for file
            if( librarySourceFile.isFile() )
            {
                return new LibraryFile( librarySourceFile );
            }

            // Nothing matched
            // trace.warningT( "suggestLibrarySource(515)", "Failed to suggest library source" );
            throw new ClassNotFoundException( "Failed to suggest library source" );
        }
        else
        {
            // trace.warningT( "suggestLibrarySource(520)", "File doesn't exist; can't suggest library source" );
            throw new ClassNotFoundException( "File doesn't exist; can't suggest library source" );
        }
    }

    /**
     * Suggest resource source based on file.
     *
     * @param resourceSourceFile          file to be used to suggest resource source
     * @return                            suggested resource source
     * @exception ClassNotFoundException  Exception raised in failure situation
     */
    public IResourceSource suggestResourceSource( File resourceSourceFile )
        throws ClassNotFoundException
    {
        // trace.infoT( "suggestResourceSource(535)", "Trying to suggest resource source for file " + resourceSourceFile );
        if( resourceSourceFile.exists() )
        {
            // Check for directory
            if( resourceSourceFile.isDirectory() )
            {
                if( resourceSourceFile.getName().startsWith( "lib" ) )
                {
                    return new JARDirectory( resourceSourceFile );
                }
                else
                {
                    return new ResourceDirectory( resourceSourceFile );
                }
            }

            // Check for file
            if( resourceSourceFile.isFile() )
            {
                if( resourceSourceFile.getName().endsWith( ".jar" ) )
                {
                    return new JARFile( resourceSourceFile );
                }
                else
                {
                    return new ResourceFile( resourceSourceFile );
                }
            }

            // Nothing matched
            // trace.warningT( "suggestResourceSource(565)", "Failed to suggest resource source" );
            throw new ClassNotFoundException( "Failed to suggest resource source" );
        }
        else
        {
            // trace.warningT( "suggestResourceSource(570)", "File doesn't exist; can't suggest resource source" );
            throw new ClassNotFoundException( "File doesn't exist; can't suggest resource source" );
        }
    }

    /**
     * Get class defintion based on class name.
     *
     * @param name                        Name of class to be retrieved
     * @return                            Class defintion byte array of class to be retrieved
     * @exception ClassNotFoundException  Exception thrown when class to be retrieved not found
     */
    public byte[] getClassDefinition( String name )  throws ClassNotFoundException
    {
        // Safeguard operations
        try
        {
            synchronized( classSources )
            {
                // Protocol method entering
                // trace.entering( "getClassDefinition(591)" );
                // trace.debugT( "getClassDefinition(592)", "Trying to get class definition for class " + name );

                // Init class definition to null
                byte[] classDefinition = null;

                // Look for class in class path
                for( Iterator iter = classSources.iterator(); ( iter.hasNext() ) && ( classDefinition == null );  )
                {
                    try
                    {
                        IClassSource classSource = ( IClassSource )iter.next();
                        // trace.debugT( "getClassDefinition(603)", "Looking in class path " + classSource.getClassPath() );
                        if( ( classDefinition = classSource.getClassDefinition( name ) ) != null )
                        {
                            // Returning class definition
                            // trace.debugT( "getClassDefinition(607)", "Returning retrieved class definition " + classDefinition );
                            return classDefinition;
                        }
                    }
                    catch( ClassNotFoundException exception )
                    {
                        // Try next one
                    }
                }
                // trace.debugT( "getClassDefinition(616)", "Throwing ClassNotFoundException() because class " + name + " couldn't be retrieved" );
                throw new ClassNotFoundException( name );
            }
        }
        finally
        {
            // Protocol method exiting
            // trace.exiting( "getClassDefinition(623)" );
        }
    }

    /**
     * Check if class definition can be found within class path.
     *
     * @param name  Name of class to be looked for
     * @return      flag indicating successful localization
     */
    public boolean hasClassDefinition( String name )
    {
        // Safeguard operations
        try
        {
            synchronized( classSources )
            {
                // Protocol method entering
                // trace.entering( "hasClassDefinition(641)" );
                // trace.debugT( "hasClassDefinition(642)", "Trying to find class definition for class " + name );

                // Look for class in class path
                for( Iterator iter = classSources.iterator(); ( iter.hasNext() );  )
                {
                    IClassSource classSource = ( IClassSource )iter.next();
                    // trace.debugT( "hasClassDefinition(648)", "Looking in class path " + classSource.getClassPath() );
                    if( classSource.hasClassDefinition( name ) )
                    {
                        return true;
                    }
                    // Try next one
                }
                return false;
            }
        }
        finally
        {
            // Protocol method exiting
            // trace.exiting( "hasClassDefinition(661)" );
        }
    }

  protected final Class defineClass_FAKE_FOR_COMPILER_BUG_(String name, byte[] b, int off, int len) throws ClassFormatError
   {
      return defineClass(name,b,off,len);
   }
    /**
     * Find a class. This method is called in response to the loadClass() call.
     *
     * @param name                        Name of class to be searched
     * @return                            Class object of class to be searched
     * @exception ClassNotFoundException  Exception thrown when class to be searched not found
     */
    protected Class findClass( final String name )        throws ClassNotFoundException
    {
				// Safeguard operations
				try
				{
					synchronized (classSources)
					{
						// Protocol method entering
						// trace.entering( "findClass(681)" );
						// trace.debugT( "findClass(682)", "Trying to find class " + name );
						// Perform priviledged action
						return (Class) AccessController.doPrivileged(new PrivilegedExceptionAction()
						{
							/**
							 * Main processing method for the ExtendedClassLoader object.
							 *
							 * @return                            Class object of class to be searched
							 * @exception ClassNotFoundException  Exception thrown when class to be
							 *      searched not found
							 */
							public Object run() throws ClassNotFoundException
							{
								byte[] classDefinition = getClassDefinition(name);
								return defineClass_FAKE_FOR_COMPILER_BUG_(name, classDefinition, 0, classDefinition.length);
							}
						}, accessControlContext);
					}
				}
				catch (java.security.PrivilegedActionException exception)
				{
					// trace.debugT( "findClass(706)", "Catched security exception " + exception.getMessage() );
					throw new ClassNotFoundException(exception.getException().getMessage());
				}
				finally
				{
					// Protocol method exiting
					// trace.exiting( "findClass(712)" );
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
        // Safeguard operations
        try
        {
            synchronized( librarySources )
            {
                // Protocol method entering
                // trace.entering( "getLibraryLocation(730)" );
                // trace.debugT( "getLibraryLocation(731)", "Trying to get library location for library " + name );

                // Init library location to null
                String libraryLocation = null;

                // Look for library in library path
                for( Iterator iter = librarySources.iterator(); ( iter.hasNext() ) && ( libraryLocation == null );  )
                {
                    ILibrarySource librarySource = ( ILibrarySource )iter.next();
                    // trace.debugT( "getLibraryLocation(740)", "Looking in library path " + librarySource.getLibraryPath() );
                    if( ( libraryLocation = librarySource.getLibraryLocation( name ) ) != null )
                    {
                        // Returning library location
                        // trace.debugT( "getLibraryLocation(744)", "Returning retrieved library location " + libraryLocation );
                        return libraryLocation;
                    }
                }
                // trace.debugT( "getLibraryLocation(748)", "Returning null because library " + name + " couldn't be located" );
                return libraryLocation;
            }
        }
        finally
        {
            // Protocol method exiting
            // trace.exiting( "getLibraryLocation(755)" );
        }
    }

    /**
     * Find a library.
     *
     * @param name  Name of library to be searched
     * @return      Absolute path name of a native library
     */
    public String findLibrary( final String name )
    {
        // Safeguard operations
        try
        {
            synchronized( librarySources )
            {
                // Protocol method entering
                // trace.entering( "findLibrary(773)" );
                // trace.debugT( "findLibrary(774)", "Trying to find library " + name );

                // Perform priviledged action
                return ( String )AccessController.doPrivileged(
                    new PrivilegedExceptionAction()
                    {
                        /**
                         * Main processing method for the ExtendedClassLoader object.
                         *
                         * @return   Absolute path name of a native library
                         */
                        public Object run()
                        {
                            return getLibraryLocation( name );
                        }
                    }, accessControlContext );
            }
        }
        catch( java.security.PrivilegedActionException exception )
        {
            // trace.debugT( "findLibrary(794)", "Catched security exception " + exception.getMessage() );
            return null;
        }
        finally
        {
            // Protocol method exiting
            // trace.exiting( "findLibrary(800)" );
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
        // Safeguard operations
        try
        {
            synchronized( resourceSources )
            {
                // Protocol method entering
                // trace.entering( "getResourceLocation(818)" );
                // trace.debugT( "getResourceLocation(819)", "Trying to get resource location for resource " + name );

                // Init resource location to null
                URL resourceLocation = null;

                // Look for resource in resource path
                for( Iterator iter = resourceSources.iterator(); ( iter.hasNext() ) && ( resourceLocation == null );  )
                {
                    IResourceSource resourceSource = ( IResourceSource )iter.next();
                    // trace.debugT( "getResourceLocation(828)", "Looking in resource path " + resourceSource.getResourcePath() );
                    if( ( resourceLocation = resourceSource.getResourceLocation( name ) ) != null )
                    {
                        // Returning resource location
                        // trace.debugT( "getResourceLocation(832)", "Returning retrieved resource location " + resourceLocation );
                        return resourceLocation;
                    }
                }
                // trace.debugT( "getResourceLocation(836)", "Returning null because resource " + name + " couldn't be located" );
                return resourceLocation;
            }
        }
        finally
        {
            // Protocol method exiting
            // trace.exiting( "getResourceLocation(843)" );
        }
    }

    /**
     * Find a resource. This method is called in response to the getResource() call.
     *
     * @param name  Name of resource to be searched
     * @return      URL of resource
     */
    protected URL findResource( final String name )
    {
        // Safeguard operations
        try
        {
            synchronized( resourceSources )
            {
                // Protocol method entering
                // trace.entering( "findResource(861)" );
                // trace.debugT( "findResource(862)", "Trying to find resource " + name );

                // Perform priviledged action
                return ( URL )AccessController.doPrivileged(
                    new PrivilegedExceptionAction()
                    {
                        /**
                         * Main processing method for the ExtendedClassLoader object.
                         *
                         * @return   URL of resource
                         */
                        public Object run()
                        {
                            return getResourceLocation( name );
                        }
                    }, accessControlContext );
            }
        }
        catch( java.security.PrivilegedActionException exception )
        {
            // trace.debugT( "findResource(882)", "Catched security exception " + exception.getMessage() );
            return null;
        }
        finally
        {
            // Protocol method exiting
            // trace.exiting( "findResource(888)" );
        }
    }

    /**
     * Get resource locations based on resource name.
     *
     * @param name  Name of resources to be searched
     * @return      Enumeration of URLs of resources
     */
    public Enumeration getResourceLocations( String name )
    {
        // Safeguard operations
        try
        {
            synchronized( resourceSources )
            {
                // Protocol method entering
                // trace.entering( "getResourceLocations(906)" );
                // trace.debugT( "getResourceLocations(907)", "Trying to get resource location for resource " + name );

                // Init resource locations to null
                URL resourceLocation = null;
                Enumeration resourceLocations = null;
                Vector resourceAllLocations = new Vector();

                // Look for resource in resource path
                for( Iterator iter = resourceSources.iterator(); iter.hasNext();  )
                {
                    IResourceSource resourceSource = ( IResourceSource )iter.next();
                    // trace.debugT( "getResourceLocations(918)", "Looking in resource path " + resourceSource.getResourcePath() );
                    if( ( resourceLocations = resourceSource.getResourceLocations( name ) ) != null )
                    {
                        // Adding resource locations
                        // trace.debugT( "getResourceLocations(922)", "Adding retrieved resource locations" );
                        while( resourceLocations.hasMoreElements() )
                        {
                            resourceLocation = ( URL )resourceLocations.nextElement();
                            // trace.debugT( "getResourceLocations(926)", "Adding retrieved resource location " + resourceLocation );
                            resourceAllLocations.add( resourceLocation );
                        }
                    }
                }
                // trace.debugT( "getResourceLocations(931)", "Returning " + resourceAllLocations.size() + " retrieved resource locations" );
                return resourceAllLocations.elements();
            }
        }
        finally
        {
            // Protocol method exiting
            // trace.exiting( "getResourceLocations(938)" );
        }
    }

    /**
     * Find an enumeration of resources. This method is called in response to the getResources()
     * call.
     *
     * @param name             Name of resources to be searched
     * @return                 Enumeration of URLs of resources
     * @exception IOException  Exception raised in failure situation
     */
    protected Enumeration findResources( final String name )
        throws IOException
    {
        // Safeguard operations
        try
        {
            synchronized( resourceSources )
            {
                // Protocol method entering
                // trace.entering( "findResources(959)" );
                // trace.debugT( "findResources(960)", "Trying to find resources " + name );

                // Perform priviledged action
                return ( Enumeration )AccessController.doPrivileged(
                    new PrivilegedExceptionAction()
                    {
                        /**
                         * Main processing method for the ExtendedClassLoader object.
                         *
                         * @return   Enumeration of URLs of resources
                         */
                        public Object run()
                        {
                            return getResourceLocations( name );
                        }
                    }, accessControlContext );
            }
        }
        catch( java.security.PrivilegedActionException exception )
        {
            // trace.debugT( "findResources(980)", "Catched security exception " + exception.getMessage() );
            return null;
        }
        finally
        {
            // Protocol method exiting
            // trace.exiting( "findResources(986)" );
        }
    }
}
