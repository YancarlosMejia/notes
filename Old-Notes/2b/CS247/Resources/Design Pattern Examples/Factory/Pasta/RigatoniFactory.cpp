#include "RigatoniFactory.h"
#include "Rigatoni.h"

Rigatoni* RigatoniFactory::create(const int type, Inventory& i, int quantity){
    i.setDough( i.getDough() - quantity*0.5 );
    i.restock( "rigatoni", quantity );
    return new Rigatoni(quantity);
}

