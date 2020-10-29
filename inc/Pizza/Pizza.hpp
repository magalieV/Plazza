/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Pizza class
 *
 * File creation = 01.05.20
 * Last modification = 05.05.20
 */

#ifndef __PIZZA__
#define __PIZZA__

#include <iostream>
#include <map>

namespace plazza {
    enum PizzaType {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    enum PizzaState {
        Waiting,
        InProgress,
        Done
    };

    class Pizza {
        public:
            Pizza(const std::string &size, const std::string &type);
            ~Pizza() = default;
            Pizza();
            [[nodiscard]] PizzaSize getPizzaSize() const;
            [[nodiscard]] std::string getSize() const;
            [[nodiscard]] PizzaType getPizzaType() const;
            [[nodiscard]] std::string getType() const;
            void setPizzaState(const PizzaState &state);
            [[nodiscard]] PizzaState getPizzaState() const;
            [[nodiscard]] std::string getState() const;
            [[nodiscard]] bool isValid() const;
            int pack();
            Pizza unpack(int mask);

        private:
            PizzaState _state;
            PizzaSize _size;
            PizzaType _type;
            std::string _sizeString;
            std::string _typeString;
            bool _valid;
    };
}


#endif //__PIZZA__