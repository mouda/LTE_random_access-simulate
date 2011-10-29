#include <iostream>

using namespace std

int time = 1;// the order of the subframe 
int preamnble[54];
int MAX = 10;
int count = 0;//to record the tutle number of successful and abort End 
void respForUseSamePreamble();//for 

// to set the probablity of successful receive, the input is the number of the restransmission
int setProbablity( int retransmit ); 

int main {
  End end[100];
  for(; count<100; time +=5 ){
    for( int n = 0; n < 100; n++ )
      end[n].setpreamble      
    responseForOnlyOne();
    for( int n = 0; n < 100; n++ ){
      end[n].responseForOnlyOne();
      end[n].settime()
    }
  }
  return 0;
}

void respForUseSamePreamble()
{
  for( int i = 1; i < 54, i++ ){
    if( preamnble[i] > 1 ){
      preamnble[i] = setProbablity(1);
    }
  }
}
