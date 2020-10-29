/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Pizza error of plazza
 *
 * File creation = 01.05.20
 * Last modification = 02.05.20
 */

#include "error/PizzaError.hpp"

plazza::PizzaError::PizzaError(const std::string &message, const std::string &component) :
    GlobalError(message, component)
{
}