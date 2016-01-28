#!/bin/bash
rm win/*.o
i686-w64-mingw32-c++ -c -o win/Operation.o Operation.cpp
i686-w64-mingw32-c++ -c -o win/ViewArea.o ViewArea.cpp
i686-w64-mingw32-c++ -c -o win/Calculator.o Calculator.cpp
i686-w64-mingw32-c++ -c -o win/MyMenuBar.o MyMenuBar.cpp
i686-w64-mingw32-c++ -c -o win/calc80.o calc80.cpp  `/usr/i686-w64-mingw32/sys-root/mingw/bin/fltk-config --cxxflags`
i686-w64-mingw32-windres -c -o win/resources.rs win/resources.o
i686-w64-mingw32-c++ -g -o win/calc80.exe win/calc80.o win/resources.o win/MyMenuBar.o win/Calculator.o win/ViewArea.o win/Operation.o `/usr/i686-w64-mingw32/sys-root/mingw/bin/fltk-config --ldflags --use-images` -lfltk
rm "calc80(win version).zip"
cd win
zip "../calc80(win version).zip" *.dll
zip "../calc80(win version).zip" calc80.exe
cd ..
zip "calc80(win version).zip" *.cpp
zip "calc80(win version).zip" *.h
zip "calc80(win version).zip" README CHANGELOG LICENSE


