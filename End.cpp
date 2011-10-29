void End::setpreamble( int time);
{
  if(_setTime != time) return; 
  else {
    _preamble = rand(54); 
    preamnble[_preamble-1]++;
  }

}

void End::responseForOnlyOne()
{
  if(preamnble[_preamble-1] == 1)
    //probability base on the retransmission
    preamnble[_preamble-1] = setProbablity(_index);  

}

void End::settime()
{
  if(preamnble[_preamble-1] == 1) id();// case for success
  else if (preamnble[_preamble-1] > 1){
    _setTime = [48+rand(20)+SOMETHING];
    _index++;
    if(index > MAX) {
      _setTime = -2;
      count++;
    }
  }else {
    _setTime = [8+rand(20)+SOMETHING];//set the next preamble transmission time
    _index++
    if(index > MAX){
      count++;
      _setTime = -2;
    }
  }
}

void End::id()
{
  if ( setProbablity == 1 ) {
    _setTime = -1;
    count++;
  }
  else{
    _setTime = [48+rand(20)+SOMETHING];
    index++;
    if ( index > MAX){
      _setTime = -2;
      count++;
    }
  }
}
