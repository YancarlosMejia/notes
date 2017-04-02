#ifndef PRINTER_H
#define PRINTER_H

#include "q2voter.h"

/*****************************************************************************
 Voter Data Object
     An object to store data about the voter for the printer buffer
*****************************************************************************/

struct VoterData{
  Voter::States state; //state of voter
  unsigned int value; //numerical value for blocked and unblocked state
  TallyVotes::Tour vote; //vote value for voted and finished states
};

/*****************************************************************************
 Printer Object
     An object to printer voter state efficiently

     Contains print function that record data for printing and a flush function
      that outputs data
*****************************************************************************/

_Monitor Printer {
  unsigned int voters; //number of voters
  VoterData **data; //array of voter data
  void flush();
  public:
    Printer( unsigned int voters );
    ~Printer();
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour vote );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
};

#endif
