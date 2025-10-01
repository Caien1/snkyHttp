
@echo off
REM ADD A BIN DIR BEFORE RUNNING
set cc=g++

@REM echo Compiling Curl...

@REM set source=.\src\libcurlWrapper.cpp
@REM set output=-o .\bin\test.exe
@REM set flag=-I .\src -lcurl -Wall -lssl -lcrypto -lz -lws2_32 -lcrypt32 -lwldap32 -DCURL_STATICLIB

@REM %cc% %source% %output% %flag%

@REM echo Done


echo Compiling Raylib...
set sourceui=.\src\uiDriver.cpp 
set outputui=-o .\bin\ray.exe
set flagui=-I include -L lib -lraylib  -lgdi32 -lwinmm -Wall -L./ -lui

%cc% %sourceui% %outputui% %flagui%

echo Done

g++ -c .\src\uiImpl.cpp -o ./build/ui.o -L lib -lraylib  -lgdi32 -lwinmm -Wall
g++ -shared -o ./bin/ui.dll ./build/ui.o  -L lib -lraylib  -lgdi32 -lwinmm -Wall