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


#ifndef GENERATION_H
#define GENERATION_H


#include "space.h"
#include "item_base.h"

#include <vector>
#include <iostream>


int create_walled_room(
        space_vect &            smap,
        coordinate              bl,
        coordinate              tr,
        bool                    walled,
        int                     wall_strength,
        std::vector<base_item> *items);


int create_straight_corridor(
        space_vect &            smap,
        direction               dir,
        coordinate              start,
        int                     length,
        bool                    walled,
        int                     wall_strength,
        std::vector<base_item> *items);

int fill_map(
        space_vect & smap,
        coordinate   size,
        space_type   type);


#endif
