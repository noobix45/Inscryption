#include "../headers/cards.h"


Card::Card() = default; // pentru caz default in card_factoy

// Constructor for cards that take blood
Card::Card(const std::string& name_, int hp_, int damage_, int cost_in_blood_, Effect e_)
    : name{name_}, hp{hp_}, damage{damage_}, cost_in_blood{cost_in_blood_}, cost_in_bones{0}, e{e_} {}

// Constructor for cards that take bones
Card::Card(const std::string& name_, int hp_, int damage_, int cost_in_bones_, Effect e_, [[maybe_unused]] bool bone)
    : name{name_}, hp{hp_}, damage{damage_}, cost_in_blood{0}, cost_in_bones{cost_in_bones_}, e{e_} {}

Card::~Card() = default;

Card::Card(const Card& other_card) = default;

std::string Card::get_name() const {
    return name;
}

Card& Card::operator=(const Card& other_card) {
    if(this != &other_card) {
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
std::ostream& operator<<(std::ostream& out, const Card& card) {
    out << card.name << " hp: " << card.hp << " damage: " << card.damage;
    if (card.cost_in_bones != 0)
        out << " cost_in_bones: " << card.cost_in_bones;
    else
        out << " cost_in_blood: " << card.cost_in_blood;
    out << " effect: " << card.e << "\n";
    return out;
}
