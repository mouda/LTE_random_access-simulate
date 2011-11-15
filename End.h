//rxtern int time;
//extern int preamble[54];
//extern int _count;
//extern int MAX;
//extern int setProbablity(int);
class End {
  public:
    End(){ _setTime = 1; _preamble = 0; _index = 0; };
    void setpreamble();
    void responseForOnlyOne();
    void settime();
    void id();
  private:
    int _setTime;
    int _preamble;
    // to record number of retransmission, _index = -1 means success
    // _index = -2 means abort
    int _index;
};
