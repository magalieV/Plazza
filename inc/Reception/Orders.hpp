/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Orders class
 *
 * File creation = 02.05.20
 * Last modification = 02.05.20
 */

#ifndef __ORDERS__
#define __ORDERS__

#include <iostream>
#include <list>
#include "Reception/Order.hpp"

namespace plazza
{
    class Orders
    {
        public:
            Orders();
            ~Orders() = default;
            void clear();
            void addOrders(const std::string &order);
            [[nodiscard]] bool haveNextOrder() const;
            [[nodiscard]] plazza::Order getNextOrder();

        private:
            std::list<Order> _allOrders;
            unsigned int _amount;

    };
}

#endif //__ORDERS