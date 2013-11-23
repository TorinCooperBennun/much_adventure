#ifndef ITEM_BASE_H
#define ITEM_BASE_H


#include <string>
#include <vector>

#include "item_types.h"


class base_item
{
    public:
        base_item();
        ~base_item();

                item_type                 get_type();
                std::string               get_name();
                std::vector<std::string>  get_actions();

        virtual std::string               interact(int action_num);

    private:
                item_type                 type;
                std::string               name;
                std::vector<std::string>  actions;
};


#endif
