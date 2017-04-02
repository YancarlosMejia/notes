#include <iostream>
#include <fstream>
using namespace std;
#include "q1mergesort.h"

/***************************** Mergesort ***************************************
     Purpose: A thread that sorts an array via the mergesort algorithm

     Returns: Nothing

     Errors: None

     Parameters:
            values - the array of unsorted values
            low - index of bottom edge of range currently being sorted
            high - index of top edge of range currently being sorted
            depth - current depth in tree
            holder - array for holding copied values during sorting
*******************************************************************************/
//internal private constructor for child threads
template<typename T>
Mergesort<T>::Mergesort(T values[], unsigned int low, unsigned int high, unsigned int depth, T holder[]) : values(values), low(low), high(high), depth(depth), holder(holder) { }

//this constructor is only called by main and thus only used to create top thread
template<typename T>
Mergesort<T>::Mergesort(T values[], unsigned int low, unsigned int high, unsigned int depth) : values(values), low(low), high(high), depth(depth) {
    holder = new T[high - low];                                                 //if this is the top thread create the holder array
}

template<typename T>
Mergesort<T>::~Mergesort() {
    if (!low) {                                                                 //if this is the top thread (indicated by low - 0) delete the holder array
        delete[] holder;
    }//if
}

template <typename T>
void Mergesort<T>::main(){
    sort();
}

/***************************** Sort ********************************************
     Purpose: A function that sorts an array via the mergesort algorithm

     Returns: Nothing

     Errors: None

     Parameters: None
*******************************************************************************/
template <typename T>
void Mergesort<T>::sort(){
    if(high - low == 1) {                                                       //if current range only spans one value do nothing
        return;
    }//if
    unsigned int middle = (high+low)/2;                                         //create middle value and holders for current range
    int ltemp = low;
    int htemp = high;
    {
        if(depth > 0){                                                          //if the depth is greater than 0 sort right side by spawning new thread
            depth -= 1;
            Mergesort<T> right(values, middle, high, depth, holder);
        } else {                                                                //if the depth is equal than 0 sort right side recursively
            low = middle;                                                       //set low to new range
            sort();
            low = ltemp;                                                        //reset low to previous value
        }//if
                                                                                //sort left side recursively
        high = middle;                                                          //set high to new range
        sort();
        high = htemp;                                                           //reset high
    }
                                                                                //merge left and right sides
    unsigned int l = low, r = middle, c = low;
    while(l < middle && r < high) {                                             //iterate through left and right storing values in correct order in holder array
        if(values[l] < values[r]) {
            holder[c] = values[l];
            ++c;
            ++l;
        } else {
            holder[c] = values[r];
            ++c;
            ++r;
        }//if
    }//while
    while(l < middle) {
        holder[c] = values[l];
        ++c;
        ++l;
    }//while
    while(r < high) {
        holder[c] = values[r];
        ++c;
        ++r;
    }//while
    memcpy(&values[low], &holder[low], (high - low) * sizeof(T));               //move sorted range of holder array into values array
}


void uMain::main() {
    istream *instream;
    ostream *outstream;
    if(strcmp(argv[1], "-s") == 0){                                             //if input indicates sort mode
                                                                                //Attempt to open input file
        try {
            instream = new ifstream( argv[2] );
        } catch( uFile::Failure ) {
            cerr << "Error! Could not open input file \"" << argv[2] << "\"" << endl;
            exit(-1);
        } //try
                                                                                //Attempt to open output file
        if(argc > 3){
            try {
                outstream = new ofstream( argv[3] );
            } catch( uFile::Failure ) {
                outstream = &cout;
            }//try
        } else {
            outstream = &cout;
        }//if
                                                                                //Read in first character of line
        int count = 0;
        TYPE curr;
        while( *instream >> count){
            if(count == 0) {                                                    //If line is empty (starts with 0) print gaps and continue
                *outstream << endl << endl << endl;
                continue;
            } //if

            TYPE values[count];                                                 //create values array and populate it
            for(int i = 0; i < count; i++){
                *instream >> curr;
                values[i] = curr;
            }//for

            for(int i = 0; i < count; i++){                                     //print unsorted values
                *outstream << values[i] << " ";
                if(i && i % 22 == 0){
                    *outstream << endl << " ";
                }//if
            }//for

            *outstream << endl;
            {
                Mergesort<TYPE>sorter(values, 0, count, 0);                     //sort values
            }

            for(int i = 0; i < count; i++){                                     //print sorted values
                *outstream << values[i] << " ";
                if(i && i % 22 == 0){
                    *outstream << endl << " ";
                }//if
            }//for
            *outstream << endl << endl;
        }//while
        if (instream != &cin) {                                                 //delete instream
            delete instream;
        }//if
        if (outstream != &cout) {                                               //delete outstream
            delete outstream;
        }//if
    } else if(strcmp(argv[1], "-t") == 0){                                      //if input indicates time mode
        unsigned int size;
        unsigned int depth = 0;
        if(argc  < 3){                                                          //read in size parameter and check that it is a integer in range
            cerr << "A size value is required.";
            exit(-1);
        } else {
            try{
                size = stoi(argv[2]);
            } catch (...) {
                cerr << "Size must be a integer.";
                exit(-1);
            }//try
        }//if
        if(argc >= 4){                                                          //read in depth parameter and check that it is an integer in range
            try{
                depth = stoi(argv[3]);
            } catch (...) {
                cerr << "Depth must be a integer.";
                exit(-1);
            }//try
            if(depth < 0){
                cerr << "Depth must be non-negative.";
                exit(-1);
            }//if
        }//if

        int *values = new TYPE[size];                                           //create array of values
        for(unsigned int i = 0; i < size; i++){
            values[i] = size - i;
        }//for

        uProcessor p[ (1 << depth) - 1 ] __attribute__ (( unused ));
        {
            Mergesort<TYPE>sorter(values, 0, size, depth);                      //sort array
        }

        delete values;

    } else {                                                                    //catch invalid mode input
        cerr << "Invalid flag! Usage is: -s for sort mode or -t for time mode"<< endl;
        exit(-1);
    }//if

    return;
}
