_Monitor Printer;

#if defined( IMPLTYPE_MC )
class TallyVotes {
  public:
    enum Tour { Picture, Statue };
  private:
    uOwnerLock mlk;
    uCondLock clk;
    uCondLock workingLk;
    int picCount = 0;
    int statCount = 0;
    int groupCount = 0;
    bool working = false;
    Tour results;
#elif defined( IMPLTYPE_BAR )
_Cormonitor TallyVotes : public uBarrier {
#elif defined( IMPLTYPE_SEM )
class TallyVotes {
#else
    #error unsupported voter type
#endif
    unsigned int group;
    Printer &printer;
  public:
    TallyVotes( unsigned int group, Printer &printer );
    Tour vote( unsigned int id, Tour ballot );
};


_Task Voter {
  unsigned int id;
  TallyVotes & voteTallier;
  Printer &printer;

  void main();
  public:
    enum States { Start = 'S', Vote = 'V', Block = 'B', Unblock = 'U',
                   Complete = 'C', Finished = 'F' };
    Voter( unsigned int id, TallyVotes &voteTallier, Printer &printer );
};

struct VoterData{
  Voter::States state;
  unsigned int value;
  TallyVotes::Tour vote;
};

_Monitor Printer {
  unsigned int voters;
  VoterData **data;
  void flush();
  public:
    Printer( unsigned int voters );
    ~Printer();
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour vote );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
};
