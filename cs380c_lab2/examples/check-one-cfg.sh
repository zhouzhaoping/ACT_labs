#!/usr/bin/env bash

C_SUBSET_COMPILER=../../cs380c_lab1/src/csc
THREE_ADDR_TO_C_TRANSLATOR=../lab2/run.sh

[ $# -ne 1 ] && { echo "Usage $0 PROGRAM" >&2; exit 1; }

# set -v

PROGRAM=$1
BASENAME=`basename $PROGRAM .c`
echo $PROGRAM
${C_SUBSET_COMPILER} $PROGRAM > ${BASENAME}.3addr
${THREE_ADDR_TO_C_TRANSLATOR} -backend=cfg < ${BASENAME}.3addr > ${BASENAME}.cfg
rm ${BASENAME}.3addr
md5sum ${BASENAME}.cfg ${BASENAME}.ta.cfg
rm ${BASENAME}.cfg
