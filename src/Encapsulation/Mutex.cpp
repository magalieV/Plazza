/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Encapsulation for mutex
 *
 * File creation = 05.05.20
 * Last modification = 07.05.20
 */

#include "Encapsulation/Mutex.hpp"

#include <iostream>
#include <string>
#include <thread>

Mutex::Mutex()
    : _mutex(new mutex_t{})
{
    _mutex->_mutex = PTHREAD_MUTEX_INITIALIZER;
}


Mutex::~Mutex()
{
    pthread_mutex_unlock(&(_mutex->_mutex));
    pthread_mutex_destroy(&(_mutex->_mutex));
}

bool Mutex::tryLock()
{
    return pthread_mutex_trylock(&(_mutex->_mutex)) > 0;
}

void Mutex::lock()
{
    pthread_mutex_lock(&(_mutex->_mutex));
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&(_mutex->_mutex));
}