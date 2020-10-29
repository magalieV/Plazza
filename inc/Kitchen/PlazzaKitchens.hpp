/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = PlazzaKitchens class
 *
 * File creation = 03.05.20
 * Last modification = 06.05.20
 */

#ifndef __PLAZZA_KITCHENS__
#define __PLAZZA_KITCHENS__

#include "Pizza/Pizza.hpp"
#include "Kitchen/KitchenManager.hpp"
#include "plazza_header.hpp"
#include "Encapsulation/Process.hpp"
#include <map>
#include <memory>

#define KITCHENS(message, state) \
    [&](const std::string &message_, bool state_) {    \
        if (state)  \
            std::cout << C_CYAN << "[KITCHENS]" << C_RESET << ": ";    \
        else \
            std::cout << C_RED << "[KITCHENS]" << C_RESET << ": ";    \
        std::cout << message << std::endl;    \
    } (message, state)

namespace plazza
{
    class PlazzaKitchens
    {
        public:
            explicit PlazzaKitchens(unsigned int cooksNumber, float cooksTimers, unsigned int stockTimer);
            ~PlazzaKitchens() = default;
            void removeUselessKitchen();
            void status();
            void closeKitchens();
            [[nodiscard]] std::shared_ptr<plazza::KitchenManager> getKitchen(const Pizza &pizza);

        private:
            std::map<std::shared_ptr<Process>, std::shared_ptr<plazza::KitchenManager>> _useKitchen;
            std::map<std::shared_ptr<Process>, std::shared_ptr<plazza::KitchenManager>> _unusedKitchen;
            unsigned int _cooksNumber;
            float _cooksTimer;
            unsigned int _stockTimer;

        private:
            [[nodiscard]] bool haveAvailable(const Pizza &pizza) noexcept;
            [[nodiscard]] bool useKitchenHavePlace(const Pizza &pizza) noexcept;
            [[nodiscard]] std::shared_ptr<plazza::KitchenManager> getAvailable(const Pizza &pizza);
            [[nodiscard]] std::shared_ptr<plazza::KitchenManager> foundLessUse(const Pizza &pizza);
    };
}

#endif //__PLAZZA_KITCHENS__