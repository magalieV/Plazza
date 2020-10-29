/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Stock class
 *
 * File creation = 05.05.20
 * Last modification = 06.05.20
 */

#include "Kitchen/Stock.hpp"
#include <chrono>
#include <thread>
#include <pthread.h>
#include <iostream>
#include <string>

plazza::Stock::Stock(unsigned int timer)
    //: _refill([this]() {
   // while (_isRunning) {
   //     auto timer = std::chrono::steady_clock::now() + std::chrono::milliseconds(this->_timer);
   //     std::this_thread::sleep_until(timer);
   //     this->regenerate();
   // }
//})
{
   // _refill.detach();
    _stockList[Doe] = 5;
    _stockList[Tomato] = 5;
    _stockList[Gruyere] = 5;
    _stockList[Ham] = 5;
    _stockList[Mushrooms] = 5;
    _stockList[Steack] = 5;
    _stockList[EggPlant] = 5;
    _stockList[GoatChees] = 5;
    _stockList[ChiefLove] = 5;
    _timer = timer;
    _ingredientStr[Doe] = "Doe";
    _ingredientStr[Tomato] = "Tomato";
    _ingredientStr[Gruyere] = "Gruyere";
    _ingredientStr[Ham] = "Ham";
    _ingredientStr[Mushrooms] = "Mushrooms";
    _ingredientStr[Steack] = "Steack";
    _ingredientStr[EggPlant] = "EggPlant";
    _ingredientStr[GoatChees] = "GoatChees";
    _ingredientStr[ChiefLove] = "ChiefLove";
    _isRunning = true;
}

plazza::Stock::~Stock()
{
    _isRunning = false;
 //   _refill.cancel();
}

bool plazza::Stock::canConsume(const plazza::Pizza &pizza) const
{
    std::map<IngredientList, int> tmp = _stockList;
    if (PizzaIngredient.find(pizza.getPizzaType()) == PizzaIngredient.end())
        return false;
    std::list<plazza::IngredientList> ingredientList = PizzaIngredient.at(pizza.getPizzaType());

    for (auto &ingredient : tmp) {
        for (const auto &ing : ingredientList) {
            if (ing == ingredient.first and ingredient.second <= 0) {
                return false;
            }
        }
    }
    return true;
}

void plazza::Stock::useStock(const plazza::Pizza &pizza)
{
    std::map<IngredientList, int> tmp;
    bool found = false;
    if (PizzaIngredient.find(pizza.getPizzaType()) == PizzaIngredient.end())
        return;
    std::list<plazza::IngredientList> ingredientList = PizzaIngredient.at(pizza.getPizzaType());

    for (auto &ingredient : _stockList) {
        found = false;
        for (const auto &ing : ingredientList) {
            if (ing == ingredient.first) {
                found = true;
                break;
            }
        }
        if (found)
            tmp[ingredient.first] = ingredient.second - 1;
        else
            tmp[ingredient.first] = ingredient.second;
    }
    _stockList = tmp;
}

std::list<std::string> plazza::Stock::status()
{
    std::list<std::string> list;
    std::map<IngredientList, int> tmp = _stockList;

    list.emplace_back("[Stock] ->");
    for (const auto &al : tmp) {
        list.emplace_back("\t" + _ingredientStr.at(al.first) + ": " + std::to_string(al.second));
    }
    return list;
}

void plazza::Stock::timerRegen(std::shared_ptr<plazza::Stock> &stock)
{
    std::thread([stock, this]() {
        while (_isRunning) {
            auto timer = std::chrono::steady_clock::now() + std::chrono::milliseconds(this->_timer);
            std::this_thread::sleep_until(timer);
            stock->regenerate();
        }
    }).detach();
}

void plazza::Stock::endRegen(std::shared_ptr<plazza::Stock> &stock)
{
    stock->_isRunning = false;
}

bool plazza::Stock::removeThat(const IngredientList &ingredient)
{
    int value;

    if (_stockList.at(ingredient) <= 0)
        return false;
    value = _stockList.at(ingredient);
    _stockList[ingredient] = (value - 1);
    return true;
}

void plazza::Stock::regenerate()
{
    std::map<IngredientList, int> tmp;

    for (auto &ingredient : _stockList) {
        tmp[ingredient.first] = ingredient.second + 1;
    }
    _stockList = tmp;
}
