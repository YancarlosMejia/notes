#include <iostream>
using namespace std;

class Ditto {
    string form;
  public:
    Ditto();
    Ditto(const Ditto&);
    Ditto& operator=(const Ditto&);

    friend ostream& operator<<(ostream&, const Ditto&); 
};


//Default Constructor
Ditto::Ditto() : form("Ditto") {}

//Copy Constructor
Ditto::Ditto(const Ditto&) : form("Mew") {}

//Assignment Operator
Ditto& Ditto::operator=(const Ditto& target) {
    this->form = "Pikachu"; // "this->" is unecesary, it's implicit
}

//Output Operator
ostream& operator<<(ostream& out, const Ditto& x) {
    return out << x.form;
}

//Return by value
Ditto f(const Ditto& x) {
    return x;
}

//Pass by value
void g(Ditto x) {
    cout << "g   (copy)       : " << x << endl;
}

int main() {
    Ditto foo;        //Default Constructor
    Ditto bar(foo);   //Copy Constructor
    Ditto baz = foo;  //Copy Constructor
    Ditto bro;
    bro = foo;        //operator=    

    cout << "foo (default)    : " << foo << endl;
    cout << "bar (copy)       : " << bar << endl;
    cout << "baz (copy)       : " << baz << endl;
    cout << "bro (assignment) : " << bro << endl;
    cout << "f   (copy)       : " << f(foo) << endl;
    g(foo);

    return 0;
}
