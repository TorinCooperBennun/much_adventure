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


#ifndef WAGN_H
#define WAGN_H


/* resolving cyclical dependency */
class command_obj;


#include "item_base.h"
#include "command.h"
#include "space.h"

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <fstream>


class wagn
{
    public:
        wagn();
        ~wagn();

        void                                   print_info();
        void                                   print(std::string str);
        command_obj                            get_input();

        void                                   generate_spaces();
        bool                                   is_closed();

    private:
        void                                   set_string_vectors();
        std::string&                           pick_str_from_vect(std::vector<std::string>& vect);

        std::vector<base_item *>               inventory;
        std::vector<command_obj>               history;
        std::vector< std::vector<space_obj*> > space_map;

        int                                    map_width,
                                               map_height;

        bool                                   closed;

        int                                    coord_x,
                                               coord_y;

        std::vector<std::string>               empty_room_strings,
                                               items_seen_strings;

        friend class command_obj;
};


#endif
