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
    coord_x = 51;
    coord_y = 51;
//    coord_x = map_width / 2;
//    coord_y = map_height / 2;

    set_string_vectors();
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
    /* generate all blanks */
    space_map = std::vector< std::vector<space_obj*> > (
        map_width, std::vector<space_obj*> (
            map_height, NULL
        )
    );
    for (int y = 0; y < map_height; y++) {
        for (int x = 0; x < map_width; x++) {
            space_map[y][x] = new space_obj(true);
        }
    }

    /* generate 5x5 walled square in centre */
    int x_west  = map_width / 2 - 2,
        x_east  = map_width / 2 + 2,
        y_north = map_height / 2 + 2,
        y_south = map_height / 2 - 2;

    x_west--; x_east--; y_north--; y_south--;

    for (int y = y_south; y <= y_north; y++) {
        for (int x = x_west; x <= x_east; x++) {
            delete space_map[y][x];
            space_map[y][x] = new space_obj();
        }
    }

    /* walls */
    for (int x = x_west; x <= x_east; x++) {
        delete space_map[y_north + 1][x];
        delete space_map[y_south - 1][x];
        space_map[y_north + 1][x] = new wall_obj();
        space_map[y_south - 1][x] = new wall_obj();
    }
    for (int y = y_south - 1; y <= y_north + 1; y++) {
        delete space_map[y][x_east - 1];
        delete space_map[y][x_west + 1];
        space_map[y][x_east - 1] = new wall_obj();
        space_map[y][x_west - 1] = new wall_obj();
    }

    std::ofstream f("map.txt");
    if (f.is_open()) {
        for (int y = map_height - 1; y >= 0; y--) {
            std::stringstream s;
            s << y;
            for (int i = 0; i < 3 - s.str().size(); i++) {
                f << ' ';
            }
            f << y << ' ';
            for (int x = 0; x < map_width; x++) {
                char c = (space_map[y][x]->get_type() == SPACE_EMPTY) ? '0' : '1';
                if (x == 51 and x == y) {
                    c = 'p';
                }
                f << c;
            }
            f << "\r\n";
        }
    }
}


bool wagn::is_closed()
{
    return closed;
}


void wagn::set_string_vectors()
{
    empty_room_strings = {
        "The space around you is empty.",
        "There are no items immediately near you.",
        "You glance around, but spot nothing interesting.",
        "You appear to be in an empty space.",
    };

    items_seen_strings = {
        "You glance around the immediate area and spot ",
        "In front of you, you see ",
        "Behold! You see ",
    };
}


std::string& wagn::pick_str_from_vect(std::vector<std::string>& vect)
{
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);
    std::uniform_int_distribution<unsigned> dist(0, vect.size() - 1);
    return vect[dist(engine)];
}
