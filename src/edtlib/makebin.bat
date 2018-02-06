@echo off
if %1.==. call x:\bin32\vcvars32.bat
nmake /f edtlib.mak CFG="edtlib - Win32 Release"