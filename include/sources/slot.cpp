#include "headers/slot.h"
#include <iostream>
Slot::Slot(const sf::Texture &texture_) : card(nullptr), slot_texture(texture_) { std::cout << "Slot created\n"; }

void Slot::setUp()
{
    slot_sprite.setTexture(slot_texture);
    slot_sprite.setOrigin(static_cast<float>(one_slot_width) / 2, static_cast<float>(one_slot_height) / 2);
}

Slot::Slot(const Slot &other_slot)
{
    if (this != &other_slot)
    {
        std::cout << "Copying Slot\n";
        card = other_slot.card;
        slot_texture = other_slot.slot_texture;
    }
}

Slot &Slot::operator=(const Slot &other_slot)
{
    if (this != &other_slot)
    {
        card = other_slot.card;
        slot_texture = other_slot.slot_texture;
    }
    std::cout << "Slot operator\n";
    return *this;
}


Slot::~Slot()
{
    delete card;
    std::cout << "Slot destroyed\n";
}


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

void Slot::remove_card()
{
    delete card;
    card = nullptr; }


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

sf::Sprite &Slot::get_sprite()
{
    return slot_sprite;
}