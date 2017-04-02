#include <iostream>
using namespace std;

class Base {    
    int i; 
    friend bool operator==(const Base&, const Base&);

  public:
    Base(int i);
};

Base::Base(int i) : i(i) {}

bool operator==(const Base& b1, const Base& b2) {
    return (b1.i == b2.i);
}

class Derived : public Base {
    string str;
    friend bool operator==(const Derived&, const Derived&);

  public: 
    Derived(string, int);
};

Derived::Derived(string word, int i = 42) : Base(i), str(word) {}

bool operator==(const Derived& b1, const Derived& b2) {
    if (static_cast<Base>(b1) == static_cast<Base>(b2)) //this checks if the two base classes are equal
        return (b1.str == b2.str);
    else
        return false;
}

int main() {
    Base foo(99);
    Derived bar("Hello"), baz("Balloons", 99), bro("Goodbye");
    
    cout << "foo : 99" << endl;
    cout << "bar : 42, Hello" << endl;
    cout << "baz : 99, Balloons" << endl;
    cout << "bro : 42, Goodbye" << endl;

    //Implicit Conversion
    cout << "bar == string(\"Hello\")" << endl;
    cout << (bar == string("Hello")) << endl;
    cout << "foo == 99" << endl; 
    cout << (foo == 99) << endl;
    cout << "string(\"Balloons\") == baz" << endl;
    cout << (string("Balloons") == baz) << endl;
    cout << "foo == baz" << endl;
    cout << (foo == baz) << endl;
    cout << "baz == foo" << endl;
    cout << (baz == foo) << endl;

    // Explicit
    cout << "static_cast<Base>(bar) == static_cast<Base>(bro)" << endl;
    cout << (static_cast<Base>(bar) == static_cast<Base>(bro)) << endl;
    cout << "bar == bro (for comparison)" << endl;
    cout << (bar == bro)  << endl;

    // Polymorphic Pointers
    Base *bp1, *bp2;
    bp1 = &bar;
    bp2 = &bro;
    cout << "bar == bro (by Base*)" << endl;   
    cout << (*bp1 == *bp2)  << endl;
}
