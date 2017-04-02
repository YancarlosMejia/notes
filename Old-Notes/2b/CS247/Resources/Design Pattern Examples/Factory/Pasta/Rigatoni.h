#ifndef _RIGATONI_H_
#define _RIGATONI_H_


#include "Pasta.h"
#include "Rigatoni.h"

class Rigatoni: public Pasta{
public:
    Rigatoni(int q);
    ~Rigatoni();
    double cost();
private:
	static double cost_;
};


#endif
