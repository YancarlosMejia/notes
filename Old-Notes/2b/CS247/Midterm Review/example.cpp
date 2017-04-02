#include <iostream>
using namespace std;

struct Base {
    Base() { cout << "base created!" << endl; };
    ~Base() { cout << "base destroyed!" << endl; };
    virtual int getVal() { return n; } 
    virtual int getVal2() { return m; } 
    virtual int getVal3() { return m; } 

    void test() {
        f();
        g();
    }
    void f() { cout << "Base::f" << endl; }
    virtual void g() { cout << "Base::g" << endl; }

    static int n;
    static int m;
};

struct Derived : public Base {
    Derived() { cout << "derived created!" << endl; };
    ~Derived() { cout << "derived destroyed!" << endl; };
    virtual int getVal() { return n; }
    virtual int getVal2() { return m; } 

    void f() { cout << "Derived::f" << endl; }
    virtual void g() { cout << "Derived::g" << endl; }
    static int m;

};

int Base::n = 99;
int Base::m = 11;
int Derived::m = 123;

int main() {
    Base *b = new Base;
    Base *d = new Derived;

    cout << b->getVal() << endl;
    cout << b->getVal2() << endl;
    cout << b->getVal3() << endl;
    cout << d->getVal() << endl;
    cout << d->getVal2() << endl;
    cout << d->getVal3() << endl;

    d->Base::f();
    d->Base::g();
    d->f();
    d->g();
    d->test();
    
    delete d;
    delete b;
}
