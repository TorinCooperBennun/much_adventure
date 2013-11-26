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
    std::stringstream stream(original_str);

    action = "";

    while ((action == " ") or (action == "")) {
        if (!std::getline(stream, action, ' ')) {
            action = "bullshitcommandlol";
        }
    }
    std::transform(action.begin(), action.end(), action.begin(), tolower);

    std::string token;
    while (std::getline(stream, token, ' ')) {
        if ((token != "") and (token != " ")) {
            parameters.push_back(token);
        }
    }
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
    bool valid = true;

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
                    space_obj &current_space = wign->space_map[wign->coord_x][wign->coord_y],
                              &next_space    = wign->space_map[new_x][new_y];

                    bool hit_wall = false,
                         locked_door = false,
                         door = false;
                    
                    /* check for walls, doors
                     * on another note DON'T READ THIS CODE LOL I DON'T KNOW
                     * WHAT I'M DOING ANY MORE */

                    if (dir == DIR_NORTH) {
                        if ((current_space.get_wall_mask() & WALL_NORTH) or (next_space.get_wall_mask() & WALL_SOUTH)) {
                            wign->print("You try to go north, but hit a wall.");
                            hit_wall = true;
                        }
                        if ((!hit_wall) and ((current_space.get_door_lock_mask() & DOOR_NORTH_LOCK) or (next_space.get_door_lock_mask() & DOOR_SOUTH_LOCK))) {
                            wign->print("You try to go north, but encounter a locked door.");
                            locked_door = true;
                        }
                        if ((!locked_door) and ((current_space.get_door_mask() & DOOR_NORTH) or (next_space.get_door_mask() & DOOR_SOUTH))) {
                            door = true;
                        }
                    }
                    else if (dir == DIR_EAST) {
                        if ((current_space.get_wall_mask() & WALL_EAST) or (next_space.get_wall_mask() & WALL_WEST)) {
                            wign->print("You try to go east, but hit a wall.");
                            hit_wall = true;
                        }
                        if ((!hit_wall) and ((current_space.get_door_lock_mask() & DOOR_EAST_LOCK) or (next_space.get_door_lock_mask() & DOOR_WEST_LOCK))) {
                            wign->print("You try to go east, but encounter a locked door.");
                            locked_door = true;
                        }
                        if ((!locked_door) and ((current_space.get_door_mask() & DOOR_EAST) or (next_space.get_door_mask() & DOOR_WEST))) {
                            door = true;
                        }
                    }
                    else if (dir == DIR_SOUTH) {
                        if ((current_space.get_wall_mask() & WALL_SOUTH) or (next_space.get_wall_mask() & WALL_NORTH)) {
                            wign->print("You try to go south, but hit a wall.");
                            hit_wall = true;
                        }
                        if ((!hit_wall) and ((current_space.get_door_lock_mask() & DOOR_SOUTH_LOCK) or (next_space.get_door_lock_mask() & DOOR_NORTH_LOCK))) {
                            wign->print("You try to go south, but encounter a locked door.");
                            locked_door = true;
                        }
                        if ((!locked_door) and ((current_space.get_door_mask() & DOOR_SOUTH) or (next_space.get_door_mask() & DOOR_NORTH))) {
                            door = true;
                        }
                    }
                    else if (dir == DIR_WEST) {
                        if ((current_space.get_wall_mask() & WALL_WEST) or (next_space.get_wall_mask() & WALL_EAST)) {
                            wign->print("You try to go west, but hit a wall.");
                            hit_wall = true;
                        }
                        if ((!hit_wall) and ((current_space.get_door_lock_mask() & DOOR_WEST_LOCK) or (next_space.get_door_lock_mask() & DOOR_EAST_LOCK))) {
                            wign->print("You try to go west, but encounter a locked door.");
                            locked_door = true;
                        }
                        if ((!locked_door) and ((current_space.get_door_mask() & DOOR_WEST) or (next_space.get_door_mask() & DOOR_EAST))) {
                            door = true;
                        }
                    }

                    if (door) {
                        wign->print("You pass through an open door.");
                    }

                    if (!hit_wall and !locked_door) {
                        std::stringstream movestr;
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

                        if (door) {
                            movestr << " and pass through an open door.";
                        }
                        else {
                            movestr << ".";
                        }

                        wign->print(movestr.str());

                        command_obj look_cmd("look");
                        look_cmd.execute(wign);
                    }
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
            space_obj &space = wign->space_map[wign->coord_x][wign->coord_y];
            std::vector<base_item> &items = space.get_items();

            std::stringstream lookstr;
            lookstr << "You look around and see ";

            if (items.size() == 0) {
                lookstr << "basically nothing.";
            }
            else {
                for (unsigned i = 0; i < items.size(); i++) {
                    std::string name = items[i].get_name();

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
