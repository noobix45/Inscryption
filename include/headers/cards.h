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
    Card() = default;
    //constructor for cards that take blood
    Card(const std::string& name_, int hp_, int damage_, int cost_in_blood_, Effect e_) : name{name_}, hp{hp_}, damage{damage_}, cost_in_blood{cost_in_blood_}, cost_in_bones{0}, e{e_} {}
    //constructor for cards that take bones
    Card(const std::string& name_, int hp_, int damage_, int cost_in_bones_, Effect e_, [[maybe_unused]] bool bone) : name{name_}, hp{hp_}, damage{damage_}, cost_in_blood{0}, cost_in_bones{cost_in_bones_}, e{e_} {}

    ~Card() {std::cout<<"Card burned\n";}

    Card(const Card& other_card) = default; //probabil ca unele carti vor avea posbilitatea de clonare

    friend std::ostream& operator << (std::ostream& out, const Card& card) { // pentru afisare
        out << card.name << " hp: " <<card.hp << " damage: "<<card.damage;
        if(card.cost_in_bones !=0)
            out << " cost_in_bones: "<<card.cost_in_bones;
        else
            out<< " cost_in_blood: "<<card.cost_in_blood;
        out << " effect: " <<card.e << "\n";
        return out;
    }

};

#endif