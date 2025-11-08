@echo off
setlocal enabledelayedexpansion

REM Nazwa pliku wynikowego
set OUT=main.exe

REM Kompilacja wszystkich cpp w katalogu
g++ -Wall -Wextra -std=c++17 *.cpp -o %OUT%
if ERRORLEVEL 1 (
    pause
    exit /b 1
)

%OUT%
pause
