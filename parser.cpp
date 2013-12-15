#include "parser.h"


int yaml_parse::parse(space_vect smap)
{
    /* load file */
    YAML::Node storyfile = YAML::LoadFile(_filename);
    if (!storyfile) {
        std::cerr << "Could not load " << _filename << " as YAML.\r\n";
        return -1;
    }

    /* load rooms node */
    YAML::Node rooms = storyfile["rooms"];
    if (!rooms) {
        std::cerr << _filename << " is missing 'rooms' node.\r\n";
        return -1;
    }

    /* load player node */
    YAML::Node playeroptions = storyfile["player"];
    if (!player) {
        std::cerr << _filename << " is missing 'player' node.\r\n";
    }

    /* get all the rooms */
    for (YAML::const_iterator i = rooms.begin(); i != rooms.end(); ++i)
    {
        std::string name = i->first.as<std::string>();
        YAML::Node node = i->second;
        if (!node) {
            std::cerr << "idk! " << name << " node is fucked up.\r\n";
        }

        /* we have two pointers, just in case we're dealing with a corridor.
         * (yaml_corridor is a child class of yaml_room)
         */
        yaml_room *p_room = NULL;
        yaml_corridor *p_corridor = NULL;

        /* if we're dealing with a corridor, we'll know later because
         * p_corridor will not be NULL
         */
        YAML::Node type = node["type"];
        if (!type or type.as<std::string>() == "room") {
            p_room = new yaml_room;
        }
        else if (type.as<std::string>() == "corridor") {
            p_corridor = new yaml_corridor;
            p_room = p_corridor;
        }

        /* deal with attributes common to rooms and corridors now */
        YAML::Node walled = node["walled"],
                   wall_strength = node["wall_strength"]
                   dark = node["dark"],
                   size = node["size"],
                   items = node["items"],
                   str = node["string"];

        if (!walled) {
            p_room->walled = true;
        } else {
            p_room->walled = walled.as<bool>();
        }

        if (!wall_strength) {
            p_room->wall_strength = 50;
        } else {
            p_room->wall_strength = wall_strength.as<int>();
        }

        if (!dark) {
            p_room->dark = true;
        } else {
            p_room->dark = dark.as<bool>();
        }

        if (!size) {
            p_room->size = coordinate(1,1);
        } else {
            int p_size[2] = {0,0};
            p_size = size.as<int[2]>();
            p_room->size = coordinate(p_size[0], p_size[1]);

        }

        if (
    return 0;
}


bool yaml_node_exists(YAML::Node parent, std::string child_name)
{
    return false;
}
