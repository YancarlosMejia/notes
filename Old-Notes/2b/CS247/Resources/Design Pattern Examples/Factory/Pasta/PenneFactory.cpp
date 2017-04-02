#include "PenneFactory.h"
#include "Penne.h"

Penne* PenneFactory::create(const int type, Inventory& i, int quantity){
    i.setDough( i.getDough() - quantity) ;
    i.restock( "penne", quantity);
    return new Penne(quantity);
}
