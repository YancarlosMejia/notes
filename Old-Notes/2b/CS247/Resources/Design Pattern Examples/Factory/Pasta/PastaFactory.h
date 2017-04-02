#ifndef _PASTAFACTORY_H_
#define _PASTAFACTORY_H_

#include "Pasta.h"
#include "Inventory.h"

class PastaFactory{
public:
	virtual ~PastaFactory() {}
    virtual Pasta* create (const int type, Inventory& i, int quantity) = 0;
};


#endif
