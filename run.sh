#!/bin/bash

rm result.txt
index=0;
simulateTimes=10;
for index in $(seq 1 $simulateTimes)
do 
  ./simulate -end 100 -rand 20 -type uniform >> result.txt
done
