/*
 * Created on Nov 28, 2003
 *
 * To change the template for this generated file go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package de.freegroup.util.ant;

import java.io.*;
import java.util.*;

import org.apache.tools.ant.*;
import org.apache.tools.ant.input.DefaultInputHandler;
import org.apache.tools.ant.input.InputHandler;
import org.apache.tools.ant.util.JavaEnvUtils;

import de.freegroup.digitalsimulator.Trace;

// Referenced classes of package org.apache.tools.ant:
//            BuildException, Project, DemuxOutputStream, BuildListener, 
//            BuildLogger, DefaultLogger, Target, Diagnostics, 
//            ProjectHelper

public class AntWrapper
{

		private static void printMessage(Throwable t)
		{
			String message = t.getMessage();
			if (message != null)
				Trace.warning(message);
		}

    public static void start(String args[])
    {
      try
      {
				ClassLoader coreLoader = null;
				AntWrapper m = new AntWrapper(args);
				m.runBuild(coreLoader);
		//		System.exit(0);
      }
      catch(BuildException be)
      {
          printMessage(be);
      }
      catch(Throwable exc)
      {
          exc.printStackTrace();
          printMessage(exc);
      }
   }


    protected AntWrapper(String args[])   throws BuildException
    {
        msgOutputLevel = 2;
        targets = new Vector(5);
        definedProps = new Properties();
        listeners = new Vector(5);
        propertyFiles = new Vector(5);
        loggerClassname = null;
        inputHandlerClassname = null;
        emacsMode = false;
        readyToRun = false;
        projectHelp = false;
        String searchForThis = null;
        PrintStream logTo = null;
        for(int i = 0; i < args.length; i++)
        {
            String arg = args[i];
            if(arg.equals("-help"))
            {
                printUsage();
                return;
            }
            if(arg.equals("-version"))
            {
                printVersion();
                return;
            }
            if(arg.equals("-diagnostics"))
            {
                Diagnostics.doReport(System.out);
                return;
            }
            if(arg.equals("-quiet") || arg.equals("-q"))
                msgOutputLevel = 1;
            else
            if(arg.equals("-verbose") || arg.equals("-v"))
            {
                printVersion();
                msgOutputLevel = 3;
            } else
            if(arg.equals("-debug"))
            {
                printVersion();
                msgOutputLevel = 4;
            } else
            if(arg.equals("-logfile") || arg.equals("-l"))
                try
                {
                    File logFile = new File(args[i + 1]);
                    i++;
                    logTo = new PrintStream(new FileOutputStream(logFile));
                    isLogFileUsed = true;
                }
                catch(IOException ioexception)
                {
                    String msg = "Cannot write on the specified log file. Make sure the path exists and you have write permissions.";
                    Trace.info(msg);
                    return;
                }
                catch(ArrayIndexOutOfBoundsException arrayindexoutofboundsexception5)
                {
                    String msg = "You must specify a log file when using the -log argument";
                    Trace.info(msg);
                    return;
                }
            else
            if(arg.equals("-buildfile") || arg.equals("-file") || arg.equals("-f"))
                try
                {
                    buildFile = new File(args[i + 1]);
                    i++;
                }
                catch(ArrayIndexOutOfBoundsException arrayindexoutofboundsexception)
                {
                    String msg = "You must specify a buildfile when using the -buildfile argument";
                    Trace.info(msg);
                    return;
                }
            else
            if(arg.equals("-listener"))
                try
                {
                    listeners.addElement(args[i + 1]);
                    i++;
                }
                catch(ArrayIndexOutOfBoundsException arrayindexoutofboundsexception1)
                {
                    String msg = "You must specify a classname when using the -listener argument";
                    Trace.info(msg);
                    return;
                }
            else
            if(arg.startsWith("-D"))
            {
                String name = arg.substring(2, arg.length());
                String value = null;
                int posEq = name.indexOf("=");
                if(posEq > 0)
                {
                    value = name.substring(posEq + 1);
                    name = name.substring(0, posEq);
                } else
                if(i < args.length - 1)
                    value = args[++i];
                definedProps.put(name, value);
            } else
            if(arg.equals("-logger"))
            {
                if(loggerClassname != null)
                {
                    Trace.info("Only one logger class may  be specified.");
                    return;
                }
                try
                {
                    loggerClassname = args[++i];
                }
                catch(ArrayIndexOutOfBoundsException arrayindexoutofboundsexception2)
                {
                    Trace.info("You must specify a classname when using the -logger argument");
                    return;
                }
            } else
            if(arg.equals("-inputhandler"))
            {
                if(inputHandlerClassname != null)
                {
                    Trace.info("Only one input handler class may be specified.");
                    return;
                }
                try
                {
                    inputHandlerClassname = args[++i];
                }
                catch(ArrayIndexOutOfBoundsException arrayindexoutofboundsexception3)
                {
                    Trace.info("You must specify a classname when using the -inputhandler argument");
                    return;
                }
            } else
            if(arg.equals("-emacs"))
                emacsMode = true;
            else
            if(arg.equals("-projecthelp"))
                projectHelp = true;
            else
            if(arg.equals("-find"))
            {
                if(i < args.length - 1)
                    searchForThis = args[++i];
                else
                    searchForThis = "build.xml";
            } else
            if(arg.startsWith("-propertyfile"))
            {
                try
                {
                    propertyFiles.addElement(args[i + 1]);
                    i++;
                }
                catch(ArrayIndexOutOfBoundsException arrayindexoutofboundsexception4)
                {
                    String msg = "You must specify a property filename when using the -propertyfile argument";
                    Trace.info(msg);
                    return;
                }
            } else
            {
                if(arg.startsWith("-"))
                {
                    String msg = "Unknown argument: " + arg;
                    Trace.info(msg);
                    printUsage();
                    return;
                }
                targets.addElement(arg);
            }
        }

        if(buildFile == null)
            if(searchForThis != null)
                buildFile = findBuildFile(System.getProperty("user.dir"), searchForThis);
            else
                buildFile = new File("build.xml");
        if(!buildFile.exists())
        {
            Trace.info("Buildfile: " + buildFile + " does not exist!");
            throw new BuildException("Build failed");
        }
        if(buildFile.isDirectory())
        {
            Trace.info("What? Buildfile: " + buildFile + " is a dir!");
            throw new BuildException("Build failed");
        }
        for(int propertyFileIndex = 0; propertyFileIndex < propertyFiles.size(); propertyFileIndex++)
        {
            String filename = (String)propertyFiles.elementAt(propertyFileIndex);
            Properties props = new Properties();
            FileInputStream fis = null;
            try
            {
                fis = new FileInputStream(filename);
                props.load(fis);
            }
            catch(IOException e)
            {
                Trace.info("Could not load property file " + filename + ": " + e.getMessage());
            }
            finally
            {
                if(fis != null)
                    try
                    {
                        fis.close();
                    }
                    catch(IOException ioexception1) { }
            }
            for(Enumeration propertyNames = props.propertyNames(); propertyNames.hasMoreElements();)
            {
                String name = (String)propertyNames.nextElement();
                if(definedProps.getProperty(name) == null)
                    definedProps.put(name, props.getProperty(name));
            }

        }

        if(msgOutputLevel >= 2)
            Trace.info("Buildfile: " + buildFile);
        if(logTo != null)
        {
            out = err = logTo;
            System.setOut(out);
            System.setErr(out);
        }
        readyToRun = true;
    }

    private File getParentFile(File file)
    {
        String filename = file.getAbsolutePath();
        file = new File(filename);
        filename = file.getParent();
        if(filename != null && msgOutputLevel >= 3)
            Trace.info("Searching in " + filename);
        return filename != null ? new File(filename) : null;
    }

    private File findBuildFile(String start, String suffix)
        throws BuildException
    {
        if(msgOutputLevel >= 2)
            Trace.info("Searching for " + suffix + " ...");
        File parent = new File((new File(start)).getAbsolutePath());
        File file;
        for(file = new File(parent, suffix); !file.exists(); file = new File(parent, suffix))
        {
            parent = getParentFile(parent);
            if(parent == null)
                throw new BuildException("Could not locate a build file!");
        }

        return file;
    }

    private void runBuild(ClassLoader coreLoader)  throws BuildException
    {
        if(!readyToRun)
            return;
        Project project = new Project();
        project.setCoreLoader(coreLoader);
        Throwable error = null;
        try
        {
            addBuildListeners(project);
            addInputHandler(project);
            PrintStream err = System.err;
            PrintStream out = System.out;
            SecurityManager oldsm = null;
            if(!JavaEnvUtils.isJavaVersion("1.0") && !JavaEnvUtils.isJavaVersion("1.1"))
                oldsm = System.getSecurityManager();
            try
            {
                System.setOut(new PrintStream(new DemuxOutputStream(project, false)));
                System.setErr(new PrintStream(new DemuxOutputStream(project, true)));
                if(!projectHelp)
                    project.fireBuildStarted();
                project.init();
                project.setUserProperty("ant.version", getAntVersion());
                String arg;
                String value;
                for(Enumeration e = definedProps.keys(); e.hasMoreElements(); project.setUserProperty(arg, value))
                {
                    arg = (String)e.nextElement();
                    value = (String)definedProps.get(arg);
                }

                project.setUserProperty("ant.file", buildFile.getAbsolutePath());
                ProjectHelper.configureProject(project, buildFile);
                if(projectHelp)
                {
                    printDescription(project);
                    printTargets(project, msgOutputLevel > 2);
                    return;
                }
                if(targets.size() == 0)
                    targets.addElement(project.getDefaultTarget());
                project.executeTargets(targets);
            }
            finally
            {
                if(oldsm != null)
                    System.setSecurityManager(oldsm);
                System.setOut(out);
                System.setErr(err);
            }
        }
        catch(RuntimeException exc)
        {
            error = exc;
            throw exc;
        }
        catch(Error err)
        {
            error = err;
            throw err;
        }
        finally
        {
            if(!projectHelp)
                project.fireBuildFinished(error);
        }
    }

    protected void addBuildListeners(Project project)
    {
        project.addBuildListener(createLogger());
        for(int i = 0; i < listeners.size(); i++)
        {
            String className = (String)listeners.elementAt(i);
            try
            {
                BuildListener listener = (BuildListener)Class.forName(className).newInstance();
                project.addBuildListener(listener);
            }
            catch(Throwable exc)
            {
                throw new BuildException("Unable to instantiate listener " + className, exc);
            }
        }

    }

    private void addInputHandler(Project project)
    {
        InputHandler handler = null;
        if(inputHandlerClassname == null)
            handler = new DefaultInputHandler();
        else
            try
            {
                handler = (InputHandler)Class.forName(inputHandlerClassname).newInstance();
            }
            catch(ClassCastException classcastexception)
            {
                String msg = "The specified input handler class " + inputHandlerClassname + " does not implement the InputHandler interface";
                throw new BuildException(msg);
            }
            catch(Exception e)
            {
                String msg = "Unable to instantiate specified input handler class " + inputHandlerClassname + " : " + e.getClass().getName();
                throw new BuildException(msg);
            }
        project.setInputHandler(handler);
    }

    private BuildLogger createLogger()
    {
        BuildLogger logger = null;
        if(loggerClassname != null)
            try
            {
                logger = (BuildLogger)Class.forName(loggerClassname).newInstance();
            }
            catch(ClassCastException classcastexception)
            {
                System.err.println("The specified logger class " + loggerClassname + " does not implement the BuildLogger interface");
                throw new RuntimeException();
            }
            catch(Exception e)
            {
                System.err.println("Unable to instantiate specified logger class " + loggerClassname + " : " + e.getClass().getName());
                throw new RuntimeException();
            }
        else
            logger = new DefaultLogger();
        logger.setMessageOutputLevel(msgOutputLevel);
        logger.setOutputPrintStream(out);
        logger.setErrorPrintStream(err);
        logger.setEmacsMode(emacsMode);
        return logger;
    }

    private static void printUsage()
    {
        String lSep = System.getProperty("line.separator");
        StringBuffer msg = new StringBuffer();
        msg.append("ant [options] [target [target2 [target3] ...]]" + lSep);
        msg.append("Options: " + lSep);
        msg.append("  -help                  print this message" + lSep);
        msg.append("  -projecthelp           print project help information" + lSep);
        msg.append("  -version               print the version information and exit" + lSep);
        msg.append("  -diagnostics           print information that might be helpful to" + lSep);
        msg.append("                         diagnose or report problems." + lSep);
        msg.append("  -quiet, -q             be extra quiet" + lSep);
        msg.append("  -verbose, -v           be extra verbose" + lSep);
        msg.append("  -debug                 print debugging information" + lSep);
        msg.append("  -emacs                 produce logging information without adornments" + lSep);
        msg.append("  -logfile <file>        use given file for log" + lSep);
        msg.append("    -l     <file>                ''" + lSep);
        msg.append("  -logger <classname>    the class which is to perform logging" + lSep);
        msg.append("  -listener <classname>  add an instance of class as a project listener" + lSep);
        msg.append("  -buildfile <file>      use given buildfile" + lSep);
        msg.append("    -file    <file>              ''" + lSep);
        msg.append("    -f       <file>              ''" + lSep);
        msg.append("  -D<property>=<value>   use value for given property" + lSep);
        msg.append("  -propertyfile <name>   load all properties from file with -D" + lSep);
        msg.append("                         properties taking precedence" + lSep);
        msg.append("  -inputhandler <class>  the class which will handle input requests" + lSep);
        msg.append("  -find <file>           search for buildfile towards the root of the" + lSep);
        msg.append("                         filesystem and use it" + lSep);
        Trace.info(msg.toString());
    }

    private static void printVersion()
        throws BuildException
    {
        Trace.info(getAntVersion());
    }

    public static synchronized String getAntVersion()
        throws BuildException
    {
        if(antVersion == null)
            try
            {
                Properties props = new Properties();
                InputStream in = (org.apache.tools.ant.Main.class).getResourceAsStream("/org/apache/tools/ant/version.txt");
                props.load(in);
                in.close();
                StringBuffer msg = new StringBuffer();
                msg.append("Apache Ant version ");
                msg.append(props.getProperty("VERSION"));
                msg.append(" compiled on ");
                msg.append(props.getProperty("DATE"));
                antVersion = msg.toString();
            }
            catch(IOException ioe)
            {
                throw new BuildException("Could not load the version information:" + ioe.getMessage());
            }
            catch(NullPointerException nullpointerexception)
            {
                throw new BuildException("Could not load the version information.");
            }
        return antVersion;
    }

    private static void printDescription(Project project)
    {
        if(project.getDescription() != null)
            project.log(project.getDescription());
    }

    private static void printTargets(Project project, boolean printSubTargets)
    {
        int maxLength = 0;
        Enumeration ptargets = project.getTargets().elements();
        Vector topNames = new Vector();
        Vector topDescriptions = new Vector();
        Vector subNames = new Vector();
        while(ptargets.hasMoreElements()) 
        {
            Target currentTarget = (Target)ptargets.nextElement();
            String targetName = currentTarget.getName();
            String targetDescription = currentTarget.getDescription();
            if(targetDescription == null)
            {
                int pos = findTargetPosition(subNames, targetName);
                subNames.insertElementAt(targetName, pos);
            } else
            {
                int pos = findTargetPosition(topNames, targetName);
                topNames.insertElementAt(targetName, pos);
                topDescriptions.insertElementAt(targetDescription, pos);
                if(targetName.length() > maxLength)
                    maxLength = targetName.length();
            }
        }
        printTargets(project, topNames, topDescriptions, "Main targets:", maxLength);
        if(topNames.size() == 0)
            printSubTargets = true;
        if(printSubTargets)
            printTargets(project, subNames, null, "Subtargets:", 0);
        String defaultTarget = project.getDefaultTarget();
        if(defaultTarget != null && !"".equals(defaultTarget))
            project.log("Default target: " + defaultTarget);
    }

    private static int findTargetPosition(Vector names, String name)
    {
        int res = names.size();
        for(int i = 0; i < names.size() && res == names.size(); i++)
            if(name.compareTo((String)names.elementAt(i)) < 0)
                res = i;

        return res;
    }

    private static void printTargets(Project project, Vector names, Vector descriptions, String heading, int maxlen)
    {
        String lSep = System.getProperty("line.separator");
        String spaces;
        for(spaces = "    "; spaces.length() < maxlen; spaces = spaces + spaces);
        StringBuffer msg = new StringBuffer();
        msg.append(heading + lSep + lSep);
        for(int i = 0; i < names.size(); i++)
        {
            msg.append(" ");
            msg.append(names.elementAt(i));
            if(descriptions != null)
            {
                msg.append(spaces.substring(0, (maxlen - ((String)names.elementAt(i)).length()) + 2));
                msg.append(descriptions.elementAt(i));
            }
            msg.append(lSep);
        }

        project.log(msg.toString());
    }

    public static final String DEFAULT_BUILD_FILENAME = "build.xml";
    private int msgOutputLevel;
    private File buildFile;
    private static PrintStream out;
    private static PrintStream err;
    private Vector targets;
    private Properties definedProps;
    private Vector listeners;
    private Vector propertyFiles;
    private String loggerClassname;
    private String inputHandlerClassname;
    private boolean emacsMode;
    private boolean readyToRun;
    private boolean projectHelp;
    private static boolean isLogFileUsed = false;
    private static String antVersion = null;

    static 
    {
        out = System.out;
        err = System.err;
    }
}
