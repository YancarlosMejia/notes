#include <iostream>
using namespace std;

struct  Base {
    int i;
};

struct Derived : public Base {
    int k;
};

int main() {
    Base *foo;
    Base spam;
    Derived bar, baz;

    bar.i = 7;
    bar.k = 9;

    baz.i = 9001;
    baz.k = 9003;

    foo = &bar;
    *foo = baz;

    cout << "i : " << bar.i << endl;
    cout << "k : " << bar.k << endl;

    spam = baz;
    cout << "i : " << spam.i << endl;
   // cout << "k : " << bar.k << endl;    Wouldn't compile
}
