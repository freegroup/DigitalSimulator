@echo off
echo *
echo *
echo *
echo *
echo *****************************************************
echo copy source to build of [%1]
echo *****************************************************

echo make copy of original files
copy ..\build\context.cpp      ..\build\context.cpp_orig
copy ..\build\context.rc       ..\build\context.rc_orig
copy ..\build\ConfigDialog.cpp ..\build\ConfigDialog.cpp_orig
copy ..\build\ConfigDialog.h   ..\build\ConfigDialog.h_orig
copy ..\build\resource.h       ..\build\resource.h_orig

echo copy source files to build directory
copy ..\source\%1.cpp              ..\build\context.cpp
copy ..\source\%1.rc               ..\build\context.rc
copy ..\source\%1_ConfigDialog.c   ..\build\ConfigDialog.cpp
copy ..\source\%1_ConfigDialog.h   ..\build\ConfigDialog.h
copy ..\source\%1_resource.h       ..\build\resource.h
