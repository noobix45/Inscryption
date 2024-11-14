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
            return {"include/pictures/squirrel.png", "Squirrel", 1, 0, 0, none};
        case CardType::Adder:
            return {"include/pictures/adder.png", "Adder", 1, 1, 2, poison};
        case CardType::Wolf:
            return {"include/pictures/wolf.png", "Wolf", 2, 3, 2, none};
        case CardType::Stinkbug:
            return {"include/pictures/stinkbug_talking.png", "Stinkbug", 2, 1, 2, stinkbug, true};
        case CardType::RiverSnapper:
            return {"include/pictures/river_snapper.png", "River Snapper", 6, 1, 2, none};
        case CardType::Bullfrog:
            return {"include/pictures/bullfrog.png", "Bullfrog", 2, 1, 1, air_defence};
        default:
            return {};
    }
}

#endif
