#ifndef _PASTA_H_
#define _PASTA_H_

#include <string>

class Pasta{

protected:
    Pasta(int quant);
	std::string desc_;
    std::string name_;
    int quantity_;

public:
    virtual ~Pasta() {}
    virtual double cost() = 0;
	
    std::string getDesc();
    std::string getName();
	int getQuantity();
    void setDesc(std::string desc);
    void setName(std::string name);
	void setQuantity(int i);
};

#endif
