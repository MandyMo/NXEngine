@rem Script to build Lua under "Visual Studio .NET Command Prompt".
@rem Do not run from this directory; run it from the toplevel: etc\luavs.bat .
@rem It creates lua51.dll, lua51.lib, lua.exe, and luac.exe in src.
@rem (contributed by David Manura and Mike Pall)

@setlocal
@set LUA_COMPILE=cl /nologo /W3 /c /D_CRT_SECURE_NO_DEPRECATE
@set LUA_LINK=link /nologo
@set LUA_MT=mt /nologo
@set LUA_LIB=lib /nologo /nodefaultlib
@set LUA_DLLNAME=lua51.dll
@set LUA_LIBNAME=lua51.lib

@if "%1" neq "debug" goto :NODEBUG
@set LUA_DLLNAME=lua51_d.dll
@set LUA_LIBNAME=lua51_d.lib
@shift
@set LUA_COMPILE=%LUA_COMPILE% /Zi
@set LUA_LINK=%LUA_LINK% /debug
:NODEBUG
@if "%1"=="static" goto :STATIC
%LUA_COMPILE% /MD /DLUA_BUILD_AS_DLL l*.c
@if errorlevel 1 goto :BAD
del lua.obj luac.obj
%LUA_LINK% /DLL /out:%LUA_DLLNAME% l*.obj
@if errorlevel 1 goto :BAD
@goto :MTDLL
:STATIC
%LUA_COMPILE% /DLUA_BUILD_AS_DLL l*.c
@if errorlevel 1 goto :BAD
del lua.obj luac.obj
%LUA_LIB% /OUT:%LUA_LIBNAME% l*.obj
@if errorlevel 1 goto :BAD
@goto :MTDLL
:MTDLL
if exist %LUA_DLLNAME%.manifest^
  %LUA_MT% -manifest %LUA_DLLNAME%.manifest -outputresource:%LUA_DLLNAME%;2

%LUA_COMPILE% lua.c
@if errorlevel 1 goto :BAD
%LUA_LINK% /out:lua.exe lua.obj %LUA_LIBNAME%
@if errorlevel 1 goto :BAD
if exist lua.exe.manifest^
  %LUA_MT% -manifest lua.exe.manifest -outputresource:lua.exe

del lua.obj luac.obj
%LUA_COMPILE% luac.c
%LUA_COMPILE% print.c
%LUA_LINK% /out:luac.exe l*.obj print.obj %LUA_LIBNAME%
if exist luac.exe.manifest^
  %LUA_MT% -manifest luac.exe.manifest -outputresource:luac.exe

@del *.obj *.manifest *.ilk *.pdb
@echo.
@echo === Successfully built Lua for Windows ===

@goto :END
:BAD
@echo.
@echo *******************************************************
@echo *** Build FAILED -- Please check the error messages ***
@echo *******************************************************
@goto :END
:FAIL
@echo You must open a "Visual Studio .NET Command Prompt" to run this script
:END