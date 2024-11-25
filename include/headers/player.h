#ifndef PLAYER_H
#define PLAYER_H
#include "deck.h"
#include "pile.h"

class Player
{
private:
    std::string name; // cum se numeste jucatorul //optional
    int id; // cei 2 jucatori vor avea un id 1 sau 2 poate 0 sau 1
    int blood; // how much blood the player can spend on playing a card (on construction 0)
    int bones;
    Deck deck;
    sf::Font font;
    sf::Text blood_text;
    sf::Text bone_text;
    sf::Texture blood_texture;
    sf::Sprite blood_sprite;
    sf::Texture bones_texture;
    sf::Sprite bones_sprite;

public:
    Player(std::string name_, int id_, const sf::Font &);

    ~Player();

    void make_deck();

    void draw_card(Pile &pile);

    //static void sacrifice() {} // vor fi implementate
    //static void ring_bell() {} // schimba randul jucatorului // vor fi implementate
    void deck_draw(sf::RenderWindow &window,const float&,const float&) const;

    void count_draw(sf::RenderWindow &window, const float &, const float &);

    friend std::ostream &operator<<(std::ostream &out, const Player &player);

    std::vector<Card*>& get_deck();

    void add_blood(int);

    void take_blood(int);

    int get_blood() const;

    void init_textures();

    void update_numbers(sf::RenderWindow &window);

};

#endif