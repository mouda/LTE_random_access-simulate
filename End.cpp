#include "End.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
extern int _time;
extern int preamble[54];
extern int _count;
extern int MAX;
extern int setProbablity(int);
void End::setpreamble()
{
  if(_setTime != _time) return;
  else {
    _preamble = rand()%54;
    preamble[_preamble]++;
  }
}
void End::responseForOnlyOne()
{
    if (_setTime != _time)
	return;
    if(preamble[_preamble] == 1) {
	//probability base on the retransmission
	preamble[_preamble] = setProbablity(_index);
	/*----debug-----
	cout << _preamble << " : " << preamble[_preamble] << endl;
	//----debug-----*/
    }
}
void End::settime()
{
    if (_setTime != _time)
	return;
    //cout << "settime in, preamble : " << _preamble 
	// << "howmany : " << preamble[_preamble] << endl;
    if(preamble[_preamble] == 1) {
	//cout << "preamble == 1\n";
	id();// case for success
    }
    else if (preamble[_preamble] > 1){
	int tmp = 48 + rand()%20;
	if (tmp % 5 == 0) _setTime += tmp;
	else _setTime += tmp / 5 * 5 + 5;
	//_setTime = [48+rand(20)+SOMETHING];
	_index++;
	if(_index > MAX) {
	    _setTime = -2;
	    _count++;
	}
    }else {
	int tmp2 = 8 + rand()%20;
	if (tmp2 % 5 == 0) _setTime += tmp2;
	else _setTime += tmp2/5*5 + 5;
	//_setTime = [8+rand(20)+SOMETHING];
	//set the next preamble transmission time
	_index++;
	if(_index > MAX){
	    _count++;
	    _setTime = -2;
	}
    }
    //cout << "settime : " << _setTime << endl;
}
void End::id()
{
  //cout << "id success.\n\n";
  if ( setProbablity(_index) == 1 ) {
    _setTime = -1;
    _count++;
  }
  else{
    int tmp = 48 + rand()%20;
    if (tmp % 5 == 0) _setTime += tmp;
    else _setTime += tmp / 5 * 5 + 5;
    _index++;
    if ( _index > MAX){
      _setTime = -2;
      _count++;
    }
  }
}
