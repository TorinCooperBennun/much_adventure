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


#ifndef PARSER_H
#define PARSER_H


#include <vector>
#include <string>
#include <yaml-cpp/yaml.h>
#include <boost/utility.hpp>

#include "space.h"
#include "item_base.h"
#include "generation.h"


class yaml_room
{
    public:
        yaml_room() { constructed = false; }
        ~yaml_room() {}

    public:
        std::string name;

        bool walled;
        int wall_strength;
        bool dark;
        coordinate size;
        std::vector<base_item*> items;
        std::string str;

        bool constructed;
};


class yaml_corridor : public yaml_room
{
    public:
        yaml_corridor() { constructed = false; }
        ~yaml_corridor() {}

    public:
        int length;
        std::string start_room,
                    end_room;
        direction dir;
};


class yaml_parse
{
    public:
        yaml_parse(std::string filename) : _filename(filename) {}
        yaml_parse() : _filename("story.yml") {}
        ~yaml_parse() {}
        
        int parse(space_vect& smap);
    private:
        std::string _filename;
        std::vector<yaml_room *> rooms;
        std::vector<yaml_corridor *> corridors;

        int generate(space_vect& smap);
        int construct_recursive(space_vect& smap, yaml_room *room, bool is_corridor);
};


#endif
