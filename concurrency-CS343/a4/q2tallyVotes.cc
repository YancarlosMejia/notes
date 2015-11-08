#include <iostream>
using namespace std;

#include "uBarrier.h"
#include "q2tallyVotes.h"
#include "MPRNG.h"

MPRNG *mprng;                                                                                                           //randomizer


#if defined( IMPLTYPE_MC )
TallyVotes::TallyVotes(unsigned int group, Printer &printer) :
    group(group), printer(printer){}

TallyVotes::Tour TallyVotes::vote(unsigned int id, TallyVotes::Tour ballot){
    mlk.acquire();
    if(working) {
        workingLk.wait(mlk);
    }//if
    if(ballot == Picture){
        picCount += 1;
    } else {
        statCount += 1;
    }//if
    printer.print(id, Voter::Vote, ballot);
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
#endif

#if defined( IMPLTYPE_BAR )
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
    }
    return results;
}

void TallyVotes::last(){
    results = (picCount > statCount) ? Picture : Statue;
    picCount = statCount = 0;
    resume();
}

#endif

/*
#if defined( IMPLTYPE_SEM )
TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot){
}
void Voter::main(){
}
#endif*/

Voter::Voter(unsigned int id, TallyVotes &voteTallier, Printer &printer ) :
    id(id), voteTallier(voteTallier), printer(printer) {};

void Voter::main(){
    printer.print(id, Start);                                                                                           //print start state
    yield((*mprng)(0, 19));                                                                                             //yield a random number of times
    TallyVotes::Tour ballot = static_cast<TallyVotes::Tour>( (*mprng)(0,1));                                            //create ballot
    TallyVotes::Tour res = voteTallier.vote(id, ballot);                                                                //vote
    printer.print(id, Finished, res);                                                                                   //print finish state
}

Printer::Printer(unsigned int voters) : voters(voters){
    data = new VoterData*[voters];                                                                                      //initialize array of voters
    for(unsigned int i = 0; i < voters; i++){                                                                           //print header
        cout << "Voter" << i << "\t";
    }//for
    cout << endl;
    for(unsigned int i = 0; i < voters; i++){
        cout << "======= ";
    }//for
    cout << endl;
    for(int i = 0; i < (int)voters; i++){                                                                               //set all voters to null
        data[i] = NULL;
    }//for

}

Printer::~Printer() {
    cout << "=================" << endl;                                                                                //print footer
    cout << "All tours started" << endl;
    delete data;                                                                                                        //delete data array
}

void Printer::print(unsigned int id, Voter::States state) {
    if(data[id]){                                                                                                       //if new data would overwrite, flush
        flush();
    }//if
    data[id] = new VoterData();                                                                                         //create new object to store voter data
    data[id]->state = state;
}

void Printer::print(unsigned int id, Voter::States state, TallyVotes::Tour vote) {
    if(state == Voter::Finished){                                                                                       //Special case for a voter finishing
        flush();
        for(unsigned int i = 0; i < voters; i++){                                                                       //print ... for every other voter and data for finished voter
            if(i == id){
                cout << (char)state << " " << vote;
            } else {
                cout << "...";
            }//if
            cout << "\t";
        }//for
        cout << endl;
        return;
    }//if
    if(data[id]){                                                                                                       //if new data would overwrite, flush
        flush();
    }//if
    data[id] = new VoterData();                                                                                         //create new object to store voter data
    data[id]->state = state;
    data[id]->vote = vote;
}

void Printer::print(unsigned int id, Voter::States state, unsigned int numblocked) {
    if(data[id]){                                                                                                       //if new data would overwrite, flush
        flush();
    }//if
    data[id] = new VoterData();                                                                                         //create new object to store voter data
    data[id]->state = state;
    data[id]->value = numblocked;
}

void Printer::flush() {
    for(int i = 0; i < (int)voters; i++){
        if(data[i]){                                                                                                    //only print if there is new information for that voter
            cout << (char)data[i]->state << " ";                                                                        //print the state
            switch(data[i]->state){
                case Voter::Block:
                case Voter::Unblock:                                                                                    //if voter's state requires a numeric value to be printed print it
                    cout << data[i]->value;
                    break;
                case Voter::Vote:                                                                                       //if voter's state requires letter representation of their vote
                    if(data[i]->vote == TallyVotes::Picture){
                        cout << "p";
                    } else if (data[i]->vote == TallyVotes::Statue) {
                        cout << "s";
                    }
                    break;
                default:
                    break;

            }//switch
        }//if

        cout << "\t";                                                                                                   //print tab spacing
    }//for
    cout << endl;                                                                                                       //line break
    for(int i = 0; i < (int)voters; i++){                                                                               //delete voter data
        delete data[i];
        data[i] = NULL;
    }//for
}

void uMain::main() {
    int tourSize = 6, groupSize = 3, seed = getpid();                                                                   //set default values

    switch(argc){
        case 1:
            try{                                                                                                        //check that value is an integer
                seed = stoi(argv[3]);
            } catch(...){
                cerr << "Error: Seed must be an integer." << endl;
                exit(-1);
            }//try

            if(seed <= 0){                                                                                              //check that value is in valid range
                cerr << "Error: Seed must be greater than 0." << endl;
                exit(-1);
            }//if
        case 3:
            try{                                                                                                        //check that value is an integer
                groupSize = stoi(argv[2]);
            } catch(...){
                cerr << "Error: Group size must be an integer." << endl;
                exit(-1);
            }//try

            if(groupSize <= 0){                                                                                         //check that value is in valid range
                cerr << "Error: Group size must be greater than 0." << endl;
                exit(-1);
            }//if

            if(groupSize % 2 == 0){                                                                                     //check that groups are an odd size
                cerr << "Error: Group size must be odd." << endl;
                exit(-1);
            }//if
        case 2:
            try{                                                                                                        //check that value is an integer
                tourSize = stoi(argv[1]);
            } catch(...){
                cerr << "Error: Tour size must be an integer." << endl;
                exit(-1);
            }//try

            if(tourSize <= 0){                                                                                          //check that value is in valid range
                cerr << "Error: Tour size must be greater than 0." << endl;
                exit(-1);
            }//if

            if(tourSize % groupSize != 0){                                                                              //check that tour size is divisible by group size
                cerr << "Error: Tour size must be divisible by group size." << endl;
                exit(-1);
            }//if
    }//switch

    mprng = new MPRNG(seed);                                                                                            //populate random generator with seed
    Printer printer(tourSize);                                                                                          //create printer
    TallyVotes tallier(groupSize, printer);                                                                             //create vote tallier
    Voter *voters[tourSize];                                                                                            //create array of voters

    for(int i = 0; i < tourSize; i++){                                                                                  //initialize each voter
        voters[i] = new Voter((unsigned int)i, tallier, printer);
    }//for

    for(int i = 0; i < tourSize; i++){                                                                                  //wait for each voter to finish
        delete voters[i];
    }//for
}
