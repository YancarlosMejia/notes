#include "q2printer.h"
#include "q2tallyVotes.h"
#include "q2voter.h"

#include <iostream>
using namespace std;

#if defined( IMPLTYPE_MC )
TallyVotes::TallyVotes(unsigned int group, Printer &printer) :
    group(group), printer(printer){}

TallyVotes::Tour TallyVotes::vote(unsigned int id, TallyVotes::Tour ballot){
    mlk.acquire();                                                                                                      //acquire lock for mutual exclusion
    if(working) {                                                                                                       //check barging flag and wait if appropriate
        workingLk.wait(mlk);
    }//if
    if(ballot == Picture){                                                                                              //cast vote
        picCount += 1;
    } else {
        statCount += 1;
    }//if
    printer.print(id, Voter::Vote, ballot);                                                                             //print status vote
    groupCount += 1;
    if(groupCount < (int)group){                                                                                        //if group is not full block until it is
        printer.print(id, Voter::Block, groupCount);                                                                    //print status blocked
        clk.wait(mlk);
        groupCount -= 1;
        printer.print(id, Voter::Unblock, groupCount);                                                                  //print status unblocked
    } else {                                                                                                            //if last voter into the group calculate result
        working = true;
        results = (picCount > statCount) ? Picture : Statue;
        picCount = statCount = 0;
        printer.print(id, Voter::Complete);
        groupCount -= 1;
        clk.broadcast();                                                                                                //trigger all voters waiting in group
    }//if
    if(groupCount == 0) {
        workingLk.broadcast();
        working = false;
    }//if
    mlk.release();
    return results;
}
#elif defined( IMPLTYPE_BAR )
TallyVotes::TallyVotes(unsigned int group, Printer &printer) : uBarrier(group), printer(printer){}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot){
    if(ballot == Picture){                                                                                              //cast vote
        picCount += 1;
    } else {
        statCount += 1;
    }//if

    printer.print(id, Voter::Vote, ballot);                                                                             //print status vote
    if(waiters() + 1 != total()){                                                                                       //if not last print blocking messages
        printer.print(id, Voter::Block, waiters() + 1);
        uBarrier::block();
        printer.print(id, Voter::Unblock, waiters() + 1);
    } else {
        printer.print(id, Voter::Complete);                                                                             //print complete
        uBarrier::block();
    }//if
    return results;
}

void TallyVotes::last(){
    results = (picCount > statCount) ? Picture : Statue;                                                                //calculate results
    picCount = statCount = 0;                                                                                           //reset counters
    resume();                                                                                                           //unblock
}

#elif defined( IMPLTYPE_SEM )
TallyVotes::TallyVotes(unsigned int group, Printer &printer) :
    group(group), printer(printer), mlk(1), clk(0), workingLk(0){}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot){
    mlk.P();                                                                                                            //acquire semaphore for mutual exclusion
    if(working) {                                                                                                       //if blocked on barging flag release mutual exclusion semaphore
        mlk.V();
        workingLk.P();
    }//if
    if(ballot == Picture){                                                                                              //cast vote
        picCount += 1;
    } else {
        statCount += 1;
    }//if
    groupCount += 1;
    printer.print(id, Voter::Vote, ballot);                                                                             //print vote status
    if(clk.counter() + (int)group !=  1){                                                                               //if not last voter into group
        printer.print(id, Voter::Block, -clk.counter() + 1);                                                            //print blocked status
        mlk.V();                                                                                                        //release mutual exclusion semaphore
        clk.P();                                                                                                        //wait on synchronization semaphore
        groupCount -= 1;
        printer.print(id, Voter::Unblock, groupCount);                                                                  //print unblock status
    } else {
        working = true;                                                                                                 //set barging flag
        results = (picCount > statCount) ? Picture : Statue;                                                            //calculate result
        picCount = statCount = 0;                                                                                       //reset counters
        printer.print(id, Voter::Complete);                                                                             //print complete status
        clk.V(group - 1);                                                                                               //signal waiting voters
    }//if
    if(clk.empty()) {                                                                                               //if last voter out of group trip barging flag
        workingLk.V(group);
        working = false;
    }//if
    mlk.V();                                                                                                            //release mutual exclusion semaphore
    return results;
}
#endif
