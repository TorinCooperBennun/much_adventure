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


#ifndef SPACE_H
#define SPACE_H


#include <vector>

#include "item_base.h"


//#define WALL_NORTH 0x01
//#define WALL_SOUTH 0x02
//#define WALL_EAST  0x04
//#define WALL_WEST  0x08
//
//#define DOOR_NORTH 0x01
//#define DOOR_SOUTH 0x02
//#define DOOR_EAST  0x04
//#define DOOR_WEST  0x08
//
//#define DOOR_NORTH_LOCK 0x01
//#define DOOR_SOUTH_LOCK 0x02
//#define DOOR_EAST_LOCK  0x04
//#define DOOR_WEST_LOCK  0x08


enum direction
{
    DIR_NORTH,
    DIR_EAST,
    DIR_SOUTH,
    DIR_WEST,
};


enum space_type
{
    SPACE_EMPTY,
    SPACE_ROOM,
    SPACE_WALL,
    SPACE_DOOR,
    SPACE_CORRIDOR,
};


class space_obj
{
    public:
//        space_obj(space_type type);
        space_obj();

        std::vector<base_item>& get_items();
        int                     get_max_items();
        space_type              get_type();

//        int                     get_wall_mask();
//        int                     get_door_mask();
//        int                     get_door_lock_mask();


        void                    add_item(base_item item);
        void                    add_items(std::vector<base_item> items);

//        void                    set_walls(int wall_mask);
//        void                    set_doors(int door_mask);
//        void                    lock_doors(int door_lock_mask);

    private:
        void                    set_default_values();

        space_type              type;
        std::vector<base_item>  items;
        int                     max_items;

//        bool                    north_wall,
//                                south_wall,
//                                east_wall,
//                                west_wall;
//
//        bool                    north_door,
//                                south_door,
//                                east_door,
//                                west_door;
//
//        bool                    north_door_locked,
//                                south_door_locked,
//                                east_door_locked,
//                                west_door_locked;
};


#endif
