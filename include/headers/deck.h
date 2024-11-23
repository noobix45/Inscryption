#ifndef DECK_H
#define DECK_H
#include <vector>
#include "cards.h"
#include "pile.h"

class Deck
{
    int player_id;
    sf::Font font_;
    std::vector<Card> deck; // cartile din deck-ul jucatorului

public:
    Deck(int player_id_, const std::vector<Card>&);

    ~Deck();

    void make_deck(const std::vector<Card>&);

    [[nodiscard]] int get_num_of_cards() const; //how many cards are in the deck
    const  Card& get_card(int i) const; // gets info about a card
    void add_card(const Card& card); //when a card is drawn from the draw pile it is added to the deck

    void draw_card(Pile&);

    friend std::ostream &operator<<(std::ostream &out, const Deck &deck);

    void deck_draw(sf::RenderWindow &window, const float &x, const float &y);

    static std::pair<float, float> get_start_positions(const sf::RenderWindow &window, int player_id);

    std::vector<Card>& get_all();

};
#endif