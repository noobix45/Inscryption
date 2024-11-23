#ifndef PLAYER_H
#define PLAYER_H
#include "deck.h"
#include "pile.h"

class Player
{
private:
    std::string name; // cum se numeste jucatorul //optional
    int id; // cei 2 jucatori vor avea un id 1 sau 2 poate 0 sau 1
    int blood; // how much blood the player can spend on playing a card (on construction 0)
    int bones;
    Deck deck;

public:
    Player(std::string name_, int id_,const sf::Font&);

    ~Player();

    void make_deck();

    void draw_card(Pile &pile);

    //static void sacrifice() {} // vor fi implementate
    //static void ring_bell() {} // schimba randul jucatorului // vor fi implementate
    void deck_draw(sf::RenderWindow &window);

    friend std::ostream &operator<<(std::ostream &out, const Player &player);


    std::vector<Card>& whose_deck();
};

#endif