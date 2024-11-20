#ifndef CARDS_FACTORY_H
#define CARDS_FACTORY_H
#include "cards.h"

#ifndef num_of_types
#define num_of_types 5   // cate carti pot exista - squirrel
#endif

inline Card card_factory(const CardType type)
{
    switch (type)
    {
        case CardType::Squirrel:
            return {"pictures/squirrel.png", "Squirrel", 1, 0, 0, none};
        case CardType::Adder:
            return {"pictures/adder.png", "Adder", 1, 1, 2, poison};
        case CardType::Wolf:
            return {"pictures/wolf.png", "Wolf", 2, 3, 2, none};
        case CardType::Beaver:
            return {"pictures/beaver.png", "Beaver", 2, 1, 2, dam};
        case CardType::Mantis:
            return {"pictures/mantis.png", "Mantis", 1, 1, 1, bifurcated};
        case CardType::Bullfrog:
            return {"pictures/bullfrog.png", "Bullfrog", 2, 1, 1, air_defence};
        default:
            return {};
    }
}

#endif