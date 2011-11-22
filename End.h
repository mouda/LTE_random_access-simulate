class End {
  public:
    End(){ _setTime = 1; _preamble = 0; _index = 1; _finish = 0; _collision = 0; _start = 0;};
    void setpreamble();
    void responseForOnlyOne();
    void settime();
    void id();
    void setStartTime(int t) { _setTime = t; _start = t;}
    int getStartTime() { return _setTime; }
    int getDelayTime() { return (_finish - _start); }
    int getIndex() { return _index; }
    int getCollision() { return _collision; }
    int getStart() { return _start; }
  private:
    int _setTime;
    int _preamble;
    int _CountCeil(int t); //ceiling
    int _finish;
    int _collision;
    int _start;
	
    // to record number of retransmission, _index = -1 means success
    // _index = -2 means abort
    int _index;
};
