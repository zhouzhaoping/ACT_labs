#/usr/bin/env bash
for PROGRAM in example1.c example2.c example3.c example4.c example5.c
do
		../examples/check-one.sh ${PROGRAM}
done
echo "md5sum hash of outputs"
md5sum *.txt

rm *.3addr*
rm *.gcc*
