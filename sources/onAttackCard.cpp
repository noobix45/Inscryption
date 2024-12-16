#include "onAttackCard.h"
#include <iostream>



Adder::Adder(const sf::Font &font) : onAttackCard("pictures/adder.png", "Adder", 1, 1, 2, Effect::poison, font)
{
    std::cout << "Adder created\n";
}

void Adder::action(const Board &board, const int i, const int j, Scales &scales)
{
    std::cout << "Adder attack!\n";
    if(const int opus = (i==0)? 1 :0; board.get_slot(opus,j)->is_empty()) // verifica daca exista carte, daca nu updateaza scales
    {
        scales.update(get_damage(),opus);
    }
    else
        deal_damage(100, board, opus, j);
}

Wolf::Wolf(const sf::Font &font) : onAttackCard("pictures/wolf.png", "Wolf", 2, 3, 2, Effect::none, font)
{
    std::cout << "Wolf created\n";
}

void Wolf::action(const Board &board, const int i, const int j,Scales& scales)
{
    std::cout << "Wolf attack\n";
    if(const int opus = (i==0)? 1 :0; board.get_slot(opus,j)->is_empty())
    {
        scales.update(get_damage(),opus);
    }
    else
    {
        deal_damage(get_damage(), board, opus, j);
    }
}

Mantis::Mantis(const sf::Font &font) : onAttackCard("pictures/mantis.png", "Mantis", 1, 1, 1, Effect::bifurcated, font)
{
    std::cout << "Mantis created\n";
}

void Mantis::action(const Board &board, const int i, const int j,Scales& scales)
{
    std::cout << "Bifurcated attack\n";
    const int opus = (i==0) ? 1 : 0;

    if(j+1<=3) // daca slotul e valid
    {
        if(board.get_slot(opus,j+1)->is_empty()) // daca e gol update
            scales.update(get_damage(),opus);
        else
            deal_damage(get_damage(),board,opus,j+1); // daca nu deal damage
    }
    if(j-1>=0)
    {
        if(board.get_slot(opus,j-1)->is_empty())
            scales.update(get_damage(),opus);
        else
            deal_damage(get_damage(),board,opus,j-1);
    }
}


Bullfrog::Bullfrog(const sf::Font &font): onAttackCard("pictures/bullfrog.png", "Bullfrog", 2, 1, 1, Effect::air_defence, font)
{
    std::cout << "Bullfrog created\n";
}

void Bullfrog::action(const Board &board, const int i, const int j,Scales& scales)
{
    std::cout << "Bullfrog attack\n";
    if(const int opus = (i==0)? 1 :0; board.get_slot(opus,j)->is_empty()) // verifica daca exista carte, daca nu updateaza scales
    {
        scales.update(get_damage(),opus);
    }
    else
        deal_damage(get_damage(),board,opus,j);
}