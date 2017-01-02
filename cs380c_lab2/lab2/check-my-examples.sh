#/usr/bin/env bash
for PROGRAM in example1.c example2.c example3.c example4.c example5.c
do
		../../cs380c_lab1/src/csc ${PROGRAM} | ./CFG_gen 
done

rm *.3addr*
rm *.gcc*
