#ifndef TALLYVOTES_H
#define TALLYVOTES_H

#include "MPRNG.h"

_Monitor Printer;

/*****************************************************************************
 Vote Tallier Object
     An object to tally votes from voters for a specific group safely

     Contains vote function that voters call to cast vote
*****************************************************************************/

#if defined( IMPLTYPE_EXT )
_Monitor TallyVotes {
  public:
    enum Tour { Picture, Statue };
  private:
    unsigned int picCount = 0;
    unsigned int statCount = 0;
    unsigned int counter = 0;
    Tour res;
    unsigned int group;
    Printer &printer;
  public:
    TallyVotes( unsigned int group, Printer &printer );
    Tour vote( unsigned int id, Tour ballot );
};

#elif defined( IMPLTYPE_INT )
_Monitor TallyVotes {
public:
    enum Tour { Picture, Statue };
  private:
    uCondition notFull;
    unsigned int picCount = 0;
    unsigned int statCount = 0;
    unsigned int counter = 0;
    unsigned int group;
    Tour res;
    Printer &printer;
  public:
    TallyVotes( unsigned int group, Printer &printer );
    Tour vote( unsigned int id, Tour ballot );
};

#elif defined( IMPLTYPE_INTB )
_Monitor TallyVotes {
  public:
    enum Tour { Picture, Statue };
  private:
    uCondition bench;
    unsigned int picCount = 0;
    unsigned int statCount = 0;
    unsigned int counter = 0;
    unsigned int group;
    Tour res;
    Printer &printer;
    void wait();
    void signalAll();
  public:
    TallyVotes( unsigned int group, Printer &printer );
    Tour vote( unsigned int id, Tour ballot );
};

#elif defined( IMPLTYPE_AUTO )
#include "AutomaticSignal.h"

_Monitor TallyVotes {
  public:
    enum Tour { Picture, Statue };
  private:
    AUTOMATIC_SIGNAL;
    unsigned int picCount = 0;
    unsigned int statCount = 0;
    unsigned int counter = 0;
    bool groupFlag = false;
    Tour res;
    unsigned int group;
    Printer &printer;
public:
    TallyVotes( unsigned int group, Printer &printer );
    Tour vote( unsigned int id, Tour ballot );
};

#elif defined( IMPLTYPE_TASK )
_Monitor TallyVotes {
  public:
    TallyVotes( unsigned int group, Printer &printer );
    enum Tour { Picture, Statue };
    Tour vote( unsigned int id, Tour ballot );
};
#else
#error unsupported voter type
#endif

#endif
