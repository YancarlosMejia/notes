#include "q2printer.h"
#include "q2tallyVotes.h"
#include "q2voter.h"

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
    printer.print(id, Voter::Vote, ballot);                                                                             //print
    groupCount += 1;
    if(groupCount < (int)group){
        printer.print(id, Voter::Block, groupCount);
        clk.wait(mlk);
        printer.print(id, Voter::Unblock, groupCount--);
        if(groupCount == 0) {
            workingLk.broadcast();
            working = false;
        }//if
    } else {
        working = true;
        results = (picCount > statCount) ? Picture : Statue;
        picCount = statCount = 0;
        printer.print(id, Voter::Complete);
        groupCount -= 1;
        clk.broadcast();
    }//if
    mlk.release();
    return results;
}
#elif defined( IMPLTYPE_BAR )
TallyVotes::TallyVotes(unsigned int group, Printer &printer) : uBarrier(group), printer(printer){}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot){
    if(ballot == Picture){
        picCount += 1;
    } else {
        statCount += 1;
    }//if

    printer.print(id, Voter::Vote, ballot);
    if(waiters() + 1 != total()){
        printer.print(id, Voter::Block, waiters() + 1);
        uBarrier::block();
        printer.print(id, Voter::Unblock, waiters() + 1);
    } else {
        printer.print(id, Voter::Complete);
        uBarrier::block();
    }//if
    return results;
}

void TallyVotes::last(){
    results = (picCount > statCount) ? Picture : Statue;
    picCount = statCount = 0;
    resume();
}

#elif defined( IMPLTYPE_SEM )
TallyVotes::TallyVotes(unsigned int group, Printer &printer) :
    group(group), printer(printer), mlk(1), clk(0), workingLk(0){}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot){
    mlk.P();
    if(working) {
        mlk.V();
        workingLk.P();
    }//if
    if(ballot == Picture){
        picCount += 1;
    } else {
        statCount += 1;
    }//if
    groupCount += 1;
    printer.print(id, Voter::Vote, ballot);
    if(clk.counter() + (int)group !=  1){
        printer.print(id, Voter::Block, -clk.counter() + 1);
        mlk.V();
        clk.P();
        groupCount -= 1;
        printer.print(id, Voter::Unblock, groupCount);
        if(clk.empty()) {
            workingLk.V(group);
            working = false;
        }//if
    } else {
        working = true;
        results = (picCount > statCount) ? Picture : Statue;
        picCount = statCount = 0;
        printer.print(id, Voter::Complete);
        clk.V(group - 1);
    }//if
    mlk.V();
    return results;
}
#endif
