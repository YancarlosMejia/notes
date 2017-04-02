#include "Inventory.h"
#include <iostream>

using namespace std;

Inventory::Inventory() : cash_(0), dough_(0) {
    inv_["ravioli"] = 0;
    inv_["rigatoni"] = 0;
    inv_["penne"] = 0;
}

Inventory::~Inventory(){}

int Inventory::lookup( string pasta){
    return inv_[pasta];
}

double Inventory::getCash(){
    return cash_;
}
int Inventory::getDough(){
    return dough_;
}

void Inventory::restock( string pasta, int i ){
	inv_[pasta] += i;
}

void Inventory::setCash(int i){
    cash_ = i;
}
void Inventory::setDough(int i){
    dough_ = i;
}
void Inventory::sellPasta(Pasta* p, int q){
	if ( p->getQuantity() >= q )
    {
        inv_[ p->getName() ] -= q;
        cash_ += p->cost()*q;
        if ( p->getQuantity()== q ){
            delete p;
        }
        else{
            p->setQuantity((p->getQuantity()) - q);
        }
    }

    else{
        cout<< "Not enough boxes of " << p->getName() << endl << endl;
    }

}
void Inventory::buyDough(int q)
{
	if (cash_>=double(q)/2)
	{
        dough_=dough_+q;
        cash_=cash_-double(q)/2;
	}
	else{
        cout<<"Not enough money to buy " << q << " kilograms of dough" << endl;
	}
}
