// ***************************************************************************
#ifndef KentuckyFriedChicken_h_included_
#define KentuckyFriedChicken_h_included_

#include "YumRestaurant.h"
#include "YumRestaurantFactory.h"

class KentuckyFriedChicken : public YumRestaurant
{
  KentuckyFriedChicken();
  ~KentuckyFriedChicken();

  friend class YumRestaurantFactoryInitializer;  
  friend class Factory;

  class Factory :public YumRestaurantFactory{
  public:
    YumRestaurant* create(){ return new KentuckyFriedChicken; }
    friend class YumRestarurantFactoryInitializer;
  };

public:

  virtual std::string getName();
  virtual std::vector<std::string> getMenu();

};
#endif
// ***************************************************************************
