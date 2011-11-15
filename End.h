//rxtern int _time;
//extern int preamble[54];
//extern int _count;
//extern int MAX;
//extern int setProbablity(int);
class End {
  public:
    End(){ _setTime = 1; _preamble = 0; _index = 1; _finishTime = 0; _collisionTime = 0;};
    void setpreamble();
    void responseForOnlyOne();
    void settime();
    void id();
    int getCollision() { return _collisionTime;}
    int getFinish() {return _finishTime;}
    int getSettime() {return _setTime;}
  private:
    int _setTime;
    int _preamble;
    // to record number of retransmission, _index = -1 means success
    // _index = -2 means abort
    int _index;
    int _finishTime;
    int _collisionTime;
    int _CountCeil(int t); //ceiling

    //int _setTime;
    //int _preamble;

    //int _CountCeil(int t); //ceiling
	
    //int _index;
};
