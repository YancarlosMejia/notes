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
    if(counter != group){                                                                                               //if not last print blocking messages
        printer.print(id, Voter::Block, counter);
        wait();                                                                                                         //wait until group is full
        counter -= 1;
        printer.print(id, Voter::Unblock, counter);
    } else {
        counter -= 1;
        printer.print(id, Voter::Complete);                                                                             //print complete
        res = (picCount > statCount) ? Picture : Statue;                                                                //calculate results
        signalAll();                                                                                                    //signal all waiting threads
    }//if
    picCount = 0;                                                                                                       //reset counters
    statCount = 0;
    return res;
}

void TallyVotes::wait() {
    bench.wait();                                                                                                       // wait until signalled
    while ( rand() % 5 == 0 ) {                                                                                         // multiple bargers allowed
        _Accept( vote ) {                                                                                               // accept barging callers
        } _Else {                                                                                                       // do not wait if no callers
        } // Accept
    } // while
}
void TallyVotes::signalAll() {
    while ( ! bench.empty() ) bench.signal(); // drain the condition
}
