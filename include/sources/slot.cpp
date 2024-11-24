#include "headers/slot.h"
#include <iostream>

///current version is all generated

// Use a shared texture for all slots to avoid duplication
sf::Texture shared_slot_texture;

Slot::Slot(const sf::Texture &texture_) : card(nullptr), slot_texture(texture_), slot_sprite() {
    std::cout << "Slot created\n";
}

Slot::Slot() : card(nullptr), slot_sprite() {
    if (shared_slot_texture.getSize().x == 0) { // Load shared texture only once
        if (!shared_slot_texture.loadFromFile("pictures/slot.png")) {
            std::cout << "Slot could not load shared texture\n";
        }
    }
    slot_texture = shared_slot_texture;
    slot_sprite.setTexture(slot_texture);
}

void Slot::setUp() {
    slot_sprite.setOrigin(static_cast<float>(one_slot_width) / 2, static_cast<float>(one_slot_height) / 2);
}

Slot::Slot(const Slot &other_slot) : card(other_slot.card), slot_texture(other_slot.slot_texture), slot_sprite() {
    slot_sprite.setTexture(slot_texture);
    std::cout << "Copying Slot\n";
}

Slot &Slot::operator=(const Slot &other_slot) {
    if (this != &other_slot) {
        card = other_slot.card;
        slot_texture = other_slot.slot_texture;
        slot_sprite.setTexture(slot_texture);
    }
    std::cout << "Slot operator\n";
    return *this;
}

Slot::~Slot() {
    delete card; // Safely delete the dynamically allocated card
    std::cout << "Slot destroyed\n";
}

bool Slot::is_empty() const {
    return card == nullptr;
}

void Slot::place_card(Card *new_card) {
    if (card == nullptr) {
        card = new_card;
    } else {
        std::cout << "Slot is already in use" << std::endl;
    }
}

void Slot::remove_card() {
    delete card;
    card = nullptr;
}

void Slot::draw(sf::RenderWindow &window, const float &x, const float &y) {
    slot_sprite.setPosition(x + slot_sprite.getLocalBounds().width / 2, y + slot_sprite.getLocalBounds().height / 2);
    window.draw(slot_sprite);
}

void Slot::update(sf::RenderWindow &window) const {
    if (card) {
        card->draw(window, slot_sprite.getPosition().x, slot_sprite.getPosition().y);
        card->update_number(window);
    }
}

sf::Sprite &Slot::get_sprite() {
    return slot_sprite;
}
