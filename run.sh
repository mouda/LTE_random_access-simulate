#!/bin/bash

index=0;
simulateTimes=30;
endNumber=100;
nameForEndEvent="resultEnd_";
nameForEndReport="reportEnd_";

suffix="_.txt";
EventFileName="resultEnd";
ReportFileName="reportEnd";
dirName="./result";

rm *_.tx
if [ ! -d $dirName ]; then
  mkdir $dirName;
fi 

for index in $(seq 1 $simulateTimes)
do 
  parameter=`expr 1000 + $index \* 2000`;
#  echo $index;
  EventFileName=${dirName}'/'${nameForEndEvent}${parameter}${suffix};
  ReportFileName=${dirName}'/'${nameForEndReport}${parameter}${suffix};
  echo "==================== End number $parameter ======================";
  echo "EventFileName: $EventFileName";
  ./simulate -end $parameter -rand 1 -type beta -max 10 -pre 10 >> ${EventFileName} 2>> ${ReportFileName};
done
