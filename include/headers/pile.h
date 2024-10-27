#ifndef PILE_H
#define PILE_H
#include <stack>
#include "cards.h"
#include "pile.h"

class Pile{ // 2 piles will be defined, one with squirrels, one with normal cards
    int number_of_cards; // how many cards are in the pile
    int pile_id;
    std::stack <Card> pile; // always draw from top, decrease number of cards by one when drawn.
public:
    Pile(int n, int id); // pile 1  = squirrels // pile 2 = normal cards
    [[nodiscard]] Card get_top() const;
    Card get_card();
    [[nodiscard]] int get_size() const;
    void get_pile();

    friend std::ostream& operator<<(std::ostream& out, const Pile& pile);
};

#endif
