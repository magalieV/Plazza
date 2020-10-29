/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Encapsulation for mutex
 *
 * File creation = 07.05.20
 * Last modification = 07.05.20
 */

#ifndef __PIZZA_COOKING__
#define __PIZZA_COOKING__

#include "Kitchen/Stock.hpp"
#include "Pizza/Pizza.hpp"
#include <list>

const std::map<plazza::PizzaType, unsigned int> PizzaTime = {
    {plazza::PizzaType::Margarita, 1000},
    {plazza::PizzaType::Regina, 2000},
    {plazza::PizzaType::Americana, 2000},
    {plazza::PizzaType::Fantasia, 4000}
};

#endif //__PIZZA_COOKING__