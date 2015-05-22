set CLASSPATH=

set JAVA_HOME=%~dp0..\..\jdk
set ANT_HOME=%~dp0..\..\pluginSDK\ant
set OLD_PATH=%PATH%
set PATH=%ANT_HOME%\bin\
ant -Dplugin.name=%1
