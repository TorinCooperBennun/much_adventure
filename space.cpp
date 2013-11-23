#include "space.h"


space_obj::space_obj(space_attribute attributes, std::vector<base_item> &extra_items)
{
    current_attributes = attributes;
    current_max_items = 25;
    current_extra_items = extra_items;

    current_items = extra_items;
}


space_obj::space_obj()
{
    current_attributes = SPACE_EMPTY;
    current_max_items = 25;
}


std::vector<base_item>& space_obj::get_current_items()
{
    return current_items;
}


std::vector<base_item>& space_obj::get_extra_items()
{
    return current_extra_items;
}


int space_obj::get_max_items()
{
    return current_max_items;
}


space_attribute space_obj::get_attributes()
{
    return current_attributes;
}


void space_obj::add_item(base_item item)
{
    current_items.push_back(item);
}


void space_obj::add_items(std::vector<base_item> items)
{
    
