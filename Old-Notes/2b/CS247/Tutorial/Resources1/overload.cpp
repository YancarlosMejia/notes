#include <iostream>
#include <string>
using namespace std;

void f(int x){
    cout << x + 5 << endl;
}

void f(string str){
    cout << str << endl;
}

int main(){
   string phrase;
   phrase = string("Somebody ") + "set up us the bomb";

   f(phrase);
   f(11);
}
