#include "CatFactory.h"

Cat* CatFactory::create() {
    Cat* g = new Cat();
    g->soundOff();
    return g;
}
