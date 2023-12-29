#!/bin/bash
g++ -std=c++20 -o iepuri iepuri2.cpp
for i in `seq 0 9`
do
	echo "Testul $i :"
	time ./iepuri < "iepuri$i.in" > "iepuri.out"
	cat "iepuri$i.ko"
	cat "iepuri.out"
#	diff "iepuri$i.ko" "iepuri.out"
	echo
done
