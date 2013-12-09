#ifndef GENERATION_H
#define GENERATION_H


#include "space.h"
#include "item_base.h"

#include <vector>
#include <iostream>


int create_walled_room(
        space_vect &           smap,
        coordinate             bottom_left_flr,
        coordinate             top_right_flr,
        bool                   walled,
        int                    wall_strength,
        bool                   overwrite,
        std::vector<base_item> items);


int create_straight_corridor(
        space_vect &           smap,
        direction              dir,
        coordinate             start,
        int                    length,
        bool                   walled,
        int                    wall_strength,
        bool                   overwrite,
        std::vector<base_item> items);


#endif
