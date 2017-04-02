#ifndef TALLYVOTES_H
#define TALLYVOTES_H

#include "MPRNG.h"

_Monitor Printer;

/*****************************************************************************
 Vote Tallier Object
     An object to tally votes from voters for a specific group safely

     Contains vote function that voters call to cast vote
*****************************************************************************/

#if defined( IMPLTYPE_MC )
class TallyVotes {
  public:
    enum Tour { Picture, Statue };
  private:
    uOwnerLock mlk; //lock to provide mutual exclusion
    uCondLock clk; //lock to provide synchronization
    uCondLock workingLk; //lock to prevent barging
    int groupCount = 0; //count of how many voters have voted to this group
    int picCount = 0; //count of votes for picture tour
    int statCount = 0; //count of votes for statue tour
    bool working = false; //flag to block barging
    Tour results; //results of the vote
    unsigned int group; //number of voters per group
    Printer &printer; //reference to printer for printing vote state
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
    Tour results; // results of vote
    int picCount = 0; //count of votes for picture tour
    int statCount = 0; //count of votes for statue tour
    Printer &printer; //reference to printer for printing voter state
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
    uSemaphore mlk; //semaphore for mutual exclusion
    uSemaphore clk; //semaphore for synchronization
    uSemaphore workingLk; //semaphore to prevent barging
    int groupCount = 0; //count of number of voters
    int picCount = 0; //count of votes for picture tour
    int statCount = 0; //count of votes for statue tour
    Tour results; //results of vote
    bool working = false; //barging flag
    unsigned int group; // number of people per group
    Printer &printer; //reference to printer for printing voter state
  public:
    TallyVotes( unsigned int group, Printer &printer );
    Tour vote( unsigned int id, Tour ballot );
};

#else
    #error unsupported voter type
#endif


#endif
