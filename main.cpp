#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "End.h"
using namespace std;
//lynn is here   jas try
//hello world~
//for parameter not changed!!
int Simulation_Time = 1000;
int MAX = 10;
//
//for parameter measuring the efficiency!!!
int finish_time[100];
int access_time = 0;
int collision_time = 0;
//
int _time = 1;// the order of the subframe
int preamble[54] = {0};
int _count = 0;//to record the tutle number of successful and abort End
void responseForUseSamePreamble();//for
// to set the probablity of successful receive, the input is the number of the restransmission
int setProbablity( int );
int main() {
    End end[100];
    srand(time(NULL));
    for(; _count < 100 ; _time +=5 ){
	for( int n = 0; n < 100; n++ )
	    end[n].setpreamble(); 
	/*-----debug-----
	for (int i = 0; i < 54; i++)
	    cout << i << " : " << preamble[i] << endl;
	//-----debug-----*/
	responseForUseSamePreamble();
	/*-----debug-----
	for (int i = 0; i < 54; i++)
	    cout << i << " : " << preamble[i] << endl;
	//-----debug-----*/
	for( int n = 0; n < 100; n++ ){
	    end[n].responseForOnlyOne();
	    end[n].settime();
	}
 
	cout << _time << "\t" << _count << endl;
	
	for (int i = 0; i < 54; i++) {
	    preamble[i] = 0;
	}
    }

    return 0;
}
void responseForUseSamePreamble()
{
    for( int i = 0; i < 54;  i++ ){
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
