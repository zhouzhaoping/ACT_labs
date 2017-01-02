#!/usr/bin/env bash
cp ~/projects/Project1/CFG_main.cpp CFG_main.cpp
cp ~/projects/Project1/CFG.cpp CFG.cpp
cp ~/projects/Project1/CFG.h CFG.h
g++ CFG_main.cpp CFG.cpp -o CFG_gen
