#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "End.h"
#include "main.h"
#include "parse.h"
#include <iomanip>
#include "specialfunctions.h"

using namespace std;
using namespace alglib;

//for parameter measuring the efficiency!!!
int* finish_time;
int access_time = 0;
int collision_time = 0;

//for connection parameters
int lte::preambleNum = default_preambleNum;
int lte::EndNum = default_EndNum;
int lte::Simulation_Time = default_Simulation_Time;
int lte::MAX = default_MAX;
int lte::RandomBackoffIndex = default_RandomBackoffIndex;
int lte::firstWaiting = default_firstWaiting;
int lte::secondWaiting = default_secondWaiting;
int lte::traffic_type = default_start;

//

//global changeable variables
int _time = 1;// the order of the subframe
int* preamble;
int _count = 0;//to record the tutle number of successful and abort End
int _goodEnd = 0;
int _retransmission = 0;
//
double betaDistribution(double, double, double);
void responseForUseSamePreamble();
void set_traffic(End* end);
// to set the probablity of successful receive, the input is the number of the restransmission
int setProbablity( int );
void cleanup() {
	delete preamble;
	delete finish_time;
}

void analysisForEvent(int, int, int);
void analysisForNode(End &, int);

int main(int argc, char** argv) {

	lineParsing(argc, argv); //./simulate -end endnum -rand RandomBackoffIndex -type start_scenario
	cout << "connection scenario is setting..." << endl;
	
	preamble = new int[lte::preambleNum];
	finish_time = new int[lte::EndNum];
	
	//end definitions!!
    End end[lte::EndNum];
	set_traffic(end);
	//
	
    srand(time(NULL));
    for(; _count < lte::EndNum ; _time +=5 ){
	for( int n = 0; n < lte::EndNum; n++ )
	    end[n].setpreamble(); 
	responseForUseSamePreamble();
	for( int n = 0; n < lte::EndNum; n++ ){
	    end[n].responseForOnlyOne();
	    end[n].settime();
	}
 
	if (_time == 1)
		cout << "===Event===" << endl;
	analysisForEvent(_time, _count, _goodEnd);
	
	for (int i = 0; i < lte::preambleNum; i++) {
	    preamble[i] = 0;
	}
    }
	
	cout << "===Node===\n";
	for (int i = 0; i < lte::EndNum; i++)	
		analysisForNode(end[i], i);
		
	int _Taccess = 0;
	int _TEcollision = 0;
    int _Tdelay = 0;
	for (int i = 0; i < lte::EndNum; i++)
	{	
		_Taccess += end[i].getIndex();
		_TEcollision += end[i].getCollision();
		_Tdelay += end[i].getDelayTime();
    }
	cerr << "_Taccess = " << _Taccess << endl;
    cerr << "===Analysis===\n";
    cerr << "Total success number : " << _goodEnd << endl
		 << "Total collision (counted by preambles) : " << collision_time << endl
		 << "Total collision (counted by terminals) : " << _TEcollision << endl
		 << "Collision probability (counted by preambles) : " << ((double) collision_time)/((double)_Taccess) << endl
		 << "Collision probability (counted by terminals) : " << ((double) _TEcollision)/((double) _Taccess) << endl
		 << "Access success probability : " << ((double) _goodEnd)/((double) _Taccess) << endl
		 << "Average delay : " << ((double) _Tdelay)/((double) lte::EndNum) << endl;
	// << "Variance of delay : " <<  << endl;
	

	cleanup();
    return 0;
}

void analysisForEvent(int _time, int _count, int _goodEnd) {
	cout << "\t" << "time(ms)" << "\t" << (_time+1)
	<< "\t" << "abort" << "\t" << (_count-_goodEnd)
	<< "\t" << "success" << "\t" << (_goodEnd)
	<< "\t" << "collision" << "\t" << collision_time
	<< endl;
}

void analysisForNode(End &e, int i) {
	string _state;
	 if (e.getStartTime() == -1)
		_state = "o";
	else if (e.getStartTime() == -2)
		_state = "xxx";
	else _state = "==err==";
	
	cout << "\t" << "node" << "\t" << (i+1)
	<< "\t" << "start" << "\t" << e.getStart()
	<< "\t" << "delay" << "\t" << e.getDelayTime()
	<< "\t" << "retrans" << "\t" << e.getIndex()
	<< "\t" << "collision" << "\t" << e.getCollision()
	<< "\t" << "finally" << "\t" << _state
	<< endl;
}

void responseForUseSamePreamble()
{
    for( int i = 0; i < lte::preambleNum;  i++ ){
	if( preamble[i] > 1 ){
	//preamble[i] = setProbablity(1); 
	    if (setProbablity(1) == 0) { 
		preamble[i] = 0;
		/*/------debug-----
		cout << "setpro = 0\n";
		//------debug-----*/
	    }
	}
  }
}
int setProbablity( int retransmit )
{
 double p = 1 - exp((double) retransmit*(-1));
 int p1 = p*1000;
 int p2 = (1.0 - p)*1000;
 
 int key = rand() % (p1 + p2);
 
 if (key <= p1) return 1;
 else return 0;
}

double betaDistribution(double t, double a, double b ) {
    return pow(t, a-1.0) * pow((1.0-t), b-1.0) / beta(a, b) / 2.085;
}

void set_traffic(End* end) {
	if (lte::traffic_type == uniform_start) {
		for (int i = 0; i < lte::EndNum; i++) 
			end[i].setStartTime((rand()%12000)*5 + 1);
	}
	/*
	Beta(a,b): a=3 b=4    Beta(3,4) = 1/60
	p(t) = 6/10^5*t^2*(10-t)^3
	access_intensity(i) = EndNum * integral of p(t) from ti to ti+1
	*/
	else if (lte::traffic_type == beta_start) {
		for (int i = 0; i < lte::EndNum; i++) {
			//int setPeriod = (int)floor(2000.0*beta(3.0, 4.0));
			//end[i].setStartTime(setPeriod*5 + 1);
			int setPeriod = (int)(2000.0*betaDistribution((rand() / ((double)RAND_MAX)), 3.0, 4.0));
			end[i].setStartTime(setPeriod*5 + 1);
			//cerr << "!!!!!!!!!!!!!" << betaDistribution((rand() / ((double)RAND_MAX + 1.0)), 3.0, 4.0) << endl;
		}
		
	}
}
