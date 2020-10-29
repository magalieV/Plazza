/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Order class
 *
 * File creation = 02.05.20
 * Last modification = 03.05.20
 */

#include "Reception/Order.hpp"
#include "Tools/Tools.hpp"
#include <regex>
#include <vector>

plazza::Order::Order(const std::string &order)
{
    std::vector<std::string> tmp;
    std::string amount;
    bool spaces = false;

    _order = order;
    while (!_order.empty() and _order.at(0) == ' ') {
        _order.erase(0, 1);
    }
    while (!_order.empty() and _order.at(_order.size() - 1) == ' ') {
        _order.erase(_order.size() - 1, 1);
    }
    if (isValidOrder()) {
        tmp = Tools::split(order, " ");
        _type = tmp[0];
        _size = tmp[1];
        amount = tmp[2].erase(0, 1);
        _amount = stoi(amount);
    } else {
        _amount = 0;
    }
}

bool plazza::Order::isValidOrder() const
{
    return std::regex_match(_order,
        std::regex("([a-z|A-Z]+) (S|M|L|XL|XXL) x([1-9][0-9]*)"));
}

std::string plazza::Order::getSize() const
{
    return _size;
}

std::string plazza::Order::getType() const
{
    return _type;
}

unsigned int plazza::Order::getAmount() const
{
    return _amount;
}

std::string plazza::Order::getOrder() const
{
    return _order;
}