/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Pizza class file
 *
 * File creation = 01.05.20
 * Last modification = 05.05.20
 */

#include "Pizza/Pizza.hpp"
#include "Pizza/PizzaMap.hpp"
#include <algorithm>

plazza::Pizza::Pizza(const std::string &size, const std::string &type)
{
    std::string tmp = size;

    _valid = true;
    if (PizzaMapSize.find(tmp) == PizzaMapSize.end()) {
        _valid = false;
    } else
        _size = PizzaMapSize.at(tmp);
    _sizeString = tmp;
    tmp = type;
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    if (PizzaMapType.find(tmp) == PizzaMapType.end()) {
        _valid = false;
    } else
        _type = PizzaMapType.at(tmp);
    _typeString = tmp;
    _state = PizzaState::Waiting;
}

plazza::Pizza::Pizza()
{
    _valid = false;
    _size = plazza::PizzaSize::S;
    _type = plazza::PizzaType::Margarita;
    _state = plazza::PizzaState::Waiting;
}

plazza::PizzaSize plazza::Pizza::getPizzaSize() const
{
    return _size;
}

plazza::PizzaType plazza::Pizza::getPizzaType() const
{
    return _type;
}

plazza::PizzaState plazza::Pizza::getPizzaState() const
{
    return _state;
}

void plazza::Pizza::setPizzaState(const plazza::PizzaState &state)
{
    _state = state;
}

bool plazza::Pizza::isValid() const
{
    return _valid;
}

std::string plazza::Pizza::getType() const
{
    return _typeString;
}

std::string plazza::Pizza::getSize() const
{
    return _sizeString;
}

std::string plazza::Pizza::getState() const
{
    std::string state;

    switch (_state) {
        case Waiting:
            state = "Waiting";
            break;
        case InProgress:
            state  = "Being prepared";
            break;
        default:
            state = "Finished";
            break;
    }
    return state;
}

int plazza::Pizza::pack()
{
    int mask = 0;

    mask |= (int) this->_type << 5;
    mask |= (int) this->_size;
    return mask;
}

plazza::Pizza plazza::Pizza::unpack(int mask)
{
    this->_type = static_cast<PizzaType>(mask >> 5);
    switch (this->_type) {
        case PizzaType::Regina:
            this->_typeString = "Regina";
            break;
        case PizzaType::Margarita:
            this->_typeString = "Margarita";
            break;
        case PizzaType ::Fantasia:
            this->_typeString = "Fantasia";
            break;
        default:
            this->_typeString = "Americana";
            break;
    }
    this->_size = static_cast<PizzaSize>(mask - (32 * this->_type));
    switch (this->_size) {
        case PizzaSize::S:
            this->_sizeString = "S";
            break;
        case PizzaSize::L:
            this->_sizeString = "L";
            break;
        case PizzaSize::M:
            this->_sizeString = "M";
            break;
        case PizzaSize::XL:
            this->_sizeString = "XL";
            break;
        default:
            this->_sizeString = "XXL";
            break;
    }
    return *this;
}