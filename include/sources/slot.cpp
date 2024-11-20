#include "headers/slot.h"
#include <iostream>
Slot::Slot() : card(nullptr) {}

bool Slot::is_empty() const
{
    return card == nullptr; // daca card e nullptr return true else return false,
}

void Slot::place_card(Card *new_card)
{
    if (card == nullptr) // daca slotul e gol // card e cartea interna, privata a slotului
    {
        card = new_card;
        // debugg std::cout<<"New card is "<<*new_card<<"\n";
    } else { std::cout << "Slot is already in use" << std::endl; }
}

void Slot::remove_card() { card = nullptr; }

void Slot::textures_init()
{
    if (!slot_texture.loadFromFile("pictures/slot.png"))
    {
        // incarca textura
        std::cout << "Error in loading picture slots\n";
        // maybe throw exception and stop launch of program??
    }

    slot_sprite.setTexture(slot_texture);
    slot_sprite.setOrigin(static_cast<float>(one_slot_width) / 2, static_cast<float>(one_slot_height) / 2);
}

void Slot::draw(sf::RenderWindow &window, const float &x, const float &y)
{
    slot_sprite.setPosition(x + slot_sprite.getLocalBounds().width / 2, y + slot_sprite.getLocalBounds().height / 2);
    window.draw(slot_sprite);
}


void Slot::update(sf::RenderWindow &window) const
{
    card->draw(window, slot_sprite.getPosition().x, slot_sprite.getPosition().y);
    card->update_number(window);
}

sf::Sprite& Slot::get_sprite()
{
    return slot_sprite;
}