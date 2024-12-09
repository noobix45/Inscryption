#include "slot.h"
#include "constante.h"
#include <iostream>
#include <player.h>

#include "cards.h"

Slot::Slot() : card(nullptr),damage_effect(0),hp_effect(0)
{
    std::cout << "Slot created" << std::endl;
    textures_init();
}

Slot::~Slot()
{
    if(card)
    {
        std::cout << "Deleting card inside the slot\n";
        delete card;
    }
    std::cout << "Slot destroyed" << std::endl;
}

bool Slot::is_empty() const
{
    return card == nullptr; // daca card e nullptr return true else return false,
}

Card *Slot::get_card() const { return card; }

void Slot::place_card(Card *new_card)
{
    if (card == nullptr) // daca slotul e gol // card e cartea interna, privata a slotului
    {
        card = new_card;
        // debugg std::cout<<"New card is "<<*new_card<<"\n";
    } else { std::cout << "Slot is already in use" << std::endl; }
}

void Slot::remove_card() { delete card; card = nullptr; }

void Slot::update(sf::RenderWindow &window,Player& p)
{
    if (card != nullptr)
        if(!card->is_dead())
        {
            card->draw(window, slot_sprite.getPosition().x, slot_sprite.getPosition().y);
            card->update_number(window);
        }
        else
        {
            //card is dead give 1 bone to the player delete the card mark slot as empty
            p.modify_bone(1);
            remove_card();
        }
}

void Slot::textures_init()
{
    if (!slot_texture.loadFromFile("pictures/slot.png"))
    {
        // incarca textura
        std::cout << "Error in loading picture slots\n";
        // maybe throw exception and stop launch of program??
    }
    slot_sprite.setTexture(slot_texture);
    slot_sprite.setOrigin(static_cast<float>(ONE_SLOT_WIDTH) / 2, static_cast<float>(ONE_SLOT_HEIGHT) / 2);
}

void Slot::setPos(const float &x, const float &y)
{
    slot_sprite.setPosition(x,y);
}

sf::Sprite &Slot::get_sprite() { return slot_sprite; }

std::ostream &operator<<(std::ostream &os, const Slot &slot)
{
    if (!slot.is_empty())
        os << slot.get_card();
    else
        os << "Slot is empty\n";
    return os;
}