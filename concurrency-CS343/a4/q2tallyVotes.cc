#include <iostream>
using namespace std;

#include "q2tallyVotes.h"
#include "MPRNG.h"

MPRNG *mprng;                                                                   //randomizer for yield values

TallyVotes::TallyVotes(unsigned int group, Printer &printer) :
    group(group), printer(printer){}

Voter::Voter(unsigned int id, TallyVotes &voteTallier, Printer &printer ) :
    id(id), voteTallier(voteTallier), printer(printer) {};


#if defined( IMPLTYPE_MC )
TallyVotes::Tour TallyVotes::vote(unsigned int id, TallyVotes::Tour ballot){
    mlk.acquire();
    if(working) workingLk.wait(mlk);
    TallyVotes::Tour ret;

    if(ballot == Picture){
        picCount += 1;
    } else {
        statCount += 1;
    }
    printer.print(id, Voter::Vote, ballot);

    groupCount += 1;
    if(groupCount < (int)group){\
        printer.print(id, Voter::Block, groupCount);
        clk.wait(mlk);
        printer.print(id, Voter::Unblock, groupCount--);
        if(groupCount == 0) {
            workingLk.broadcast();
            working = false;
        }
    } else {
        working = true;
        ret = (picCount > statCount) ? Picture : Statue;
        picCount = statCount = 0;
        printer.print(id, Voter::Complete);
        groupCount -= 1;
        clk.broadcast();
    }
    mlk.release();
    return ret;
}

void Voter::main(){
    printer.print(id, Start);
    yield((*mprng)(0, 19));
    TallyVotes::Tour ballot = static_cast<TallyVotes::Tour>( (*mprng)(0,1));
    TallyVotes::Tour res = voteTallier.vote(id, ballot);
    printer.print(id, Finished, res);
}
#endif

/*#if defined( IMPLTYPE_BAR )
Tour TallyVotes::vote(unsigned int id, Tour ballot){
}
void Voter::main(){
}
#endif

#if defined( IMPLTYPE_SEM )
TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot){
}
void Voter::main(){
}
#endif*/


Printer::Printer(unsigned int voters) : voters(voters){
    data = new VoterData*[voters];


    for(unsigned int i = 0; i < voters; i++){
        cout << "Voter" << i << "\t";
    }
    cout << endl;

    for(unsigned int i = 0; i < voters; i++){
        cout << "======= ";
    }
    cout << endl;

    for(int i = 0; i < (int)voters; i++){
        data[i] = NULL;
    }

}

Printer::~Printer() {
    cout << "=================" << endl;
    cout << "All tours started" << endl;
    delete data;
}

void Printer::print(unsigned int id, Voter::States state) {
    if(data[id]){
        flush();
    }
    data[id] = new VoterData();
    data[id]->state = state;

}
void Printer::print(unsigned int id, Voter::States state, TallyVotes::Tour vote) {
    //Special case for task finishing
    if(state == Voter::Finished){
        flush();

        for(unsigned int i = 0; i < voters; i++){
            if(i == id){
                cout << (char)state << " " << vote;
            } else {
                cout << "...";
            }
            cout << "\t";
        }
        cout << endl;
        return;
    }


    if(data[id]){
        flush();
    }

    data[id] = new VoterData();
    data[id]->state = state;
    data[id]->vote = vote;
}
void Printer::print(unsigned int id, Voter::States state, unsigned int numblocked) {
    if(data[id]){
        flush();
    }

    data[id] = new VoterData();
    data[id]->state = state;
    data[id]->value = numblocked;
}

void Printer::flush() {
    for(int i = 0; i < (int)voters; i++){
        if(data[i]){
            cout << (char)data[i]->state << " ";
            switch(data[i]->state){
                case Voter::Block:
                case Voter::Unblock:
                    cout << data[i]->value;
                    break;
                case Voter::Vote:
                    if(data[i]->vote == TallyVotes::Picture){
                        cout << "p";
                    } else if (data[i]->vote == TallyVotes::Statue) {
                        cout << "s";
                    }
                    break;
                default:
                    break;

            }
        }

        cout << "\t";
    }
    cout << endl;

    for(int i = 0; i < (int)voters; i++){
        delete data[i];
        data[i] = NULL;
    }
}


void uMain::main() {
    int tourSize = 6, groupSize = 3, seed = getpid();

    switch(argc){
        case 1:
            try{
                seed = stoi(argv[3]);
            } catch(...){
                cerr << "Error: Seed must be an integer." << endl;
                exit(-1);
            }//try

            if(seed <= 0){
                cerr << "Error: Seed must be greater than 0." << endl;
                exit(-1);
            }//if
        case 3:
            try{
                groupSize = stoi(argv[2]);
            } catch(...){
                cerr << "Error: Group size must be an integer." << endl;
                exit(-1);
            }//try

            if(groupSize <= 0){
                cerr << "Error: Group size must be greater than 0." << endl;
                exit(-1);
            }//if

            if(groupSize % 2 == 0){
                cerr << "Error: Group size must be odd." << endl;
                exit(-1);
            }//if
        case 2:
            try{
                tourSize = stoi(argv[1]);
            } catch(...){
                cerr << "Error: Tour size must be an integer." << endl;
                exit(-1);
            }//try

            if(tourSize % groupSize != 0){
                cerr << "Error: Tour size must be divisible by group size." << endl;
                exit(-1);
            }//if
    }//switch

    mprng = new MPRNG(seed);
    Printer printer(tourSize);
    TallyVotes tallier(groupSize, printer);
    Voter *voters[tourSize];

    for(int i = 0; i < tourSize; i++){
        voters[i] = new Voter((unsigned int)i, tallier, printer);
    }

    for(int i = 0; i < tourSize; i++){
        delete voters[i];
    }
}
