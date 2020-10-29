/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Reception class header
 *
 * File creation = 02.05.20
 * Last modification = 03.05.20
 */

#ifndef __RECEPTION__
#define __RECEPTION__

#include <iostream>
#include <functional>
#include "plazza_header.hpp"
#include "Kitchen/PlazzaKitchens.hpp"
#include "Arguments/Arguments.hpp"

#define RECEPTION(message, state) \
    [&](const std::string &message_, bool state_) {    \
        if (state)  \
            std::cout << C_GREEN << "[RECEPTION]" << C_RESET << ": ";    \
        else \
            std::cout << C_RED << "[RECEPTION]" << C_RESET << ": ";    \
        std::cout << message << std::endl;    \
    } (message, state)

namespace plazza
{
    class Reception
    {
        public:
            Reception(Arguments<ArgsEnum> &args);
            ~Reception() = default;
            void run();
            void exit() noexcept;
            void status();
            void useOrder(const std::string &order);

        private:
            bool _isOpen;
            PlazzaKitchens _kitchens;
            Arguments<ArgsEnum> _args;

    };
}

#endif //__RECEPTION__