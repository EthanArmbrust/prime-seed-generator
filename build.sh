#!/bin/bash

i686-w64-mingw32-g++-posix -std=c++11 -c ./src/apstring.cpp ./src/dirChecker.cpp ./src/mainOptions.cpp ./src/cleanup.cpp ./src/logChecker.cpp
i686-w64-mingw32-g++-posix -o SeedGenerator.exe apstring.o dirChecker.o cleanup.o logChecker.o mainOptions.o -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
rm apstring.o cleanup.o dirChecker.o logChecker.o mainOptions.o
