#ifndef CARDS_H
#define CARDS_H
#include <board.h>

#include "effects.h"
#include <SFML/Graphics.hpp>

#include "scales.h"


class Card
{
private:
    std::string name; // how is the card called
    int hp; // how much hp the card has
    int cost_in_blood; // how much blood it takes to deploy card (if any)
    int cost_in_bones; // how many bones it takes to deploy card (if any)
    Effect e = Effect::none;
    bool can_sacrifice = true;
    sf::Texture card_texture;
    sf::Sprite card_sprite;
    sf::Text hp_text;
    sf::Text damage_text;
    bool clicked = false;

protected:
    int damage; // how much damage a card deals (if any)
    static void deal_damage(int d, const Board &board, int i, int j);

public:
    Card()=delete; // pentru caz default in card_factoy
    //constructor for cards that take blood
    Card(const std::string &file_name, std::string name_, int hp_, int damage_, int cost_in_blood_,
         Effect e_, const sf::Font &font_, bool can_sacrifice_ = true);

    //constructor for cards that take bones
    Card(const std::string &file_name, std::string name_, int hp_, int damage_, int cost_in_bones_,
         Effect e_, [[maybe_unused]] bool bone, const sf::Font &font_, bool can_sacrifice_ = true);

    //destructor
    virtual ~Card();

    //default copy constructor
    Card(const Card &other_card);

    Card &operator=(const Card &other_card);

    friend std::ostream &operator <<(std::ostream &out, const Card &card);

    [[nodiscard]] std::string get_name() const;

    void draw(sf::RenderWindow &window, const float &, const float &);

    sf::Sprite& get_sprite();

    int get_blood() const;
    int get_bone() const;
    //int get_damage() const;

    bool sacrificabil() const;

    bool is_dead() const;

    void on_click_select();

    void on_click_unselect();

    bool is_clicked() const;

    void update_number(sf::RenderWindow &window);

    void effect_action(const Board &board, const int i, const int j, Scales &scales) { action(board, i, j, scales); }

    virtual Card *clone() const = 0;

    void take_damage(int d);

private:
    virtual void action(const Board &board, int i, int j, Scales &scales) = 0;
    void init_texture(const std::string& file_name,const sf::Font& font);
    void scale_small();
    void scale_big();
};

#endif
