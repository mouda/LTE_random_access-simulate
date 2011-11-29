#!/bin/bash

rm result.txt
index=0;
simulateTimes=20;
endNumber=100;
for index in $(seq 1 $simulateTimes)
do 
  parameter=`expr 1000 + $index \* 2000`;
#  echo $index;
  echo "==================== End number $parameter ======================";
  ./simulate -end $parameter -rand 20 -type uniform >> result.txt
done
