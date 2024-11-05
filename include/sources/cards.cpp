#include "../headers/cards.h"

Card::Card() = default; // pentru caz default in card_factoy

// Constructor for cards that take blood
Card::Card(std::string name_, const int hp_, int const damage_, const int cost_in_blood_, const Effect e_) : name{
        std::move(name_)
    }, hp{hp_}, damage{damage_}, cost_in_blood{cost_in_blood_}, cost_in_bones{0}, e{e_} { init_texture(); }

// Constructor for cards that take bones
Card::Card(std::string name_, const int hp_, const int damage_, const int cost_in_bones_, const Effect e_, [[maybe_unused]] bool bone) : name
    {std::move(name_)}, hp{hp_}, damage{damage_}, cost_in_blood{0}, cost_in_bones{cost_in_bones_},
    e{e_} { init_texture();}

Card::~Card() = default;

Card::Card(const Card &other_card) = default;

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
    }
    return *this;
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

void Card::init_texture()
{
    if (!card_texture.loadFromFile("../include/pictures/card_empty.png")) //test texture
    {
        //some error handling;
    }
    card_sprite.setTexture(card_texture);
    card_sprite.setOrigin(static_cast<float>(card_texture.getSize().x) / 2,
                          static_cast<float>(card_texture.getSize().y) / 2);
}

void Card::draw(sf::RenderWindow &window, const float &x, const float &y)
{
    card_sprite.setPosition(x, y);
    window.draw(card_sprite);
}




