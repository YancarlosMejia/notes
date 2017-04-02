#include <iostream>
using namespace std;

struct Cow {
    Cow() : milk(5), foo(milk+5) {} // Initializes foo to milk+5 THEN milk to 5.
    friend int f(Cow); 
    private:
    int foo;   //Switch order of variables to fix
    int milk;
};


int f(Cow bob){
   cout << bob.foo <<endl;
}

int main() {
    Cow bar;
    f(bar);
}


//This will compile but foo is initialized before milk so it goes crazy/
