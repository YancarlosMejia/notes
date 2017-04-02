#include "DogFactory.h"

Dog* DogFactory::create() {
    Dog* g = new Dog();
    g->soundOff();
    return g;
}
