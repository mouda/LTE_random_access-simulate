#include "End.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "main.h"

using namespace std;
extern int _time;
extern int* preamble;
extern int _count;
extern int _goodEnd;
extern int setProbablity(int);

void End::setpreamble()
{
  if(_setTime != _time) return;
  else {
    _preamble = rand()%lte::preambleNum;
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
	_setTime += _CountCeil(lte::firstWaiting + lte::secondWaiting + rand()%lte::RandomBackoffIndex);
	//_setTime = [48+rand(20)+SOMETHING];
	_index++;
	if(_index > lte::MAX) {
	    _setTime = -2;
	    _count++;
	}
    }else {
	_setTime += _CountCeil(lte::firstWaiting + rand()%lte::RandomBackoffIndex);
	//set the next preamble transmission time
	_index++;
	if(_index > lte::MAX){
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
	_goodEnd++;
    _count++;
  }
  else{
	_setTime += _CountCeil(lte::firstWaiting + lte::secondWaiting + rand()%lte::RandomBackoffIndex);
    _index++;
    if ( _index > lte::MAX){
      _setTime = -2;
      _count++;
    }
  }
}

int End::_CountCeil(int t) {
	if (t % 5 == 0) return t;
	else return (t%5 + 1)*5;
}
