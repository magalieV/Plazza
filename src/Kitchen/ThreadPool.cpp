/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Encapsulation for mutex
 *
 * File creation = 07.05.20
 * Last modification = 07.05.20
 */

#include "Kitchen/ThreadPool.hpp"
#include "Kitchen/PizzaCooking.hpp"
#include "Encapsulation/MessageQueue.hpp"
#include "Encapsulation/Shared.hpp"
#include "plazza_header.hpp"

plazza::ThreadPool::ThreadPool(unsigned int stockTimer, unsigned int cooksNumber,
    float cooksTimer, unsigned int kitchenId)
{
    _cooksNumbers = cooksNumber;
    _stock = std::shared_ptr<plazza::Stock>(new plazza::Stock(stockTimer));
    _cooksTimer = cooksTimer;
    _threadVector.clear();
    _end = false;
    _id = kitchenId;
    _threadId = 0;
    _isActive = true;
    _workerNumber = 0;
}

void plazza::ThreadPool::addOrder(const plazza::Pizza &pizza)
{
    _pizzaQueue.push_back(pizza);
    _mutex.lock();
    _stock->useStock(pizza);
    _mutex.unlock();
}

unsigned int plazza::ThreadPool::getPlace()
{
    return _cooksNumbers - _pizzaQueue.size();
}

std::vector<std::string> plazza::ThreadPool::getStatus() const
{
    return _cooksStatus;
}

std::list<std::string> plazza::ThreadPool::getStockStatus() const
{
    return _stock->status();
}

bool plazza::ThreadPool::canConsumeThat(const plazza::Pizza &pizza) const
{
    return _stock->canConsume(pizza);
}

void plazza::ThreadPool::run()
{
    _timeLastCommand = std::chrono::system_clock::now();
    _stock->timerRegen(_stock);
    auto func = [this]()
    {
        bool te = false;
        int idCooks = 0;
        _mutex.lock();
        _cooksStatus.emplace_back(std::string(""));
        idCooks = _cooksStatus.size() - 1;
        _mutex.unlock();
        while (!_end) {
            if (_pizzaQueue.empty() and te == false) {
                _cooksStatus[idCooks] = "Cooks [" + std::to_string(idCooks) + "]: Do nothing";
                te = true;
                pthread_yield();
            }
            _mutex.lock();
            if (_pizzaQueue.size() > 0) {
                plazza::Pizza pizza = _pizzaQueue.front();
                _pizzaQueue.pop_front();
                _workerNumber += 1;
                _timeLastCommand = std::chrono::system_clock::now();
                _cooksStatus[idCooks] = "Cooks [" + std::to_string(idCooks) + "]: "
                                      "Cooking -> Pizza = Type(" + pizza.getType() + "), Size(" + pizza.getSize() + ").";
                float timer = PizzaTime.at(pizza.getPizzaType()) * _cooksTimer;
                _mutex.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(timer)));
                te = false;
                _mutex.lock();
                _timeLastCommand = std::chrono::system_clock::now();
                std::cout << "\nCooks [" << std::to_string(idCooks) << "]: "
                       "Cooking -> Pizza = Type(" + pizza.getType() << "), Size(" + pizza.getSize() + ") -> Done" << std::endl;
                _workerNumber -= 1;
                _mutex.unlock();
            } else {
                _mutex.unlock();
            }
            if (static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now() - _timeLastCommand).count()) >= 5 and _workerNumber == 0
                and !_end) {
                _end = true;
                MessageQueue message(".", (int)_id * 2);
                plazza::Shared sharedData;
                sharedData.setData(-1);
                message<<sharedData;
                break;
            }
        }

    };
    for (int i = 0; i < _cooksNumbers; i++) {
        auto myThread = new Thread<void>(func);
        myThread->detach();
        _threadId += 1;
        _threadVector.emplace_back(myThread);
    }
}

void plazza::ThreadPool::deleteThreadPool()
{
    _end = true;
    _isActive = false;
    _stock->endRegen(_stock);
    if (_threadVector.empty())
        return;
    for (int i = (int)_threadVector.size() - 1; i >= 0; i--) {
        _threadVector[i]->join();
        delete(_threadVector[i]);
        _threadVector.pop_back();
    }
    _threadVector.clear();
}

plazza::ThreadPool::~ThreadPool()
{
    _end = true;
    _isActive = false;
    _stock->endRegen(_stock);
    if (_threadVector.empty())
        return;
    for (int i = (int)_threadVector.size() - 1; i >= 0; i--) {
        _threadVector[i]->join();
        delete(_threadVector[i]);
        _threadVector.pop_back();
    }
}