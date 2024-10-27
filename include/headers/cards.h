#ifndef CARDS_H
#define CARDS_H
#include "effects.h"
#include <iostream>

enum class CardType {Squirrel,Adder,Wolf,Stinkbug}; 

class Card {

private:
    std::string name; // how is the card called
    int hp; // how much hp the card has
    int damage; // how much damage a card deals (if any)
    int cost_in_blood; // how much blood it takes to deploy card (if any)
    int cost_in_bones; // how many bones it takes to deploy card (if any)
    Effect e;
public:
    Card(); // pentru caz default in card_factoy
    //constructor for cards that take blood
    Card(const std::string& name_, int hp_, int damage_, int cost_in_blood_, Effect e_);
    //constructor for cards that take bones
    Card(const std::string& name_, int hp_, int damage_, int cost_in_bones_, Effect e_, [[maybe_unused]] bool bone);
    //destructor
    ~Card();
    //default copy constructor
    Card(const Card& other_card); //probabil ca unele carti vor avea posbilitatea de clonare
    //overloading for printing
    [[nodiscard]] std::string get_name() const;

    Card& operator=(const Card& other_card);

    friend std::ostream& operator << (std::ostream& out, const Card& card);
};

#endif