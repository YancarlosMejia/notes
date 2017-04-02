#include <iostream>
using namespace std;

#include "MPRNG.h"

#include "q2printer.h"
#include "q2tallyVotes.h"
#include "q2voter.h"

MPRNG mprng;

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

    mprng.seed(seed);                                                                                            //populate random generator with seed
    Printer printer(tourSize);                                                                                          //create printer
    TallyVotes tallier(groupSize, printer);                                                                             //create vote tallier
    Voter *voters[tourSize];                                                                                            //create array of voters

    for(int i = 0; i < tourSize; i++){                                                                                  //initialize each voters
        voters[i] = new Voter(i, tallier, printer);
    }//for

    for(int i = 0; i < tourSize; i++){                                                                                  //wait for each voter to finish
        delete voters[i];
    }//for
}
