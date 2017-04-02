#include <iostream>
#include <string>
using namespace std;

struct one{
   void f(){
       cout << "Fred" << endl;
   }
};

struct two : public one{
   void f(){
       cout << "Derf" << endl;
   }
};

int main(){
   one foo;
   two bar;

   foo.f();
   bar.f();
   bar.one::f();
}
