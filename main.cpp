#include "main.h"


int main()
{
    wagn *wogn = new wagn();
    wogn->generate_spaces();
    while (!wogn->is_closed()) {
        wogn->print_info();
        command_obj cmd = wogn->get_input();
        std::string response = cmd.execute();
        wogn->print(response);
    }
}
