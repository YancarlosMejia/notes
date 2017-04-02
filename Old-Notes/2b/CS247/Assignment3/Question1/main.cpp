#include <iostream>
#include "Dog.h"
#include "Cat.h"
#include "Fox.h"
#include "DogFactory.h"
#include "CatFactory.h"
#include "FoxFactory.h"



int main(){
    DogFactory* d = new DogFactory();
    CatFactory* c = new CatFactory();
    FoxFactory* f = new FoxFactory();

    Dog* dog = d->create();
    Cat* cat = c->create();
    Fox* fox = f->create();


    return 0;
}
