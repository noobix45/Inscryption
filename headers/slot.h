#ifndef SLOT_H
#define SLOT_H
#include <SFML/Graphics.hpp>

//////////////to do!!! op= copy pentru slot

class Player;
class Card;

class Slot
{
    Card *card; // daca exista cartea are o valoare, daca nu e nullptr
    int damage_effect;
    int hp_effect;
    sf::Texture slot_texture;
    sf::Sprite slot_sprite;

public:
    Slot();

    ~Slot();

    [[nodiscard]] bool is_empty() const;

    Card *get_card() const;

    void place_card(Card *);

    void remove_card();

    void update(sf::RenderWindow &window,Player&);

    void textures_init();

    void setPos(const float&,const float&);

    sf::Sprite& get_sprite();

    friend std::ostream &operator<<(std::ostream &os, const Slot &slot);
};

#endif //SLOT_H