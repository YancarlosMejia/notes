#include <iostream>
using namespace std;

struct  Animal {
    void call(){
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

    foo = &bar;
    foo->call();
    bar.call();
}
