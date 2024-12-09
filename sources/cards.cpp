#include "cards.h"
#include "constante.h"
#include <iostream>
#include <utility>

//deleted Card::Card(); // pentru caz default in card_factoy

// Constructor for cards that take blood
Card::Card(const std::string &file_name, std::string name_, const int hp_, int const damage_, const int cost_in_blood_,const Effect e_,
    const sf::Font& font_):
name{std::move(name_)}, hp{hp_}, damage{damage_}, cost_in_blood{cost_in_blood_}, cost_in_bones{0},e{e_}
{
    init_texture(file_name,font_);
    std::cout<<name<<" created from abstract"<<std::endl;
}

// Constructor for cards that take bones
Card::Card(const std::string &file_name, std::string name_, const int hp_, const int damage_, const int cost_in_bones_,
    const Effect e_,[[maybe_unused]] bool bone, const sf::Font& font_):
name{std::move(name_)}, hp{hp_}, damage{damage_}, cost_in_blood{0},cost_in_bones{cost_in_bones_},e{e_}
{ init_texture(file_name,font_); }

Card::~Card()// = default;
{
    card_sprite.setTexture(sf::Texture());
    hp_text.setFont(sf::Font());
    damage_text.setFont(sf::Font());
    card_texture = sf::Texture();
    clicked = false;
    std::cout << "Resources cleared for Card: " << name << "\n";
    std::cout << name<< " destroyed" << std::endl;
}

Card::Card(const Card &other_card) : name(other_card.name), hp(other_card.hp), damage(other_card.damage),
                                     cost_in_blood(other_card.cost_in_blood), cost_in_bones(other_card.cost_in_bones),
                                     e(other_card.e) { std::cout << "carte copiata\n"; }

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

std::string Card::get_name() const { return name; }


void Card::init_texture(const std::string &file_name,const sf::Font& font)
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
}

void Card::draw(sf::RenderWindow &window, const float &x, const float &y)
{
    card_sprite.setPosition(x, y);
    window.draw(card_sprite);
}

sf::Sprite& Card::get_sprite()
{
    return card_sprite;
}

int Card::get_blood() const { return cost_in_blood; }
int Card::get_bone() const { return cost_in_bones; }

bool Card::is_dead() const {return hp<=0;}


void Card::on_click_select()
{
    scale_big();
    clicked = true;
}

void Card::on_click_unselect()
{
    scale_small();
    clicked = false;
}

bool Card::is_clicked() const{ return clicked; }

void Card::scale_small()
{
    const sf::Vector2u textureSize = card_texture.getSize();
    const float scaleX = ONE_SLOT_WIDTH / static_cast<float>(textureSize.x);
    const float scaleY = ONE_SLOT_HEIGHT / static_cast<float>(textureSize.y);
    card_sprite.setScale(scaleX, scaleY);
}

void Card::scale_big()
{
    const sf::Vector2u textureSize = card_texture.getSize();
    const float scaleX =( ONE_SLOT_WIDTH / static_cast<float>(textureSize.x))*1.1f;
    const float scaleY =( ONE_SLOT_HEIGHT / static_cast<float>(textureSize.y)) *1.1f;
    card_sprite.setScale(scaleX, scaleY);
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

    const sf::FloatRect bounds = card_sprite.getGlobalBounds(); // top left = y x
    const auto hp_x = (bounds.left + bounds.width) - bounds.width * 0.15f;
    const auto hp_y = (bounds.top + bounds.height) - bounds.height * 0.185f;

    const auto damage_x = bounds.left + bounds.width * 0.090f;
    const auto damage_y = bounds.top+bounds.height - bounds.height * 0.33f;

    // debugg std :: cout<<"x: "<<hp_x<<" y: "<<hp_y<<"\n";
    hp_text.setPosition(hp_x,hp_y);
    damage_text.setPosition(damage_x,damage_y);
    window.draw(hp_text);
    window.draw(damage_text);
}

void Card::deal_damage(const int d, const Board &board, const int i, const int j) //ensure damage is poz
{
    if(!board.get_slot(i,j)->is_empty())
    board.get_slot(i,j)->get_card()->take_damage(d);
}

void Card::take_damage(const int d)
{
    hp-=d; // damage must be poz
}


