#!/bin/bash
g++ -std=c++0x -o judet judete_ok_ok_ha.cpp
for i in `seq 0 9`
do
	echo "Testul $i :"
	time ./jud < "$i-JUDETE.IN" > "judete.out"
	cat "$i-JUDETE.OK"
	cat "judete.out"
#	diff "iepuri$i.ko" "iepuri.out"
	echo
done
