// ***************************************************************************
#ifndef TacoBell_h_included_
#define TacoBell_h_included_

#include "YumRestaurant.h"
#include "YumRestaurantFactory.h"

class TacoBell: public YumRestaurant
{
  TacoBell();
  ~TacoBell();

  friend class YumRestaurantFactoryInitializer;  
  friend class Factory;

  class Factory : public YumRestaurantFactory{
  public:
    YumRestaurant* create(){ return new TacoBell; }
    friend class YumRestarurantFactoryInitializer;
  };

public:

  virtual std::string getName();
  virtual std::vector<std::string> getMenu();

};
#endif
// ***************************************************************************
