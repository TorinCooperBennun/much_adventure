#include "wagn.h"


wagn::wagn()
{
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
            map_height, space_obj(SPACE_ROOM)
        )
    );
}


bool wagn::is_closed()
{
    return closed;
}
