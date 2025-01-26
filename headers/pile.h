#ifndef PILE_H
#define PILE_H
#include "cards.h"
#include <stack>

class CardFactory;

class Pile
{
    int pile_id; // 2 piles will be defined, one with squirrels, one with normal cards
    std::stack<Card *> pile; // always draw from top, decrease number of cards by one when drawn.
    sf::Texture pile_texture;
    sf::Sprite pile_sprite;

    void make_pile(const CardFactory&);
    void init_texture();
    void scale();

public:
    Pile(int id, const CardFactory&); // pile 1  = squirrels // pile 2 = normal cards

    Pile()=default;
    ~Pile();

    Card *get_card();

    int get_size() const;

    friend std::ostream &operator<<(std::ostream &out, Pile &pile);

    void setPos(const float &,const float &);

    sf::Sprite& get_sprite();

    //nu sunt folosite in joc, doar pentru tema2
    Pile(const Pile &other);
    Pile &operator=(Pile other);
    friend void swap(Pile &first, Pile &second) noexcept;
};

#endif