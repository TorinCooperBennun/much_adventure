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


#include "generation.h"


int create_walled_room(
        space_vect &            smap,
        coordinate              bl,
        coordinate              tr,
        bool                    walled,
        int                     wall_strength,
        std::vector<base_item> *items)
{
    int size_y, size_x;

    size_y = smap.size();
    if (!size_y) {
        std::cerr << "Space map has no height.\r\n";
        return -1;
    }

    size_x = smap[0].size();
    if (!size_x) {
        std::cerr << "Space map has no width.\r\n";
        return -1;
    }

    int min = 0;
    if (walled) {
        min = 1;
    }

    if (bl.get_x() < min or bl.get_y() < min or tr.get_x() < min or tr.get_y() < min) {
        std::cerr << "Negative value on coordinate.";
        return -1;
    }

    int xmax = smap[0].size() - 1,
        ymax = smap.size() - 1;
    if (walled) {
        xmax -= 1;
        ymax -= 1;
    }

    if (bl.get_x() > xmax or bl.get_y() > ymax or tr.get_x() > xmax or tr.get_y() > ymax) {
        std::cerr << "Coordinate too large.";
        return -1;
    }

    if (bl.get_x() > tr.get_x() or bl.get_y() > tr.get_y()) {
        std::cerr << "Top-left and bottom-right coordinates mix badly.";
        return -1;
    }

    int min_x, max_x, min_y, max_y;

    min_x = bl.get_x();
    if (walled) {
        min_x -= 1;
    }

    min_y = bl.get_y();
    if (walled) {
        min_y -= 1;
    }

    max_x = tr.get_x();
    if (walled) {
        max_x += 1;
    }

    max_y = tr.get_y();
    if (walled) {
        max_y += 1;
    }

    for (int y = bl.get_y(); y <= tr.get_y(); y++) {
        for (int x = bl.get_x(); x <= tr.get_x(); x++) {
            if (smap[y][x] != NULL) {
                delete smap[y][x];
            }
            smap[y][x] = new space_obj();
        }
    }

    if (walled) {
        wall_obj *wall = NULL;
        for (int y = min_y; y <= max_y; y++) {
            if (smap[y][min_x] != NULL) {
                delete smap[y][min_x];
            }
            wall = new wall_obj();
            wall->set_strength(wall_strength);
            smap[y][min_x] = wall;

            if (smap[y][max_x] != NULL) {
                delete smap[y][max_x];
            }
            wall = new wall_obj();
            wall->set_strength(wall_strength);
            smap[y][max_x] = wall;
        }
        for (int x = min_x; x <= max_x; x++) {
            if (smap[min_y][x] != NULL) {
                delete smap[min_y][x];
            }
            wall = new wall_obj();
            wall->set_strength(wall_strength);
            smap[min_y][x] = wall;

            if (smap[max_y][x] != NULL) {
                delete smap[max_y][x];
            }
            wall = new wall_obj();
            wall->set_strength(wall_strength);
            smap[max_y][x] = wall;
        }
    }

    return 0;
}


int fill_map(
        space_vect & smap,
        coordinate   size,
        space_type   type)
{
    smap.clear();

    for (int i = 0; i < size.get_y(); i++) {
        smap.push_back(std::vector<space_obj*>());
        for (int j = 0; j < size.get_x(); j++) {
            space_obj *sp = NULL;
            switch (type) {
                case SPACE_EMPTY:
                    sp = new space_obj(true);
                    break;
                case SPACE_ROOM:
                    sp = new space_obj();
                    break;
                case SPACE_WALL:
                    sp = new wall_obj();
                    break;
                default:
                    std::cerr << "Unimplemented space type!\r\n";
                    return -1;
            }
            smap[i].push_back(sp);
        }
    }

    return 0;
}
