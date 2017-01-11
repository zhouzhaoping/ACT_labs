#!/usr/bin/env bash

# $Id: check.sh 820 2007-09-02 18:18:52Z suriya $

echo "check cfg....."
for PROGRAM in collatz.c gcd.c hanoifibfac.c loop.c mmm.c prime.c \
    regslarge.c struct.c sort.c sieve.c
do
    ./check-one-cfg.sh ${PROGRAM}
done
echo "md5sum hash of outputs"
md5sum *.cfg

echo "check simple constant propagation....."
for PROGRAM in collatz.c gcd.c hanoifibfac.c loop.c mmm.c prime.c \
    regslarge.c struct.c sort.c sieve.c
do
    ./check-one-scp.sh ${PROGRAM}
done
echo "md5sum hash of outputs"
md5sum *.txt

echo "check dead statement elimination"
for PROGRAM in collatz.c gcd.c hanoifibfac.c loop.c mmm.c prime.c \
    regslarge.c struct.c sort.c sieve.c
do
    ./check-one-dse.sh ${PROGRAM}
done
echo "md5sum hash of outputs"
md5sum *.txt

./clean.sh
