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
        space_obj(space_type type);
        space_obj();

        std::vector<base_item>& get_items();
        int                     get_max_items();
        space_type              get_type();


        void                    add_item(base_item item);
        void                    add_items(std::vector<base_item> items);

    private:
        space_type              type;
        std::vector<base_item>  items;
        int                     max_items;
};


#endif
