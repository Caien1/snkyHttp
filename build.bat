
@echo off
REM ADD A BIN DIR BEFORE RUNNING


echo Compiling Curl...
set cc=g++
set source=.\src\libcurlWrapper.cpp
set output=-o .\bin\test.exe
set flag=-I .\src -lcurl -Wall -lssl -lcrypto -lz -lws2_32 -lcrypt32 -lwldap32 -DCURL_STATICLIB

%cc% %source% %output% %flag%

echo Done


echo Compiling Raylib...
set sourceui=.\src\uiDriver.cpp 
set outputui=-o .\bin\ray.exe
set flagui=-I include -L lib -lraylib -lgdi32 -lwinmm -Wall

%cc% %sourceui% %outputui% %flagui%

echo Done

