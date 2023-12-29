#!/bin/bash

g++ -std=c++0x -o mars mars_old_ok.cpp

for i in `seq 0 10`
do
	echo "Testul $i"
	time ./mars < "mar$i.in" > "mars.out"
	cat "mar$i.out"
	cat "mars.out"
	echo 
done
