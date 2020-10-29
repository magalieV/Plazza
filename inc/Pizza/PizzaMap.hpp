/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Pizza class file
 *
 * File creation = 01.05.20
 * Last modification = 02.05.20
 */

#ifndef __PIZZA_MAP__
#define __PIZZA_MAP__

#include <functional>
#include "Pizza/Pizza.hpp"

const std::map<std::string, plazza::PizzaSize> PizzaMapSize = {
    {"S", plazza::PizzaSize::S},
    {"M", plazza::PizzaSize::M},
    {"L", plazza::PizzaSize::L},
    {"XL", plazza::PizzaSize::XL},
    {"XXL", plazza::PizzaSize::XXL}
};

const std::map<std::string, plazza::PizzaType> PizzaMapType = {
    {"regina", plazza::PizzaType::Regina},
    {"margarita", plazza::PizzaType::Margarita},
    {"americana", plazza::PizzaType::Americana},
    {"fantasia", plazza::PizzaType::Fantasia},
};


#endif //__PIZZA_MAP__