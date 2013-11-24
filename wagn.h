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


class wagn
{
    public:
        wagn();
        ~wagn();

        void                                  print_info();
        void                                  print(std::string str);
        command_obj                           get_input();

        void                                  generate_spaces();
        bool                                  is_closed();

    private:
        std::vector<base_item>                inventory;
        std::vector<command_obj>              history;
        std::vector< std::vector<space_obj> > space_map;

        int                                   map_width,
                                              map_height;

        bool                                  closed;

        int                                   coord_x,
                                              coord_y;

        friend class command_obj;
};


#endif
