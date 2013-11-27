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

//    north_wall = false;
//    south_wall = false;
//    east_wall = false;
//    west_wall = false;
//
//    north_door = false;
//    south_door = false;
//    east_door = false;
//    west_door = false;
//
//    north_door_locked = false;
//    south_door_locked = false;
//    east_door_locked = false;
//    west_door_locked = false;

    items.push_back(base_item());
    items.push_back(base_item());
    items.push_back(base_item());
}


//space_obj::space_obj(space_type type)
//{
//    this->set_default_values();
//    this->type = type;
//}


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


//int space_obj::get_wall_mask()
//{
//    int bitmask = 0;
//    bitmask |= ((north_wall == true) * WALL_NORTH);
//    bitmask |= ((south_wall == true) * WALL_SOUTH);
//    bitmask |= ((east_wall == true) * WALL_EAST);
//    bitmask |= ((west_wall == true) * WALL_WEST);
//    return bitmask;
//}
//
//
//int space_obj::get_door_mask()
//{
//    int bitmask = 0;
//    bitmask |= ((north_door == true) * DOOR_NORTH);
//    bitmask |= ((south_door == true) * DOOR_SOUTH);
//    bitmask |= ((east_door == true) * DOOR_EAST);
//    bitmask |= ((west_door == true) * DOOR_WEST);
//    return bitmask;
//}
//
//
//int space_obj::get_door_lock_mask()
//{
//    int bitmask = 0;
//    bitmask |= ((north_door_locked == true) * DOOR_NORTH_LOCK);
//    bitmask |= ((south_door_locked == true) * DOOR_SOUTH_LOCK);
//    bitmask |= ((east_door_locked == true) * DOOR_EAST_LOCK);
//    bitmask |= ((west_door_locked == true) * DOOR_WEST_LOCK);
//    return bitmask;
//}


void space_obj::add_item(base_item item)
{
    items.push_back(item);
}


void space_obj::add_items(std::vector<base_item> items)
{
    this->items.insert(this->items.end(), items.begin(), items.end());
}


//void space_obj::set_walls(int wall_mask)
//{
//    if (wall_mask & WALL_NORTH) {
//        north_wall = true;
//    }
//    if (wall_mask & WALL_SOUTH) {
//        south_wall = true;
//    }
//    if (wall_mask & WALL_EAST) {
//        east_wall = true;
//    }
//    if (wall_mask & WALL_WEST) {
//        west_wall = true;
//    }
//}
//
//
//void space_obj::set_doors(int door_mask)
//{
//    if (door_mask & DOOR_NORTH) {
//        north_door = true;
//    }
//    if (door_mask & DOOR_SOUTH) {
//        south_door = true;
//    }
//    if (door_mask & DOOR_EAST) {
//        east_door = true;
//    }
//    if (door_mask & DOOR_WEST) {
//        west_door = true;
//    }
//}
//
//
//void space_obj::lock_doors(int door_lock_mask)
//{
//    if (door_lock_mask & DOOR_NORTH_LOCK) {
//        north_door_locked = true;
//    }
//    if (door_lock_mask & DOOR_SOUTH_LOCK) {
//        south_door_locked = true;
//    }
//    if (door_lock_mask & DOOR_EAST_LOCK) {
//        east_door_locked = true;
//    }
//    if (door_lock_mask & DOOR_WEST_LOCK) {
//        west_door_locked = true;
//    }
//}
