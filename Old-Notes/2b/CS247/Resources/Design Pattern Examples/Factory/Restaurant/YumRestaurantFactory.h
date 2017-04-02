// ***************************************************************************
#ifndef YumRestaurantFactory_h_included_
#define YumRestaurantFactory_h_included_
;
#include <map>
#include "YumRestaurant.h"

class YumRestaurantFactory
{
public:
  virtual ~YumRestaurantFactory();
  friend class YumRestaurantFactoryInitializer;
  static YumRestaurant* createRestaurant(const std::string& id); 

private:
  virtual YumRestaurant* create() = 0; //Factory Method
  static std::map<std::string, YumRestaurantFactory*> factories;

};

class YumRestaurantFactoryInitializer
{
  static YumRestaurantFactoryInitializer si;
  YumRestaurantFactoryInitializer();
  YumRestaurantFactoryInitializer (const YumRestaurantFactoryInitializer& );
	
};

#endif
// ***************************************************************************
