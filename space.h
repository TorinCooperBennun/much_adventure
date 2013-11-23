#ifndef SPACE_H
#define SPACE_H


#include <vector>

#include "item_base.h"


class space_obj
{
    public:
        space_obj(space_attribute attributes, std::vector<base_item> &extra_items);
        space_obj();

        std::vector<base_item>& get_current_items();
        std::vector<base_item>& get_extra_items();
        int                     get_max_items();
        space_attribute         get_attributes();


        void                    add_item(base_item item);
        void                    add_items(std::vector<base_item> items);

    private:
        space_attribute         current_attributes;
        std::vector<base_item>  current_extra_items;
        int                     current_max_items;

        std::vector<base_item>  current_items;
};


enum space_attribute
{
    SPACE_EMPTY  = 0x00000001,
    SPACE_EVENT  = 0x00000002,
    SPACE_RANDOM = 0x00000004,
};
