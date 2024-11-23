#include "headers/player.h"
#include "headers/slot.h"
#include <iostream>

Player::Player(std::string name_, const int id_,const sf::Font& font) : name{std::move(name_)}, id{id_}, blood{0}, bones{0}, deck{id_,font}
{
    std::cout << "Player "<<id<<" created" << std::endl;
}

Player::~Player()
{
    std::cout << "Starting destruction of Player " << id << "\n";
    for (const auto &card: deck.get_all())
    {
        delete card; // Delete the dynamically allocated card
    }
    deck.get_all().clear();
    std::cout << "Finished destruction of Player " << id << "\n";
}
void Player::make_deck() { deck.get_deck(); }

void Player::draw_card(Pile &pile)
{
    if(pile.get_size()>0)
        deck.add_card(pile.get_card()); // get card from pile, add card in deck
    else
        std::cout << "Pile is empty" << std::endl;
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