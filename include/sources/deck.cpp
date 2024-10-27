#include "../headers/deck.h"
#include <ctime>
#include "../headers/cards_factory.h"

Deck::Deck(int player_id_) : player_id{player_id_}, number_of_cards{3} {get_deck();}

void Deck::get_deck(){  // ii da jucatorului carti random la inceput de joc

    deck.push_back(card_factory(CardType::Squirrel));
    srand(time(nullptr));
    for(int i=0;i<3;i++)
    {
        int r=(rand()%3)+1;
        deck.push_back(card_factory(static_cast<CardType>(r)));
    }
}
int Deck::get_num_of_cards() const {return static_cast<int>(deck.size());} //how many cards are in the deck
Card Deck::get_card(int i) const {return deck[i];} // gets info about a card
void Deck::add_card(const Card& card) {deck.push_back(card);} //when a card is drawn from the draw pile it is added to the deck
void Deck::remove_card(int i) //when card gets played, it is removed from the deck
    {
    deck.erase(deck.begin()+i);
    deck.shrink_to_fit();
    }
std::ostream& operator<<(std::ostream& out, const Deck& deck)
{
    for(int i=0;i<deck.get_num_of_cards();i++) {
        out << deck.get_card(i) << "\n";
    }
    return out;
}