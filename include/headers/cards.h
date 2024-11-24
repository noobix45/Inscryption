#ifndef CARDS_H
#define CARDS_H
#include "effects.h"
#include <SFML/Graphics.hpp>


enum class CardType { Squirrel, Adder, Wolf, Beaver, Mantis, Bullfrog };

class Card
{
private:
    std::string name; // how is the card called
    int hp = 0; // how much hp the card has
    int damage = 0; // how much damage a card deals (if any)
    int cost_in_blood = 0; // how much blood it takes to deploy card (if any)
    int cost_in_bones = 0; // how many bones it takes to deploy card (if any)
    Effect e = Effect::none;
    sf::Texture card_texture;
    sf::Sprite card_sprite;
    sf::Font font;
    sf::Text hp_text;
    sf::Text damage_text;
    bool clicked = false;

public:
    Card(); // pentru caz default in card_factoy
    Card(std::string name_, int hp_, int damage_, int cost_in_blood_, Effect e_, const sf::Texture &texture_,
         const sf::Font &font_);
    //constructor for cards that take blood

    //constructor for cards that take bones
    Card(const std::string& file_name, std::string name_, int hp_, int damage_, int cost_in_bones_, Effect e_,
        const sf::Texture& texture_,const sf::Font& font_,[[maybe_unused]] bool bone);

    //destructor
    ~Card();

    //default copy constructor
    Card(const Card &other_card);

    [[nodiscard]] std::string get_name() const;

    Card &operator=(const Card &other_card);

    bool operator==(const Card &) const;

    friend std::ostream &operator <<(std::ostream &out, const Card &card);

    void init_texture(const std::string& file_name,const sf::Font& font);

    void draw(sf::RenderWindow &window, const float &, const float &);

    const sf::Sprite& get_sprite() const;

    void on_click_select();

    void on_click_unselect();

    bool is_clicked() const;

    void scale_small();

    void scale_big();

    void initStyle();

    void update_number(sf::RenderWindow &window);
};

#endif