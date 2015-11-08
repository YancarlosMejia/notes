_Monitor Printer;

#if defined( IMPLTYPE_MC )
class TallyVotes {
  public:
    enum Tour { Picture, Statue };
  private:
    unsigned int group;
    uOwnerLock mlk;
    uCondLock clk;
    uCondLock workingLk;
    int groupCount = 0;
    bool working = false;
#elif defined( IMPLTYPE_BAR )
_Cormonitor TallyVotes : public uBarrier {
    public:
    enum Tour { Picture, Statue };
    void last();
  private:
#elif defined( IMPLTYPE_SEM )
class TallyVotes {
#else
    #error unsupported voter type
#endif
    Tour results;
    int picCount = 0;
    int statCount = 0;
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
