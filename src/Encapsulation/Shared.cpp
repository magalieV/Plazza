/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Shared data
 *
 * File creation = 06.05.20
 * Last modification = 06.05.20
 */

#include "Encapsulation/Shared.hpp"

plazza::Shared::Shared()
{
    _data = 0;
}

int plazza::Shared::getData() const
{
    return _data;
}

void plazza::Shared::setData(int data)
{
    _data = data;
}

std::string plazza::Shared::getMessage() const
{
    return std::string(_message);
}

void plazza::Shared::setMessage(const std::string &message)
{
    _message = message;
}