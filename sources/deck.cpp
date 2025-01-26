#include "deck.h"
#include "constante.h"
#include "card_factory.h"
#include <random>
#include <iostream>

Deck::Deck(const int player_id_, const CardFactory& card_factory) : player_id{player_id_}
{
    make_deck(card_factory);
    std::cout << "Deck " << player_id << " created\n";
}

Deck::~Deck()
{
    std::cout << "Starting destruction of Deck " << player_id << "\n";
    for (const auto card : deck)
    {
        delete card;
    }
    deck.clear();
    std::cout << "called deck.clear Finished destruction of Deck " << player_id << "\n";
}

void Deck::make_deck(const CardFactory &card_factory)
{
    // ii da jucatorului carti random la inceput de joc
    std::cout<<"Adding cards in deck "<< player_id << "...\n";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(EXCLUDED_TYPES, NUM_OF_TYPES);


    deck.push_back(card_factory.create_card(CardType::Squirrel));
    for (int i = 0; i < 3; i++) //deckul are 3 carti plus veverita initial
    {
        int r = dis(gen);
        deck.push_back(card_factory.create_card(static_cast<CardType>(r)));
    }
    std::cout<<"Cards added in deck " << player_id << ".\n";
}

void Deck::add_card(Card *card) { deck.push_back(card); } // este folosita cand se trage o carte din pile

void Deck::remove_card(const Card *selected_card)
{
    const Card *temp_card = nullptr;
    for(int i = 0; i < static_cast<int>(deck.size()); i++)
    {
        temp_card = deck[i];
        if(temp_card == selected_card)
        {
            deck.erase(deck.begin() + i);
            deck.shrink_to_fit();
        }
    }
}

Card * Deck::go_through_deck(const sf::Vector2i &mousePos)
{
    for (Card *c: deck) // parcurge deckul si verifica daca click-ul a fost in spatiul unei carti
    {
        if(!c->is_clicked())
            if(c->get_sprite().getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
            {
                c->on_click_select();
                return c; // returneaza cartea selectata(pe care s-a dat click)
            }
    }
    return nullptr; //sau null daca nu s-a selectat nimic
}

Card* Deck::get_card(const int i) const { return deck[i]; } // gets info about a card

std::pair<float, float> Deck::get_start_positions(const sf::RenderWindow &window, const int player_id) // generated
{
    const sf::Vector2u window_size = window.getSize();

    float start_x, start_y;
    if (player_id == 1)
    {
        start_x = static_cast<float>(window_size.x) * 0.2f;
        start_y = static_cast<float>(window_size.y) * 0.85f;
    } else
    {
        // player 2
        start_x = static_cast<float>(window_size.x) * 0.8f;
        start_y = static_cast<float>(window_size.y) * 0.15f;
    }
    return {start_x, start_y};
}

void Deck::setStartPos(const float &x, const float &y)
{
    start_x= x;
    start_y= y;
}

void Deck::deck_draw(sf::RenderWindow &window) const
{
    for (int i = 0; i < static_cast<int>(deck.size()); i++) // deseneaza cartile din dekc care sunt unselected
    {
        if(player_id==1 && !deck[i]->is_clicked())
        {
            deck[i]->draw(window,start_x + static_cast<float>(i*ONE_SLOT_WIDTH),start_y);
            deck[i]->update_number(window);
        }
        else if (player_id==2 && !deck[i]->is_clicked())
        {
            deck[i]->draw(window,start_x - static_cast<float>(i*ONE_SLOT_WIDTH),start_y); // pentru player 2 desenez de la dr la st
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
            deck[i]->draw(window,start_x + static_cast<float>(i*ONE_SLOT_WIDTH),start_y-lift_offset); //ridic pnetru player 1
        }
        else if(player_id==2 && deck[i]->is_clicked())
        {
            deck[i]->draw(window,start_x - static_cast<float>(i*ONE_SLOT_WIDTH),start_y+lift_offset);
        }
    }
}

std::ostream &operator<<(std::ostream &out, const Deck &deck)
{
    for (int i = 0; i < static_cast<int>(deck.deck.size()); i++) { out << *deck.get_card(i) << "\n"; }
    return out;
}


//nu sunt folosite in joc, doar pentru tema 2
Deck::Deck(const Deck &other)
{
    for(const auto& card : other.deck)
    {
        deck.emplace_back(card->clone());
    }
    player_id = other.player_id;
    start_x = other.start_x;
    start_y = other.start_y;
}

Deck& Deck::operator=(Deck other)// noexcept
{
    swap(*this,other);
    return *this;
}

void swap(Deck &a, Deck &b) noexcept
{
    using std::swap;
    swap(a.deck,b.deck);
    swap(a.player_id,b.player_id);
    swap(a.start_x,b.start_x);
    swap(a.start_y,b.start_y);
}
