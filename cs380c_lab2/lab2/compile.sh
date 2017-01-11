#!/usr/bin/env bash

cp ~/projects/Project1/Code3addr.h Code3addr.h
cp ~/projects/Project1/Code3addr.cpp Code3addr.cpp
cp ~/projects/Project1/Function.h Function.h
cp ~/projects/Project1/Function.cpp Function.cpp
cp ~/projects/Project1/tools.h tools.h
cp ~/projects/Project1/tools.cpp tools.cpp
cp ~/projects/Project1/CFG.h CFG.h
cp ~/projects/Project1/CFG.cpp CFG.cpp
cp ~/projects/Project1/CFG_main.cpp CFG_main.cpp

cp ~/projects/Project1/Graph.h Graph.h
cp ~/projects/Project1/Graph.cpp Graph.cpp
cp ~/projects/Project1/SCR_main.cpp SCR_main.cpp
cp ~/projects/Project1/SCP_main.cpp SCP_main.cpp
cp ~/projects/Project1/DSE_main.cpp DSE_main.cpp

#g++ SCR_main.cpp Graph.cpp CFG.cpp -o SCR_gen

g++ -c *.cpp
g++ CFG_main.o CFG.o Function.o Code3addr.o Graph.o tools.o -o CFG_gen
g++ SCR_main.o CFG.o Function.o Code3addr.o Graph.o tools.o -o SCR_gen
g++ SCP_main.o CFG.o Function.o Code3addr.o Graph.o tools.o -o SCP_gen
g++ DSE_main.o CFG.o Function.o Code3addr.o Graph.o tools.o -o DSE_gen
rm *.o
