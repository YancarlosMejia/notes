#include <iostream>
#include <fstream>
using namespace std;

#include "q1binsertsort.h"

/****************************************************
* Dummy
*  used for demonstrating adaptabilty of binsertsort
*****************************************************/

Dummy::Dummy(int value, char name){
    Dummy::value = value;
    Dummy::name = name;
}

Dummy::Dummy(){
    Dummy::value = 0;
    Dummy::name = 'a';
}

bool Dummy::operator<=(Dummy a){
    return value <= a.value;
}

bool Dummy::operator==(Dummy a){
    return value == a.value;
}

ostream& operator<<(ostream &o,  Dummy d){
    o << d.name << ':' << d.value;
    return o;
}

istream& operator>>( istream &i, Dummy d){
    i >> d.value;
    d.name = 'a';
    return i;
}

/****************************************************
* Binsertsort Coroutine
*  used for sorting values
*****************************************************/
template <typename T>
void Binsertsort<T>::main() {
    //Store current value of node
    T pivot = value;
    suspend();
    //Check if no more values exist (this is a leaf node)
    if(!(pivot == Sentinel)){
        //If this is not a leaf node create children
        Binsertsort<T> less(Sentinel);
        Binsertsort<T> greater(Sentinel);
        //Keep passing new values to children until sentinel
        while(!(value == Sentinel)) {
            if(value <= pivot){
                less.sort(value);
            } else {
                greater.sort(value);
            } //if
            suspend();
        }//while
        //pass sentinel to children to trigger stop
        less.sort(Sentinel);
        greater.sort(Sentinel);
        suspend();
        //set the current value to pivot (stored at start)
        value = pivot;
        //Keep retrieving values from left children and passing them up
        while(!(value == Sentinel)){
            value = less.retrieve();
            if(!(value == Sentinel)) {
                suspend();
            }//if
        }//while
        //Set value to pivot for retrieval
        value = pivot;
        suspend();
        //Keep retrieving values from right children and passing them up
        while(!(value == Sentinel)){
            value = greater.retrieve();
            if(!(value == Sentinel)) {
                suspend();
            }//if
        }//while
    } else { //if this is the child of a leaf node set its value to sentinel
        value = Sentinel;
        suspend();
    }//if
}

void uMain::main() {
    istream *infile;
    ostream *outfile;
    //Attempt to open input file
    if(argc > 1){
        try {
            infile = new ifstream( argv[1] );
        } catch( uFile::Failure ) {
            cerr << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
            exit(-1);
        } //try
    } else {
        infile = &cin;
    }//if
    //Attempt to open output file
    if(argc > 2){
        try {
            outfile = new ofstream( argv[2] );
        } catch( uFile::Failure ) {
            cerr << "Error! Could not open output file \"" << argv[2] << "\"" << endl;
            exit(-1);
        }//try
    } else {
        outfile = &cout;
    }//if
    //Read in first character of line
    int i = 0;
    while( *infile >> i){
        //If line is empty (starts with 0) print gaps and continue
        if(i == 0) {
            *outfile << endl << endl << endl;
            continue;
        } //if
        //Create root coroutine initialized to 0
        Binsertsort<TYPE> root(SENTINEL);
        TYPE curr;
        for (int j = 0; j < i; j++){
            //Read in current value
            *infile >> curr;
            //Write out current value
            *outfile << curr;
            if(i != j-1){
                *outfile << " ";
            } //if
            //Pass current value into root coroutine
            root.sort(curr);
        }//for
        *outfile << endl;
        //Pass in sentinel to end sorting
        root.sort(SENTINEL);
        while (!(curr == SENTINEL)){
            //Keep retrieving sorted values until sentinel is returned
            curr = root.retrieve();
            if(!(curr == SENTINEL)){
                //Write out sorted values
                *outfile << curr << " ";
            } //if
        } //while
        *outfile << endl << endl;
    }//while
    //Delete infile
    if (infile != &cin) {
        delete infile;
    }//if
    //Delete outfile
    if (outfile != &cout) {
        delete outfile;
    }//if
    return;
}
