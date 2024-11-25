#include "headers/player.h"
#include "headers/slot.h"
#include <iostream>

Player::Player(std::string name_, const int id_, const sf::Font &font_) : name{std::move(name_)}, id{id_}, blood{0},
                                                                          bones{0},
                                                                          deck{id_, font_}, font(font_)
{
    std::cout<<"Initializing textures for the counts of a player...\n";
    init_textures();
    std::cout << "Player "<<id<<" created" << std::endl;
}

Player::~Player()
{
    std::cout << "Starting destruction of Player " << id << "\n";
    for (const auto &card: deck.get_all())
    {
        delete card; // Delete the dynamically allocated card
    }
    deck.get_all().clear();
    std::cout << "Finished destruction of Player " << id << "\n";
}
void Player::make_deck() { deck.make_deck(); }

void Player::draw_card(Pile &pile)
{
    if(pile.get_size() > 0)
        deck.add_card(pile.get_card()); // get card from pile, add card in deck
    else
        std::cout << "Pile is empty" << std::endl;
}

void Player::add_blood(const int sacrificed_blood)
{
    //std::cout << "current blood: "<<blood<<std::endl;
    blood += sacrificed_blood;
    //std::cout << "blood after add: "<<blood<<std::endl;
}

void Player::take_blood(const int played_blood) { blood-=played_blood; }

int Player::get_blood() const { return blood; }

void Player::deck_draw(sf::RenderWindow &window, const float &x, const float &y) const { deck.deck_draw(window, x, y); }

void Player::count_draw(sf::RenderWindow &window, const float &x, const float &y)
{
    blood_sprite.setOrigin(static_cast<float>(blood_texture.getSize().x) / 2.0f,
                           static_cast<float>(blood_texture.getSize().y) / 2.0f);
    blood_sprite.setPosition(x, y);
    window.draw(blood_sprite);
}

void Player::init_textures()
{
    if (!blood_texture.loadFromFile("pictures/blood.png")) { std::cout << "Unable to load blood.png\n"; }
    blood_sprite.setTexture(blood_texture);
    blood_sprite.setScale(2.5f, 2.5f);
    blood_text.setFont(font);
    bone_text.setFont(font);
    //std::cout << "Sprite for blood set\n";
    // in viitor va incarca si textura pentru bones;
}


std::ostream &operator<<(std::ostream &out, const Player &player)
{
    out << "Player's name: " << player.name << " Player's blood count: " << player.blood << " Player's bones count: " <<
            player.bones;
    out << "\nDeck:\n";
    out << player.deck;
    return out;
}

std::vector<Card *> &Player::get_deck() { return deck.get_all(); }

void Player::update_numbers(sf::RenderWindow &window)
{
    blood_text.setString(std::to_string(blood));
    blood_text.setFillColor(sf::Color::White);
    blood_text.setCharacterSize(60.0f);
    blood_text.setOrigin(blood_text.getGlobalBounds().width / 2, blood_text.getGlobalBounds().height / 2);
    // originea in centru
    blood_text.setPosition(blood_sprite.getPosition().x , blood_sprite.getPosition().y - one_slot_height*0.05f);
    window.draw(blood_text);
}