@echo off
if "%OS%" == "Windows_NT" set PATH=%MSDevDir%\BIN;%MSVCDir%\BIN;%VSCommonDir%\TOOLS\%VcOsDir%;%VSCommonDir%\TOOLS;%PATH%
if "%OS%" == "" set PATH="%MSDevDir%\BIN";"%MSVCDir%\BIN";"%VSCommonDir%\TOOLS\%VcOsDir%";"%VSCommonDir%\TOOLS";"%windir%\SYSTEM";"%PATH%"
set INCLUDE=%MSVCDir%\ATL\INCLUDE;%MSVCDir%\INCLUDE;%MSVCDir%\MFC\INCLUDE;%INCLUDE%;e:\projets\kapsul\core;E:\SOURCES\CIMAGE\IMAGELIB\HEADERS;E:\PROJETS\KAPSUL\EIC\SRC
set LIB=%MSVCDir%\LIB;%MSVCDir%\MFC\LIB;%LIB%;e:\projets\kapsul;E:\SOURCES\CIMAGE\LIBRAIRIES;E:\PROJETS\KAPSUL\EIC\SRC

e:
cd\projets\kapsul\iokdk
NMAKE CLEAN /f "IOkdk.mak" CFG="IOkdk - Win32 Release"
NMAKE /f "IOkdk.mak" CFG="IOkdk - Win32 Release"