// **************************************************************************
#ifndef YumRestaurant_h_included_
#define YumRestaurant_h_included_

#include <vector>
#include <string>

class YumRestaurant
{
  protected:
    // ======================================================================
    // Constructor
    YumRestaurant();

  public:
    virtual ~YumRestaurant();

  public:
    // ======================================================================
    // Interface

    virtual std::string getName() = 0;

    virtual std::vector<std::string> getMenu() = 0;

  protected:
    // ======================================================================
    // Data Member

    std::string m_name;

    std::vector<std::string> m_menu;
};
#endif
// **************************************************************************
