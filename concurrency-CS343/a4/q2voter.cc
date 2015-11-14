#include "q2tallyVotes.h"
#include "q2printer.h"
#include "q2voter.h"

extern MPRNG mprng;

Voter::Voter(unsigned int id, TallyVotes &voteTallier, Printer &printer ) :
    id(id), voteTallier(voteTallier), printer(printer) {};

void Voter::main(){
    yield(mprng(19));                                                                                                   //yield a random number of times
    printer.print(id, Voter::States::Start);                                                                            //print start state
    TallyVotes::Tour ballot = TallyVotes::Tour(mprng(1));                                                               //create ballot
    TallyVotes::Tour res = voteTallier.vote(id, ballot);                                                                //vote
    printer.print(id, Finished, res);                                                                                   //print finish state
}

