/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Pizza error of plazza
 *
 * File creation = 01.05.20
 * Last modification = 02.05.20
 */

#ifndef __PIZZA_ERROR__
#define __PIZZA_ERROR__

#include "error/GlobalError.hpp"

#define NOT_EXIST std::string("The pizza doesn't exist")

namespace plazza {
    class PizzaError : public GlobalError {
        public:
            PizzaError(const std::string &message,
                       const std::string &component = "Pizza");
            virtual ~PizzaError() noexcept {};
    };
}

#endif //__PIZZA_ERROR