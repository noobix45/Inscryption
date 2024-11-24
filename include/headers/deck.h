#ifndef DECK_H
#define DECK_H
#include <vector>
#include "cards.h"

class Deck
{
    int player_id;
    sf::Font font_;
    std::vector<Card*> deck; // cartile din deck-ul jucatorului

public:
    explicit Deck(int player_id_);

    ~Deck();

    void make_deck(const std::vector<Card *> &predefined);

    [[nodiscard]] int get_num_of_cards() const; //how many cards are in the deck
    [[nodiscard]] Card* get_card(int i) const; // gets info about a card
    void add_card(Card *card); //when a card is drawn from the draw pile it is added to the deck

    static std::pair<float, float> get_start_positions(const sf::RenderWindow &window, int player_id);

    friend std::ostream &operator<<(std::ostream &out, const Deck &deck);

    void deck_draw(sf::RenderWindow &window,const float&,const float&) const;

    std::vector<Card*>& get_all();

};
#endif