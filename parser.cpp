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


#include "parser.h"


/* TODO
 * fix code-breaking gaps here
 * where I haven't finished the exception handling
 * (just copy-pasted tons instead)
 */


int yaml_parse::parse(space_vect smap)
{
    /* load file */
    YAML::Node storyfile = YAML::LoadFile(_filename);
    if (!storyfile) {
        std::cerr << "Error: Could not load file '" << _filename << "' as YAML.\r\n";
        return -1;
    }

    /* load rooms node */
    YAML::Node rooms = storyfile["rooms"];
    if (!rooms) {
        std::cerr << "Error: File '" << _filename << "' is missing 'rooms' node.\r\n";
        return -1;
    }

    /* load player node */
    YAML::Node playeroptions = storyfile["player"];
    if (!playeroptions) {
        std::cerr << "Error: File '" << _filename << "' is missing 'player' node.\r\n";
        return -1;
    }

    /* get all the rooms */
    for (YAML::const_iterator i = rooms.begin(); i != rooms.end(); ++i) {
        std::string name = i->first.as<std::string>();
        YAML::Node node = i->second;
        if (!node) {
            std::cerr << "Error: idk! '" << name << "' node is fucked up.\r\n";
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
        else {
            std::cerr << "Error: Invalid type given for room '" << name << "'.\r\n";
            return -1;
        }

        /* deal with attributes common to rooms and corridors now */
        YAML::Node walled = node["walled"],
                   wall_strength = node["wall_strength"],
                   dark = node["dark"],
                   size = node["size"],
                   items = node["items"],
                   str = node["string"];

        /* walled */
        if (!walled) {
            p_room->walled = true;
        } else {
            try {
                p_room->walled = walled.as<bool>();
            } catch (YAML::TypedBadConversion& e) {
                std::cerr << "Error: Invalid value of 'walled' given for room '" << name << "'.\r\n";
            }
        }

        /* wall_strength */
        if (!wall_strength) {
            p_room->wall_strength = 50;
        } else {
                p_room->wall_strength = wall_strength.as<int>();
            } catch (YAML::TypedBadConversion& e) {
                std::cerr << "Error: Invalid value of 'walled' given for room '" << name << "'.\r\n";
            }
        }

        /* dark */
        if (!dark) {
            p_room->dark = true;
        } else {
                p_room->dark = dark.as<bool>();
            } catch (YAML::TypedBadConversion& e) {
                std::cerr << "Error: Invalid value of 'walled' given for room '" << name << "'.\r\n";
            }
        }

        /* size */
        if (!size) {
            p_room->size = coordinate(1,1);
        } else {
            if (size.size() != 2) {
                std::cerr << "Error: Invalid size given for room '" << name << "'.\r\n";
                delete p_room;
                return -1;
            }
                p_room->size = coordinate(size[0].as<int>(), size[1].as<int>());
            } catch (YAML::TypedBadConversion& e) {
                std::cerr << "Error: Invalid value of 'walled' given for room '" << name << "'.\r\n";
            }
        }

        /* items */
        if (!items) {
            p_room->items = std::vector<base_item*>();
        } else {
            std::cerr << "Warning: Items not implemented yet.\r\n";
        }

        /* string */
        if (!str) {
            p_room->str = "";
        } else {
                p_room->str = str.as<std::string>();
            } catch (YAML::TypedBadConversion& e) {
                std::cerr << "Error: Invalid value of 'walled' given for room '" << name << "'.\r\n";
            }
        }

        /* now corridor-only attributes (push back room if not corridor) */
        if (p_corridor == NULL) {
            this->rooms.push_back(p_room);
        }
        else {
            YAML::Node length = node["length"],
                       start = node["start"],
                       end = node["end"],
                       dir = node["direction"];

            /* start (required) */
            if (!start) {
                std::cerr << "Error: 'start' not given for corridor '" << name << "'.\r\n";
                delete p_room;
                return -1;
            }
                p_corridor->start_room = start.as<std::string>();
            } catch (YAML::TypedBadConversion& e) {
                std::cerr << "Error: Invalid value of 'walled' given for room '" << name << "'.\r\n";
            }

            /* end (required) */
            if (!end) {
                std::cerr << "Error: 'end' not given for corridor '" << name << "'.\r\n";
                delete p_room;
                return -1;
            }
                p_corridor->end_room = end.as<std::string>();
            } catch (YAML::TypedBadConversion& e) {
                std::cerr << "Error: Invalid value of 'walled' given for room '" << name << "'.\r\n";
            }

            /* direction (required) */
            if (!dir) {
                std::cerr << "Error: 'direction' not given for corridor '" << name << "'.\r\n";
                delete p_room;
                return -1;
            }
                std::string s_dir = dir.as<std::string>();
            } catch (YAML::TypedBadConversion& e) {
                std::cerr << "Error: Invalid value of 'walled' given for room '" << name << "'.\r\n";
            }
            if (s_dir == "north") {
                p_corridor->dir = DIR_NORTH;
            } else if (s_dir == "east") {
                p_corridor->dir = DIR_EAST;
            } else if (s_dir == "south") {
                p_corridor->dir = DIR_SOUTH;
            } else if (s_dir == "west") {
                p_corridor->dir = DIR_WEST;
            } else {
                std::cerr << "Error: Invalid 'direction' given for corridor '" << name << "'.\r\n";
                delete p_room;
                return -1;
            }

            /* length */
            if (!length) {
                p_corridor->length = 1;
            } else {
                    p_corridor->length = length.as<int>();
            } catch (YAML::TypedBadConversion& e) {
                std::cerr << "Error: Invalid value of 'walled' given for room '" << name << "'.\r\n";
            }
            }

            this->corridors.push_back(p_corridor);
        }
    }

    std::cout << "Parse success.\r\n";

    return 0;
}


bool yaml_node_exists(YAML::Node parent, std::string child_name)
{
    return false;
}
