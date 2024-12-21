#ifndef CARDS_FACTORY_H
#define CARDS_FACTORY_H
#include "derivate.h"
#include "exceptii.h"
#include <SFML/Graphics.hpp>

    inline Card* card_factory(const CardType type, const sf::Font& font)
    {
        switch (type)
        {
            case CardType::Squirrel:
                return new Squirrel(font);
            case CardType::Dam:
                return new Dam(font);
            case CardType::Adder:
                return new Adder(font);
            case CardType::Wolf:
                return new Wolf(font);
            case CardType::Beaver:
                return new Beaver(font);
            case CardType::Mantis:
                return new Mantis(font);
            case CardType::Bullfrog:
                return new Bullfrog(font);
            default:
                return nullptr;
        }
    }



#endif