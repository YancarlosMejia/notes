#ifndef _PENNE_H_
#define _PENNE_H_


#include "Pasta.h"


class Penne: public Pasta{
	static double cost_;
	
public:

    Penne(int q);
    ~Penne();
    double cost();
};


#endif
