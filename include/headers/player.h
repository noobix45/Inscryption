#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "deck.h"
#include "pile.h"

class Player{
private:
    std::string name; // cum se numeste jucatorul //optional
    int id; // cei 2 jucatori vor avea un id 1 sau 2 poate 0 sau 1
    int blood; // how much blood the player can spend on playing a card (on construction 0)
    int bones;
    Deck deck;
public:
    Player(std::string name_, int id_);
    void draw_card(class Pile& pile);
    static void play_card(){} //temp static
    static void sacrifice(){}
    static void ring_bell(){} // schimba randul jucatorului

    friend std::ostream& operator<<(std::ostream& out, const Player& player);
};

#endif