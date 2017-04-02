#include "SharedPointer.h"
#include <algorithm>

struct SharedPointer::Data {
    int * ptr;
    int refCount;    
};

SharedPointer::SharedPointer(int * ptr) {
    data = new Data;
    data->refCount = 1;
    data->ptr = ptr;
}

SharedPointer::~SharedPointer() {
    data->refCount--;
    if (data->refCount == 0) {
        delete data->ptr;
        delete data;
    }
}

SharedPointer::SharedPointer(const SharedPointer &s) {
    data = s.data;
    data->refCount++;
}

// dereference
int& SharedPointer::operator*() const {
    return *data->ptr;
}

SharedPointer& SharedPointer::operator=(const SharedPointer &s) {
    SharedPointer temp(s);
    swap(temp); 
    return *this;
//at the end the object temp gets destroyed because it goes out of scope
}

bool SharedPointer::operator==(SharedPointer &s) const {
    return data->ptr == s.data->ptr;
}

bool SharedPointer::operator!=(SharedPointer &s) const {
    return !(*this == s);
}

void SharedPointer::swap(SharedPointer &s) {
    std::swap(s.data, data);
}