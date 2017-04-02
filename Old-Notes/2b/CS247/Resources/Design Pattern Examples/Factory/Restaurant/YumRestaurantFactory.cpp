#include "YumRestaurantFactory.h"
#include "KentuckyFriedChicken.h"
#include "TacoBell.h"
#include "PizzaHut.h"

YumRestaurantFactory::~YumRestaurantFactory(){
	std::map<std::string, YumRestaurantFactory*>::iterator it = YumRestaurantFactory::factories.begin();
	while (it != YumRestaurantFactory::factories.end()){
		delete it++->second;
	}//while
}

YumRestaurant* YumRestaurantFactory::createRestaurant(const std::string& id){
    if (factories.find(id) != factories.end()){
      return factories[id]->create();
    }//if
    else{
      return NULL;
    }
}
//static member
std::map<std::string, YumRestaurantFactory*> YumRestaurantFactory::factories;

YumRestaurantFactoryInitializer::YumRestaurantFactoryInitializer(){
    YumRestaurantFactory::factories["KentuckyFriedChicken"] = new KentuckyFriedChicken::Factory;
    YumRestaurantFactory::factories["TacoBell"] = new TacoBell::Factory;
    YumRestaurantFactory::factories["PizzaHut"] = new PizzaHut::Factory;
}



//Static member defination:
YumRestaurantFactoryInitializer YumRestaurantFactoryInitializer::si;
