#ifndef WAGN_H
#define WAGN_H


#include "item_base.h"
#include "command.h"
#include "space.h"

#include <iostream>
#include <vector>
#include <string>


class wagn
{
	public:
		wagn();
		~wagn();

	private:
		std::vector<item_obj> inventory;
		std::vector<command_obj> history;
		std::vector<std::vector<space_obj>> space_map;
		int map_width, map_height;
};


#endif
