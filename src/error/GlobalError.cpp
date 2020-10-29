/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Global error of plazza
 *
 * File creation = 01.05.20
 * Last modification = 02.05.20
 */

#include "error/GlobalError.hpp"

plazza::GlobalError::GlobalError(const std::string &message, const std::string &component)
{
    _message = message;
    _componement = component;
}

const std::string & plazza::GlobalError::getComponent() const
{
    return _componement;
}

const char * plazza::GlobalError::what() const noexcept
{
    return _message.c_str();
}