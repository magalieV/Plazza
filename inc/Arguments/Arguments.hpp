/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Arguments class
 *
 * File creation = 01.05.20
 * Last modification = 01.05.20
 */

#ifndef __ARGUMENTS__
#define __ARGUMENTS__

#include <iostream>
#include "plazza_header.hpp"
#include <map>
#include <any>

template <typename T>
class Arguments
{
    private:
        std::map<T, std::any> _map;

    public:
        Arguments() = default;
        ~Arguments() = default;
        void addArguments(const T &key, const std::any &value)
        {
            _map[key] = value;
        }
        bool operator|(const T &key)
        {
            return _map.find(key) != _map.end();
        }
        const std::any &operator<<(const T &key)
        {
            return _map.at(key);
        }
};

#endif //__ARGUMENTS__