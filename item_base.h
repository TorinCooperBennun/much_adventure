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
