#include "TacoBell.h"

// ---------------------------------------------------------------------------
TacoBell::TacoBell()
{
  m_name = "Taco Bell";
  m_menu.push_back("Taco 1");
  m_menu.push_back("Taco 2");
}

// ---------------------------------------------------------------------------

TacoBell::~TacoBell()
{
  // nothing
}

std::string TacoBell::getName(){
  return m_name;
}

std::vector<std::string> TacoBell::getMenu(){
  return m_menu;
}

