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

void Player::modify_blood(const int sacrificed_blood)
{
    //std::cout << "current blood: "<<blood<<std::endl;
    blood += sacrificed_blood;
    //std::cout << "blood after add: "<<blood<<std::endl;
}

//void Player::take_blood(const int played_blood) { blood-=played_blood; }

int Player::get_blood() const { return blood; }

void Player::modify_bone(const int num) { bones += num; }


int Player::get_bones() const { return bones; }

void Player::deck_draw(sf::RenderWindow &window) const { deck.deck_draw(window); }

void Player::setDeckPos(const float &x, const float &y)
{
    deck.setStartPos(x,y);
}

void Player::init_textures()
{
    if (!blood_texture.loadFromFile("pictures/blood.png")) { std::cout << "Unable to load blood.png\n"; }
    if (!bone_texture.loadFromFile("pictures/bone.png")) { std::cout << "Unable to load bone.png\n"; }
    blood_sprite.setTexture(blood_texture);
    bone_sprite.setTexture(bone_texture);

    blood_sprite.setOrigin(static_cast<float>(blood_texture.getSize().x) / 2.0f,
                           static_cast<float>(blood_texture.getSize().y) / 2.0f);

    bone_sprite.setOrigin(static_cast<float>(bone_texture.getSize().x) / 2.0f,
                          static_cast<float>(bone_texture.getSize().y) / 2.0f);

    blood_sprite.setScale(2.5f, 2.5f);
    bone_sprite.setScale(2.5f, 2.5f);

    blood_text.setFont(font);
    bone_text.setFont(font);

    blood_text.setFillColor(sf::Color::White);
    blood_text.setCharacterSize(60.0f);
    bone_text.setFillColor(sf::Color::White);
    bone_text.setCharacterSize(60.0f);

    blood_text.setOrigin(blood_text.getGlobalBounds().width / 2, blood_text.getGlobalBounds().height / 2);
    bone_text.setOrigin(blood_text.getGlobalBounds().width / 2, blood_text.getGlobalBounds().height / 2);

    //std::cout << "Sprite for blood set\n";
    //std::cout << "Sprite for bone set\n";
}

void Player::setSpritesPos(const std::pair<float, float> &blood_pos, const std::pair<float, float> &bone_pos)
{
    blood_sprite.setPosition(blood_pos.first, blood_pos.second);
    blood_text.setPosition(blood_sprite.getPosition().x , blood_sprite.getPosition().y - ONE_SLOT_HEIGHT * 0.15f);

    bone_sprite.setPosition(bone_pos.first, bone_pos.second);
    bone_text.setPosition(bone_sprite.getPosition().x, bone_sprite.getPosition().y - ONE_SLOT_HEIGHT *0.15f);
}

void Player::count_draw(sf::RenderWindow &window)
{
    blood_text.setString(std::to_string(blood));
    bone_text.setString(std::to_string(bones));

    window.draw(blood_sprite);
    window.draw(blood_text);

    window.draw(bone_sprite);
    window.draw(bone_text);

}

std::ostream &operator<<(std::ostream &out, const Player &player)
{
    out << "Player's name: " << player.name << " Player's blood count: " << player.blood << " Player's bones count: " <<
            player.bones;
    out << "\nDeck:\n";
    out << player.deck;
    return out;
}