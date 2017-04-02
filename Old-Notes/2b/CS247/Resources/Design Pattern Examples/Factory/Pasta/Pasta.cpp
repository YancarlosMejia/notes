#include "Pasta.h"

using namespace std;

Pasta::Pasta(int quant) : quantity_(quant) { }

string Pasta::getDesc(){
    return desc_;
}

string Pasta::getName(){
    return name_;
}
int Pasta::getQuantity(){
	return quantity_;
}


void Pasta::setDesc(string desc){
    desc_ = desc;
}

void Pasta::setName(string name){
    name_ = name;
}

void Pasta::setQuantity(int i){
    quantity_ = i;
}


