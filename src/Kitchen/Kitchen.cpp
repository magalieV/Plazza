/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Kitchens class
 *
 * File creation = 06.05.20
 * Last modification = 06.05.20
 */

#include "Kitchen/Kitchen.hpp"
#include <csignal>

plazza::Kitchen::Kitchen(unsigned int cooksNumber, unsigned int id, float cooksTimer, int stockTimer) :
    _cooks(stockTimer, cooksNumber, cooksTimer, id),
    _message(".", ((int)id * 2) - 1)
{
    _cooksNumber = cooksNumber;
    _id = id;
    _channelRead = 0;
    _channelWrite = 0;
}

plazza::Kitchen::~Kitchen()
{
}

unsigned int plazza::Kitchen::getPlaces(const plazza::Pizza &pizza)
{
    unsigned int tmp = _cooks.getPlace();

    if (_cooks.canConsumeThat(pizza)) {
        return tmp;
    }
    return 0;
}

int plazza::Kitchen::run()
{
    plazza::Shared data;
    bool state = false;

    _channelWrite = (_id * 2) - 1;
    _channelRead = _id * 2;
    _cooks.run();
    _run = true;
    while (_run) {
        data = _message.getInfo(state, ".", (int)_id * 2);
        if (state) {
            executeAction(data);
        }
    }
    _cooks.deleteThreadPool();
    plazza::Shared shared;
    shared.setData(-3);
    _message<<shared;
    _message.deleteQueue();
    return 0;
}

void plazza::Kitchen::status()
{
    plazza::Shared shared;
    std::vector<std::string> listPizza = _cooks.getStatus();
    for (const auto &element : listPizza) {
        shared.setMessage(element);
        _message<<shared;
    }
    std::list<std::string> listStock = _cooks.getStockStatus();
    for (const auto &ingredient : listStock) {
        shared.setMessage(ingredient);
        _message<<shared;
    }
    shared.setMessage("END");
    _message<<shared;
}

void plazza::Kitchen::executeAction(const plazza::Shared &data)
{
    Pizza pizza;
    plazza::Shared shared;

    if (!data.getMessage().empty() and data.getMessage() == "PLACES") {
        pizza = pizza.unpack(data.getData());
        shared.setData((int)this->getPlaces(pizza));
        _message<<shared;
        return;
    }
    switch (data.getData()) {
        case -1:
            _run = false;
            break;
        case -3:
            this->status();
            break;
        default:
            pizza = pizza.unpack(data.getData());
            _cooks.addOrder(pizza);
        break;
    }
}
