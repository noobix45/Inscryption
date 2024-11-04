#ifndef SLOT_H
#define SLOT_H
#include "cards.h"
#include <SFML/Graphics.hpp>

class Slot
{
    Card *card; // daca exista cartea are o valoare, daca nu e nullptr
    sf::Texture slot_texture;
    sf::Sprite slot_sprite;
    unsigned int one_slot_width = 0;
    unsigned int one_slot_height = 0;

public:
    Slot();

    [[nodiscard]] bool is_empty() const;

    void place_card(Card *);

    void remove_card();

    void textures_init();

    void draw(sf::RenderWindow &window, const float &, const float &);

    unsigned int get_slot_width() const;

    unsigned int get_slot_height() const;
};

#endif //SLOT_H
