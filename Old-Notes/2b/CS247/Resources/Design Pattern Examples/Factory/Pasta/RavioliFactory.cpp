#include "RavioliFactory.h"
#include "Ravioli.h"

Ravioli* RavioliFactory::create(const int type, Inventory& i, int quantity){
    i.setDough( i.getDough() - quantity*2.5);
	i.restock( "ravioli", quantity );
    return new Ravioli(quantity);
}
