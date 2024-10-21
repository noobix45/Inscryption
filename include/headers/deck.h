#ifndef DECK_H
#define DECK_H
#include <iostream>
#include <vector>
#include "cards.h"
#include <time.h>
#include "cards_factory.h"

class Deck{
private:
    int player_id;
    int number_of_cards;
    std::vector<Card> deck; // cartile din deck-ul jucatorului

public:
    Deck(int player_id_) : player_id{player_id_}, number_of_cards{3} {get_deck();}

    void get_deck(){  // ii da jucatorului carti random la inceput de joc

        deck.push_back(card_factory(CardType::Squirrel));
        srand(time(0));
        for(int i=0;i<3;i++)
        {
            int r=(rand()%3)+1;
            deck.push_back(card_factory(CardType(r)));
        }
    }

    int get_num_of_cards() const {return deck.size();} //how many cards are in the deck
    Card get_card(int i) const {return deck[i];} // gets info about a card
    void add_card(const Card& card) {deck.push_back(card);} //when a card is drawn from the draw pile it is added to the deck
    void remove_card(int i) //when card gets played, it is removed from the deck 
    { 
        deck.erase(deck.begin()+i);
        deck.shrink_to_fit();
    }
    friend std::ostream& operator<<(std::ostream& out, const Deck& deck)
    {
        for(int i=0;i<deck.get_num_of_cards();i++) {
            out << deck.get_card(i) << "\n";
        }
        return out;
    }
};
#endif