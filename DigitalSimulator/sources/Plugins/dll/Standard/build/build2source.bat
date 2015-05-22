@echo off
echo *
echo *
echo *
echo *
echo *****************************************************
echo copy build to source directory [%1]
echo *****************************************************

echo copy build files to source directory
copy ..\build\context.cpp           ..\source\%1.cpp
copy ..\build\context.rc            ..\source\%1.rc  
copy ..\build\ConfigDialog.cpp      ..\source\%1_ConfigDialog.c
copy ..\build\ConfigDialog.h        ..\source\%1_ConfigDialog.h
copy ..\build\resource.h            ..\source\%1_resource.h
