#ifndef CARDS_H
#define CARDS_H
#include "effects.h"
#include <iostream>
#ifndef num_of_types
#define num_of_types 6
#endif

enum class CardType {Squirrel,Adder,Wolf,Stinkbug,RiverSnapper,Bullfrog};

class Card {

private:
    std::string name; // how is the card called
    int hp=0; // how much hp the card has
    int damage=0; // how much damage a card deals (if any)
    int cost_in_blood=0; // how much blood it takes to deploy card (if any)
    int cost_in_bones=0; // how many bones it takes to deploy card (if any)
    Effect e=none;
public:
    Card(); // pentru caz default in card_factoy
    //constructor for cards that take blood
    Card(std::string name_, int hp_, int damage_, int cost_in_blood_, Effect e_);
    //constructor for cards that take bones
    Card(std::string name_, int hp_, int damage_, int cost_in_bones_, Effect e_, [[maybe_unused]] bool bone);
    //destructor
    ~Card();
    //default copy constructor
    Card(const Card& other_card);

    [[nodiscard]] std::string get_name() const;

    Card& operator=(const Card& other_card);

    friend std::ostream& operator << (std::ostream& out, const Card& card);
};

#endif