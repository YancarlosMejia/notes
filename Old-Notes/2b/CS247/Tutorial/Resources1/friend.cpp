#include <iostream>
using namespace std;

struct Cow {
    Cow() : milk(5) {}
    friend int f(Cow); 
  private:
    int milk;
};


int f(Cow bob){
   cout << bob.milk <<endl;
}

int main() {
    Cow bar;
    f(bar);    
}
