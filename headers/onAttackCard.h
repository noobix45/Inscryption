#ifndef ONATTACKCARD_H
#define ONATTACKCARD_H
#include "cards.h"
#include "board.h"
#include "scales.h"

class onAttackCard : public Card
{
public:
    using Card::Card;
    //virtual void action(const Board&, int i, int j, Scales&) = 0; // specifica temei //i j sunt indicii din slot la care se aflta cartea
    //virtual Card* clone() const = 0;
    //static void deal_damage(int d, const Board &, int, int); // d damage in board at pos int, int or to player
};

class Adder : public onAttackCard
{
public:
    explicit Adder(const sf::Font& font);

    void action(const Board& board, int i,int j,Scales&) override;

    Card* clone() const override {
        return new Adder(*this);
    }
};

class Wolf : public onAttackCard
{
public:
    explicit Wolf(const sf::Font& font);
    void action(const Board& board, int i,int j,Scales&) override;
    Card* clone() const override
    {
        return new Wolf(*this);
    }
};

class Mantis : public onAttackCard
{
public:
    explicit Mantis(const sf::Font& font);
    void action(const Board& board, int i,int j,Scales&) override;
    Card* clone() const override
    {
        return new Mantis(*this);
    }
};

class Bullfrog : public onAttackCard
{
public:
    explicit Bullfrog(const sf::Font& font);
    void action(const Board& board, int i, int j,Scales&) override;
    Card* clone() const override
    {
        return new Bullfrog(*this);
    }
};

#endif //ONATTACK_H
