#include "headers/player.h"
#include "headers/slot.h"
#include <iostream>

Player::Player(std::string name_, const int id_) : name{std::move(name_)}, id{id_}, blood{0}, bones{0}, deck{id_}
{
    std::cout << "Player "<<id<<" created" << std::endl;
}

Player::~Player()
{
    std::cout << "Starting destruction of Player " << id << "\n";
    /*for (const auto &card: deck.get_all())
    {
        delete card; // Delete the dynamically allocated card
    }
    deck.get_all().clear();*/
    std::cout << "Finished destruction of Player " << id << "\n";
}
void Player::make_deck(const std::vector<Card*>& predefined) { deck.make_deck(predefined); }

void Player::draw_card(Pile &pile)
{
    if(pile.get_size()>0)
        deck.add_card(pile.get_card()); // get card from pile, add card in deck
    else
        std::cout << "Pile is empty" << std::endl;
}


void Player::deck_draw(sf::RenderWindow &window,const float& x,const float& y) const { deck.deck_draw(window,x,y); }

std::ostream &operator<<(std::ostream &out, const Player &player)
{
    out << "Player's name: " << player.name << " Player's blood count: " << player.blood << " Player's bones count: " <<
            player.bones;
    out << "\nDeck:\n";
    out << player.deck;
    return out;
}

std::vector<std::unique_ptr<Card>>& Player::get_deck() { return deck.get_all(); }