#!/bin/bash
rm win/*
i686-w64-mingw32-c++ -c -o win/Operation.o Operation.cpp
i686-w64-mingw32-c++ -c -o win/ViewArea.o ViewArea.cpp
i686-w64-mingw32-c++ -c -o win/Calculator.o Calculator.cpp
i686-w64-mingw32-c++ -c -o win/MyMenuBar.o MyMenuBar.cpp
i686-w64-mingw32-c++ -c -o win/calc80.o calc80.cpp  `/usr/i686-w64-mingw32/sys-root/mingw/bin/fltk-config --cxxflags`
i686-w64-mingw32-c++ -g -o calc80.exe win/calc80.o win/MyMenuBar.o win/Calculator.o win/ViewArea.o win/Operation.o `/usr/i686-w64-mingw32/sys-root/mingw/bin/fltk-config --ldflags --use-images` -lfltk

