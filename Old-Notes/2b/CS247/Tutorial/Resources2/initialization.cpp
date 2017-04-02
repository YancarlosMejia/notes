#include <iostream>
using namespace std;

class Object1 {
    string info_;
  public:
    Object1();
    Object1(const string&);
    string info();
};

Object1::Object1() : info_("Hello World!") {}

Object1::Object1(const string& word) : info_(word) {}

string Object1::info() {
    return info_;
}

class Object2 : public Object1 {
    const int data;
  public:
    Object2();
};

class Object3 : public Object1 {
    const int data;
  public:
    Object3();
};

// Causes Compilation Error
/*
Object2::Object2() {
    data = 42;
}
*/

//Working Constructor

Object2::Object2() : data(42) {
    cout << info() << endl;
    cout << data << endl;    
}


// Another Working Constructor
Object3::Object3() : Object1("Greetings Earth!"), data(247) {
    cout << info() << endl;
    cout << data << endl;    
}


int main() {
    Object2 foo;
    Object3 bar;
}
