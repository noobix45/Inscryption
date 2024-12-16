#ifndef DERIVATE_H
#define DERIVATE_H
#include "cards.h"

class Squirrel : public Card
{
public:
    explicit Squirrel(const sf::Font& font);

    void action(const Board &, int i, int j, Scales &) override;

    Card *clone() const override
    {
        return new Squirrel(*this);
    }
};

class Dam : public Card
{
public:
    explicit Dam(const sf::Font &font);

    void action(const Board &, int i, int j, Scales &) override;

    Card *clone() const override { return new Dam(*this); }
};

class Adder : public Card
{
public:
    explicit Adder(const sf::Font& font);
    void action(const Board &, int i, int j, Scales &) override;

    Card *clone() const override
    {
        return new Adder(*this);
    }
};

class Wolf : public Card
{
public:
    explicit Wolf(const sf::Font& font);
    void action(const Board &board, int i, int j, Scales &) override;

    Card *clone() const override
    {
        return new Wolf(*this);
    }
};

class Mantis : public Card
{
public:
    explicit Mantis(const sf::Font& font);
    void action(const Board &board, int i, int j, Scales &) override;

    Card *clone() const override
    {
        return new Mantis(*this);
    }
};

class Bullfrog : public Card
{
public:
    explicit Bullfrog(const sf::Font& font);

    void action(const Board &board, int i, int j, Scales &) override;

    Card* clone() const override
    {
        return new Bullfrog(*this);
    }
};

class Beaver : public Card
{
public:
    explicit Beaver(const sf::Font &font);

    void action(const Board &, int i, int j, Scales &) override;

    void on_place_action(const Board &board, int i, int j,const sf::Font&);

    Card *clone() const override { return new Beaver(*this); }
};

#endif //DERIVATE_H
