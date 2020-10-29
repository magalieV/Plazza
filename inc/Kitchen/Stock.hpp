/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Stock class
 *
 * File creation = 05.05.20
 * Last modification = 06.05.20
 */

#ifndef __STOCK__
#define __STOCK__

#include <iostream>
#include <map>
#include <memory>
#include <list>
#include "Pizza/Pizza.hpp"
#include "Kitchen/StockConsume.hpp"
#include "Encapsulation/Thread.hpp"

namespace plazza
{
    class Stock
    {
        public:
            Stock(unsigned int timer);
            ~Stock();
            bool removeThat(const IngredientList &ingredient);
            void regenerate();
            std::list<std::string> status();
            void useStock(const plazza::Pizza &pizza);
            bool canConsume(const plazza::Pizza &pizza) const;
            void timerRegen(std::shared_ptr<plazza::Stock> &stock);
            void endRegen(std::shared_ptr<plazza::Stock> &stock);

        private:
            std::map<IngredientList, int> _stockList;
            unsigned int _timer;
            std::map<IngredientList, std::string> _ingredientStr;
            bool _isRunning;
    };
}

#endif //__STOCK__