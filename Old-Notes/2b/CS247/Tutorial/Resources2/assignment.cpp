#include <iostream>
using namespace std;

class intPoint {
    int* value;
  public:
    intPoint();
    intPoint(const intPoint&);
    intPoint& operator=(const intPoint&);    
    ~intPoint();
    int val() const;
    void valIs(int);
};

// Default Constructor
intPoint::intPoint() {
    value = new int;
    *value = 42;
}

//Copy Constructor
intPoint::intPoint(const intPoint& intp) {
    value = new int;
    *value = intp.val();
}

// Assignment Operator
// Using Copy and Swap
intPoint& intPoint::operator=(const intPoint& target) {
    intPoint copy(target);
    int* temp;

    temp = copy.value;
    copy.value = value;
    value = temp;

    return *this;
}

// Assignment Operator
// Alternative Implementation
/*
intPoint& intPoint::operator=(const intPoint& target) {
    if (this != &target) {
        delete value;
        value = new int;
        *value = target.val();
    }
    return *this;
}*/

intPoint::~intPoint() {
    delete value;
    value = 0;
}

//Accessor
int intPoint::val() const { 
    return *value;
}

//Mutator
void intPoint::valIs(int num) {
    *value = num;
}

int main() {
    intPoint foo, bar, baz;
    
    foo.valIs(9001);
    cout << "foo : " << foo.val() << endl;
    cout << "bar : " << bar.val() << endl;
    cout << "baz : " << baz.val() << endl;
    baz = bar = foo; 
    foo = foo;
    cout << "After baz = bar = foo;" << endl;
    cout << "foo : " << foo.val() << endl;
    cout << "bar : " << bar.val() << endl;
    cout << "baz : " << baz.val() << endl;
    
    return 0;
}
