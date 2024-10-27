#include "../headers/player.h"

Player::Player(const std::string& name_, int id_) : name{name_}, id{id_}, blood{0},bones {0}, deck{id_} {}

void Player::draw_card(class Pile& pile)
{
    deck.add_card(pile.get_card()); // get card from pile, add card in deck
}

std::ostream& operator<<(std::ostream& out, const Player& player) {
    out << "Player's name: "<<player.name << " Player's blood count: "<<player.blood << " Player's bones count: "<<player.bones;
    out << "\nDeck:\n";
    out<<player.deck;
    return out;
}