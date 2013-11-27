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


#include "wagn.h"


wagn::wagn()
{
    std::stringstream notices;
    notices << "wagnventures Copyright (C) 2013 Torin Cooper-Bennun\r\n"
            << "This program comes with ABSOLUTELY NO WARRANTY.\r\n"
            << "\r\n"
            << "Type \'help\' for a list of commands.\r\n";
    this->print(notices.str());

    map_width = 101;
    map_height = 101;
    closed = false;
    coord_x = map_width / 2;
    coord_y = map_height / 2;
}


wagn::~wagn()
{
}


void wagn::print_info()
{
    std::cout << "X: " << coord_x << "\r\n"
              << "Y: " << coord_y << "\r\n"
              << "Items in inventory: " << inventory.size() << "\r\n"
              << "\r\n"
              << "Map: (not yet)\r\n";
}


void wagn::print(std::string str)
{
    std::cout << str << "\r\n";
}


command_obj wagn::get_input()
{
    std::cout << ">";
    std::string input;
    std::getline(std::cin, input);
    command_obj cmd(input);
    return cmd;
}


void wagn::generate_spaces()
{
    /* this is the biggest hack known to man.
     * I honestly don't know any more. */
    space_map = std::vector< std::vector<space_obj> > (
        map_width, std::vector<space_obj> (
            map_height, space_obj()
        )
    );
}


bool wagn::is_closed()
{
    return closed;
}
