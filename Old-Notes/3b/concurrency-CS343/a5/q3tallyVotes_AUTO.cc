#include "q3printer.h"
#include "q3tallyVotes.h"
#include "q3voter.h"

#include <iostream>
using namespace std;

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
    if(counter == group){
        printer.print(id, Voter::Complete);
        groupFlag = true;                                                                                               //signal waiting threads to run
        res = (picCount > statCount) ? Picture : Statue;                                                                //calculate results
        counter -= 1;
    } else {
        WAITUNTIL(groupFlag, printer.print(id, Voter::Block, counter), printer.print(id, Voter::Unblock, --counter));   //wait until the group is full
    }//if
    if(counter == 0){
        groupFlag = false;                                                                                              //flip flag to start blocking again
    }//if
    picCount = 0;                                                                                                       //reset counters
    statCount = 0;
    RETURN(res);
}
