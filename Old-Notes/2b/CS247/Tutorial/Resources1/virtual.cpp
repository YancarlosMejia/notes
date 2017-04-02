#include <iostream>
using namespace std;

struct  Animal {
    virtual void call(){
        cout << "unknown animal" << endl;
    }
};

struct Cow : public Animal {
    void call(){
        cout << "moo!" << endl;
    } 
};

int main() {
    Animal* foo;
    Cow bar;

    foo = new Cow;
    foo->call();
    bar.call();
    delete foo;
}
