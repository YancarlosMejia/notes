#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "Pasta.h"
#include <map>
#include <string>

class Inventory{

public:

    Inventory();
    ~Inventory();
    int lookup( std::string );
	double getCash();
	int getDough();
    void restock( std::string, int i);
    void sell( std::string, int i);
	void setCash(int i);
	void setDough(int i);
	void sellPasta(Pasta*, int q);
	void buyDough(int i);

protected:
	std::map<std::string, int> inv_;
	double cash_;
	int dough_;
};

#endif
