/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Reception command parser
 *
 * File creation = 03.05.20
 * Last modification = 03.05.20
 */

#ifndef __RECEPTION_COMMAND_PARSER__
#define __RECEPTION_COMMAND_PARSER__

#include <iostream>
#include <map>
#include "Reception/Reception.hpp"

using receptFunc = void(plazza::Reception::*)(void);

std::map<std::string, receptFunc> CommandParser = {
    {"exit", &plazza::Reception::exit},
    {"status", &plazza::Reception::status},
};

#endif //____RECEPTION_COMMAND_PARSER__