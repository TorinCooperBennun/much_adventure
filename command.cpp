#include "command.h"


command_obj::command_obj(const std::string& original_str)
{
    std::stringstream stream(original_str);
    std::getline(stream, action, ' ');
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
    if (action == "help") {
        wign->print_help();
    } else if ((action == "move") or (action == "mv")) {
        if (parameters.size() < 1) {
            wign->print("Move requires a direction!");
        } else {
            if (parameters[0] == "north") {
                wign->coord_y++;
            } else if (parameters[0] == "south") {
                wign->coord_y--;
            } else if (parameters[0] == "east") {
                wign->coord_x++;
            } else if (parameters[0] == "west") {
                wign->coord_x--;
            } else {
                wign->print("Unrecognised direction (north/east/south/west)!");
            }
        }
    } else {
        wign->print("Unrecognised command! Try help!");
    }
}
