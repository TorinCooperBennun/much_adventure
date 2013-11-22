#include "wagn.h"


wagn::wagn()
{
    map_width = 100;
    map_height = 100;

    /* this is the biggest hack known to man.
     * I honestly don't know any more. */
    space_map = std::vector<std::vector<space_obj>> (
        max_width, std::vector<space_obj> (
            max_height, space_obj(SPACE_EMPTY)
        )
    );

    std::cout << space_map.size() << std::endl;
}


wagn::~wagn()
{
}
