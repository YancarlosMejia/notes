#include "PizzaHut.h"

// ---------------------------------------------------------------------------
PizzaHut::PizzaHut()
{
  m_name = "Pizza Hut";
  m_menu.push_back("Large Pizza");
  m_menu.push_back("Medium Pizza");
}

// ---------------------------------------------------------------------------

PizzaHut::~PizzaHut()
{
  // nothing
}

std::string PizzaHut::getName(){
  return m_name;
}

std::vector<std::string> PizzaHut::getMenu(){
  return m_menu;
}

