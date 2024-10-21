#ifndef CARDS_FACTORY_H
#define CARDS_FACTORY_H
#include "cards.h"

Card card_factory(CardType type)
{
    switch(type)
    {
        case CardType::Squirrel:
        return Card("Squirell",1,0,0,none);
        case CardType::Adder:
        return Card("Addder",1,1,2,poison);
        case CardType::Wolf:
        return Card("Wolf",2,3,2,none);
        case CardType::Stinkbug:
        return Card("Stinkbug",2,1,2,stinkbug,true);
        default:
        return Card();
    }
}

#endif