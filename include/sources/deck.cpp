
#include "headers/deck.h"
#include <random>
#include <iostream>
#include "headers/cards_factory.h"
#include "headers/slot.h"

Deck::Deck(const int player_id_, const std::vector<Card>& predefined) : player_id{player_id_}
{
    std::cout<<"Creating deck..."<<std::endl;
    std::cout<<"Calling make deck...\n";
    make_deck(predefined);
    std::cout<<"Deck" << player_id << " created"<<std::endl;
}

Deck::~Deck()
{
    std::cout << "Deck" << player_id << "destroyed" << std::endl;
}


void Deck::make_deck(const std::vector<Card>& predefined)
{
    // ii da jucatorului carti random la inceput de joc

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, num_of_types);
std::cout << "adding the squirrel for deck "<< player_id << std::endl;
    deck.push_back(predefined[0]);
    std::cout<<"adding the rest of deck "<< player_id << std::endl;
    for (int i = 0; i < 3; i++) //deckul are 3 carti plus veverita initial
    {
        const int r = dis(gen);
        std::cout<<predefined[r];
        deck.push_back(predefined[r]);
    }
    std::cout<<"Finished adding cards\n";
    std::cout<<"Printing the content of Deck " << player_id <<std::endl;
    for(const auto & i : deck)
        std::cout<<i<<std::endl;
}

int Deck::get_num_of_cards() const { return static_cast<int>(deck.size()); } //how many cards are in the deck

const Card& Deck::get_card(const int i) const { return deck[i]; } // gets info about a card

void Deck::add_card(const Card& card) { deck.push_back(card); } // este folosita la draw from pile

void Deck::draw_card(Pile &pile) //when a card is drawn from the draw pile it is added to the deck
{
    deck.push_back(pile.get_card());
}


std::ostream &operator<<(std::ostream &out, const Deck &deck)
{
    for (int i = 0; i < deck.get_num_of_cards(); i++) { out << deck.get_card(i) << "\n"; }
    return out;
}

void Deck::deck_draw(sf::RenderWindow &window,const float& x,const float& y)
{
    // const sf::Vector2u window_size = window.getSize();
    // const auto start_x1 = static_cast<float>(window_size.x) *0.2f;
    // const auto start_y1 = static_cast<float>(window_size.y) *0.85f;
    // const auto start_x2 = static_cast<float>(window_size.x) *0.8f;
    // const auto start_y2 = static_cast<float>(window_size.y) *0.15f;

    for (int i = 0; i < static_cast<int>(deck.size()); i++) // deseneazza cartile din dekc care sunt unselected
    {
        if(player_id==1 && !deck[i].is_clicked())
        {
            deck[i].draw(window,x + static_cast<float>(i*one_slot_width),y);
            deck[i].update_number(window);
        }
        else if (player_id==2 && !deck[i].is_clicked())
        {
            deck[i].draw(window,x - static_cast<float>(i*one_slot_width),y); // pentru player 2 desenez de la dr la st
            deck[i].update_number(window);
        }
    }
    // deseneaza cartile din deck care sunt selecte
    //ca atunci cand o carte e selctat sa fie peste toate celelalte
    for (int i = 0; i < static_cast<int>(deck.size()); i++)
    {
        constexpr float lift_offset = 20;
        if(player_id==1 && deck[i].is_clicked())
        {
            deck[i].draw(window,x + static_cast<float>(i*one_slot_width),y-lift_offset); //ridic pnetru player 1
        }
        else if(player_id==2 && deck[i].is_clicked())
        {
            deck[i].draw(window,x - static_cast<float>(i*one_slot_width),y+lift_offset);
        }
    }
}

std::pair<float, float> Deck::get_start_positions(const sf::RenderWindow &window, const int player_id)  // generated
{
    const sf::Vector2u window_size = window.getSize();

    float start_x, start_y;
    if (player_id == 1) {
        start_x = static_cast<float>(window_size.x) * 0.2f;
        start_y = static_cast<float>(window_size.y) * 0.85f;
    } else { // player 2
        start_x = static_cast<float>(window_size.x) * 0.8f;
        start_y = static_cast<float>(window_size.y) * 0.15f;
    }
    return {start_x, start_y};
}


std::vector<Card>& Deck::get_all() {return deck;}
