/* Copyright 2013 Torin Cooper-Bennun
 *
 * This file is part of wagnventures.
 * 
 * wagnventures is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * wagnventures is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with wagnventures.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#include "space.h"


void space_obj::set_default_values()
{
    type = SPACE_ROOM;
    max_items = 3;

    base_item it;

    items.push_back(it);
}


space_obj::space_obj()
{
    this->set_default_values();
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


void wall_obj::set_strength(int val)
{
    strength = val;
}


int wall_obj::get_strength()
{
    return strength;
}


void wall_obj::set_default_values()
{
    type = SPACE_WALL;
    max_items = 1;
    strength = 100;
}
