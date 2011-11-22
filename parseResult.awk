BEGIN {
				totaldelay;
				maximunIndex = 0;
				simulationTimes = 5;
				collisionTimes = 0;
				restransmitTimes = 0;
				successNumber =0;
}
#For plot the time/event chart
$1=="time(ms)" { 
				abortArray[$2]+=$4;
				connectArray[$2]+=$6;
				if(maximunIndex <= $2){ maximunIndex = $2 ;}
				#  printf("connectArray[%d] %d \n",$2,connectArray[$2]);
}
$9=="collision" {
	collisionTimes+=$10;
}
#For calculate the average delay
$1=="node" {
				

}
$7=="retrans" {
	retransmit+=$8;
}
$11=="finally" && $12=="o"{
	successNumber+=1;
}
END {
				# print the success number chart
				printf("maximumTime:%d\n", maximunIndex);

				for( i = 2; i <= maximunIndex; i+= 5){
								printf("%f\n",connectArray[i]/simulationTimes);
				}
				# print the abort number chart
#				printf("maximumTime:%d\n", maximunIndex);
#				for( i = 2; i <= maximunIndex; i+= 5){
#								printf("%f\n",abortArrayArray[i]/simulationTimes);
#				}
				averageCollisionTimes = collisionTimes/simulationTimes;
				printf("collisionTimes:%f\n", averageCollisionTimes);
				averageRetransmitTimes = retransmit/simulationTimes;
				printf("retransmit times:%f\n", averageRetransmitTimes);
				averageSuccessNumbers = successNumber/simulationTimes;
				printf("Success number: %f\n", averageSuccessNumbers);

				printf("collision probability: %f%%\n",
							 100*(averageCollisionTimes/averageRetransmitTimes));
				printf("success probability: %f%%\n", 
							 100*(averageSuccessNumbers/averageRetransmitTimes));



}


