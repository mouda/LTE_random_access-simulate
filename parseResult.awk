BEGIN {
#  abortArrayi[];
#  connectArray[];
  totaldelay;
  maximunIndex = 0;
  simulationTimes = 10;
}
#For plot the time/event chart
$1=="time(ms)" { 
  abortArray[$2]+=$4;
  connectArray[$2]+=$6;
  if(maximunIndex <= $2){ maximunIndex = $2 ;}
#  printf("connectArray[%d] %d \n",$2,connectArray[$2]);
}
#For calculate the average delay
$1=="end" {
  
}
END {
#	#print the average delay of UDP2
#	AverageDelay=UDP2_Total_DelayTime/count;
#	printf ("Average Delay: %f %s\n",AverageDelay,"(s)")
#
#	#print the loss rate UDP2
#	lossRate=(lossNum/totalSend)*100;
#	#printf ("Total Send: %d\n",totalSend);
#	printf ("Loss Rate: %f %s\n",lossRate,"(%)");
#	
#	#print the throughput(bps) UDP2
#	totalTime=$2;
#	throughPut=((float)totalReceive*512)/(totalTime-1);
#	throughPut=throughPut/1000;
#	#printf ("Total Time: %f\n",totalTime);
#	#printf ("Total Receive: %d\n",totalReceive);
#	printf ("ThroughPut: %f %s\n",throughPut,"(bps)");
	printf("maximumTime:%d\n", maximunIndex);
	for( i = 2; i <= maximunIndex; i+= 5){
		printf("%f\n",connectArray[i]/simulationTimes);
	}

}
	

