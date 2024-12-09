#include "derivate.h"
#include <iostream>

Squirrel::Squirrel(const sf::Font &font) : Card("pictures/squirrel.png", "Squirrel", 1, 0, 0, Effect::none, font)
{
    std::cout << "Squirrel created" << std::endl;
}

void Squirrel::action(const Board &board, const int i, const int j)
{
    std::cout << "I'm just a squirrel!" << std::endl;
}


Adder::Adder(const sf::Font &font) : Card("pictures/adder.png", "Adder", 1, 1, 2, Effect::poison, font)
{
    std::cout << "Adder created\n";
}

void Adder::action(const Board &board, const int i, const int j)
{
    std::cout << "Adder attack!\n";
    if (i == 0) // cartea aparinte playerului1
    {
        deal_damage(100, board, 1, j);
    } else if (i == 1) //cartea apartine playerului 2
    {
        deal_damage(100, board, 0, j);
    } else // indexul de rand e invalid
    {
        std::cout << "adder error code\n";
    }
    // trebuie sa stiu dinainte pe ce pozitie e cartea ca sa stiu care ii este opusa
    // fiecare ccartea va avea permanent updatat pozitiile i si j la care se afla in board
}

Wolf::Wolf(const sf::Font &font) : Card("pictures/wolf.png", "Wolf", 2, 3, 2, Effect::none, font)
{
    std::cout << "Wolf created\n";
}

void Wolf::action(const Board &board, const int i, const int j) { std::cout << "Normal attack\n"; }

Beaver::Beaver(const sf::Font &font) : Card("pictures/beaver.png", "Beaver", 2, 1, 2, Effect::dam, font)
{
    std::cout << "Beaver created\n";
}

void Beaver::action(const Board &board, const int i, const int j) { std::cout << "Beaver attack\n"; }

Mantis::Mantis(const sf::Font &font) : Card("pictures/mantis.png", "Mantis", 1, 1, 1, Effect::bifurcated, font)
{
    std::cout << "Mantis created\n";
}

void Mantis::action(const Board &board, const int i, const int j) { std::cout << "Bifurcated attack\n"; }

Bullfrog::Bullfrog(const sf::Font &font): Card("pictures/bullfrog.png", "Bullfrog", 2, 1, 1, Effect::air_defence, font)
{
    std::cout << "Bullfrog created\n";
}

void Bullfrog::action(const Board &board, const int i, const int j) { std::cout << "Bullfrog attack\n"; }


