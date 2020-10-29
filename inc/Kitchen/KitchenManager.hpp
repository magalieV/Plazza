/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Kitchens class
 *
 * File creation = 03.05.20
 * Last modification = 03.05.20
 */

#ifndef __KITCHEN_MANAGER__
#define __KITCHEN_MANAGER__

#include "Pizza/Pizza.hpp"
#include "plazza_header.hpp"
#include "Encapsulation/MessageQueue.hpp"
#include <list>
#include "Encapsulation/Process.hpp"
#include "Kitchen/Kitchen.hpp"

#define KITCHEN_MANAGER(message, id, state) \
    [&](const std::string &message_, unsigned int id_, bool state_) {    \
        if (state)  \
            std::cout << C_YELLOW << "[KITCHEN {" << id_ << "}]" << C_RESET << ": ";    \
        else \
            std::cout << C_RED << "[KITCHEN {" << id_ << "}]" << C_RESET << ": ";    \
        std::cout << message << std::endl;    \
    } (message, id, state)

namespace plazza
{

    class KitchenManager
    {
        public:
            KitchenManager(unsigned int cooksNumber, unsigned int id, float cooksTimer, int stockTimer);
            ~KitchenManager();
            KitchenManager();
            void status();
            [[nodiscard]] unsigned int getPlaces(Pizza pizza);
            [[nodiscard]] bool havePlace(Pizza pizza);
            void addPizzaOrder(Pizza pizza);
            void stop();
            [[nodiscard]] std::shared_ptr<Kitchen> getKitchen() const;

        private:
            unsigned int _maxPlaces;
            std::list<plazza::Pizza> _listPizza;
            unsigned int _id;
            MessageQueue _messageQueue;
            std::shared_ptr<Kitchen> _kitchen;
    };
}

#endif //__KITCHEN_MANAGER__