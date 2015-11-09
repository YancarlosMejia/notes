#ifndef TALLYVOTES_H
#define TALLYVOTES_H

#include "MPRNG.h"

_Monitor Printer;

#if defined( IMPLTYPE_MC )
class TallyVotes {
  public:
    enum Tour { Picture, Statue };
  private:
    uOwnerLock mlk;
    uCondLock clk;
    uCondLock workingLk;
    int groupCount = 0;
    int picCount = 0;
    int statCount = 0;
    bool working = false;
    Tour results;
    unsigned int group;
    Printer &printer;
  public:
    TallyVotes( unsigned int group, Printer &printer );
    Tour vote( unsigned int id, Tour ballot );
};

#elif defined( IMPLTYPE_BAR )
#include <uBarrier.h>
_Cormonitor TallyVotes : public uBarrier {
  public:
    enum Tour { Picture, Statue };
  private:
    Tour results;
    int picCount = 0;
    int statCount = 0;
    Printer &printer;
  public:
    TallyVotes( unsigned int group, Printer &printer );
    Tour vote( unsigned int id, Tour ballot );
    void last();
};

#elif defined( IMPLTYPE_SEM )
#include <uSemaphore.h>
class TallyVotes {
public:
    enum Tour { Picture, Statue };
  private:
    uSemaphore mlk;
    uSemaphore clk;
    uSemaphore workingLk;
    int groupCount = 0;
    int picCount = 0;
    int statCount = 0;
    Tour results;
    bool working = false;
    unsigned int group;
    Printer &printer;
  public:
    TallyVotes( unsigned int group, Printer &printer );
    Tour vote( unsigned int id, Tour ballot );
};

#else
    #error unsupported voter type
#endif


#endif
