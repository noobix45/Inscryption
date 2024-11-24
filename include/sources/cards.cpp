#include "headers/cards.h"
#include <iostream>

#include "headers/slot.h"

Card::Card() = default; // pentru caz default in card_factoy

// Constructor for cards that take blood
Card::Card(std::string name_, const int hp_, int const damage_, const int cost_in_blood_, const Effect e_,
           const sf::Texture &texture_, const sf::Font &font_) : name{std::move(name_)}, hp{hp_}, damage{damage_},
                                                                 cost_in_blood{cost_in_blood_}, cost_in_bones{0}, e{e_},
                                                                 card_texture(texture_), font(font_)
{
    //init_texture(file_name,font); /// moved to cards factory
    initStyle();
    std::cout<<name<<" created"<<std::endl;
}

// Constructor for cards that take bones
Card::Card(const std::string &file_name, std::string name_, const int hp_, const int damage_, const int cost_in_bones_,
           const Effect e_, const sf::Texture &texture_, const sf::Font &font_,
           [[maybe_unused]] bool bone): name{std::move(name_)}, hp{hp_}, damage{damage_}, cost_in_blood{0},
                                        cost_in_bones{cost_in_bones_}, e{e_},
                                        card_texture(texture_), font(font_)
{
    std::cout<<name<<" created"<<std::endl;
}

Card::~Card()
{
    std::cout<<this->name<< " Destroyed"<<std::endl;
}

Card::Card(const Card &other_card) : name(other_card.name), hp(other_card.hp),damage(other_card.damage),
cost_in_blood(other_card.cost_in_blood),cost_in_bones(other_card.cost_in_bones), e(other_card.e),
card_texture(other_card.card_texture),font(other_card.font)// constructor de copiere
{
    initStyle();
    std::cout<<this->name<< " Created from copy constructor"<<std::endl;
}

std::string Card::get_name() const { return name; }

Card &Card::operator=(const Card &other_card)
{
    if (this != &other_card)
    {
        name = other_card.name;
        hp = other_card.hp;
        damage = other_card.damage;
        cost_in_blood = other_card.cost_in_blood;
        cost_in_bones = other_card.cost_in_bones;
        e = other_card.e;
        card_texture = other_card.card_texture;
        font = other_card.font;
        initStyle();
    }
    std::cout<<this->name<< " operator egal"<<std::endl;
    return *this;
}

bool Card::operator==(const Card &other_card) const
{
    return name == other_card.name && hp == other_card.hp && damage == other_card.damage &&
        cost_in_blood == other_card.cost_in_blood && cost_in_bones == other_card.cost_in_bones && e == other_card.e;
}

// Overload << operator for outputting card info
std::ostream &operator<<(std::ostream &out, const Card &card)
{
    out << card.name << " hp: " << card.hp << " damage: " << card.damage;
    if (card.cost_in_bones != 0)
        out << " cost_in_bones: " << card.cost_in_bones;
    else
        out << " cost_in_blood: " << card.cost_in_blood;
    out << " effect: " << card.e << "\n";
    return out;
}

/*out of use
void Card::init_texture(const std::string &file_name,const sf::Font &font)
{
    if (!card_texture.loadFromFile(file_name)) //test texture
    {
        std::cout<<"Unable to find the image\n";
    }
    card_sprite.setTexture(card_texture);
    card_sprite.setOrigin(static_cast<float>(card_texture.getSize().x) / 2,
                          static_cast<float>(card_texture.getSize().y) / 2);
    scale_small();

    hp_text.setFont(font);
    damage_text.setFont(font);
}*/

void Card::draw(sf::RenderWindow &window, const float &x, const float &y)
{
    card_sprite.setPosition(x, y);
    window.draw(card_sprite);
}

const sf::Sprite& Card::get_sprite() const
{
    return card_sprite;
}

void Card::on_click_select()
{
    scale_big();
    clicked = true;
}
 /// move the scale procces in a separate function
void Card::on_click_unselect()
{
    scale_small();
    clicked = false;
}

bool Card::is_clicked() const{ return clicked; }

void Card::scale_small()
{
    const sf::Vector2u textureSize = card_texture.getSize();
    const float scaleX = one_slot_width / static_cast<float>(textureSize.x);
    const float scaleY = one_slot_height / static_cast<float>(textureSize.y);
    card_sprite.setScale(scaleX, scaleY);
}

void Card::scale_big()
{
    const sf::Vector2u textureSize = card_texture.getSize();
    const float scaleX =( one_slot_width / static_cast<float>(textureSize.x))*1.1f;
    const float scaleY =( one_slot_height / static_cast<float>(textureSize.y)) *1.1f;
    card_sprite.setScale(scaleX, scaleY);
}

void Card::initStyle()
{
    card_sprite.setTexture(card_texture);
    card_sprite.setOrigin(static_cast<float>(card_texture.getSize().x) / 2,
                          static_cast<float>(card_texture.getSize().y) / 2);
    scale_small();

    hp_text.setFont(font);
    damage_text.setFont(font);

}

void Card::update_number(sf::RenderWindow &window)
{
    hp_text.setString(std::to_string(hp));
    damage_text.setString(std::to_string(damage));
    hp_text.setFillColor(sf::Color::Black);
    damage_text.setFillColor(sf::Color::Black);

    hp_text.setCharacterSize(50.0f);
    damage_text.setCharacterSize(50.0f);

    hp_text.setOrigin(hp_text.getGlobalBounds().width / 2, hp_text.getGlobalBounds().height / 2); // originea in centru
    //damage_text.setOrigin(damage_text.getGlobalBounds().width/2, damage_text.getGlobalBounds().height / 2);

    const sf::FloatRect bounds = card_sprite.getGlobalBounds(); // top left = y x
    const auto hp_x = (bounds.left + bounds.width) - bounds.width * 0.15f;
    const auto hp_y = (bounds.top + bounds.height) - bounds.height * 0.185f;

    const auto damage_x = bounds.left + bounds.width * 0.090f;
    const auto damage_y = bounds.top+bounds.height - bounds.height * 0.33f;

    hp_text.setPosition(hp_x,hp_y);
    damage_text.setPosition(damage_x,damage_y);
    window.draw(hp_text);
    window.draw(damage_text);
}