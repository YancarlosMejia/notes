#include <iostream>
using namespace std;

#include "q2printer.h"
#include "q2tallyVotes.h"
#include "q2voter.h"

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
    for(unsigned int i = 0; i < voters; i++){                                                                           //set all voters to null
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

