template<typename T> class BoundedBuffer {
  public:
    BoundedBuffer( const unsigned int size = 10 );
    void insert( T elem );
    T remove();
};

#ifdef BUSY                            // busy waiting implementation
// implementation
#endif // BUSY

#ifdef NOBUSY                        // no busy waiting implementation
// implementation
#endif // NOBUSY

_Task Producer {
    void main();
  public:
    Producer( BoundedBuffer<BTYPE> &buffer, const int Produce, const int Delay );
};

_Task Consumer {
    void main();
  public:
    Consumer( BoundedBuffer<BTYPE> &buffer, const int Delay, const BTYPE Sentinel,
                BTYPE &sum );
};

_Monitor MPRNG {
  public:
    MPRNG( unsigned int seed = 1009 ) { srand( seed ); }    // set seed
    void seed( unsigned int seed ) { srand( seed ); }        // set seed
    unsigned int operator()() { return rand(); }            // [0,UINT_MAX]
    unsigned int operator()( unsigned int u ) { return operator()() % (u + 1); } // [0,u]
    unsigned int operator()( unsigned int l, unsigned int u ) { return operator()( u - l ) + l; } // [l,u]
};
