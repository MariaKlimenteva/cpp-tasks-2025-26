#!/bin/bash

echo "--- Benchmarking Header-based Build (06.01) ---"
rm -f *.o solution_headers

echo "Compiling Object 1..."
/usr/bin/time -f "%e" g++ -std=c++23 -c rational_h.cpp -o rational_h.o

echo "Compiling Main..."
/usr/bin/time -f "%e" g++ -std=c++23 -c main_h.cpp -o main_h.o

echo "Linking..."
/usr/bin/time -f "%e" g++ rational_h.o main_h.o -o solution_headers

echo "Total size:"
du -h solution_headers

echo ""
echo "--- Benchmarking Module-based Build (06.02) ---"
rm -f *.o *.gcm solution_modules

# Предкомпиляция системных хедеров (однократно)
g++ -std=c++23 -fmodules-ts -x c++-system-header iostream compare numeric cassert vector algorithm map filesystem

echo "Compiling Interface..."
/usr/bin/time -f "%e" g++ -std=c++23 -fmodules-ts -c rational.ixx

echo "Compiling Implementation..."
/usr/bin/time -f "%e" g++ -std=c++23 -fmodules-ts -c rational.cpp

echo "Compiling Main..."
/usr/bin/time -f "%e" g++ -std=c++23 -fmodules-ts -c main.cpp

echo "Linking..."
/usr/bin/time -f "%e" g++ rational.o main.o rational_interface.o -o solution_modules

echo "Total size:"
du -h solution_modules