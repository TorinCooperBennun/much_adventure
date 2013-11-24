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
};


#endif
