/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Kitchens class
 *
 * File creation = 06.05.20
 * Last modification = 06.05.20
 */

#ifndef __KITCHEN__
#define __KITCHEN__

#include <iostream>
#include <list>
#include "Pizza/Pizza.hpp"
#include "Encapsulation/MessageQueue.hpp"
#include "Encapsulation/Procedure.hpp"
#include "Kitchen/Stock.hpp"
#include "Kitchen/ThreadPool.hpp"

#define KITCHEN(message, id, state) \
    [&](const std::string &message_, unsigned int id_, bool state_) {    \
        if (state)  \
            std::cout << C_BLUE << "[KITCHEN {" << id_ << "}]" << C_RESET << ": ";    \
        else \
            std::cout << C_RED << "[KITCHEN {" << id_ << "}]" << C_RESET << ": ";    \
        std::cout << message << std::endl;    \
    } (message, id, state)

namespace plazza
{
    class Kitchen : public Procedure
    {
        public:
            Kitchen(unsigned int cooksNumber, unsigned int id, float cooksTimer, int stockTimer);
            virtual ~Kitchen();
            unsigned int getPlaces(const plazza::Pizza &pizza);
            int run() final;
            void status();

        private:
            void executeAction(const plazza::Shared &data);

        private:
            unsigned int _channelRead;
            unsigned int _channelWrite;
            unsigned int _cooksNumber;
            plazza::ThreadPool _cooks;
            MessageQueue _message;
    };
}

#endif //__KITCHEN__