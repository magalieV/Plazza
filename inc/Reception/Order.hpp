/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Order class
 *
 * File creation = 02.05.20
 * Last modification = 03.05.20
 */

#ifndef __ORDER__
#define __ORDER__

#include <iostream>
#include <list>

namespace plazza
{
    class Order
    {
        public:
            Order(const std::string &order);
            Order() = default;
            ~Order() = default;
            [[nodiscard]] bool isValidOrder() const;
            [[nodiscard]] std::string getSize() const;
            [[nodiscard]] std::string getType() const;
            [[nodiscard]] unsigned int getAmount() const;
            [[nodiscard]] std::string getOrder() const;

        private:
            std::string _size;
            std::string _type;
            std::string _order;
            unsigned int _amount;
    };
}

#endif //__ORDER