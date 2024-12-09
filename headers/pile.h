#ifndef PILE_H
#define PILE_H
#include "cards.h"
#include <stack>

class Pile
{
    int pile_id; // 2 piles will be defined, one with squirrels, one with normal cards
    sf::Font font_;
    std::stack<Card *> pile; // always draw from top, decrease number of cards by one when drawn.
    sf::Texture pile_texture;
    sf::Sprite pile_sprite;

public:
    explicit Pile(int id, const sf::Font &); // pile 1  = squirrels // pile 2 = normal cards

    Pile()=default;
    ~Pile();

    void make_pile();

    [[nodiscard]] Card *get_top();

    Card *get_card();

    bool is_clicked(sf::Vector2i) const;

    int get_size() const;

    friend std::ostream &operator<<(std::ostream &out, Pile &pile);

    void init_texture();

    void scale();

    void setPos(const float &,const float &);

    sf::Sprite& get_sprite();


    //nu sunt folosite in joc, doar pentru tema2
    //const std::stack<Card *> getPile() const;

    //void customPop();

    Pile(const Pile &other);
    Pile &operator=(Pile other);
    friend void swap(Pile &first, Pile &second) noexcept;
};

#endif