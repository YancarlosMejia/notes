#ifndef PRINTER_H
#define PRINTER_H

#include "q2voter.h"

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

#endif
