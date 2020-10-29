/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Encapsulation for mutex
 *
 * File creation = 07.05.20
 * Last modification = 07.05.20
 */

#ifndef __CONSUMER_PIZZA__
#define __CONSUMER_PIZZA__

namespace plazza
{
    enum IngredientList {
        Doe,
        Tomato,
        Gruyere,
        Ham,
        Mushrooms,
        Steack,
        EggPlant,
        GoatChees,
        ChiefLove
    };
}

const std::list<plazza::IngredientList> MargaritaIngredient = {
    plazza::IngredientList::Doe,
    plazza::IngredientList::Tomato,
    plazza::IngredientList::Gruyere
};

const std::list<plazza::IngredientList> ReginaIngredient = {
    plazza::IngredientList::Doe,
    plazza::IngredientList::Tomato,
    plazza::IngredientList::Gruyere,
    plazza::IngredientList::Ham,
    plazza::IngredientList::Mushrooms
};

const std::list<plazza::IngredientList> AmericanaIngredient = {
    plazza::IngredientList::Doe,
    plazza::IngredientList::Tomato,
    plazza::IngredientList::Gruyere,
    plazza::IngredientList::Steack
};

const std::list<plazza::IngredientList> FantasiaIngredient = {
    plazza::IngredientList::Doe,
    plazza::IngredientList::Tomato,
    plazza::IngredientList::EggPlant,
    plazza::IngredientList::GoatChees,
    plazza::IngredientList::ChiefLove
};

const std::map<plazza::PizzaType, std::list<plazza::IngredientList> > PizzaIngredient = {
    {plazza::PizzaType::Margarita, MargaritaIngredient},
    {plazza::PizzaType::Regina, ReginaIngredient},
    {plazza::PizzaType::Americana, AmericanaIngredient},
    {plazza::PizzaType::Fantasia, FantasiaIngredient}
};

#endif //__CONSUMER_PIZZA__