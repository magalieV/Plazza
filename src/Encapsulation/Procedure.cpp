/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Kitchens class
 *
 * File creation = 06.05.20
 * Last modification = 06.05.20
 */

#include "Encapsulation/Procedure.hpp"
#include <iostream>

int Procedure::run()
{
    std::cout << "Nothing to run" << std::endl;
    _id = 0;
    return 0;
}

void Procedure::stop()
{
    std::cout << "STOP\n";
    _run = false;
}