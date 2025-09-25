@echo off
set PRESET=Release
cmake --preset %PRESET% || exit /b 1
cmake --build --preset %PRESET% --target package || exit /b 1
echo.
echo Packages are in: %CD%\build-%PRESET%
dir /b build-%PRESET%\*.zip build-%PRESET%\*.exe 2>nul