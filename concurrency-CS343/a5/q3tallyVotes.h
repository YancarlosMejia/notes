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
    unsigned int picCount = 0;
    unsigned int statCount = 0;
    unsigned int counter = 0;
    unsigned int group;
    Printer &printer;
    void flush();
  public:
    TallyVotes( unsigned int group, Printer &printer );
    enum Tour { Picture, Statue };
    Tour vote( unsigned int id, Tour ballot );
};

#elif defined( IMPLTYPE_INT )
_Monitor TallyVotes {
  public:
    TallyVotes( unsigned int group, Printer &printer );
    enum Tour { Picture, Statue };
    Tour vote( unsigned int id, Tour ballot );
};

#elif defined( IMPLTYPE_INTB )
_Monitor TallyVotes {
    uCondition bench;
    void wait();
    void signalAll();
  public:
    TallyVotes( unsigned int group, Printer &printer );
    enum Tour { Picture, Statue };
    Tour vote( unsigned int id, Tour ballot );
};

#elif defined( IMPLTYPE_AUTO )

_Monitor TallyVotes {
public:
    TallyVotes( unsigned int group, Printer &printer );
    enum Tour { Picture, Statue };
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
