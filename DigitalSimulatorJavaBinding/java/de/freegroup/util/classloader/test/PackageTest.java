/*
 * SAPMarkets Copyright (c) 2001
 * All rights reserved
 *
 * @version $Id: PackageTest.java,v 1.1 2004/01/28 14:33:36 freegroup Exp $
 */

package de.freegroup.util.classloader.test;

import de.freegroup.util.classloader.*;

import java.io.*;
import java.lang.reflect.*;
import java.net.*;
import java.text.*;
import java.util.*;

//import junit.framework.*;

/**
 * Test class for the class loader.
 *
 * @created   26. April 2001
 */
public class PackageTest// extends TestCase
{
  /*
    public PackageTest( String name )
    {
       // super( name );
    }

     public void testLoadInterface()
        throws Exception
    {
        // Load interface
        assertNotNull( Class.forName( "com.sapmarkets.technology.classloader.test.IMyClass" ) );
    }

     public void testNoClassSources()
        throws Exception
    {
        ExtendedClassLoader extendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
        // System.out.println( "Classpath: " + extendedClassLoader.getClassPath() );

        assertNotNull( extendedClassLoader.loadClass( "com.sapmarkets.technology.classloader.test.IMyClass" ) );// demonstrate base class loader delegation

        try
        {
            Class loadedClass = extendedClassLoader.loadClass( "com.sapmarkets.technology.classloader.test.None" );
            throw new Exception( "Found class but shouldn't have found class!" );
        }
        catch( ClassNotFoundException exception )
        {
            // Everything ok
        }

        extendedClassLoader.appendClassSource( extendedClassLoader.suggestClassSource( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\classes\\com\\sapmarkets\\technology\\classloader\\test\\MyFirstInstClass.class" ) ) );
        extendedClassLoader.appendClassSource( extendedClassLoader.suggestClassSource( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\classes\\com\\sapmarkets\\technology\\classloader\\test\\MySecondInstClass.class" ) ) );
        extendedClassLoader.appendClassSource( extendedClassLoader.suggestClassSource( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\classes\\com\\sapmarkets\\technology\\classloader\\test\\MyFirstInstClass.class" ) ) );
        extendedClassLoader.appendClassSource( extendedClassLoader.suggestClassSource( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\classes\\com\\sapmarkets\\technology\\classloader\\test\\MySecondInstClass.class" ) ) );
        extendedClassLoader.appendClassSource( extendedClassLoader.suggestClassSource( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\classes" ) ) );
        extendedClassLoader.appendClassSource( extendedClassLoader.suggestClassSource( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\classes" ) ) );
        extendedClassLoader.appendClassSource( extendedClassLoader.suggestClassSource( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\java\\com\\sapmarkets\\technology\\classloader\\test\\MyFirstInstClass.java" ) ) );
        extendedClassLoader.appendClassSource( extendedClassLoader.suggestClassSource( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\java\\com\\sapmarkets\\technology\\classloader\\test\\MySecondInstClass.java" ) ) );
        extendedClassLoader.appendClassSource( extendedClassLoader.suggestClassSource( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\java\\com\\sapmarkets\\technology\\classloader\\test\\MyFirstInstClass.java" ) ) );
        extendedClassLoader.appendClassSource( extendedClassLoader.suggestClassSource( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\java\\com\\sapmarkets\\technology\\classloader\\test\\MySecondInstClass.java" ) ) );
        extendedClassLoader.appendClassSource( extendedClassLoader.suggestClassSource( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\java" ) ) );
        extendedClassLoader.appendClassSource( extendedClassLoader.suggestClassSource( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\java" ) ) );
        extendedClassLoader.appendClassSource( extendedClassLoader.suggestClassSource( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\lib\\ClassLoaderTestV1.jar" ) ) );
        extendedClassLoader.appendClassSource( extendedClassLoader.suggestClassSource( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\lib\\ClassLoaderTestV2.jar" ) ) );
        extendedClassLoader.appendClassSource( extendedClassLoader.suggestClassSource( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\lib" ) ) );
        extendedClassLoader.appendClassSource( extendedClassLoader.suggestClassSource( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\lib" ) ) );
        // System.out.println( "Classpath: " + extendedClassLoader.getClassPath() );

        try
        {
            Class loadedClass = extendedClassLoader.loadClass( "com.sapmarkets.technology.classloader.test.None" );
            throw new Exception( "Found class but shouldn't have found class!" );
        }
        catch( ClassNotFoundException exception )
        {
            // Everything ok
        }
    }


        public void testClassesFromClassFile()
        throws Exception
    {
        {// Load classes from class directory
            ExtendedClassLoader v1ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v1ExtendedClassLoader.appendClassSource( new ClassFile( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\classes\\com\\sapmarkets\\technology\\classloader\\test\\MyFirstInstClass.class" ) ) );
            v1ExtendedClassLoader.appendClassSource( new ClassFile( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\classes\\com\\sapmarkets\\technology\\classloader\\test\\MySecondInstClass.class" ) ) );// Demonstrate classpath ordering
            v1ExtendedClassLoader.appendClassSource( new ClassFile( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\classes\\com\\sapmarkets\\technology\\classloader\\test\\MyFirstInstClass.class" ) ) );
            v1ExtendedClassLoader.appendClassSource( new ClassFile( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\classes\\com\\sapmarkets\\technology\\classloader\\test\\MySecondInstClass.class" ) ) );// Demonstrate classpath ordering
            Class v1FirstLoadedClass = v1ExtendedClassLoader.loadClass( "com.sapmarkets.technology.classloader.test.MyFirstInstClass" );
            {
                Object v1FirstInstClass = v1FirstLoadedClass.newInstance();
                Method v1FirstMethod = v1FirstLoadedClass.getMethod( "getVersion", null );
                assert( ( ( Integer )v1FirstMethod.invoke( v1FirstInstClass, null ) ).intValue() == 1 );
            }
            {
                IMyClass v1FirstInstClass = ( IMyClass )v1FirstLoadedClass.newInstance();
                assert( v1FirstInstClass.getVersion() == 1 );
            }
            // System.out.println( "Classpath: " + v1ExtendedClassLoader.getClassPath() );
        }
        {
            ExtendedClassLoader v2ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v2ExtendedClassLoader.appendClassSource( new ClassFile( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\classes\\com\\sapmarkets\\technology\\classloader\\test\\MyFirstInstClass.class" ) ) );
            v2ExtendedClassLoader.appendClassSource( new ClassFile( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\classes\\com\\sapmarkets\\technology\\classloader\\test\\MySecondInstClass.class" ) ) );// Demonstrate classpath ordering
            v2ExtendedClassLoader.appendClassSource( new ClassFile( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\classes\\com\\sapmarkets\\technology\\classloader\\test\\MyFirstInstClass.class" ) ) );
            v2ExtendedClassLoader.appendClassSource( new ClassFile( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\classes\\com\\sapmarkets\\technology\\classloader\\test\\MySecondInstClass.class" ) ) );// Demonstrate classpath ordering
            Class v2FirstLoadedClass = v2ExtendedClassLoader.loadClass( "com.sapmarkets.technology.classloader.test.MyFirstInstClass" );
            {
                Object v2FirstInstClass = v2FirstLoadedClass.newInstance();
                Method v2FirstMethod = v2FirstLoadedClass.getMethod( "getVersion", null );
                assert( ( ( Integer )v2FirstMethod.invoke( v2FirstInstClass, null ) ).intValue() == 2 );
            }
            {
                IMyClass v2FirstInstClass = ( IMyClass )v2FirstLoadedClass.newInstance();
                assert( v2FirstInstClass.getVersion() == 2 );
            }
            // System.out.println( "Classpath: " + v2ExtendedClassLoader.getClassPath() );
        }
    }

    public void testClassesFromClassDirectory()
        throws Exception
    {
        {// Load classes from class directory
            ExtendedClassLoader v1ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v1ExtendedClassLoader.appendClassSource( new ClassDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\classes" ) ) );
            v1ExtendedClassLoader.appendClassSource( new ClassDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\classes" ) ) );// Demonstrate classpath ordering
            Class v1FirstLoadedClass = v1ExtendedClassLoader.loadClass( "com.sapmarkets.technology.classloader.test.MyFirstInstClass" );
            {
                Object v1FirstInstClass = v1FirstLoadedClass.newInstance();
                Method v1FirstMethod = v1FirstLoadedClass.getMethod( "getVersion", null );
                assert( ( ( Integer )v1FirstMethod.invoke( v1FirstInstClass, null ) ).intValue() == 1 );
            }
            {
                IMyClass v1FirstInstClass = ( IMyClass )v1FirstLoadedClass.newInstance();
                assert( v1FirstInstClass.getVersion() == 1 );
            }
            // System.out.println( "Classpath: " + v1ExtendedClassLoader.getClassPath() );
        }
        {
            ExtendedClassLoader v2ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v2ExtendedClassLoader.appendClassSource( new ClassDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\classes" ) ) );
            v2ExtendedClassLoader.appendClassSource( new ClassDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\classes" ) ) );// Demonstrate classpath ordering
            Class v2FirstLoadedClass = v2ExtendedClassLoader.loadClass( "com.sapmarkets.technology.classloader.test.MyFirstInstClass" );
            {
                Object v2FirstInstClass = v2FirstLoadedClass.newInstance();
                Method v2FirstMethod = v2FirstLoadedClass.getMethod( "getVersion", null );
                assert( ( ( Integer )v2FirstMethod.invoke( v2FirstInstClass, null ) ).intValue() == 2 );
            }
            {
                IMyClass v2FirstInstClass = ( IMyClass )v2FirstLoadedClass.newInstance();
                assert( v2FirstInstClass.getVersion() == 2 );
            }
            // System.out.println( "Classpath: " + v2ExtendedClassLoader.getClassPath() );
        }
    }

 
         public void testClassesFromJavaFile()
        throws Exception
    {
        {// Load classes from java file
            ExtendedClassLoader v1ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v1ExtendedClassLoader.appendClassSource( new JavaFile( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\java\\com\\sapmarkets\\technology\\classloader\\test\\MyFirstInstClass.java" ), "java" ) );
            v1ExtendedClassLoader.appendClassSource( new JavaFile( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\java\\com\\sapmarkets\\technology\\classloader\\test\\MySecondInstClass.java" ), "java" ) );
            v1ExtendedClassLoader.appendClassSource( new JavaFile( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\java\\com\\sapmarkets\\technology\\classloader\\test\\MyFirstInstClass.java" ), "java" ) );// Demonstrate classpath ordering
            v1ExtendedClassLoader.appendClassSource( new JavaFile( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\java\\com\\sapmarkets\\technology\\classloader\\test\\MySecondInstClass.java" ), "java" ) );// Demonstrate classpath ordering
            Class v1FirstLoadedClass = v1ExtendedClassLoader.loadClass( "com.sapmarkets.technology.classloader.test.MyFirstInstClass" );
            {
                Object v1FirstInstClass = v1FirstLoadedClass.newInstance();
                Method v1FirstMethod = v1FirstLoadedClass.getMethod( "getVersion", null );
                assert( ( ( Integer )v1FirstMethod.invoke( v1FirstInstClass, null ) ).intValue() == 1 );
            }
            {
                IMyClass v1FirstInstClass = ( IMyClass )v1FirstLoadedClass.newInstance();
                assert( v1FirstInstClass.getVersion() == 1 );
            }
            // System.out.println( "Classpath: " + v1ExtendedClassLoader.getClassPath() );
        }
        {
            ExtendedClassLoader v2ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v2ExtendedClassLoader.appendClassSource( new JavaFile( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\java\\com\\sapmarkets\\technology\\classloader\\test\\MyFirstInstClass.java" ), "java" ) );
            v2ExtendedClassLoader.appendClassSource( new JavaFile( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\java\\com\\sapmarkets\\technology\\classloader\\test\\MySecondInstClass.java" ), "java" ) );
            v2ExtendedClassLoader.appendClassSource( new JavaFile( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\java\\com\\sapmarkets\\technology\\classloader\\test\\MyFirstInstClass.java" ), "java" ) );// Demonstrate classpath ordering
            v2ExtendedClassLoader.appendClassSource( new JavaFile( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\java\\com\\sapmarkets\\technology\\classloader\\test\\MySecondInstClass.java" ), "java" ) );// Demonstrate classpath ordering
            Class v2FirstLoadedClass = v2ExtendedClassLoader.loadClass( "com.sapmarkets.technology.classloader.test.MyFirstInstClass" );
            {
                Object v2FirstInstClass = v2FirstLoadedClass.newInstance();
                Method v2FirstMethod = v2FirstLoadedClass.getMethod( "getVersion", null );
                assert( ( ( Integer )v2FirstMethod.invoke( v2FirstInstClass, null ) ).intValue() == 2 );
            }
            {
                IMyClass v2FirstInstClass = ( IMyClass )v2FirstLoadedClass.newInstance();
                assert( v2FirstInstClass.getVersion() == 2 );
            }
            // System.out.println( "Classpath: " + v2ExtendedClassLoader.getClassPath() );
        }

        // Delete compiled class files - assert their existence
        assert( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\java\\com\\sapmarkets\\technology\\classloader\\test\\MyFirstInstClass.class" ).delete() );
        assert( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\java\\com\\sapmarkets\\technology\\classloader\\test\\MySecondInstClass.class" ).delete() );
        assert( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\java\\com\\sapmarkets\\technology\\classloader\\test\\MyFirstInstClass.class" ).delete() );
        assert( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\java\\com\\sapmarkets\\technology\\classloader\\test\\MySecondInstClass.class" ).delete() );
        assert( new File( System.getProperty( "user.dir" ) + "\\java\\com\\sapmarkets\\technology\\classloader\\test\\IMyClass.class" ).delete() );
    }

     public void testClassesFromJavaDirectory()
        throws Exception
    {
        {// Load classes from java directory
            ExtendedClassLoader v1ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v1ExtendedClassLoader.appendClassSource( new JavaDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\java" ), "java" ) );
            v1ExtendedClassLoader.appendClassSource( new JavaDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\java" ), "java" ) );// Demonstrate classpath ordering
            Class v1FirstLoadedClass = v1ExtendedClassLoader.loadClass( "com.sapmarkets.technology.classloader.test.MyFirstInstClass" );
            {
                Object v1FirstInstClass = v1FirstLoadedClass.newInstance();
                Method v1FirstMethod = v1FirstLoadedClass.getMethod( "getVersion", null );
                assert( ( ( Integer )v1FirstMethod.invoke( v1FirstInstClass, null ) ).intValue() == 1 );
            }
            {
                IMyClass v1FirstInstClass = ( IMyClass )v1FirstLoadedClass.newInstance();
                assert( v1FirstInstClass.getVersion() == 1 );
            }
            // System.out.println( "Classpath: " + v1ExtendedClassLoader.getClassPath() );
        }
        {
            ExtendedClassLoader v2ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v2ExtendedClassLoader.appendClassSource( new JavaDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\java" ), "java" ) );
            v2ExtendedClassLoader.appendClassSource( new JavaDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\java" ), "java" ) );// Demonstrate classpath ordering
            Class v2FirstLoadedClass = v2ExtendedClassLoader.loadClass( "com.sapmarkets.technology.classloader.test.MyFirstInstClass" );
            {
                Object v2FirstInstClass = v2FirstLoadedClass.newInstance();
                Method v2FirstMethod = v2FirstLoadedClass.getMethod( "getVersion", null );
                assert( ( ( Integer )v2FirstMethod.invoke( v2FirstInstClass, null ) ).intValue() == 2 );
            }
            {
                IMyClass v2FirstInstClass = ( IMyClass )v2FirstLoadedClass.newInstance();
                assert( v2FirstInstClass.getVersion() == 2 );
            }
            // System.out.println( "Classpath: " + v2ExtendedClassLoader.getClassPath() );
        }

        // Delete compiled class files - assert their existence
        assert( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\java\\com\\sapmarkets\\technology\\classloader\\test\\MyFirstInstClass.class" ).delete() );
        assert( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\java\\com\\sapmarkets\\technology\\classloader\\test\\MySecondInstClass.class" ).delete() );
        assert( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\java\\com\\sapmarkets\\technology\\classloader\\test\\MyFirstInstClass.class" ).delete() );
        assert( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\java\\com\\sapmarkets\\technology\\classloader\\test\\MySecondInstClass.class" ).delete() );
        assert( new File( System.getProperty( "user.dir" ) + "\\java\\com\\sapmarkets\\technology\\classloader\\test\\IMyClass.class" ).delete() );
    }

     public void testClassesFromJARFile()
        throws Exception
    {
        {// Load classes from JAR file
            ExtendedClassLoader v1ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v1ExtendedClassLoader.appendClassSource( new JARFile( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\lib\\ClassLoaderTestV1.jar" ) ) );
            v1ExtendedClassLoader.appendClassSource( new JARFile( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\lib\\ClassLoaderTestV2.jar" ) ) );// Demonstrate classpath ordering
            Class v1FirstLoadedClass = v1ExtendedClassLoader.loadClass( "com.sapmarkets.technology.classloader.test.MyFirstInstClass" );
            {
                Object v1FirstInstClass = v1FirstLoadedClass.newInstance();
                Method v1FirstMethod = v1FirstLoadedClass.getMethod( "getVersion", null );
                assert( ( ( Integer )v1FirstMethod.invoke( v1FirstInstClass, null ) ).intValue() == 1 );
            }
            {
                IMyClass v1FirstInstClass = ( IMyClass )v1FirstLoadedClass.newInstance();
                assert( v1FirstInstClass.getVersion() == 1 );
            }
            // System.out.println( "Classpath: " + v1ExtendedClassLoader.getClassPath() );
        }
        {
            ExtendedClassLoader v2ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v2ExtendedClassLoader.appendClassSource( new JARFile( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\lib\\ClassLoaderTestV2.jar" ) ) );
            v2ExtendedClassLoader.appendClassSource( new JARFile( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\lib\\ClassLoaderTestV1.jar" ) ) );// Demonstrate classpath ordering
            Class v2FirstLoadedClass = v2ExtendedClassLoader.loadClass( "com.sapmarkets.technology.classloader.test.MyFirstInstClass" );
            {
                Object v2FirstInstClass = v2FirstLoadedClass.newInstance();
                Method v2FirstMethod = v2FirstLoadedClass.getMethod( "getVersion", null );
                assert( ( ( Integer )v2FirstMethod.invoke( v2FirstInstClass, null ) ).intValue() == 2 );
            }
            {
                IMyClass v2FirstInstClass = ( IMyClass )v2FirstLoadedClass.newInstance();
                assert( v2FirstInstClass.getVersion() == 2 );
            }
            // System.out.println( "Classpath: " + v2ExtendedClassLoader.getClassPath() );
        }
    }

      public void testClassesFromJARDirectory()
        throws Exception
    {
        {// Load classes from JAR directory
            ExtendedClassLoader v1ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v1ExtendedClassLoader.appendClassSource( new JARDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\lib" ) ) );
            v1ExtendedClassLoader.appendClassSource( new JARDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\lib" ) ) );// Demonstrate classpath ordering
            Class v1FirstLoadedClass = v1ExtendedClassLoader.loadClass( "com.sapmarkets.technology.classloader.test.MyFirstInstClass" );
            {
                Object v1FirstInstClass = v1FirstLoadedClass.newInstance();
                Method v1FirstMethod = v1FirstLoadedClass.getMethod( "getVersion", null );
                assert( ( ( Integer )v1FirstMethod.invoke( v1FirstInstClass, null ) ).intValue() == 1 );
            }
            {
                IMyClass v1FirstInstClass = ( IMyClass )v1FirstLoadedClass.newInstance();
                assert( v1FirstInstClass.getVersion() == 1 );
            }
            // System.out.println( "Classpath: " + v1ExtendedClassLoader.getClassPath() );
        }
        {
            ExtendedClassLoader v2ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v2ExtendedClassLoader.appendClassSource( new JARDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\lib" ) ) );
            v2ExtendedClassLoader.appendClassSource( new JARDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\lib" ) ) );// Demonstrate classpath ordering
            Class v2FirstLoadedClass = v2ExtendedClassLoader.loadClass( "com.sapmarkets.technology.classloader.test.MyFirstInstClass" );
            {
                Object v2FirstInstClass = v2FirstLoadedClass.newInstance();
                Method v2FirstMethod = v2FirstLoadedClass.getMethod( "getVersion", null );
                assert( ( ( Integer )v2FirstMethod.invoke( v2FirstInstClass, null ) ).intValue() == 2 );
            }
            {
                IMyClass v2FirstInstClass = ( IMyClass )v2FirstLoadedClass.newInstance();
                assert( v2FirstInstClass.getVersion() == 2 );
            }
            // System.out.println( "Classpath: " + v2ExtendedClassLoader.getClassPath() );
        }
    }

     public void testLibrariesFromLibraryFile()
        throws Exception
    {
        {// Load libraries from library file
            ExtendedClassLoader v1ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v1ExtendedClassLoader.appendLibrarySource( new LibraryFile( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\lib\\UUID.dll" ) ) );
            v1ExtendedClassLoader.appendLibrarySource( new LibraryFile( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\lib\\UUID.dll" ) ) );// Demonstrate librarypath ordering
            assertEquals( v1ExtendedClassLoader.findLibrary( "UUID" ), System.getProperty( "user.dir" ) + "\\test\\v1\\lib\\UUID.dll" );
            // System.out.println( "Librarypath: " + v1ExtendedClassLoader.getLibraryPath() );
        }
        {
            ExtendedClassLoader v2ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v2ExtendedClassLoader.appendLibrarySource( new LibraryFile( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\lib\\UUID.dll" ) ) );
            v2ExtendedClassLoader.appendLibrarySource( new LibraryFile( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\lib\\UUID.dll" ) ) );// Demonstrate librarypath ordering
            assertEquals( v2ExtendedClassLoader.findLibrary( "UUID" ), System.getProperty( "user.dir" ) + "\\test\\v2\\lib\\UUID.dll" );
            // System.out.println( "Librarypath: " + v2ExtendedClassLoader.getLibraryPath() );
        }
    }

     public void testLibrariesFromLibraryDirectory()
        throws Exception
    {
        {// Load libraries from library directory
            ExtendedClassLoader v1ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v1ExtendedClassLoader.appendLibrarySource( new LibraryDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\lib" ) ) );
            v1ExtendedClassLoader.appendLibrarySource( new LibraryDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\lib" ) ) );// Demonstrate librarypath ordering
            assertEquals( v1ExtendedClassLoader.findLibrary( "UUID" ), System.getProperty( "user.dir" ) + "\\test\\v1\\lib\\UUID.dll" );
            // System.out.println( "Librarypath: " + v1ExtendedClassLoader.getLibraryPath() );
        }
        {
            ExtendedClassLoader v2ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v2ExtendedClassLoader.appendLibrarySource( new LibraryDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\lib" ) ) );
            v2ExtendedClassLoader.appendLibrarySource( new LibraryDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\lib" ) ) );// Demonstrate librarypath ordering
            assertEquals( v2ExtendedClassLoader.findLibrary( "UUID" ), System.getProperty( "user.dir" ) + "\\test\\v2\\lib\\UUID.dll" );
            // System.out.println( "Librarypath: " + v2ExtendedClassLoader.getLibraryPath() );
        }
    }

     public void testResourcesFromResourceFile()
        throws Exception
    {
        {// Load resources from resource file
            ExtendedClassLoader v1ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v1ExtendedClassLoader.appendResourceSource( new ResourceFile( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\resources\\resources.properties" ) ) );
            v1ExtendedClassLoader.appendResourceSource( new ResourceFile( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\resources\\resources.properties" ) ) );// Demonstrate resourcespath ordering
            ResourceBundle resourceBundle = ResourceBundle.getBundle( "resources", Locale.getDefault(), v1ExtendedClassLoader );
            assertEquals( resourceBundle.getString( "version" ), "v1" );
            Enumeration resourceLocations = v1ExtendedClassLoader.getResources( "resources.properties" );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v1" ) != -1 );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v2" ) != -1 );
            // System.out.println( "Resourcepath: " + v1ExtendedClassLoader.getResourcePath() );
        }
        {
            ExtendedClassLoader v2ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v2ExtendedClassLoader.appendResourceSource( new ResourceFile( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\resources\\resources.properties" ) ) );
            v2ExtendedClassLoader.appendResourceSource( new ResourceFile( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\resources\\resources.properties" ) ) );// Demonstrate resourcespath ordering
            ResourceBundle resourceBundle = ResourceBundle.getBundle( "resources", Locale.getDefault(), v2ExtendedClassLoader );
            assertEquals( resourceBundle.getString( "version" ), "v2" );
            Enumeration resourceLocations = v2ExtendedClassLoader.getResources( "resources.properties" );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v2" ) != -1 );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v1" ) != -1 );
            // System.out.println( "Resourcepath: " + v2ExtendedClassLoader.getResourcePath() );
        }
    }

    public void testResourcesFromResourceDirectory()
        throws Exception
    {
        {// Load resources from resource directory
            ExtendedClassLoader v1ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v1ExtendedClassLoader.appendResourceSource( new ResourceDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\resources" ) ) );
            v1ExtendedClassLoader.appendResourceSource( new ResourceDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\resources" ) ) );// Demonstrate resourcespath ordering
            ResourceBundle resourceBundle = ResourceBundle.getBundle( "resources", Locale.getDefault(), v1ExtendedClassLoader );
            assertEquals( resourceBundle.getString( "version" ), "v1" );
            Enumeration resourceLocations = v1ExtendedClassLoader.getResources( "resources.properties" );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v1" ) != -1 );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v2" ) != -1 );
            // System.out.println( "Resourcepath: " + v1ExtendedClassLoader.getResourcePath() );
        }
        {
            ExtendedClassLoader v2ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v2ExtendedClassLoader.appendResourceSource( new ResourceDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\resources" ) ) );
            v2ExtendedClassLoader.appendResourceSource( new ResourceDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\resources" ) ) );// Demonstrate resourcespath ordering
            ResourceBundle resourceBundle = ResourceBundle.getBundle( "resources", Locale.getDefault(), v2ExtendedClassLoader );
            assertEquals( resourceBundle.getString( "version" ), "v2" );
            Enumeration resourceLocations = v2ExtendedClassLoader.getResources( "resources.properties" );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v2" ) != -1 );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v1" ) != -1 );
            // System.out.println( "Resourcepath: " + v2ExtendedClassLoader.getResourcePath() );
        }
    }

    public void testResourcesFromJavaDirectory()
        throws Exception
    {
        {// Load resources from resource directory
            ExtendedClassLoader v1ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v1ExtendedClassLoader.appendClassSource( new JavaDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\java" ) ) );
            v1ExtendedClassLoader.appendClassSource( new JavaDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\java" ) ) );// Demonstrate resourcespath ordering
            ResourceBundle resourceBundle = ResourceBundle.getBundle( "resources", Locale.getDefault(), v1ExtendedClassLoader );
            assertEquals( resourceBundle.getString( "version" ), "v1" );
            Enumeration resourceLocations = v1ExtendedClassLoader.getResources( "resources.properties" );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v1" ) != -1 );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v2" ) != -1 );
            // System.out.println( "Resourcepath: " + v1ExtendedClassLoader.getResourcePath() );
        }
        {
            ExtendedClassLoader v2ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v2ExtendedClassLoader.appendClassSource( new JavaDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\java" ) ) );
            v2ExtendedClassLoader.appendClassSource( new JavaDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\java" ) ) );// Demonstrate resourcespath ordering
            ResourceBundle resourceBundle = ResourceBundle.getBundle( "resources", Locale.getDefault(), v2ExtendedClassLoader );
            assertEquals( resourceBundle.getString( "version" ), "v2" );
            Enumeration resourceLocations = v2ExtendedClassLoader.getResources( "resources.properties" );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v2" ) != -1 );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v1" ) != -1 );
            // System.out.println( "Resourcepath: " + v2ExtendedClassLoader.getResourcePath() );
        }
    }

     public void testResourcesFromClassDirectory()
        throws Exception
    {
        {// Load resources from resource directory
            ExtendedClassLoader v1ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v1ExtendedClassLoader.appendClassSource( new ClassDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\classes" ) ) );
            v1ExtendedClassLoader.appendClassSource( new ClassDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\classes" ) ) );// Demonstrate resourcespath ordering
            ResourceBundle resourceBundle = ResourceBundle.getBundle( "resources", Locale.getDefault(), v1ExtendedClassLoader );
            assertEquals( resourceBundle.getString( "version" ), "v1" );
            Enumeration resourceLocations = v1ExtendedClassLoader.getResources( "resources.properties" );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v1" ) != -1 );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v2" ) != -1 );
            // System.out.println( "Resourcepath: " + v1ExtendedClassLoader.getResourcePath() );
        }
        {
            ExtendedClassLoader v2ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v2ExtendedClassLoader.appendClassSource( new ClassDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\classes" ) ) );
            v2ExtendedClassLoader.appendClassSource( new ClassDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\classes" ) ) );// Demonstrate resourcespath ordering
            ResourceBundle resourceBundle = ResourceBundle.getBundle( "resources", Locale.getDefault(), v2ExtendedClassLoader );
            assertEquals( resourceBundle.getString( "version" ), "v2" );
            Enumeration resourceLocations = v2ExtendedClassLoader.getResources( "resources.properties" );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v2" ) != -1 );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v1" ) != -1 );
            // System.out.println( "Resourcepath: " + v2ExtendedClassLoader.getResourcePath() );
        }
    }

    public void testResourcesFromJARFile()
        throws Exception
    {
        {// Load resources from resource file
            ExtendedClassLoader v1ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v1ExtendedClassLoader.appendClassSource( new JARFile( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\lib\\ClassLoaderTestV1.jar" ) ) );
            v1ExtendedClassLoader.appendClassSource( new JARFile( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\lib\\ClassLoaderTestV2.jar" ) ) );// Demonstrate resourcespath ordering
            ResourceBundle resourceBundle = ResourceBundle.getBundle( "resources", Locale.getDefault(), v1ExtendedClassLoader );
            assertEquals( resourceBundle.getString( "version" ), "v1" );
            Enumeration resourceLocations = v1ExtendedClassLoader.getResources( "resources.properties" );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v1" ) != -1 );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v2" ) != -1 );
            // System.out.println( "Resourcepath: " + v1ExtendedClassLoader.getResourcePath() );
        }
        {
            ExtendedClassLoader v2ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v2ExtendedClassLoader.appendResourceSource( new JARFile( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\lib\\ClassLoaderTestV2.jar" ) ) );
            v2ExtendedClassLoader.appendResourceSource( new JARFile( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\lib\\ClassLoaderTestV1.jar" ) ) );// Demonstrate resourcespath ordering
            ResourceBundle resourceBundle = ResourceBundle.getBundle( "resources", Locale.getDefault(), v2ExtendedClassLoader );
            assertEquals( resourceBundle.getString( "version" ), "v2" );
            Enumeration resourceLocations = v2ExtendedClassLoader.getResources( "resources.properties" );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v2" ) != -1 );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v1" ) != -1 );
            // System.out.println( "Resourcepath: " + v2ExtendedClassLoader.getResourcePath() );
        }
    }

     public void testResourcesFromJARDirectory()
        throws Exception
    {
        {// Load resources from resource directory
            ExtendedClassLoader v1ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v1ExtendedClassLoader.appendClassSource( new JARDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\lib" ) ) );
            v1ExtendedClassLoader.appendClassSource( new JARDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\lib" ) ) );// Demonstrate resourcespath ordering
            ResourceBundle resourceBundle = ResourceBundle.getBundle( "resources", Locale.getDefault(), v1ExtendedClassLoader );
            assertEquals( resourceBundle.getString( "version" ), "v1" );
            Enumeration resourceLocations = v1ExtendedClassLoader.getResources( "resources.properties" );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v1" ) != -1 );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v2" ) != -1 );
            // System.out.println( "Resourcepath: " + v1ExtendedClassLoader.getResourcePath() );
        }
        {
            ExtendedClassLoader v2ExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
            v2ExtendedClassLoader.appendResourceSource( new JARDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\lib" ) ) );
            v2ExtendedClassLoader.appendResourceSource( new JARDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\lib" ) ) );// Demonstrate resourcespath ordering
            ResourceBundle resourceBundle = ResourceBundle.getBundle( "resources", Locale.getDefault(), v2ExtendedClassLoader );
            assertEquals( resourceBundle.getString( "version" ), "v2" );
            Enumeration resourceLocations = v2ExtendedClassLoader.getResources( "resources.properties" );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v2" ) != -1 );
            assert( ( ( URL )resourceLocations.nextElement() ).toString().indexOf( "v1" ) != -1 );
            // System.out.println( "Resourcepath: " + v2ExtendedClassLoader.getResourcePath() );
        }
    }

     public void testPriorityExtendedClassLoader()
        throws Exception
    {
        // Construct extended class loader as parent class loader
        ExtendedClassLoader parentExtendedClassLoader = new ExtendedClassLoader( PackageTest.class.getClassLoader() );
        parentExtendedClassLoader.appendClassSource( new JARDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\lib" ) ) );
        parentExtendedClassLoader.appendResourceSource( new ResourceDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v1\\resources" ) ) );

        // Construct extended class loader as child class loader
        ExtendedClassLoader childExtendedClassLoader = new ExtendedClassLoader( parentExtendedClassLoader );
        childExtendedClassLoader.appendClassSource( new JARDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\lib" ) ) );
        childExtendedClassLoader.appendResourceSource( new ResourceDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\resources" ) ) );

        // Construct prioritizing extended class loader as child class loader
        ExtendedClassLoader childPriorityExtendedClassLoader = new PriorityExtendedClassLoader( parentExtendedClassLoader );
        childPriorityExtendedClassLoader.appendClassSource( new JARDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\lib" ) ) );
        childPriorityExtendedClassLoader.appendResourceSource( new ResourceDirectory( new File( System.getProperty( "user.dir" ) + "\\test\\v2\\resources" ) ) );
        {
            Class v1FirstLoadedClass = childExtendedClassLoader.loadClass( "com.sapmarkets.technology.classloader.test.MyFirstInstClass" );
            {
                Object v1FirstInstClass = v1FirstLoadedClass.newInstance();
                Method v1FirstMethod = v1FirstLoadedClass.getMethod( "getVersion", null );
                assert( ( ( Integer )v1FirstMethod.invoke( v1FirstInstClass, null ) ).intValue() == 1 );
            }
            {
                IMyClass v1FirstInstClass = ( IMyClass )v1FirstLoadedClass.newInstance();
                assert( v1FirstInstClass.getVersion() == 1 );
            }
            ResourceBundle resourceBundle = ResourceBundle.getBundle( "resources", Locale.getDefault(), childExtendedClassLoader );
            assertEquals( resourceBundle.getString( "version" ), "v1" );
            // System.out.println( "Classpath: " + childExtendedClassLoader.getClassPath() );
            // System.out.println( "Resourcepath: " + childExtendedClassLoader.getResourcePath() );
        }
        {
            Class v2FirstLoadedClass = childPriorityExtendedClassLoader.loadClass( "com.sapmarkets.technology.classloader.test.MyFirstInstClass" );
            {
                Object v2FirstInstClass = v2FirstLoadedClass.newInstance();
                Method v2FirstMethod = v2FirstLoadedClass.getMethod( "getVersion", null );
                assert( ( ( Integer )v2FirstMethod.invoke( v2FirstInstClass, null ) ).intValue() == 2 );
            }
            {
                IMyClass v2FirstInstClass = ( IMyClass )v2FirstLoadedClass.newInstance();
                assert( v2FirstInstClass.getVersion() == 2 );
            }
            ResourceBundle resourceBundle = ResourceBundle.getBundle( "resources", Locale.getDefault(), childPriorityExtendedClassLoader );
            assertEquals( resourceBundle.getString( "version" ), "v2" );
            // System.out.println( "Classpath: " + childPriorityExtendedClassLoader.getClassPath() );
            // System.out.println( "Resourcepath: " + childPriorityExtendedClassLoader.getResourcePath() );
        }
    }
    protected void setUp()
    {
        ;
    }

     protected void tearDown()
    {
        ;
    }

    public static void main( String[] args )
    {
       // junit.textui.TestRunner.run( new TestSuite( PackageTest.class ) );
    }
    */
}
