class End {
  public:
    End(){ _setTime = 1; _preamble = 0; _index = 0; };
    void setpreamble( int time);
    void responseForOnlyOne( int time);
    void settime( int time);
    void id();
  private:
    int _setTime;
    int _preamble;

    // to record number of retransmission, _index = -1 means success
    // _index = -2 means abort
    int _index;
}
