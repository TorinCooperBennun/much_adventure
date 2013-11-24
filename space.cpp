#include "space.h"


space_obj::space_obj(space_type type)
{
    this->type = type;
    this->max_items = 25;
}


space_obj::space_obj()
{
    this->type = SPACE_EMPTY;
    this->max_items = 25;
}


std::vector<base_item>& space_obj::get_items()
{
    return items;
}


int space_obj::get_max_items()
{
    return max_items;
}


space_type space_obj::get_type()
{
    return type;
}


void space_obj::add_item(base_item item)
{
    items.push_back(item);
}


void space_obj::add_items(std::vector<base_item> items)
{
    this->items.insert(this->items.end(), items.begin(), items.end());
}
