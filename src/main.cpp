/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = main file
 *
 * File creation = 01.05.20
 * Last modification = 01.05.20
 */

#include <iostream>
#include "Arguments/Arguments.hpp"
#include "plazza_header.hpp"
#include "Reception/Reception.hpp"

bool checkArguments(char *argv[], Arguments<ArgsEnum> &args)
{
    int resultI;
    float resultF;
    int resultTime;

    try {
        resultF = std::stof(argv[1]);
        args.addArguments(COOKING_TIME, resultF);
        resultI = std::stoi(argv[2]);
        args.addArguments(COOKS_NUMBER, resultI);
        resultTime = std::stoi(argv[3]);
        args.addArguments(INGREDIENTS_TIME, resultTime);
    } catch (std::exception &e) {
        std::cerr << "Invalids arguments\nAll arguments must be number\n";
        return false;
    }
    return !(resultF <= 0 or resultI <= 0 or resultTime <= 0);
}

int main(int ac, char *argv[])
{
    Arguments<ArgsEnum> args;

    if (ac != 4) {
        std::cerr << "Invalid number of arguments\n";
        return 84;
    }
    if (!checkArguments(argv, args)) {
        return 84;
    }
    try {
        plazza::Reception reception(args);
        reception.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}