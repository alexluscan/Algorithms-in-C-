#!/bin/bash

g++ -std=c++0x -o pict pictures_ok.cpp

for i in `seq 1 5`
do
	echo "Testul $i"
	time ./pict < "picture$i.in" > "picture.out"
	cat "picture$i.out"
	cat "picture.out"
	echo 
done
