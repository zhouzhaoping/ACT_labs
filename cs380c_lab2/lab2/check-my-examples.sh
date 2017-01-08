#/usr/bin/env bash
for PROGRAM in *.c
do
	#../../cs380c_lab1/src/csc ${PROGRAM} | ./SCR_gen 
	../examples/check-one.sh ${PROGRAM}
done
echo "md5sum hash of outputs"
md5sum *.txt

rm *.3addr*
rm *.gcc*
