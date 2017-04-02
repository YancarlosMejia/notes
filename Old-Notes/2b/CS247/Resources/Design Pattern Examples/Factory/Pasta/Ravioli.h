#ifndef _RAVIOLI_H_
#define _RAVIOLI_H_


#include "Pasta.h"


class Ravioli: public Pasta{

public:

    Ravioli(int q);
    ~Ravioli();
    double cost();

private:
	static double cost_;
};


#endif

