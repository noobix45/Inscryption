#include "../headers/deck.h"
#include <ctime>
#include <iostream>
#include "../headers/cards_factory.h"
#include "../headers/slot.h"

Deck::Deck(const int player_id_) : player_id{player_id_} {get_deck();}

void Deck::get_deck()
{
    // ii da jucatorului carti random la inceput de joc

    deck.push_back(new Card(card_factory(CardType::Squirrel)));
    //srand(time(nullptr));
    for (int i = 0; i < 3; i++) //deckul are 3 carti plus veverita initial
    {
        int r = rand() % (num_of_types - 1) + 1;
        deck.push_back(new Card(card_factory(static_cast<CardType>(r))));
    }
}

int Deck::get_num_of_cards() const { return static_cast<int>(deck.size()); } //how many cards are in the deck

Card* Deck::get_card(const int i) const { return deck[i]; } // gets info about a card

void Deck::add_card(Card* card) { deck.push_back(card); }
//when a card is drawn from the draw pile it is added to the deck

void Deck::remove_card(const int i) //when card gets played, it is removed from the deck
{
    deck.erase(deck.begin() + i);
    deck.shrink_to_fit();
}

std::ostream &operator<<(std::ostream &out, const Deck &deck)
{
    for (int i = 0; i < deck.get_num_of_cards(); i++) { out << deck.get_card(i) << "\n"; }
    return out;
}

void Deck::deck_draw(sf::RenderWindow &window) const
{

    const sf::Vector2u window_size = window.getSize();
    const auto start_x1 = static_cast<float>(window_size.x) *0.2f;
    const auto start_y1 = static_cast<float>(window_size.y) *0.85f;
    const auto start_x2 = static_cast<float>(window_size.x) *0.8f;
    const auto start_y2 = static_cast<float>(window_size.y) *0.15f;

    if(player_id == 1)
        for (int i = 0; i < static_cast<int>(deck.size()); i++)
        {
                deck[i]->draw(window,start_x1 + static_cast<float>(i*one_slot_width),start_y1);
        }
    else
    {
        for(int i=0;i<static_cast<int>(deck.size());i++)
        {
            deck[i]->draw(window,start_x2 - static_cast<float>(i*one_slot_width),start_y2);
        }
    }

}
