#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

class SharedPointer {
    struct Data;
    Data * data;
protected:
    virtual void swap(SharedPointer&);
    
public:
    SharedPointer(int *);
    virtual ~SharedPointer();
    SharedPointer(const SharedPointer&);
    
    // dereference
    int& operator*() const;
    
    SharedPointer& operator=(const SharedPointer&);
    
    bool operator==(SharedPointer&) const;
    bool operator!=(SharedPointer&) const;
};


#endif
