#ifndef _PENNEFACTORY_H_
#define _PENNEFACTORY_H_

#include "PastaFactory.h"
#include "Penne.h"
#include "Inventory.h"

class PenneFactory: public PastaFactory{
     private:
        Penne* create(const int type, Inventory& i, int quantity);
};

#endif

