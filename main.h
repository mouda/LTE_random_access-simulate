#ifndef __MAIN_H__
#define __MAIN_H__

//for define
#define default_preambleNum 54
#define default_EndNum 100
#define default_Simulation_Time 1000
#define default_MAX 10
#define default_RandomBackoffIndex 20
#define default_firstWaiting 8
#define default_secondWaiting 40

#define default_start 1
#define uniform_start 2
#define beta_start 3

#define uniform_index 60   //distributed in 60secs
//


//todo    parse   traffic model(uniform first)   adding success delay(random or average)  
//math model: C100取54  成功機率

//for connection parameters
struct lte {
	static int preambleNum;
	static int EndNum;
	static int Simulation_Time;
	static int MAX;
	static int RandomBackoffIndex;
	static int firstWaiting;
	static int secondWaiting;
	
	static int traffic_type;
};
//


#endif