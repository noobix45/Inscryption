#ifndef DERIVATE_H
#define DERIVATE_H
#include "cards.h"

class Squirrel : public Card
{
    void action(const Board &, int i, int j, Scales &) override;
public:
    explicit Squirrel(const sf::Font& font);

    Card *clone() const override
    {
        return new Squirrel(*this);
    }
};

class Dam : public Card
{
    void action(const Board &, int i, int j, Scales &) override;
public:
    explicit Dam(const sf::Font &font);

    Card *clone() const override { return new Dam(*this); }
};

class Adder : public Card
{
    void action(const Board &, int i, int j, Scales &) override;
public:
    explicit Adder(const sf::Font& font);

    Card *clone() const override
    {
        return new Adder(*this);
    }
};

class Wolf : public Card
{
    void action(const Board &board, int i, int j, Scales &) override;
public:
    explicit Wolf(const sf::Font& font);

    Card *clone() const override
    {
        return new Wolf(*this);
    }
};

class Mantis : public Card
{
    void action(const Board &board, int i, int j, Scales &) override;
public:
    explicit Mantis(const sf::Font& font);

    Card *clone() const override
    {
        return new Mantis(*this);
    }
};

class Bullfrog : public Card
{
    void action(const Board &board, int i, int j, Scales &) override;
public:
    explicit Bullfrog(const sf::Font& font);

    Card* clone() const override
    {
        return new Bullfrog(*this);
    }
};

class Beaver : public Card
{
    void action(const Board &, int i, int j, Scales &) override;
public:
    explicit Beaver(const sf::Font &font);

    //functie specifica beaver pentru downcast
    void on_place_action(const Board &board, int i, int j,const sf::Font&);

    Card *clone() const override { return new Beaver(*this); }
};

class Rattler : public Card
{
    void action(const Board &board, int i, int j, Scales &) override;
public:
    explicit Rattler(const sf::Font &font);

    Card *clone() const override { return new Rattler(*this); }
};

class Bat : public Card
{
    void action(const Board &board, int i, int j, Scales &) override;
public:
    explicit Bat(const sf::Font &font);

    Card *clone() const override { return new Bat(*this); }
};

#endif //DERIVATE_H
