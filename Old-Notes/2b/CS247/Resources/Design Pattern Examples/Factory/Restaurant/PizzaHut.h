// ***************************************************************************
#ifndef PizzaHut_h_included_
#define PizzaHut_h_included_

#include "YumRestaurant.h"
#include "YumRestaurantFactory.h"

class PizzaHut: public YumRestaurant
{
  PizzaHut();
  ~PizzaHut();

  friend class YumRestaurantFactoryInitializer;  
  friend class Factory;

  class Factory : public YumRestaurantFactory{
  public:
    YumRestaurant* create(){ return new PizzaHut; }
    friend class YumRestarurantFactoryInitializer;
  };

public:

  virtual std::string getName();
  virtual std::vector<std::string> getMenu();

};
#endif
// ***************************************************************************
