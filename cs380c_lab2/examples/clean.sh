#!/usr/bin/env bash

for PROGRAM in collatz.c gcd.c hanoifibfac.c loop.c mmm.c prime.c \
	regslarge.c struct.c sort.c sieve.c
do
	BASENAME=`basename $PROGRAM .c`
	#echo $BASENAME
	rm ${BASENAME}.3addr ${BASENAME}.cfg 
	rm ${BASENAME}.gcc.bin ${BASENAME}.gcc.txt 
	rm ${BASENAME}.3addr.c ${BASENAME}.3addr.bin ${BASENAME}.3addr.txt
	rm ${BASENAME}.3addr.scp ${BASENAME}.3addr.scp.rep ${BASENAME}.3addr.scp.cfg
	rm ${BASENAME}.3addr.dse ${BASENAME}.3addr.dse.rep ${BASENAME}.3addr.dse.cfg
done
