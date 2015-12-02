#include "q3printer.h"
#include "q3tallyVotes.h"
#include "q3voter.h"

#include <iostream>
using namespace std;

TallyVotes::TallyVotes(unsigned int group, Printer &printer) :
    group(group), printer(printer){}


TallyVotes::Tour TallyVotes::vote( unsigned int newid, Tour newballot ){
    id = newid;                                                                                                         //store necessary values for main
    ballot = newballot;
    return ballot;
}

void TallyVotes::main() {
    for(;;){
        unsigned int queue[group];                                                                                      //record order of entrance
        for(unsigned int i = 0 ; i < group; i++){
            _Accept(~TallyVotes){                                                                                       //break on destructor
                return;
            } or _Accept(vote){                                                                                         //accept calls to vote
                queue[i] = id;
                if(ballot == Picture){                                                                                  //cast vote
                    picCount += 1;
                } else {
                    statCount += 1;
                }//if
                printer.print(id, Voter::Vote, ballot);                                                                 //print status vote and block
                printer.print(id, Voter::Block, i+1);
            }//Accept
            if(i == group -1){
                printer.print(id, Voter::Complete);                                                                     //print complete
                res = (picCount > statCount) ? Picture : Statue;                                                        //calculate results
                picCount = 0;                                                                                           //reset counters
                statCount = 0;
            }//if
        }//for
        for(unsigned int i = 0; i < group; i++){                                                                        //unblock and finish threads in order
            printer.print(queue[i], Voter::Unblock, group - (i+1));
            printer.print(queue[i], Voter::Finished, res);
        }//for
    }//for
}
