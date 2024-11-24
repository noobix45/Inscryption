#ifndef SLOT_H
#define SLOT_H
#include "cards.h"
#include <SFML/Graphics.hpp>

#define one_slot_width 154
#define one_slot_height 226

class Slot
{
    Card *card; // daca exista cartea are o valoare, daca nu e nullptr
    sf::Texture slot_texture;
    sf::Sprite slot_sprite;

public:
    Slot();

    Slot(const Slot &other_slot);

    Slot &operator=(const Slot &other_slot);

    explicit Slot(const sf::Texture &);

    void setUp();

    ~Slot();

    [[nodiscard]] bool is_empty() const;

    Card *get_card() const;

    void place_card(Card *);

    void remove_card();

    void draw(sf::RenderWindow &window, const float &, const float &);

    void update(sf::RenderWindow &window) const;

    sf::Sprite& get_sprite();
};

#endif //SLOT_H