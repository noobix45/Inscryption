#ifndef DECK_H
#define DECK_H
#include "cards.h"
#include <vector>

class Deck
{
    int player_id;
    sf::Font font_;
    std::vector<Card*> deck; // cartile din deck-ul jucatorului
    float start_x=0, start_y=0;

public:
    Deck()=default;
    explicit Deck(int player_id_, const sf::Font &);

    ~Deck();

    void make_deck();

    void add_card(Card *card); //when a card is drawn from the draw pile it is added to the deck
    void remove_card(const Card*);

    [[nodiscard]] int get_num_of_cards() const; //how many cards are in the deck
    [[nodiscard]] Card* get_card(int i) const; // gets info about a card
    std::vector<Card*>& get_all();
    static std::pair<float, float> get_start_positions(const sf::RenderWindow &window, int player_id);

    void setStartPos(const float &, const float &);

    void deck_draw(sf::RenderWindow &window) const;

    friend std::ostream &operator<<(std::ostream &out, const Deck &deck);


    //nu sunt folosite in joc, doar pentru tema2
    Deck(const Deck &); // constructor de copiere

    Deck& operator=(Deck other); //op egal de mutare

    friend void swap(Deck &a, Deck &b) noexcept; // functei custom de swap
};
#endif