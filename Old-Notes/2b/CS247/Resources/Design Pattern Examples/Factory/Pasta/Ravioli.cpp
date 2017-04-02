#include "Ravioli.h"


double Ravioli::cost_ = 5;

Ravioli::Ravioli(int q) : Pasta(q) {
    setName("ravioli");
    setDesc("Ravioli pasta is shaped like a square!");
}

Ravioli::~Ravioli(){}

double Ravioli::cost(){
    return cost_;
}
