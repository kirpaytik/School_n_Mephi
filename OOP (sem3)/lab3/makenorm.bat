@echo off
dir /b "multithread" | findstr . >nul
if %errorlevel% equ 0 (
    echo Yoo bro, you good? Smh already in multithread! - so you must be on normal already
    exit /b
)
echo Switching to normal mode

mv cpp/Landscape.cpp ./multithread
mv hpp/Landscape.hpp ./multithread
mv mvc/Game.cpp ./multithread
mv mvc/Game.hpp ./multithread
mv hpp/Enemy.hpp ./multithread
mv hpp/Road.hpp ./multithread
mv interfaces/IControlLives.hpp ./multithread

mv normal/Landscape.cpp ./cpp
mv normal/Landscape.hpp ./hpp
mv normal/Game.cpp ./mvc
mv normal/Game.hpp ./mvc
mv normal/Enemy.hpp ./hpp
mv normal/Road.hpp ./hpp
mv normal/IControlLives.hpp ./interfaces
