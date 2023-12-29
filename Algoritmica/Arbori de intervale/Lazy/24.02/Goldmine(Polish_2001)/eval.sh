#!/bin/bash

g++ -std=c++0x -o puncte puncte_ok.cpp

for i in `seq 0 14`
do
	echo "Testul $i"
	time ./puncte < "kop$i.in" > "puncte.out"
	cat "KOP$i.OUT"
	cat "puncte.out"
	echo 
done
