#include "Penne.h"
#include "Inventory.h"

using namespace std;

double Penne::cost_ = 2;

Penne::Penne(int q) : Pasta(q) {
	setName("penne");
    setDesc("Penne pasta is shaped like a rectangle!");
}

Penne::~Penne(){}

double Penne::cost(){
    return cost_;
}
