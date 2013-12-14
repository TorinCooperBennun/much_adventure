#ifndef PARSER_H
#define PARSER_H


#include <vector>
#include <string>
#include <yaml-cpp/yaml.h>

#include "space.h"
#include "item_base.h"
#include "generation.h"


class yaml_room
{
    public:
        yaml_room() {}
        ~yaml_room() {}

    public:
        std::string name;

        bool walled;
        int wall_strength;
        bool dark;
        coordinate size;
        std::vector<base_item*> items;
        std::string str;
};


class yaml_corridor : public yaml_room
{
    public:
        yaml_corridor() {}
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
        
        int parse(space_vect smap);
    private:
        std::string _filename;
        std::vector<yaml_room *> rooms;
        std::vector<yaml_corridor *> corridors;
};


bool yaml_node_exists(YAML::Node parent, std::string child_name);


#endif
