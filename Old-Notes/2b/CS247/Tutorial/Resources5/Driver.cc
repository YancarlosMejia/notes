#include "SharedPointer.h"
#include <iostream>
using namespace std;

SharedPointer useShared(int * ptr) {
    SharedPointer ret(ptr);
    return ret;
}

int doSomething(SharedPointer s) {
    *s = (*s + 12 - 57 * 34) & ((1234567 | 0714) + *s *2);
    return *s + 123;
}


int main() {
    SharedPointer p1 = useShared(new int);
    
    SharedPointer p2 = p1;
    p2 = p2;
    p1 = p2;
    SharedPointer p3 = useShared(new int);
    *p1 = 32;
    p3 = p1;
    
    cout << *p1 << " " << *p2 << " " << *p3 << endl;
    cout << (p1 == p2) << endl;
    cout << doSomething(p1) << endl;
    cout << *p1 << " " << *p2 << " " << *p3 << endl;
    
    return 0;
}
