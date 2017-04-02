#ifndef _RIGATONIFACTORY_H_
#define _RIGATONIFACTORY_H_

#include "PastaFactory.h"
#include "Inventory.h"
#include "Rigatoni.h"

class RigatoniFactory: public PastaFactory{
     private:
        Rigatoni* create(const int type, Inventory& i, int quantity);
};

#endif


