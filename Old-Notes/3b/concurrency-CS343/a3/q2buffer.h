#ifndef Q2BUFFER_H
#define Q2BUFFER_H
#include <queue>

// BoundedBuffer class
template<typename T> class BoundedBuffer {
  const unsigned int size;                                                      //size of buffer
  std::queue<T> container;                                                      //queue containing values in buffer
  uOwnerLock lk;                                                                //owner lock of buffer to prevent more than one thread entering at once
  uOwnerLock producerlk;                                                        //owner lock to prevent producer barging
  uOwnerLock consumerlk;                                                        //owner lock to prevent consumer barging
  uCondLock fullLk;                                                             //conditional lock to store threads waiting for buffer to stop being full
  uCondLock emptyLk;                                                            //conditional lock to store threads waiting for buffer to stop being empty
  public:
    BoundedBuffer( const unsigned int size = 10 );
    void insert( T elem );                                                      //inserts element into buffer from producer
    T remove();                                                                 //removes element from buffer and passes to consumer
};

//Producer thread
_Task Producer {
    BoundedBuffer<BTYPE> &buffer;                                               //buffer that producer is acting on
    int Produce;                                                                //number of items to produce each time
    int Delay;                                                                  //number of times to yield before each production

    void main();
  public:
    Producer( BoundedBuffer<BTYPE> &buffer, const int Produce, const int Delay );
};

//Consumer thread
_Task Consumer {
    BoundedBuffer<BTYPE> &buffer;                                               //buffer that the consumer is acting
    int Delay;                                                                  //number of times to yield before consuming
    BTYPE Sentinel;                                                             //value to indicate end of consumable values
    BTYPE &sum;                                                                 //value containing sum of all consumed values

    void main();
  public:
    Consumer( BoundedBuffer<BTYPE> &buffer, const int Delay, const BTYPE Sentinel, BTYPE &sum )  ;
};

#endif

