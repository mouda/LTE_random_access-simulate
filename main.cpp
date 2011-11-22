#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "End.h"
#include "main.h"
#include "parse.h"
#include <iomanip>
using namespace std;

//for parameter measuring the efficiency!!!
int* finish_time;
int access_time = 0;
int collision_time = 0;
//====This collision_time parameter--->when there are two or more ends using the same preamble, collision_time++
//for connection parameters
int lte::preambleNum = default_preambleNum;
int lte::EndNum = default_EndNum;
int lte::Simulation_Time = default_Simulation_Time;
int lte::MAX = default_MAX;
int lte::RandomBackoffIndex = default_RandomBackoffIndex;
int lte::firstWaiting = default_firstWaiting;
int lte::secondWaiting = default_secondWaiting;
int lte::traffic_type = default_start;

//global changeable variables
int _time = 1;// the order of the subframe
int* preamble;
int _count = 0;//to record the tutle number of successful and abort End
int _goodEnd = 0;
//

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

    lineParsing(argc, argv); 
    //./simulate -end endnum -rand RandomBackoffIndex -type start_scenario
    cout << "connection scenario is setting..." << endl;
	
    preamble = new int[lte::preambleNum];
    finish_time = new int[lte::EndNum];
	
    //end definitions!!
    End end[lte::EndNum];
    set_traffic(end);
	
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
	
	//reset the preamble[] to zero!
	for (int i = 0; i < lte::preambleNum; i++) {
	    preamble[i] = 0;
	}
    
    }
    
    cout << "===Node===\n";
    for (int i = 0; i < lte::EndNum; i++)
	analysisForNode(end[i], i);

    cleanup();
    return 0;

}

void analysisForEvent(int _time, int _count, int _goodEnd) {
    cout << setw(10) << "time(ms)" << setw(10) << (_time+1) 
	 << setw(10) << "abort" << setw(10) << (_count-_goodEnd)
	 << setw(10) << "success" << setw(10) << (_goodEnd) 
	 << setw(10) << "collision" << setw(10) << collision_time
	 << endl;
}

void analysisForNode(End &e, int i) {
    
    string _state;
    if (e.getStartTime() == -1)
	_state = "o";
    else if (e.getStartTime() == -2)
	_state = "xxx";
    else _state = "==err==";

    cout << setw(10) << "node" << setw(10) << (i+1) 
	 << setw(10) << "start" << setw(10) << e.getStart()
         << setw(10) << "delay" << setw(10) << e.getDelayTime()
         << setw(10) << "retrans" << setw(10) << e.getIndex()
         << setw(10) << "collision" << setw(10) << e.getCollision()
         << setw(10) << "finally" << setw(10) << _state
         << endl;
}

void responseForUseSamePreamble()
{
    for( int i = 0; i < lte::preambleNum;  i++ ){
	if( preamble[i] > 1 ){
	//preamble[i] = setProbablity(1); 
	    collision_time++;
	    if (setProbablity(1) == 0) { 
		preamble[i] = 0;
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
		char* fileName;
		string line;
		
		int index = 0;
		double tmp;
		int settime;
		
		switch(lte::EndNum) {
		case 100:
			fileName = "betabase.txt";
			break;
		case 1000:
			fileName = "betabase1000.txt";
			break;
		case 5000:
			fileName = "betabase5000.txt";
			break;
		case 10000:
			fileName = "betabase10000.txt";
			break;
		case 30000:
			fileName = "betabase30000.txt";
			break;
		default:
			cout << lte::EndNum << " is not included, please choose 100, 1000, 5000, 10000 or 30000!!!" << endl;
			exit(1);
		}
		
		ifstream inFile(fileName);
		
		while(getline(inFile, line)) {
			tmp = atof(line.c_str());
			settime = (int)floor(tmp*2000.0);
			end[index].setStartTime(settime*5 + 1);
			index++;
		}
	}
}
