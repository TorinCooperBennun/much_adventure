#ifndef PARSER_H
#define PARSER_H


#include <vector>
#include <string>

#include "space.h"
#include "item_base.h"
#include "generation.h"


//class yaml_room
//{
//    public:
//        yaml_room(coordinate bl, coordinate tr);
//        yaml_room();
//        
//        coordinate get_bl();
//        coordinate get_tr();
//        std::string get_str();
//        std::vector<base_item*> & get_items();
//        bool is_walled();
//
//        void set_bl(coordinate bl);
//        void set_tr(coordinate tr);
//        void set_str(std::string st);
//        void add_item(base_item item);
//        void set_walled(bool w);
//
//    private:
//        coordinate _bl,
//                   _tr;
//
//        bool walled;
//
//        std::vector<base_item*> items;
//        std::string str;
//}


class yaml_parse
{
    public:
        yaml_parse(std::string filename) : _filename(filename) {}
        yaml_parse() : _filename("story.yml") {}
        ~yaml_parse() {}
        
        int parse(space_vect smap);
    private:
        std::string _filename;
};


#endif
