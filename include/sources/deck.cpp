#include "headers/deck.h"
#include <random>
#include <iostream>
#include "headers/cards_factory.h"
#include "headers/slot.h"

Deck::Deck(const int player_id_) : player_id{player_id_} {get_deck(); std::cout<<"Deck "<<player_id<<" created\n";}

Deck::~Deck()
{
    for(const Card* card : deck)
    {
        delete card;
    }
    deck.clear();
    std::cout<<"Deck " << player_id <<" destroyed\n";
}


void Deck::get_deck()
{
    // ii da jucatorului carti random la inceput de joc

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, num_of_types);

    deck.push_back(new Card(card_factory(CardType::Squirrel)));
    for (int i = 0; i < 3; i++) //deckul are 3 carti plus veverita initial
    {
        int r = dis(gen);
        deck.push_back(new Card(card_factory(static_cast<CardType>(r))));
    }
}

int Deck::get_num_of_cards() const { return static_cast<int>(deck.size()); } //how many cards are in the deck

Card* Deck::get_card(const int i) const { return deck[i]; } // gets info about a card

void Deck::add_card(Card *card) { deck.push_back(card); } // este folosita la draw from pile
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

    for (int i = 0; i < static_cast<int>(deck.size()); i++) // deseneazza cartile din dekc care sunt unselected
    {
        if(player_id==1 && !deck[i]->is_clicked())
        {
            deck[i]->draw(window,start_x1 + static_cast<float>(i*one_slot_width),start_y1);
            deck[i]->update_number(window);
        }
        else if (player_id==2 && !deck[i]->is_clicked())
        {
            deck[i]->draw(window,start_x2 - static_cast<float>(i*one_slot_width),start_y2); // pentru player 2 desenez de la dr la st
            deck[i]->update_number(window);
        }
    }
    // deseneaza cartile din deck care sunt selecte
    //ca atunci cand o carte e selctat sa fie peste toate celelalte
    for (int i = 0; i < static_cast<int>(deck.size()); i++)
    {
        constexpr float lift_offset = 20;
        if(player_id==1 && deck[i]->is_clicked())
        {
            deck[i]->draw(window,start_x1 + static_cast<float>(i*one_slot_width),start_y1-lift_offset); //ridic pnetru player 1
        }
        else if(player_id==2 && deck[i]->is_clicked())
        {
            deck[i]->draw(window,start_x2 - static_cast<float>(i*one_slot_width),start_y2+lift_offset);
        }
    }
}

std::vector<Card*>& Deck::get_all() {return deck;}