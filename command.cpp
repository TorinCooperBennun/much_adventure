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
                       << "help\r\n"
                       << "move\r\n"
                       << "quit\r\n"
                       << "\r\n"
                       << "Most commands are case-insensitive, unless it involves an item's name, description, etc.\r\n"
                       << "Say 'help' followed by a command to get more information on it!";
        }
        else if (parameters.size() > 1) {
            wign->print("Too many parameters! Either use \'help\' on its own, or put one command name after it.");
            valid = false;
        }
        else if (parameters.size() == 1) {

            std::for_each(parameters.begin(), parameters.end(),
                    [](std::string& str) {
                        std::transform(str.begin(), str.end(), str.begin(), tolower);
                    }
            );

            /* help move */
            if ((parameters[0] == "move") or (parameters[0] == "mv")) {
                helpstring << "move DIRECTION. DIRECTION must be north, east, south or west.\r\n"
                           << "May be abbreviated to 'mv'. Directions may be abbreviated to n, e, s, w.";
            }
            /* help quit */
            else if ((parameters[0] == "quit") or (parameters[0] == "exit") or (parameters[0] == "q")) {
                helpstring << "Quits game (you may use \'quit\', \'q\' or \'exit\').";
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

            /* more hack */
            std::for_each(parameters.begin(), parameters.end(),
                    [](std::string& str) {
                        std::transform(str.begin(), str.end(), str.begin(), tolower);
                    }
            );

            if ((parameters[0] == "north") or (parameters[0] == "n")) {
                new_y++;
            }
            else if ((parameters[0] == "south") or (parameters[0] == "s")) {
                new_y--;
            }
            else if ((parameters[0] == "east") or (parameters[0] == "e")) {
                new_x++;
            }
            else if ((parameters[0] == "west") or (parameters[0] == "w")) {
                new_x--;
            }
            else {
                wign->print("Unrecognised direction (north/east/south/west)!");
                valid = false;
            }

            space_obj &new_space = wign->space_map[new_x][new_y];
            
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
