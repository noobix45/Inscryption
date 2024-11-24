#ifndef DECK_H
#define DECK_H
#include <vector>
#include "cards.h"
#include <memory>

class Deck
{
    int player_id;
    sf::Font font_;
    std::vector<std::unique_ptr<Card>> deck; // cartile din deck-ul jucatorului

public:
    Deck(int player_id_, const sf::Font &);

    ~Deck();

    void make_deck();

    [[nodiscard]] int get_num_of_cards() const; //how many cards are in the deck
    [[nodiscard]] Card* get_card(int i) const; // gets info about a card
    void add_card(std::unique_ptr<Card> card); //when a card is drawn from the draw pile it is added to the deck

    static std::pair<float, float> get_start_positions(const sf::RenderWindow &window, int player_id);

    friend std::ostream &operator<<(std::ostream &out, const Deck &deck);

    void deck_draw(sf::RenderWindow &window,const float&,const float&) const;

    std::vector<std::unique_ptr<Card>>& get_all();

};
#endif