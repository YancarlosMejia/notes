#include "KentuckyFriedChicken.h"

// ---------------------------------------------------------------------------
KentuckyFriedChicken::KentuckyFriedChicken()
{
  m_name = "Kentucky Fried Chicken";
  m_menu.push_back("Unhealthy Snack 1");
  m_menu.push_back("Unhealthy Snack 2");
}

// ---------------------------------------------------------------------------

KentuckyFriedChicken::~KentuckyFriedChicken()
{
  // nothing
}

std::string KentuckyFriedChicken::getName(){
  return m_name;
}

std::vector<std::string> KentuckyFriedChicken::getMenu(){
  return m_menu;
}

