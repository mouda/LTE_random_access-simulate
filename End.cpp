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
    }
}
void End::settime()
{
    if (_setTime != _time)
	return;
    if(preamble[_preamble] == 1) {
	id();// case for success
    }
    else if (preamble[_preamble] > 1){
	int Fwait = rand() % 5 + 1;
	_collision++;
	_setTime += _CountCeil(/*lte::firstWaiting*/ (Fwait + 3) + lte::secondWaiting + rand()%lte::RandomBackoffIndex);
	_index++;
	if(_index > lte::MAX) {
	    _setTime = -2;
	    _finish = _time + (Fwait + 3) + lte::secondWaiting;
	    _count++;
	}
    }else {
	_setTime += _CountCeil(lte::firstWaiting + rand()%lte::RandomBackoffIndex);
	//set the next preamble transmission time
	_index++;
	if(_index > lte::MAX){
	    _count++;
	    _setTime = -2;
	    _finish = _time + lte::firstWaiting;
	}
    }
}
void End::id()
{
  int Fwait = rand() % 5 + 1;
  if ( setProbablity(_index) == 1 ) {
    int Swait = rand() % 48 + 1;
    _setTime = -1;
    _goodEnd++;
    _count++;
    _finish = _time + (3 +Fwait) + Swait;
  } else {
	_setTime += _CountCeil(/*lte::firstWaiting*/ (Fwait + 3) + lte::secondWaiting + rand()%lte::RandomBackoffIndex);
	_index++;
	if ( _index > lte::MAX ) {
	    _setTime = -2;
	    _count++;
	    _finish = _time + (3 + Fwait) + lte::secondWaiting;
	}
  }
}

int End::_CountCeil(int t) {
	if (t % 5 == 0) return t;
	else return (t%5 + 1)*5;
}
