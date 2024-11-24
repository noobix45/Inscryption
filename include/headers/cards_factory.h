#ifndef CARDS_FACTORY_H
#define CARDS_FACTORY_H
#include "cards.h"
#include <SFML/Graphics.hpp>

#ifndef num_of_types
#define num_of_types 5   // cate carti pot exista - squirrel
#endif


    inline Card card_factory(const CardType type,const sf::Font& font)
    {
        switch (type)
        {
            case CardType::Squirrel:
                return {"pictures/squirrel.png", "Squirrel", 1, 0, 0, Effect::none,font};
            case CardType::Adder:
                return {"pictures/adder.png", "Adder", 1, 1, 2, Effect::poison,font};
            case CardType::Wolf:
                return {"pictures/wolf.png", "Wolf", 2, 3, 2, Effect::none,font};
            case CardType::Beaver:
                return {"pictures/beaver.png", "Beaver", 2, 1, 2, Effect::dam,font};
            case CardType::Mantis:
                return {"pictures/mantis.png", "Mantis", 1, 1, 1, Effect::bifurcated,font};
            case CardType::Bullfrog:
                return {"pictures/bullfrog.png", "Bullfrog", 2, 1, 1, Effect::air_defence,font};
            default:
                return {};
        }
    }



#endif