#include <vector>
#include "YumRestaurant.h"
#include "YumRestaurantFactory.h"
#include <iostream>

int main()
{
  std::vector<YumRestaurant*> restaurants;

  std::string s;
  std::cout<<"What restaurant do you want to open? (KentuckyFriedChicken, PizzHut or TacoBell). Enter EOF to stop opening new restaurants"<<std::endl;
  std::cin >> s;

  while (std::cin){
    std::cout<<"What restaurant do you want to open? (KentuckyFriedChicken, PizzHut or TacoBell). Enter EOF to stop opening new restaurants"<<std::endl;
    restaurants.push_back(YumRestaurantFactory::createRestaurant(s));
    std::cin >>s;
  }

  for (size_t i = 0; i < restaurants.size(); i++){
    std::cout<<"Name: "<<restaurants[i]->getName()<<std::endl;
    std::cout<<"Shop Number: "<<i<<std::endl;
    std::cout<<"Menu: "<<std::endl;
    std::vector<std::string> menu = restaurants[i]->getMenu();
    for (size_t i = 0; i < menu.size(); i++){
      std::cout<<menu[i]<<std::endl;
    }//for
    std::cout<<std::endl;
  }
}
