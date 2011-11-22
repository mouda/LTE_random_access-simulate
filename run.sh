#!/bin/bash

rm result.txt
index=0;
simulateTimes=5;
for index in $(seq 1 $simulateTimes)
do 
  ./simulate -end 5000 -rand 20 -type uniform >> result.txt
done
