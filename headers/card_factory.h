#ifndef CARDS_FACTORY_H
#define CARDS_FACTORY_H
#include "derivate.h"
#include <SFML/Graphics.hpp>

class CardFactory
{
    sf::Font font;

    public:
    explicit CardFactory(const sf::Font& font_) : font(font_) {}

    Card* create_card(const CardType type) const
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
            case CardType::Rattler:
                return new Rattler(font);
            case CardType::Bat:
                return new Bat(font);
            default:
                return nullptr;
        }
    }
};

#endif