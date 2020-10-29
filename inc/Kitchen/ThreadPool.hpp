/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Encapsulation for mutex
 *
 * File creation = 07.05.20
 * Last modification = 07.05.20
 */

#ifndef __COOKS__
#define __COOKS__

#include "Pizza/Pizza.hpp"
#include "Kitchen/Stock.hpp"
#include "Encapsulation/Mutex.hpp"
#include "Encapsulation/Thread.hpp"
#include <list>
#include <vector>
#include <memory>
#include <queue>
#include <chrono>

namespace plazza
{
    class ThreadPool
    {
        public:
            ThreadPool(unsigned int stockTimer, unsigned int cooksNumber, float cooksTimer, unsigned int kitchenId);
            void addOrder(const plazza::Pizza &pizza);
            unsigned int getPlace();
            virtual ~ThreadPool();
            void run();
            void deleteThreadPool();
            std::vector<std::string> getStatus() const;
            std::list<std::string> getStockStatus() const;
            std::vector<Thread<void> *> _threadVector;
            bool canConsumeThat(const plazza::Pizza &pizza) const;

        private:
            Mutex _mutex;
            const unsigned int maxPlaces = 2;
            std::list<plazza::Pizza> _pizzaQueue;
            std::shared_ptr<plazza::Stock> _stock;
            std::vector<std::string> _cooksStatus;
            unsigned int _cooksNumbers;
            float _cooksTimer;
            bool _end;
            unsigned int _id;
            int _threadId;
            bool _isActive;
            int _workerNumber;
            std::chrono::time_point<std::chrono::system_clock> _timeLastCommand;
    };
}

#endif //__COOKS__