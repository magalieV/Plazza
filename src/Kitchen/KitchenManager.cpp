/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Kitchens class
 *
 * File creation = 03.05.20
 * Last modification = 03.05.20
 */

#include "Kitchen/KitchenManager.hpp"
#include <fstream>

plazza::KitchenManager::KitchenManager(unsigned int cooksNumber, unsigned int id,
    float cooksTimer, int stockTimer)
    : _messageQueue(".", (int)id * 2)
{
    KITCHEN_MANAGER("Open kitchen.", id, true);
    _maxPlaces = cooksNumber * 2;
    _id = id;
    _kitchen = std::shared_ptr<Kitchen>(new Kitchen(cooksNumber, id, cooksTimer, stockTimer));
}

plazza::KitchenManager::~KitchenManager()
{
    KITCHEN_MANAGER("Close kitchen.", _id, true);
    _messageQueue.deleteQueue();
}

plazza::KitchenManager::KitchenManager()
: _messageQueue(".", 2)
{
    _maxPlaces = 0;
    _id = 0;
    _kitchen = std::shared_ptr<Kitchen>(new Kitchen(0, 0, 0.0, 0));
}

unsigned int plazza::KitchenManager::getPlaces(Pizza pizza)
{
    bool state = false;

    plazza::Shared tmp;
    tmp.setMessage("PLACES");
    tmp.setData(pizza.pack());
    _messageQueue<<tmp;
    plazza::Shared shared = _messageQueue.getInfo(state, ".", ((int)_id * 2) - 1);
    if (state and shared.getData() >= 0) {
        return shared.getData();
    } else
        return 0;
}

bool plazza::KitchenManager::havePlace(Pizza pizza)
{
    int place = getPlaces(pizza);
    return place > 0;
}

void plazza::KitchenManager::addPizzaOrder(Pizza pizza)
{
    std::ofstream flux;
    flux.open ("log.txt", std::ios::app);
    flux << "Order = Type(";
    flux << pizza.getType();
    flux << "), Size(";
    flux << pizza.getSize();
    flux << ").\n";
    flux.close();
    _listPizza.emplace_back(pizza);
    plazza::Shared value;
    int pizzaPack = pizza.pack();
    value.setData(pizzaPack);
    _messageQueue<<value;
    KITCHEN_MANAGER("Order arrived", _id, true);
}

void plazza::KitchenManager::stop()
{
    plazza::Shared value;
    value.setData(-1);
    _messageQueue<<value;
}

void plazza::KitchenManager::status()
{
    unsigned int count = 1;
    bool state = false;
    plazza::Shared shared;

    std::cout << std::endl << "\t";
    KITCHEN_MANAGER("state", _id, true);
    plazza::Shared value;
    value.setData(-3);
    _messageQueue<<value;
    do {
        shared = _messageQueue.getInfo(state, ".", ((int) _id * 2) - 1);
        if (shared.getData() == -3)
            break;
        if (state and !shared.getMessage().empty() and shared.getMessage() != "END") {
            std::cout << "\t\t" << shared.getMessage() << std::endl;
        }
    } while (!shared.getMessage().empty() and shared.getMessage() != "END" and state);
    std::cout << std::endl;
}

std::shared_ptr<plazza::Kitchen> plazza::KitchenManager::getKitchen() const
{
    return _kitchen;
}