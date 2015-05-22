@echo off
set THIS_JAVA_HOME=..
IF NOT "%JAVA_HOME%"=="" set THIS_JAVA_HOME=%JAVA_HOME%
%THIS_JAVA_HOME%\bin\java -jar %THIS_JAVA_HOME%\lib\htmlconverter.jar %1 %2 %3 %4 %5 %6 %7 %8 %9
set THIS_JAVA_HOME=


