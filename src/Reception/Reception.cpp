/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Reception class
 *
 * File creation = 02.05.20
 * Last modification = 03.05.20
 */

#include "Reception/Reception.hpp"
#include "Reception/Orders.hpp"
#include "Reception/CommandParser.hpp"
#include <csignal>

bool use_keep_running(bool state, bool value)
{
    static bool keep_running = true;

    if (state == true) {
        keep_running = value;
    }
    return (keep_running);
}

void end_plazza(int sig)
{
    signal(sig, SIG_IGN);
    use_keep_running(true, false);
}

plazza::Reception::Reception(Arguments<ArgsEnum> &args)
: _kitchens(std::any_cast<int>(args<<ArgsEnum::COOKS_NUMBER), std::any_cast<float>(args<<ArgsEnum::COOKING_TIME),
            std::any_cast<int>(args<<ArgsEnum::INGREDIENTS_TIME))
{
    RECEPTION("The reception open.", true);
    _isOpen = true;
    _args = args;
}

void plazza::Reception::exit() noexcept
{
    _isOpen = false;
}

void plazza::Reception::status()
{
    RECEPTION("Status of the plazza.", true);
    _kitchens.status();
}

void plazza::Reception::useOrder(const std::string &order)
{
    plazza::Orders orders;
    plazza::Order clientOrder;
    std::shared_ptr<plazza::KitchenManager> kitchen;

    orders.clear();
    orders.addOrders(order);
    while (orders.haveNextOrder()) {
        clientOrder = orders.getNextOrder();
        if (!clientOrder.isValidOrder()) {
            RECEPTION("The order is invalid.", false);
        } else {
            for (unsigned int count = 0; count < clientOrder.getAmount(); count++) {
                plazza::Pizza pizza(clientOrder.getSize(), clientOrder.getType());
                if (!pizza.isValid())
                    RECEPTION("The pizza doesn't exist -> " + clientOrder.getOrder(), false);
                else {
                    RECEPTION("Order sent.", true);
                    kitchen = _kitchens.getKitchen(pizza);
                    kitchen->addPizzaOrder(Pizza(pizza));
                }
            }
        }
    }
}

void plazza::Reception::run()
{
    std::string order;
    receptFunc function;

    signal(SIGINT, end_plazza);
    std::cout << C_MAGENTA << "[CLIENT]" << C_RESET << ": ";
    while (_isOpen and use_keep_running(false, false)) {
        getline(std::cin, order);
        function = nullptr;
        if (CommandParser.find(order) != CommandParser.end()) {
            function = CommandParser.at(order);
            (this->*function)();
        } else
            plazza::Reception::useOrder(order);
        if (!order.empty() and _isOpen)
            std::cout << C_MAGENTA << "[CLIENT]" << C_RESET << ": ";
    }
    _kitchens.closeKitchens();
    RECEPTION("The reception close.", true);
}