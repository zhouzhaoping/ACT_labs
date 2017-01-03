#!/usr/bin/env bash
cp ~/projects/Project1/CFG_main.cpp CFG_main.cpp
cp ~/projects/Project1/CFG.cpp CFG.cpp
cp ~/projects/Project1/CFG.h CFG.h
#g++ CFG_main.cpp CFG.cpp -o CFG_gen

cp ~/projects/Project1/Graph.h Graph.h
cp ~/projects/Project1/Graph.cpp Graph.cpp
cp ~/projects/Project1/SCR_main.cpp SCR_main.cpp
#g++ SCR_main.cpp Graph.cpp CFG.cpp -o SCR_gen

g++ -c *.cpp
g++ CFG_main.o CFG.o Graph.o -o CFG_gen
g++ SCR_main.o CFG.o Graph.o -o SCR_gen
rm *.o
