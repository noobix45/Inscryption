#include "headers/player.h"
#include "headers/slot.h"
#include <iostream>

Player::Player(std::string name_, const int id_) : name{std::move(name_)}, id{id_}, blood{0}, bones{0}, deck{id_} {}


void Player::draw_card(Pile &pile)
{
    deck.add_card(pile.get_card()); // get card from pile, add card in deck
}


void Player::deck_draw(sf::RenderWindow &window) const { deck.deck_draw(window); }

std::ostream &operator<<(std::ostream &out, const Player &player)
{
    out << "Player's name: " << player.name << " Player's blood count: " << player.blood << " Player's bones count: " <<
            player.bones;
    out << "\nDeck:\n";
    out << player.deck;
    return out;
}

std::vector<Card*>& Player::whose_deck() { return deck.get_all(); }