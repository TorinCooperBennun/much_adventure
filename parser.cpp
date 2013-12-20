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


int yaml_parse::parse(space_vect& smap)
{
    bool errord = false;

    /* load file */
    YAML::Node storyfile = YAML::LoadFile(_filename);
    if (!storyfile) {
        std::cerr << "## Error: Could not load file '" << _filename << "' as YAML.\r\n";
        return -1;
    }

    /* load rooms node */
    YAML::Node rooms = storyfile["rooms"];
    if (!rooms) {
        std::cerr << "## Error: File '" << _filename << "' is missing 'rooms' node.\r\n";
        return -1;
    }

    /* load player node */
    YAML::Node playeroptions = storyfile["player"];
    if (!playeroptions) {
        std::cerr << "## Error: File '" << _filename << "' is missing 'player' node.\r\n";
        return -1;
    }

    /* get all the rooms */
    for (YAML::const_iterator i = rooms.begin(); i != rooms.end(); ++i) {

        bool recent_errord = false;
        std::string name;

        /* get name */
        try {
            name = i->first.as<std::string>();
        } catch (YAML::Exception& e) {
            std::cerr << "## Error (WEIRD): A room's node has a nonexistent or invalid name.\r\n";
            return -1;
        }

        /* get node */
        std::cerr << "Processing room " << name << " ...\r\n";
        YAML::Node node = i->second;
        if (!node) {
            std::cerr << "## Error (WEIRD): '" << name << "' node is somehow invalid.\r\n";
            return -1;
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
            std::cerr << "## Error: Invalid type given for room '" << name << "'.\r\n";
            return -1;
        }

        /* deal with attributes common to rooms and corridors now */
        YAML::Node walled = node["walled"],
                   wall_strength = node["wall_strength"],
                   dark = node["dark"],
                   size = node["size"],
                   items = node["items"],
                   str = node["string"];

        /* name */
        p_room->name = name;

        /* walled */
        if (!walled) {
            p_room->walled = true;
        } else {
            try {
                p_room->walled = walled.as<bool>();
            } catch (YAML::Exception& e) {
                std::cerr << "## Error: Invalid value of 'walled' given for room '" << name << "'.\r\n";
                recent_errord = true;
            }
        }

        /* wall_strength */
        if (!wall_strength) {
            p_room->wall_strength = 50;
        } else {
            try {
                p_room->wall_strength = wall_strength.as<int>();
            } catch (YAML::Exception& e) {
                std::cerr << "## Error: Invalid value of 'wall_strength' given for room '" << name << "'.\r\n";
                recent_errord = true;
            }
        }

        /* dark */
        if (!dark) {
            p_room->dark = true;
        } else {
            try {
                p_room->dark = dark.as<bool>();
            } catch (YAML::Exception& e) {
                std::cerr << "## Error: Invalid value of 'dark' given for room '" << name << "'.\r\n";
                recent_errord = true;
            }
        }

        /* size */
        if (!size) {
            p_room->size = coordinate(1,1);
        } else {
            if (size.size() != 2) {
                std::cerr << "## Error: Invalid value of 'size' given for room '" << name << "'.\r\n";
                recent_errord = true;
            }
            try {
                p_room->size = coordinate(size[0].as<int>(), size[1].as<int>());
            } catch (YAML::Exception& e) {
                std::cerr << "## Error: Invalid value of 'size' given for room '" << name << "'.\r\n";
                recent_errord = true;
            }
        }

        /* items */
        if (!items) {
            p_room->items = std::vector<base_item*>();
        } else {
            std::cerr << "## Warning: Item handling not implemented yet.\r\n";
        }

        /* string */
        if (!str) {
            p_room->str = "";
        } else {
            try {
                p_room->str = str.as<std::string>();
            } catch (YAML::Exception& e) {
                std::cerr << "## Error: Invalid value of 'string' given for room '" << name << "'.\r\n";
                recent_errord = true;
            }
        }

        /* now corridor-only attributes (push back room if not corridor) */
        if (p_corridor != NULL) {
            YAML::Node length = node["length"],
                       start = node["start"],
                       end = node["end"],
                       dir = node["direction"];

            /* start (required) */
            if (!start) {
                std::cerr << "## Error: 'start' not given for corridor '" << name << "'.\r\n";
                recent_errord = true;
            } else {
                try {
                    p_corridor->start_room = start.as<std::string>();
                } catch (YAML::Exception& e) {
                    std::cerr << "## Error: Invalid value of 'start_room' given for corridor '" << name << "'.\r\n";
                    recent_errord = true;
                }
            }

            /* end (required) */
            if (!end) {
                std::cerr << "## Error: 'end' not given for corridor '" << name << "'.\r\n";
                recent_errord = true;
            } else {
                try {
                    p_corridor->end_room = end.as<std::string>();
                } catch (YAML::Exception& e) {
                    std::cerr << "## Error: Invalid value of 'end_room' given for corridor '" << name << "'.\r\n";
                    recent_errord = true;
                }
            }

            /* direction (required) */
            if (!dir) {
                std::cerr << "## Error: 'direction' not given for corridor '" << name << "'.\r\n";
                recent_errord = true;
            } else {
                std::string s_dir;
                bool s_dir_conv_success = false;
                try {
                    s_dir = dir.as<std::string>();
                    s_dir_conv_success = true;
                } catch (YAML::Exception& e) {
                    std::cerr << "## Error: Invalid value of 'direction' given for corridor '" << name << "'.\r\n";
                    recent_errord = true;
                }
                if (s_dir_conv_success) {
                    if (s_dir == "north") {
                        p_corridor->dir = DIR_NORTH;
                    } else if (s_dir == "east") {
                        p_corridor->dir = DIR_EAST;
                    } else if (s_dir == "south") {
                        p_corridor->dir = DIR_SOUTH;
                    } else if (s_dir == "west") {
                        p_corridor->dir = DIR_WEST;
                    } else {
                        std::cerr << "## Error: Invalid value of 'direction' given for corridor '" << name << "'.\r\n";
                        recent_errord = true;
                    }
                }
            }

            /* length */
            if (!length) {
                p_corridor->length = 1;
            } else {
                try {
                    p_corridor->length = length.as<int>();
                } catch (YAML::Exception& e) {
                    std::cerr << "## Error: Invalid value of 'length' given for corridor '" << name << "'.\r\n";
                    recent_errord = true;
                }
            }

            /* store corridor */
            if (!recent_errord and !errord) {
                this->corridors.push_back(p_corridor);
            }
        }
        /* store room */
        if (!recent_errord and !errord and p_corridor == NULL) {
            this->rooms.push_back(p_room);
        }

        /* set error flag */
        if (recent_errord) {
            errord = true;
        }
    }

    /* starting position of player */
    YAML::Node player_start = playeroptions["starting_pos"];
    if (!player_start) {
        std::cerr << "## Error: No 'starting_pos' given in player options.\r\n";
        errord = true;
    } else {
        std::string s_player_start;
        try {
            s_player_start = player_start.as<std::string>();
            bool found = false;
            for (auto it = this->rooms.begin(); it != this->rooms.end(); ++it) {
                yaml_room *r = *it;
                std::cerr << "Checking " << s_player_start << " against " << r->name << " ... ";
                if (r->name == s_player_start) {
                    found = true;
                    std::cerr << "match!\r\n";
                    break;
                }
                std::cerr << "no match.\r\n";
            }
            if (!found) {
                std::cerr << "## Error: Room '" << s_player_start << "' given in 'starting_pos' couldn't be found, or was defined incorrectly.\r\n";
                errord = true;
            }
        } catch (YAML::Exception& e) {
            std::cerr << "## Error: Invalid value of 'starting_pos' given in player options.\r\n";
            errord = true;
        }
    }

    /* start inventory of player */
    YAML::Node inventory = playeroptions["starting_inventory"];
    if (!inventory) {
        std::cerr << "## Error: No 'starting_inventory' given in player options.\r\n";
        errord = true;
    } else {
        std::cerr << "## Warning: Item handling not implemented yet.\r\n";
    }

    /* deal with actual map generation */
    if (this->generate(smap) != 0) {
        std::cerr << "## Error: Map generation failed!\r\n";
        errord = true;
    }

    if (!errord) {
        return 0;
    } else {
        return -1;
    }
}


int yaml_parse::generate(space_vect& smap)
{
    /* we use a recursive algorithm for this,
     * keeping track of the rooms we've already dealt with;
     * otherwise the whole corridor/room thing doesn't work
     */

    /* blank the map entirely (as in, the entire vector) */
    smap.clear();

    /* iterate through the rooms */
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
        yaml_room *room = *it;
        
        if (room->constructed) {
            continue;
        }
        if (construct_recursive(smap, room, false) != 0) {
            return -1;
        }
    }

    return 0;
}


int yaml_parse::construct_recursive(space_vect& smap, yaml_room *room, bool is_corridor)
{
    if (room->constructed) {
        return 0;
    }

    std::stringstream errstr;

    std::vector<yaml_corridor *> north_corridors,
                                 east_corridors,
                                 south_corridors,
                                 west_corridors;

    /* get corridors */
    for (auto it = corridors.begin(); it != corridors.end(); ++it) {
        yaml_corridor *corridor = *it;

        if (corridor->start_room == room->name) {
            switch (corridor->dir) {
                case DIR_NORTH:
                    north_corridors.push_back(corridor);
                    break;
                case DIR_EAST:
                    east_corridors.push_back(corridor);
                    break;
                case DIR_SOUTH:
                    south_corridors.push_back(corridor);
                    break;
                case DIR_WEST:
                    west_corridors.push_back(corridor);
                    break;
            }
        }
        if (corridor->end_room == room->name) {
            switch (corridor->dir) {
                case DIR_NORTH:
                    south_corridors.push_back(corridor);
                    break;
                case DIR_EAST:
                    west_corridors.push_back(corridor);
                    break;
                case DIR_SOUTH:
                    north_corridors.push_back(corridor);
                    break;
                case DIR_WEST:
                    east_corridors.push_back(corridor);
                    break;
            }
        }
    }

    /* very long error handling */
    bool corridor_error = false;
    if (north_corridors.size() > 1) {
        errstr << "## Error: corridors ";
        for (auto it = north_corridors.begin(); it != north_corridors.end(); ++it) {
            errstr << "'" << (*it)->name << "'";
            if (boost::next(it) != north_corridors.end()) {
                errstr << ",";
            }
            errstr << " ";
        }
        errstr << "conflict; they all go north from room '" << room->name << "'.\r\n";
        corridor_error = true;
    }
    if (east_corridors.size() > 1) {
        errstr << "## Error: corridors ";
        for (auto it = east_corridors.begin(); it != east_corridors.end(); ++it) {
            errstr << "'" << (*it)->name << "'";
            if (boost::next(it) != east_corridors.end()) {
                errstr << ",";
            }
            errstr << " ";
        }
        errstr << "conflict; they all go east from room '" << room->name << "'.\r\n";
        corridor_error = true;
    }
    if (south_corridors.size() > 1) {
        errstr << "## Error: corridors ";
        for (auto it = south_corridors.begin(); it != south_corridors.end(); ++it) {
            errstr << "'" << (*it)->name << "'";
            if (boost::next(it) != south_corridors.end()) {
                errstr << ",";
            }
            errstr << " ";
        }
        errstr << "conflict; they all go south from room '" << room->name << "'.\r\n";
        corridor_error = true;
    }
    if (west_corridors.size() > 1) {
        errstr << "## Error: corridors ";
        for (auto it = west_corridors.begin(); it != west_corridors.end(); ++it) {
            errstr << "'" << (*it)->name << "'";
            if (boost::next(it) != west_corridors.end()) {
                errstr << ",";
            }
            errstr << " ";
        }
        errstr << "conflict; they all go west from room '" << room->name << "'.\r\n";
        corridor_error = true;
    }
    if (corridor_error) {
        std::cerr << errstr.str();
        return -1;
    }

    if (north_corridors.size() == 0 and east_corridors.size() == 0 and south_corridors.size() == 0 and west_corridors.size() == 0) {
        std::cerr << "## Warning: room '" << room->name << "' does not connect to other rooms, and has been omitted from the map.\r\n";
        return 0;
    }

    return 0;
}
