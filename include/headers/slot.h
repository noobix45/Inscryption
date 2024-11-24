#ifndef SLOT_H
#define SLOT_H
#include "cards.h"
#include <SFML/Graphics.hpp>
#include <memory>

#define one_slot_width 154
#define one_slot_height 226

class Slot
{
    std::unique_ptr<Card> card; // daca exista cartea are o valoare, daca nu e nullptr
    sf::Texture slot_texture;
    sf::Sprite slot_sprite;

public:
    Slot();

    ~Slot();

    [[nodiscard]] bool is_empty() const;

    Card *get_card() const;

    void place_card(std::unique_ptr<Card> new_card);

    void remove_card();

    void textures_init();

    //void setPos(const float&,const float&);
    void draw(sf::RenderWindow &window, const float &x, const float &y);

    void update(sf::RenderWindow &window) const;

    sf::Sprite& get_sprite();

    friend std::ostream &operator<<(std::ostream &os, const Slot &slot);
};

#endif //SLOT_H