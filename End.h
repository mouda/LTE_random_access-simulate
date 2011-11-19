class End {
  public:
    End(){ _setTime = 1; _preamble = 0; _index = 1; };
    void setpreamble();
    void responseForOnlyOne();
    void settime();
    void id();
	void setStartTime(int t) {_setTime = t;}
  private:
    int _setTime;
    int _preamble;
    int _CountCeil(int t); //ceiling
	
    // to record number of retransmission, _index = -1 means success
    // _index = -2 means abort
    int _index;
};
