#ifndef ONPLACECARD_H
#define ONPLACECARD_H
#include "cards.h"
#include "board.h"
#include "scales.h"

/// action este deal damage in fiecare runda
/// on place este efectul produs la plasarea functiei in board
/// pentru unele carti va dura acest efect atat timp cat cartea va fi in viata
class onPlaceCard : public Card
{
public:
    using Card::Card;
    virtual void on_place_action(const Board&, int i, int j, Scales&) = 0; // specifica temei //i j sunt indicii din slot la care se aflta cartea
    //virtual void action(const Board&, int i,int j,Scales &) = 0;
    //virtual Card* clone() const = 0;
    //static void deal_damage(int d, const Board &, int, int); // d damage in board at pos int, int or to player
};

class Beaver : public onPlaceCard
{
public:
    explicit Beaver(const sf::Font& font);
    void action(const Board &, int i, int j, Scales &) override;
    void on_place_action(const Board& board, int i, int j,Scales&) override;

    Card* clone() const override
    {
        return new Beaver(*this);
    }
};
#endif //ONPLACECARD_H
