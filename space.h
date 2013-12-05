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
        space_obj();

        std::vector<base_item>& get_items();
        int                     get_max_items();
        space_type              get_type();

        void                    add_item(base_item item);
        void                    add_items(std::vector<base_item> items);

    protected:
        virtual void            set_default_values();

        space_type              type;
        std::vector<base_item>  items;
        int                     max_items;
};


class wall_obj : public space_obj
{
    public:
        void set_strength(int val);
        int  get_strength();

    private:
        void set_default_values();

        int  strength;
};


#endif
