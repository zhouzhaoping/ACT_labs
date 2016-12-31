#!/usr/bin/env bash
javac *.java
echo "Main-Class: act_main" > manifest.mf 
jar cvfm convert.jar manifest.mf *.class
rm manifest.mf
rm *.class
