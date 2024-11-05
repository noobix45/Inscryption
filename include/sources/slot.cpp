#include "../headers/slot.h"
#include <iostream>
Slot::Slot() : card(nullptr) {}

bool Slot::is_empty() const
{
    return card == nullptr; // daca card e nullptr return true else return false,
}

void Slot::place_card(sf::RenderWindow &window,Card *new_card)
{
    if (card == nullptr)
    {
        // daca slotul e gol
        card = new_card;
        card->draw(window,slot_sprite.getPosition().x, slot_sprite.getPosition().y);

    } else { std::cout << "Slot is already in use" << std::endl; }
}

void Slot::remove_card() { card = nullptr; }

void Slot::textures_init()
{
    if (!slot_texture.loadFromFile("../include/pictures/slot.png"))
    {
        // incarca textura
        std::cout << "Error in loading picture slots\n";
        // maybe throw exception and stop launch of program??
    }
    const sf::Vector2u size = slot_texture.getSize(); // dimenisunile texturii si incarca sprite-ul
    one_slot_width = size.x;
    one_slot_height = size.y;
    slot_sprite.setTexture(slot_texture);
    slot_sprite.setOrigin(static_cast<float>(one_slot_width)/2,static_cast<float>(one_slot_height)/2);
}

void Slot::draw(sf::RenderWindow &window, const float &x, const float &y)
{
    slot_sprite.setPosition(x + slot_sprite.getLocalBounds().width/2, y+slot_sprite.getLocalBounds().height/2);
    window.draw(slot_sprite);
}

unsigned int Slot::get_slot_width() const { return slot_texture.getSize().x; }
unsigned int Slot::get_slot_height() const { return slot_texture.getSize().y; }

sf::Sprite *Slot::get_sprite()
{
    return &slot_sprite;
}


