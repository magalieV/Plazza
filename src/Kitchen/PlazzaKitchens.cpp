/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = PlazzaKitchens class
 *
 * File creation = 03.05.20
 * Last modification = 03.05.20
 */

#include "Kitchen/PlazzaKitchens.hpp"

plazza::PlazzaKitchens::PlazzaKitchens(unsigned int cooksNumber, float cooksTimer, unsigned int stockTimer)
{
    _cooksNumber = cooksNumber;
    _cooksTimer = cooksTimer;
    _stockTimer = stockTimer;
}

void plazza::PlazzaKitchens::removeUselessKitchen()
{
    std::map<std::shared_ptr<Process>, std::shared_ptr<plazza::KitchenManager>> useKitchen;
    std::map<std::shared_ptr<Process>, std::shared_ptr<plazza::KitchenManager>> unusedKitchen;

    if (_useKitchen.empty() and _unusedKitchen.empty())
        return;
    for (auto &kitchen : _unusedKitchen) {
        if (!kitchen.first->isRunning()) {
            KITCHENS("Unused kitchen removed.", true);
        } else {
            unusedKitchen[kitchen.first] = kitchen.second;
        }
    }
    for (auto &kitchen : _useKitchen) {
        if (!kitchen.first->isRunning()) {
            KITCHENS("Unused kitchen removed.", true);
        } else {
            useKitchen[kitchen.first] = kitchen.second;
        }
    }
    _useKitchen = useKitchen;
    _unusedKitchen = unusedKitchen;
}

std::shared_ptr<plazza::KitchenManager> plazza::PlazzaKitchens::getKitchen(const Pizza &pizza)
{
    removeUselessKitchen();
    if (haveAvailable(pizza)) {
        return getAvailable(pizza);
    }
    std::shared_ptr<plazza::KitchenManager> tmp = std::shared_ptr<plazza::KitchenManager>(
        new plazza::KitchenManager(_cooksNumber, _useKitchen.size() + 1, _cooksTimer, (int)_stockTimer));
    _useKitchen[std::shared_ptr<Process>(new Process())] = tmp;
    for (auto &t : _useKitchen) {
        if (t.second == tmp) {
            t.first->run(tmp->getKitchen().get());
        }
    }
    return tmp;
}

/* Private members */

bool plazza::PlazzaKitchens::haveAvailable(const Pizza &pizza) noexcept
{
    return useKitchenHavePlace(pizza) or !_unusedKitchen.empty();
}

bool plazza::PlazzaKitchens::useKitchenHavePlace(const Pizza &pizza) noexcept
{
    if (_useKitchen.empty())
        return false;
    for (const auto &kitchen : _useKitchen) {
        if (kitchen.first->isRunning() and kitchen.second->havePlace(pizza))
            return true;
    }
    removeUselessKitchen();
    return false;
}

std::shared_ptr<plazza::KitchenManager> plazza::PlazzaKitchens::getAvailable(const Pizza &pizza)
{
    if (useKitchenHavePlace(pizza))
        return foundLessUse(pizza);
    _useKitchen[_unusedKitchen.begin()->first] = _unusedKitchen.begin()->second;
    _unusedKitchen.erase(_unusedKitchen.begin());
    return _useKitchen.rbegin()->second;
}

std::shared_ptr<plazza::KitchenManager> plazza::PlazzaKitchens::foundLessUse(const Pizza &pizza)
{
    std::shared_ptr<plazza::KitchenManager> lessUse = _useKitchen.begin()->second;
    unsigned int places = _useKitchen.begin()->second->getPlaces(pizza);
    unsigned int placesKitchen = 0;

    removeUselessKitchen();
    for (auto &kitchen : _useKitchen) {
        placesKitchen = kitchen.second->getPlaces(pizza);
        if ((placesKitchen > places and placesKitchen > 0) or places == 0) {
            places = placesKitchen;
            lessUse = kitchen.second;
        }
    }
    removeUselessKitchen();
    return lessUse;
}

void plazza::PlazzaKitchens::status()
{
    KITCHENS("Status of all kitchen :", true);
    removeUselessKitchen();
    for (const auto &kitchen : _useKitchen) {
        if (kitchen.first->isRunning())
            kitchen.second->status();
    }
    for (const auto &kitchen : _unusedKitchen) {
        if (kitchen.first->isRunning())
            kitchen.second->status();
    }
    removeUselessKitchen();
}

void plazza::PlazzaKitchens::closeKitchens()
{
    bool tmp = false;

    for (auto &kitchen : _unusedKitchen) {
        kitchen.second->stop();
    }
    for (auto &kitchen : _useKitchen) {
        kitchen.second->stop();
    }
}