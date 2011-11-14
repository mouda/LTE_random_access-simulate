#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;
//lynn is here
//hello world~
//for parameter not changed!!
const int Simulation_Time = 1000;
const int MAX = 10;
//
//for parameter measuring the efficiency!!!
int finish_time[100];
int access_time = 0;
int collision_time = 0;
//
int time = 1;// the order of the subframe
int preamble[54] = {0};
int count = 0;//to record the tutle number of successful and abort End
void respForUseSamePreamble();//for
// to set the probablity of successful receive, the input is the number of the restransmission
int setProbablity( int );
int main {
  End end[100];
  for(; count < 100 ; time +=5 ){
    for( int n = 0; n < 100; n++ )
      end[n].setpreamble     
        responseForUseSamePreamble();

    /*!!!
      response...: 1. watch the preamble[], if == 1,
      if > 1, handle fail
      2.

      !!!*/
    for( int n = 0; n < 100; n++ ){
      end[n].responseForOnlyOne();
      end[n].settime()
    }

    cout << "time: " << time << "    count: " << count << endl;
  }



  return 0;
}
void respForUseSamePreamble()
{
  for( int i = 1; i < 54, i++ ){
    if( preamble[i] > 1 ){
      preamble[i] = setProbablity(1);
    }
  }
}
int setProbablity( int retransmit )
{
  double p = 1 - exp((double) retransmit*(-1));
  int p1 = p*1000;
  int p2 = (1.0 - p)*1000;

  srand(time(NULL));
  int key = rand() % (p1 + p2);

  if (key <= p1) return 1;
  else return 0;
}

