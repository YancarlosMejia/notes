#include "Rigatoni.h"

using namespace std;

double Rigatoni::cost_ = 1;

Rigatoni::Rigatoni(int q) : Pasta(q) {
    setName("rigatoni");
    setDesc("Rigatoni pasta is shaped like a circle!");
}

Rigatoni::~Rigatoni(){}

double Rigatoni::cost(){
    return cost_;
}
