#ifndef _RAVIOLIFACTORY_H_
#define _RAVIOLIACTORY_H_

#include "PastaFactory.h"
#include "Inventory.h"
#include "Ravioli.h"

class RavioliFactory: public PastaFactory{
     private:
        Ravioli* create(const int type, Inventory& i, int quantity);
};

#endif

