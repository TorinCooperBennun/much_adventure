#include "generation.h"


int create_walled_room(
        space_vect &           smap,
        coordinate             bl,
        coordinate             tr,
        bool                   walled,
        int                    wall_strength,
        bool                   overwrite,
        std::vector<base_item> items)
{
    int size_y, size_x;

    size_y = space_vect.size();
    if (!size_y) {
        std::cerr << "Space map has no height.\r\n";
        return -1;
    }

    size_x = space_vect[0].size();
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

    int xmax = space_vect[0].size() - 1,
        ymax = space_vect.size() - 1;
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


    
