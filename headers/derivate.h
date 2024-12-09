#ifndef DERIVATE_H
#define DERIVATE_H
#include "cards.h"

class Squirrel : public Card
{
public:
    explicit Squirrel(const sf::Font& font);

    void action(const Board& board, int i,int j) override;

    Card* clone() const override {
        return new Squirrel(*this);
    }
};

class Adder : public Card
{
    public:
    explicit Adder(const sf::Font& font);

    void action(const Board& board, const int i,const int j) override;

    Card* clone() const override {
        return new Adder(*this);
    }
};

class Wolf : public Card
{
    public:
    explicit Wolf(const sf::Font& font);
    void action(const Board& board, const int i,const int j) override;
    Card* clone() const override
    {
        return new Wolf(*this);
    }
};

class Beaver : public Card
{
public:
    explicit Beaver(const sf::Font& font);
    void action(const Board& board, const int i,const int j) override;

    Card* clone() const override
    {
        return new Beaver(*this);
    }
};

class Mantis : public Card
{
    public:
    explicit Mantis(const sf::Font& font);
    void action(const Board& board, const int i,const int j) override;
    Card* clone() const override
    {
        return new Mantis(*this);
    }
};

class Bullfrog : public Card
{
    public:
    explicit Bullfrog(const sf::Font& font);
    void action(const Board& board, const int i,const int j) override;
    Card* clone() const override
    {
        return new Bullfrog(*this);
    }
};

#endif //DERIVATE_H
