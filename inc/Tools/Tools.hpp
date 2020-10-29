/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Tools class
 *
 * File creation = 02.05.20
 * Last modification = 02.05.20
 */

#ifndef __TOOLS__
#define __TOOLS__

#include <iostream>
#include <vector>

class Tools
{
    public:
        static std::vector<std::string> split(const std::string &line, const std::string &delimiter);
};

#endif //__TOOLS__