#!/bin/bash

g++ -std=c++0x -o puncte puncte_lazy.cpp

for i in `seq 0 14`
do
	echo "Testul $i"
	time ./puncte < "kop$i.in" > "puncte.out"
	cat "kop$i.out"
	cat "puncte.out"
	echo 
done
