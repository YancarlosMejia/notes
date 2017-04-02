#ifndef Q1MERGESORT_H
#define Q1MERGESORT_H

//Thread Mergesort
template<typename T> _Task Mergesort {
    T *values;                                                                  //array of values to be sorted
    unsigned int low;                                                           //index of bottom range of values currently being sorted
    unsigned int high;                                                          //index of top range of values currently being sorted
    unsigned int depth;                                                         //current depth in recursion three
    T *holder;                                                                  //array to hold sorted values during merge

    void main();
    void sort();                                                                //recursive sort function, called by main

    Mergesort(T values[], unsigned int low, unsigned int high, unsigned int depth, T holder[]);
public:
    Mergesort(T values[], unsigned int low, unsigned int high, unsigned int depth);
    ~Mergesort();
};

unsigned int uDefaultStackSize() {
    return 512 * 1000;
}

#endif
