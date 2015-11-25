#include "q3printer.h"
#include "q3tallyVotes.h"
#include "q3voter.h"

#include <iostream>
using namespace std;


#if defined( IMPLTYPE_TASK )
TallyVotes::TallyVotes(unsigned int group, Printer &printer) :
    group(group), printer(printer){}


TallyVotes::Tour TallyVotes::vote( unsigned int newid, Tour newballot ){
    id = newid;
    ballot = newballot;
    return ballot;
}

void TallyVotes::main() {
    for(;;){
        unsigned int queue[group];
        for(unsigned int i = 0 ; i < group; i++){
            _Accept(~TallyVotes){
                return;
            } or _Accept(vote){
                queue[i] = id;
                if(ballot == Picture){                                                                                              //cast vote
                    picCount += 1;
                } else {
                    statCount += 1;
                }//if
                printer.print(id, Voter::Vote, ballot);                                                                             //print status vote
                printer.print(id, Voter::Block, i+1);
            }

            if(i == group -1){
                printer.print(id, Voter::Complete);                                                                             //print complete
                res = (picCount > statCount) ? Picture : Statue;
                picCount = 0;
                statCount = 0;
            }
        }

        for(unsigned int i = 0; i < group; i++){
            printer.print(queue[i], Voter::Unblock, group - (i+1));
            printer.print(queue[i], Voter::Finished, res);

        }
    }
}



#endif
