#ifndef DECK_H
#define DECK_H
#include "cards.h"
#include <vector>

class CardFactory;

class Deck
{
    int player_id;
    std::vector<Card*> deck; // cartile din deck-ul jucatorului
    float start_x=0, start_y=0;
    void make_deck(const CardFactory& card_factory);

public:
    Deck()=default;
    Deck(int player_id_, const CardFactory&);

    ~Deck();

    void add_card(Card *card); //when a card is drawn from the draw pile it is added to the deck
    void remove_card(const Card*);
    Card* go_through_deck(const sf::Vector2i& mousePos);

    [[nodiscard]] Card* get_card(int i) const; // gets info about a card
    static std::pair<float, float> get_start_positions(const sf::RenderWindow &window, int player_id);

    void setStartPos(const float &, const float &);

    void deck_draw(sf::RenderWindow &window) const;

    friend std::ostream &operator<<(std::ostream &out, const Deck &deck);

    //nu sunt folosite in joc, doar pentru tema2
    Deck(const Deck &); // constructor de copiere

    Deck &operator=(Deck other); //op egal de copiere

    friend void swap(Deck &a, Deck &b) noexcept; // functei custom de swap

};
#endif