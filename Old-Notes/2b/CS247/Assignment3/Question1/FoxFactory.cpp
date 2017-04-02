#include "FoxFactory.h"

Fox* FoxFactory::create() {
    Fox* g = new Fox();
    g->soundOff();
    return g;
}
