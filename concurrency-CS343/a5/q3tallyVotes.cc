#include "q3printer.h"
#include "q3tallyVotes.h"
#include "q3voter.h"

#include <iostream>
using namespace std;


#if defined( IMPLTYPE_EXT )
TallyVotes::TallyVotes(unsigned int group, Printer &printer) :
    group(group), printer(printer){}

TallyVotes::Tour TallyVotes::vote( unsigned int id, Tour ballot ){
    counter += 1;
    if(ballot == Picture){                                                                                              //cast vote
        picCount += 1;
    } else {
        statCount += 1;
    }//if

    printer.print(id, Voter::Vote, ballot);                                                                             //print status vote
    if(counter != group){                                                                                       //if not last print blocking messages
        printer.print(id, Voter::Block, counter);
        _Accept(vote);
        counter -= 1;
        printer.print(id, Voter::Unblock, counter);
    } else {
        counter -= 1;
        printer.print(id, Voter::Complete);                                                                             //print complete
    }//if
    return (picCount > statCount) ? Picture : Statue;
}




#endif
