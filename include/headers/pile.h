#ifndef PILE_H
#define PILE_H
#include <stack>
#include "cards.h"

class Pile
{
    // 2 piles will be defined, one with squirrels, one with normal cards
    int pile_id;
    sf::Font font_;
    std::stack<Card *> pile; // always draw from top, decrease number of cards by one when drawn.
    sf::Texture pile_texture;
    sf::Sprite pile_sprite;
public:
    explicit Pile(int id, const sf::Font &); // pile 1  = squirrels // pile 2 = normal cards

    ~Pile();

    [[nodiscard]] Card *get_top();

    Card *get_card();

    void get_pile();

    int get_size() const;

    friend std::ostream &operator<<(std::ostream &out, Pile &pile);

    void init_texture();

    void setPos(const float &,const float &);

    // void draw(sf::RenderWindow &window) const; deprecated

    void scale();

    bool is_clicked(sf::Vector2i) const;

    sf::Sprite& get_sprite();
};

#endif