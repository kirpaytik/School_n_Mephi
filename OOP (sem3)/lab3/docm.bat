cd build
rm * -rf
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=D:/mingw32/bin/gcc.exe -DCMAKE_CXX_COMPILER=D:/mingw32/bin/g++.exe ..
mingw32-make
cd ..
