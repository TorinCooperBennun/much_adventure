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


#include "command.h"


command_obj::command_obj(const std::string& original_str)
{
    valid = true;
    action = "";

    std::vector<std::string> tokens = split_by_whitespace(original_str);
    if (tokens.size() == 0) {
        valid = false;
    }
    else {
        action = tokens[0];
        std::transform(action.begin(), action.end(), action.begin(), tolower);
        for (unsigned i = 1; i < tokens.size(); i++) {
            parameters.push_back(tokens[i]);
        }
    }

//    std::stringstream stream(original_str);
//
//    auto wspace_check = [] (std::string &str) {
//        if (str.size() == 0) {
//            return true;
//        }
//        for (unsigned i = 0; i < str.size(); i++) {
//            if (isspace(str[i])) {
//                return true;
//            }
//        }
//        return false;
//    };
//
//    while (wspace_check(action)) {
//        if (!std::getline(stream, action, ' ')) {
//            valid = false;
//            break;
//        }
//    }
//    
//    std::transform(action.begin(), action.end(), action.begin(), tolower);
//
//    std::string token;
//    while (std::getline(stream, token, ' ')) {
//        if ((token != "") and (token != " ")) {
//            parameters.push_back(token);
//        }
//    }
}


command_obj::command_obj()
{
    action = "";
}


command_obj::~command_obj()
{
}


std::string command_obj::execute(wagn *wign)
{
    if (!valid) {
//        wign->print("Invalid command. Try 'help'.");
        return "lel";
    }

    /* help */
    if (action == "help") {
        std::stringstream helpstring;

        if (parameters.size() == 0) {
            helpstring << "Commands:\r\n"
                       << "\r\n"
                       << "help\r\n"
                       << "move\r\n"
                       << "look\r\n"
                       << "quit\r\n"
                       << "\r\n"
                       << "Most commands are case-insensitive, unless it involves an item's name, description, etc.\r\n"
                       << "Say 'help' followed by a command to get more information on it!";
        }
        else if (parameters.size() > 1) {
            wign->print("Too many parameters! Either use 'help' on its own, or put one command name after it.");
            valid = false;
        }
        else if (parameters.size() == 1) {

            /* hacks idk */
            std::for_each(parameters.begin(), parameters.end(),
                    [](std::string& str) {
                        std::transform(str.begin(), str.end(), str.begin(), tolower);
                    }
            );

            /* help move */
            if ((parameters[0] == "move") or (parameters[0] == "mv")) {
                helpstring << "Move character in direction. Use one of the below directions:\r\n"
                           << "\r\n"
                           << "north (n)\r\n"
                           << "east  (e)\r\n"
                           << "south (s)\r\n"
                           << "west  (w)\r\n"
                           << "\r\n"
                           << "You can abbreviate 'move' to 'mv'.\r\n";
            }
            /* help quit */
            else if ((parameters[0] == "quit") or (parameters[0] == "exit") or (parameters[0] == "q")) {
                helpstring << "Quits game (you may use 'quit', 'q' or 'exit').";
            }
            /* help help */
            else if ((parameters[0] == "help")) {
                helpstring << "Shows help (obviously).";
            }
            /* unrecognised */
            else {
                helpstring << "'" << parameters[0] << "' is an invalid command. Try 'help'.";
            }
        }

        wign->print(helpstring.str());
    }

    /* move */
    else if ((action == "move") or (action == "mv")) {

        /* correct number of parameters? */
        if (parameters.size() < 1) {
            wign->print("Move requires a direction! Try 'help move'.");
            valid = false;
        }
        else if (parameters.size() > 1) {
            wign->print("Too many parameters! Try 'help move'.");
            valid = false;
        }
        else {
            int new_x = wign->coord_x,
                new_y = wign->coord_y;

            /* little hack to set parameters lowercase */
            std::for_each(parameters.begin(), parameters.end(),
                    [](std::string& str) {
                        std::transform(str.begin(), str.end(), str.begin(), tolower);
                    }
            );

            direction dir;

            /* directions */
            if ((parameters[0] == "north") or (parameters[0] == "n")) {
                dir = DIR_NORTH;
                new_y++;
            }
            else if ((parameters[0] == "south") or (parameters[0] == "s")) {
                dir = DIR_SOUTH;
                new_y--;
            }
            else if ((parameters[0] == "east") or (parameters[0] == "e")) {
                dir = DIR_EAST;
                new_x++;
            }
            else if ((parameters[0] == "west") or (parameters[0] == "w")) {
                dir = DIR_WEST;
                new_x--;
            }
            else {
                wign->print("Unrecognised direction! Try 'help move'.");
                valid = false;
            }

            if (valid) {
                /* checking if you're off the map */
                if (new_y >= wign->map_height) {
                    wign->print("You hit the northern border of the map!");
                }
                else if (new_y < 0) {
                    wign->print("You hit the southern border of the map!");
                }
                else if (new_x >= wign->map_width) {
                    wign->print("You hit the eastern border of the map!");
                }
                else if (new_x < 0) {
                    wign->print("You hit the western border of the map!");
                }
                else {
                    std::stringstream movestr;

                    space_obj *nspace = wign->space_map[wign->coord_x][wign->coord_y];
                    space_type stype = nspace->get_type();

                    switch (stype) {
                        case SPACE_EMPTY:
                            movestr << "You cannot move into the void.";
                            break;

                        case SPACE_ROOM:
                        case SPACE_CORRIDOR:
                            movestr << "You move ";
                            if (dir == DIR_NORTH) {
                                movestr << "north";
                            }
                            else if (dir == DIR_EAST) {
                                movestr << "east";
                            }
                            else if (dir == DIR_SOUTH) {
                                movestr << "south";
                            }
                            else if (dir == DIR_WEST) {
                                movestr << "west";
                            }
                            wign->coord_x = new_x;
                            wign->coord_y = new_y;
                            movestr << ".";
                            break;

                        case SPACE_WALL:
                            {
                                wall_obj *wall = dynamic_cast<wall_obj*>(nspace);
                                movestr << "You attempt to move ";
                                if (dir == DIR_NORTH) {
                                    movestr << "north";
                                }
                                else if (dir == DIR_EAST) {
                                    movestr << "east";
                                }
                                else if (dir == DIR_SOUTH) {
                                    movestr << "south";
                                }
                                else if (dir == DIR_WEST) {
                                    movestr << "west";
                                }
                                movestr << ", but hit a wall. You knock against it, and estimate its strength to be about " << wall->get_strength() << ".";
                                break;
                            }
                        case SPACE_DOOR:
                            movestr << "You hit a locked door.";
                            break;
                    }

                    wign->print(movestr.str());

                    command_obj look_cmd("look");
                    look_cmd.execute(wign);
                }
            }
        }
    }

    /* look */
    else if ((action == "look") or (action == "see")) {

        if (parameters.size() != 0) {
            wign->print("'look' doesn't take parameters!");
            valid = false;
        }
        else {
            space_obj *space = wign->space_map[wign->coord_x][wign->coord_y];
            std::vector<base_item> &items = space->get_items();

            bool look_for_items;

            space_type stype = space->get_type();
            switch (stype) {
                case SPACE_EMPTY:
                case SPACE_ROOM:
                case SPACE_CORRIDOR:
                    look_for_items = true;
                    break;
                case SPACE_DOOR:
                case SPACE_WALL:
                    look_for_items = false;
                    break;
            }

            std::stringstream lookstr;

            std::string& space_lookstr = space->get_lookstr();
            if (space_lookstr.size() > 0) {
                lookstr << space->get_lookstr() << ". ";
            }
//            lookstr << "You look around and see ";

            if (look_for_items) {
                if (items.size() == 0) {
                    lookstr << wign->pick_str_from_vect(wign->empty_room_strings);
                }
                else {
                    lookstr << wign->pick_str_from_vect(wign->items_seen_strings);
                    for (unsigned i = 0; i < items.size(); i++) {
                        base_item& it = items[i];
                        std::string name = it.get_name();

                        if (i != 0) {
                            if ((i == items.size() - 1)) {
                                lookstr << " and ";
                            }
                            else {
                                lookstr << ", ";
                            }
                        }

                        char c = tolower(name[0]);
                        if ((c == 'a') or (c == 'e') or (c == 'i') or (c == 'o') or (c == 'u')) {
                            lookstr << "an ";
                        }
                        else {
                            lookstr << "a ";
                        }
                        lookstr << name;
                        
                        if (i == (items.size() - 1)) {
                            lookstr << ".";
                        }
                    }
                }
            }
            else {
                lookstr << "Move along.";
            }

            wign->print(lookstr.str());
        }
    }

    /* quit */
    else if ((action == "quit") or (action == "q") or (action == "exit")) {
        wign->closed = true;
    }

    /* unrecognised */
    else {
        std::stringstream strstr;
        strstr << "'" << action << "' is an invalid command. Try 'help'.";
        wign->print(strstr.str());
        valid = false;
    }

    if (valid) {
        return "";
    }
    else {
        return "lel";
    }
}


std::vector<std::string> command_obj::split_by_whitespace(std::string str)
{
    std::stringstream ss(str);
    std::string t = "";
    std::vector<std::string> a;

    while (1) {
        ss >> std::ws >> t;
        if (!ss.fail()) {
            a.push_back(t);
        }
        else {
            return a;
        }
    }
}
