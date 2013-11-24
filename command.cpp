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
            wign->print("Too many parameters! Either use 'help' on its own, or put one command name after it.");
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
                helpstring << "Quits game.";
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

            wign->coord_x = new_x;
            wign->coord_y = new_y;
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
