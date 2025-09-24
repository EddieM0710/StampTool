@echo off
setlocal EnableExtensions EnableDelayedExpansion

rem ===== CONFIG (edit if needed) =============================================
rem Project root (folder containing CMakeLists.txt). Using this .bat's folder:
set "ST_SRC=%~dp0"
if "%ST_SRC%"=="" set "ST_SRC=%CD%"

rem Toolchain (winlibs)
set "MINGW_ROOT=C:\mingw64"
set "CC=%MINGW_ROOT%\bin\gcc.exe"
set "CXX=%MINGW_ROOT%\bin\g++.exe"
set "CMAKE=%MINGW_ROOT%\bin\cmake.exe"
set "NINJA=%MINGW_ROOT%\bin\ninja.exe"
set "GEN=Ninja"

rem Installed prefixes from your winlibs builds (adjust if different)
set "WX_DEBUG=C:\mingw64\local-wx-debug"
set "WX_RELEASE=C:\mingw64\local-wx-release"
set "WXPDF_DEBUG=C:\mingw64\local-wxpdfdoc-debug"
set "WXPDF_RELEASE=C:\mingw64\local-wxpdfdoc-release"

rem Build type arg: Debug (default) or Release
set "CFG=%~1"
if "%CFG%"=="" set "CFG=Debug"

rem PATH hygiene: force winlibs first
set "PATH=%MINGW_ROOT%\bin;%PATH%"

where "%CMAKE%"  >nul 2>&1 || (echo ERROR: cmake not found at %CMAKE% & exit \b 1)
where "%CXX%"    >nul 2>&1 || (echo ERROR: g++ not found at %CXX%   & exit \b 1)
where "%NINJA%"  >nul 2>&1 || echo WARN: ninja not found at %NINJA% — will try system ninja

if \I "%CFG%"=="Debug" (
  set "BLD=%ST_SRC%\build-Debug"
  set "PREFIX=%WX_DEBUG%;%WXPDF_DEBUG%"
) else (
  set "BLD=%ST_SRC%\build-Release"
  set "PREFIX=%WX_RELEASE%;%WXPDF_RELEASE%"
)

if not exist "%ST_SRC%\CMakeLists.txt" (
  echo ERROR: No CMakeLists.txt under %ST_SRC%
  exit \b 1
)

echo === Configuring StampTool (%CFG%) in %BLD%
"%CMAKE%" -S "%ST_SRC%" -B "%BLD%" -G "%GEN%" ^
  -DCMAKE_BUILD_TYPE=%CFG% ^
  -DCMAKE_C_COMPILER="%CC%" -DCMAKE_CXX_COMPILER="%CXX%" ^
  -DCMAKE_PREFIX_PATH="%PREFIX%" ^
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
if errorlevel 1 goto :err_cfg

echo === Building StampTool (%CFG%)
"%CMAKE%" --build "%BLD%" --config %CFG%
if errorlevel 1 goto :err_build

echo.
echo SUCCESS: StampTool %CFG% build finished.
echo If needed to run outside VS Code, ensure PATH includes:
if \I "%CFG%"=="Debug" (
  echo   %MINGW_ROOT%\bin;%WX_DEBUG%\bin;%WXPDF_DEBUG%\bin
) else (
  echo   %MINGW_ROOT%\bin;%WX_RELEASE%\bin;%WXPDF_RELEASE%\bin
)
echo Exe output is typically: %BLD%\bin (or your target output dir)
echo.
exit \b 0

:err_cfg
echo ERROR: Configure failed for %CFG%
exit \b 1

:err_build
echo ERROR: Build failed for %CFG%
exit \b 1