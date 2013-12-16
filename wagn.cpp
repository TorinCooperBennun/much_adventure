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

    map_width = 100;
    map_height = 100;
    closed = false;
    p_pos = coordinate((map_width - 1) / 2, (map_height - 1) / 2);

    set_string_vectors();
}


wagn::~wagn()
{
}


void wagn::print_info()
{
    std::cout << "X: " << p_pos.get_x() << "\r\n"
              << "Y: " << p_pos.get_y() << "\r\n"
              << "No. items in inventory: " << inventory.size() << "\r\n"
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
    yaml_parse story("story.yml");
    if (story.parse(space_map) != 0) {
        std::cerr << "Parse failed.\r\n";
    }

    fill_map(space_map, coordinate(map_width, map_height), SPACE_EMPTY);

    create_walled_room(space_map, coordinate(2, 2), coordinate(8, 8),
            true, 50, NULL);
    
    p_pos.set_xy(5, 5);

    std::ofstream f("map.txt");
    if (f.is_open()) {
        for (int y = map_height - 1; y >= 0; y--) {
            std::stringstream s;
            s << y;
            for (unsigned i = 0; i < 3 - s.str().size(); i++) {
                f << ' ';
            }
            f << y << ' ';
            for (int x = 0; x < map_width; x++) {
                char c;
                switch (space_map[y][x]->get_type()) {
                    case SPACE_EMPTY:
                        c = '.';
                        break;
                    case SPACE_ROOM:
                        c = '0';
                        break;
                    case SPACE_WALL:
                        c = 'W';
                        break;
                    default:
                        c = '?';
                        break;
                }
                if (x == p_pos.get_x() and y == p_pos.get_y()) {
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
