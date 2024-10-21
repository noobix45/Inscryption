#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "cards.h"
#include "deck.h"

class Player{
private:
    std::string name; // cum se numeste jucatorul //optional
    int id; // cei 2 jucatori vor avea un id 1 sau 2 poate 0 sau 1
    int blood; // how much blood the player can spend on playing a card (on construction 0)
    int bones;
    Deck deck;
public:
    Player(const std::string& name_, int id_) : name{name_}, id{id_}, blood{0},bones {0}, deck{id_} {}
    void draw_card(const Card& card){deck.add_card(card);} ///to be modified to get a card from the pile
    void play_card(){}
    void sacrifice(){}
    void ring_bell(){} // schimba randul jucatorului

    friend std::ostream& operator<<(std::ostream& out, const Player& player) {
        out << "Player's name: "<<player.name << " Player's blood count: "<<player.blood << " Player's bones count: "<<player.bones;
        out << "\nDeck:\n";
        out<<player.deck;
        return out;
    }
};

#endif