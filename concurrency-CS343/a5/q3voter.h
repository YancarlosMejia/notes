#ifndef VOTER_H
#define VOTER_H

#include "q3tallyVotes.h"

/*****************************************************************************
 Voter Task
     A concurrent task for voting for a tour type
*****************************************************************************/
_Task Voter {
  unsigned int id; //number to identify the voter
  TallyVotes &voteTallier;  //reference to a class for tally votes
  Printer &printer;  //reference to a class for printing voter state

  void main();
  public:
    enum States { Start = 'S', Vote = 'V', Block = 'B', Unblock = 'U',
                   Complete = 'C', Finished = 'F' };
    Voter( unsigned int id, TallyVotes &voteTallier, Printer &printer );
};


#endif
