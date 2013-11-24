#ifndef SPACE_H
#define SPACE_H


#include <vector>

#include "item_base.h"


enum space_type
{
    SPACE_EMPTY,
    SPACE_ROOM,
    SPACE_WALL,
    SPACE_DOOR,
    SPACE_CORRIDOR,
};


class space_obj
{
    public:
        space_obj(space_type type);
        space_obj();

        std::vector<base_item>& get_items();
        int                     get_max_items();
        space_type              get_type();


        void                    add_item(base_item item);
        void                    add_items(std::vector<base_item> items);

    private:
        space_type              type;
        std::vector<base_item>  items;
        int                     max_items;
};


#endif
