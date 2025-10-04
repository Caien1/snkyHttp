
@REM @echo off
@REM REM ADD A BIN DIR BEFORE RUNNING
set cc=g++

@REM echo Compiling Curl...

@REM set source=.\src\libcurlWrapper.cpp
@REM set output=-o .\bin\test.exe
@REM set flag=-I .\src -lcurl -Wall -lssl -lcrypto -lz -lws2_32 -lcrypt32 -lwldap32 -DCURL_STATICLIB

@REM %cc% %source% %output% %flag%

@REM echo Done


echo Compiling Raylib...
set sourceui=.\src\ui.cpp 
set outputui=-o .\bin\ray.exe
set flagui=-O2 -I inclide -lraylib -lopengl32 -lgdi32 -luser32 -lkernel32 -lwinmm -Wall -lcurl -Wall -lssl -lcrypto -lz -lws2_32 -lcrypt32 -lwldap32 -DCURL_STATICLIB -mwindows
set undef=-U SUPPORT_MODULE_AUDIO -U SUPPORT_MODULE_TEXTURES -U SUPPORT_MODULE_MODELS -U SUPPORT_MODULE_SHAPES
%cc% %sourceui% %outputui% %flagui% %undef%

echo Done

@REM g++ -c .\src\uiImpl.cpp -o ./build/ui.o -L lib -lraylib  -lgdi32 -lwinmm -Wall
@REM g++ -shared -o ./bin/ui.dll ./build/ui.o  -L lib -lraylib  -lgdi32 -lwinmm -Wall
