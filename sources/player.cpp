#include "player.h"
#include "constante.h"
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

void Player::delete_from_deck(const Card *selected_card)
{
    // apel catre deck care isi sterge cartea
    deck.remove_card(selected_card);
}

std::vector<Card *> &Player::get_deck() { return deck.get_all(); }

void Player::add_blood(const int sacrificed_blood)
{
    //std::cout << "current blood: "<<blood<<std::endl;
    blood += sacrificed_blood;
    //std::cout << "blood after add: "<<blood<<std::endl;
}

void Player::take_blood(const int played_blood) { blood-=played_blood; }

int Player::get_blood() const { return blood; }

void Player::deck_draw(sf::RenderWindow &window) const { deck.deck_draw(window); }

void Player::setDeckPos(const float &x, const float &y)
{
    deck.setStartPos(x,y);
}

void Player::init_textures()
{
    if (!blood_texture.loadFromFile("pictures/blood.png")) { std::cout << "Unable to load blood.png\n"; }
    // if not bone textue
    blood_sprite.setTexture(blood_texture);
    //bone sprite
    blood_sprite.setOrigin(static_cast<float>(blood_texture.getSize().x) / 2.0f,
                           static_cast<float>(blood_texture.getSize().y) / 2.0f);

    //bone sprite
    blood_sprite.setScale(2.5f, 2.5f);
    //bone sprite
    blood_text.setFont(font);
    bone_text.setFont(font);

    blood_text.setFillColor(sf::Color::White);
    blood_text.setCharacterSize(60.0f);
    //bone text set fill collor and set character size

    blood_text.setOrigin(blood_text.getGlobalBounds().width / 2, blood_text.getGlobalBounds().height / 2);
    // bone text

    //std::cout << "Sprite for blood set\n";
    // in viitor va incarca si textura pentru bones;
}

void Player::setSpritesPos(const float &x, const float &y)
{
    blood_sprite.setPosition(x, y);
    blood_text.setPosition(blood_sprite.getPosition().x , blood_sprite.getPosition().y - ONE_SLOT_HEIGHT*0.15f);
    //bone sprite
    //bone text
}

void Player::count_draw(sf::RenderWindow &window)
{
    blood_text.setString(std::to_string(blood));
    //bone text set string
    window.draw(blood_sprite);
    window.draw(blood_text);
}

std::ostream &operator<<(std::ostream &out, const Player &player)
{
    out << "Player's name: " << player.name << " Player's blood count: " << player.blood << " Player's bones count: " <<
            player.bones;
    out << "\nDeck:\n";
    out << player.deck;
    return out;
}