#ifndef CARDS_H
#define CARDS_H
#include "effects.h"
#include "board.h"
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
    sf::Text hp_text;
    sf::Text damage_text;
    bool clicked = false;

public:
    Card()=delete; // pentru caz default in card_factoy
    //constructor for cards that take blood
    Card(const std::string& file_name, std::string name_, int hp_, int damage_, int cost_in_blood_, Effect e_,const sf::Font& font_);

    //constructor for cards that take bones
    Card(const std::string& file_name, std::string name_, int hp_, int damage_, int cost_in_bones_, Effect e_,
        [[maybe_unused]] bool bone,const sf::Font& font_);

    //destructor
    virtual ~Card();

    //default copy constructor
    Card(const Card &other_card);

    Card &operator=(const Card &other_card);

    friend std::ostream &operator <<(std::ostream &out, const Card &card);

    [[nodiscard]] std::string get_name() const;

    void init_texture(const std::string& file_name,const sf::Font& font);

    void draw(sf::RenderWindow &window, const float &, const float &);

    sf::Sprite& get_sprite();

    int get_blood() const;
    int get_bone() const;
    bool is_dead() const;

    void on_click_select();

    void on_click_unselect();

    bool is_clicked() const;

    void scale_small();

    void scale_big();

    void update_number(sf::RenderWindow &window);

    virtual void action(const Board&, const int i,const int j) = 0; // specifica temei //i j sunt indicii din slot la care se aflta cartea
    virtual Card* clone() const = 0;

    static void deal_damage(int d, const Board&, int,int); // d damage
    void take_damage(int d);
};

#endif