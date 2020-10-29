/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Encapsulation for mutex
 *
 * File creation = 05.05.20
 * Last modification = 05.05.20
 */

#ifndef MUTEX_HPP
#define MUTEX_HPP

extern "C"
{
    #include <pthread.h>
}

#include <memory>
#include <thread>
#include <atomic>

class Mutex
{
    private:
        struct mutex_t {
            pthread_mutex_t _mutex;
        };
    public:
        Mutex();
        ~Mutex();
        void lock();
        void unlock();
        bool tryLock();
        Mutex &operator=(const Mutex &) = delete;

    private:
        std::shared_ptr<mutex_t> _mutex = nullptr;
};

#endif