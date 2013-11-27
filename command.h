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


//#if (!defined COMMAND_H) && (!defined WAGN_H_COMMAND_OBJ_DECLARED)
#ifndef COMMAND_H
#define COMMAND_H


/* resolving cyclical dependency */
class wagn;


#include "wagn.h"

#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>


class command_obj
{
    public:
        command_obj(const std::string& original_str);
        command_obj();
        ~command_obj();

        std::string              execute(wagn *wign);

    private:
        std::string              action;
        std::vector<std::string> parameters;

        bool                     valid;
};


#endif
