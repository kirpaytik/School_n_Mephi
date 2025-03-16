@echo off
dir /b "normal" | findstr . >nul
if %errorlevel% equ 0 (
    echo Yoo bro, you good? Smh already in normal! - so you must be on thread already
    exit /b
)
echo Switching to multithread mode

mv cpp/Landscape.cpp ./normal
mv hpp/Landscape.hpp ./normal
mv mvc/Game.cpp ./normal
mv mvc/Game.hpp ./normal
mv hpp/Enemy.hpp ./normal
mv hpp/Road.hpp ./normal
mv interfaces/IControlLives.hpp ./normal

mv multithread/Landscape.cpp ./cpp
mv multithread/Landscape.hpp ./hpp
mv multithread/Game.cpp ./mvc
mv multithread/Game.hpp ./mvc
mv multithread/Enemy.hpp ./hpp
mv multithread/Road.hpp ./hpp
mv multithread/IControlLives.hpp ./interfaces
