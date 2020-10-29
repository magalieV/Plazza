/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Orders class
 *
 * File creation = 02.05.20
 * Last modification = 02.05.20
 */

#include "Reception/Orders.hpp"
#include "Tools/Tools.hpp"
#include <vector>

plazza::Orders::Orders()
{
    _amount = 0;
}

void plazza::Orders::clear()
{
    _amount = 0;
    _allOrders.clear();
}

void plazza::Orders::addOrders(const std::string &order)
{
    std::vector<std::string> orders = Tools::split(order, ";\n");

    for (const auto &ord : orders) {
        _allOrders.emplace_back(ord);
        _amount++;
    }
}

bool plazza::Orders::haveNextOrder() const
{
    return !_allOrders.empty();
}

plazza::Order plazza::Orders::getNextOrder()
{
    Order tmp;

    if (_allOrders.empty()) {
        return (Order());
    }
    tmp = _allOrders.front();
    _allOrders.pop_front();
    return (tmp);
}