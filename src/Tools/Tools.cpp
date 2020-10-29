/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Tools class
 *
 * File creation = 02.05.20
 * Last modification = 02.05.20
 */

#include "Tools/Tools.hpp"

std::vector<std::string> Tools::split(const std::string &line, const std::string &delimiter)
{
    std::string buffer;
    std::vector<std::string> result;
    bool found = false;

    for (char index : line) {
        found = false;
        for (char idx : delimiter) {
            if (index == idx)
                found = true;
        }
        if (found && !buffer.empty()) {
            result.emplace_back(buffer);
            buffer.clear();
        } else if (!found){
            buffer.push_back(index);
        }
    }
    if (!buffer.empty())
        result.emplace_back(buffer);
    return result;
}