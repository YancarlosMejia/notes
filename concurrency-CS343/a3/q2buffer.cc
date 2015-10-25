#include <iostream>
#include <queue>
using namespace std;

#include "q2buffer.h"
#include "MPRNG.h"

MPRNG *mprng;                                                                   //randomizer for yield values

/***************************** Producer ************************************
     Purpose: A thread to produce data and insert it into a BoundedBuffer for
            consumption.

     Returns: Nothing

     Errors: None

     Parameters:
            buffer - the bounded buffer to insert data into
            Produce - the number of items to produce
            Delay - the range for random delay between insertions
*******************************************************************************/
Producer::Producer(BoundedBuffer<BTYPE> &buffer, const int Produce, const int Delay) : buffer(buffer), Produce(Produce), Delay(Delay) {}

void Producer::main() {
    for(int i = 0; i <= Produce; i++){
        yield((*mprng)(0, Delay - 1));                                          //yield a random number of times in range 0 - Delay-1
        BTYPE value(i);                                                         //create value of BTYPE containing integer
        buffer.insert(value);                                                   //insert value into buffer
    }//for
}


/***************************** Consumer ****************************************
     Purpose: A thread to consume data and remove it from a BoundedBuffer for
            summing.

     Returns: Nothing

     Errors: None

     Parameters:
            buffer - the bounded buffer to remove data from
            Delay - the range for random delay between removals
            Sentinel - value to signal the end of values
            sum - running total to add consumed values to
*******************************************************************************/
//Constructor
Consumer::Consumer( BoundedBuffer<BTYPE> &buffer, const int Delay, const BTYPE Sentinel, BTYPE &sum ) : buffer(buffer), Delay(Delay), Sentinel(Sentinel), sum(sum) {}

void Consumer::main() {
    for(;;) {
        yield((*mprng)(0, Delay - 1));                                          //yield a random number of times in range 0 - Delay-1
        BTYPE value = buffer.remove();                                          //consume value from buffer
        if(value == Sentinel){                                                  //if the value is the Sentinel stop consumption
            break;
        }//if
        sum += value;                                                           //add value to sum
    }//for
}

/***************************** BoundedBuffer ************************************
     Purpose: Container to hold a given number of values from producers for
            consumers

     Returns: Nothing

     Errors: None

     Parameters:
            size - the number of values allowed in buffer
*******************************************************************************/
template<typename T>
BoundedBuffer<T>::BoundedBuffer(const unsigned int size) : size(size){}

/***************************** Insert ******************************************
     Purpose: Insert a new value onto end of the buffer

     Returns: Nothing

     Errors: None

     Parameters:
            elem - the value to be inserted into the buffer
*******************************************************************************/
template<typename T>
void BoundedBuffer<T>::insert(T elem){
    #ifdef NOBUSY                                                               //if operation mode is NOBUSY, acquire lock to block barging producers
    producerlk.acquire();
    #endif

    lk.acquire();                                                               //acquire lock to prevent producers and consumers trampling each other
    #ifdef BUSY                                                                 //if operation mode is BUSY continuously wait until the container is not full
    while(container.size() == size){
        fullLk.wait(lk);
    }//while
    #elif NOBUSY                                                                //if operation mode is NOBUSY block on the full lock until it is clear
    if(container.size() == size){
        fullLk.wait(lk);
    }//if
    #endif

    assert(container.size() != size);                                           //assert that the container is not full
    container.push(elem);                                                       //insert elem into container
    emptyLk.signal();                                                           //signal that the container is not empty
    lk.release();                                                               //release the lock that prevents producers and consumers from trampling

    #ifdef NOBUSY                                                               //if the operation mode is NOBUSY release the lock that prevents producer barging
    producerlk.release();
    #endif

}
/***************************** Remove ******************************************
     Purpose: Remove a new value from the front of the buffer

     Returns: The first element of the buffer

     Errors: None

     Parameters: None
*******************************************************************************/
template<typename T>
T BoundedBuffer<T>::remove() {
    #ifdef NOBUSY                                                               //if the operation mode is NOBUSY acquire lock that prevents consumer barging
    consumerlk.acquire();
    #endif
    lk.acquire();                                                               //acquire lock to prevent producers and consumers trampling each other
    #ifdef BUSY                                                                 //if operation mode is BUSY continuously wait until the container is not empty
    while(container.empty()){
        emptyLk.wait(lk);
    }//while
    #elif NOBUSY                                                                //if operation mode is NOBUSY block on the empty lock until it is clear
    if(container.empty()){
        emptyLk.wait(lk);
    }//if
    #endif

    assert(!container.empty());                                                 //assert that the container is not empty
    T ret = container.front();                                                  //get copy of first element of buffer for returning
    container.pop();                                                            //remove first element of buffer
    fullLk.signal();                                                            //signal that buffer is no longer full
    lk.release();                                                               //release lock that prevents producers and consumers from trampling

    #ifdef NOBUSY                                                               //if the operation mode is NOBUSY release the lock that prevents consumer barging
    consumerlk.release();
    #endif
    return ret;                                                                 //return value that was the first element of buffer
}


void uMain::main() {
    mprng = new MPRNG();
                                                                                //set up input parameter defaults
    unsigned int cons = 5; //number of consumers
    unsigned int prods = 3; //number of producers
    unsigned int produce = 10; //items made by producers
    unsigned int size = 10; //buffer size
    unsigned int delay = cons + prods; //yield

    if(argc > 1){                                                               //if cons parameter has been defined check that it is a integer an in range
        try{
            cons = stoi(argv[1]);
        } catch (...){
            cerr << "Number of consumers must be an integer" << endl;
            exit(-1);
        }//try
        if(cons < 0) {
            cerr << "Number of consumers must be positive" << endl;
            exit(-1);
        }//if
    }//if

    if(argc > 2){                                                               //if prods parameter has been defined check that it is a integer an in range
        try{
            prods = stoi(argv[2]);
        } catch (...){
            cerr << "Number of producers must be an integer" << endl;
            exit(-1);
        }//try
        if(prods < 0) {
            cerr << "Number of producers must be positive" << endl;
            exit(-1);
        }//if
    }//if

    if(argc > 3){                                                               //if produce parameter has been defined check that it is a integer an in range
        try{
            produce = stoi(argv[3]);
        } catch (...){
            cerr << "Number of items produced must be an integer" << endl;
            exit(-1);
        }//try
        if(prods < 0) {
            cerr << "Number of items produced must be positive" << endl;
            exit(-1);
        }//if
    }//if

    if(argc > 4){                                                               //if size parameter has been defined check that it is a integer an in range
        try{
            size = stoi(argv[4]);
        } catch (...){
            cerr << "Buffer size must be an integer" << endl;
            exit(-1);
        }//tru
        if(prods < 0) {
            cerr << "Buffer size must be positive" << endl;
            exit(-1);
        }//if
    }//try

    if(argc > 5){                                                               //if delay parameter has been defined check that it is a integer an in range
        try{
            delay = stoi(argv[5]);
        } catch (...){
            cerr << "Delay must be an integer" << endl;
            exit(-1);
        }//try
        if(prods < 0) {
            cerr << "Delay must be positive" << endl;
            exit(-1);
        }//if
    } else {
        delay = cons + prods;
    }//if

    #ifdef __U_MULTI__                                                          //set multi core parameter if specified
    uProcessor p[3] __attribute__ (( unused )); // create 3 kernel thread for a total of 4
    #endif // __U_MULTI__


                                                                                //create necessary data structures
    BoundedBuffer<BTYPE> buffer(size); //buffer used to store data
    BTYPE sum = 0; //total of values consumed
    Producer *producers[prods]; //array of producers
    Consumer *consumers[cons]; //array of consumers

    for(unsigned int i = 0; i < prods; i++){                                    //create producers
        producers[i] = new Producer(buffer, produce, delay);
    }//for

    for(unsigned int i = 0; i < cons; i++){                                     //create consumers
        consumers[i] = new Consumer(buffer, delay, SENTINEL, sum);
    }//for

    for(unsigned int i = 0; i < prods; i++){                                    //trigger end of producers by deletion
        delete producers[i];
    }//for

    for(unsigned int i = 0; i < cons; i++){                                     //trigger end of consumers by inserting a sentinel value for each
       buffer.insert(SENTINEL);
    }//for

    for(unsigned int i = 0; i < cons; i++){                                     //delete all consumers
        delete consumers[i];
    }//for

    cout << "total: " << sum << endl;                                           //print total values consumed
    delete mprng;                                                               //delete randomizer to prevent memory leaks
}
