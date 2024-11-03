#ifndef CARDS_FACTORY_H
#define CARDS_FACTORY_H
#include "cards.h"

inline Card card_factory(const CardType type)
{
    switch(type) {
        case CardType::Squirrel:
            return {"Squirrel",1,0,0,none};
        case CardType::Adder:
            return {"Adder",1,1,2,poison};
        case CardType::Wolf:
            return {"Wolf",2,3,2,none};
        case CardType::Stinkbug:
            return {"Stinkbug",2,1,2,stinkbug,true};
        case CardType::RiverSnapper:
            return {"River Snapper",6,1,2,none};
        case CardType::Bullfrog:
            return {"Bullfrog",2,1,1,air_defence};
        default:
            return {};
    }
}

#endif