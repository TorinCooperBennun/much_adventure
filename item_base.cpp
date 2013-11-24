#include "item_base.h"


base_item::base_item()
{
    type = NULL_TYPE;
    name = "Item";
    actions.clear();
}


base_item::~base_item()
{
}


std::string base_item::interact(int action_num)
{
    return std::string("Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
}


item_type base_item::get_type()
{
    return type;
}


std::string base_item::get_name()
{
    return name;
}


std::vector<std::string> base_item::get_actions()
{
    return actions;
}
