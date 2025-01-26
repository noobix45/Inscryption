#include "derivate.h"
#include <iostream>
#include "card_factory.h"

Squirrel::Squirrel(const sf::Font &font) : Card("pictures/squirrel.png", "Squirrel", 1, 0, 0, Effect::none, font)
{
    std::cout << "Squirrel created" << std::endl;
}

void Squirrel::action(const Board&, int, int, Scales&)
{
    std::cout << "I'm just a squirrel!" << std::endl;
}

Dam::Dam(const sf::Font &font) : Card("pictures/dam.png", "Dam", 2, 0, 0, Effect::none, font, false)
{
    std::cout << "Dam created" << std::endl;
}

void Dam::action(const Board &, int , int , Scales &)
{
    std::cout << "Dam\n";
}

Adder::Adder(const sf::Font &font) : Card("pictures/adder.png", "Adder", 1, 1, 2, Effect::poison, font)
{
    std::cout << "Adder created\n";
}

void Adder::action(const Board &board, const int i, const int j, Scales &scales)
{
    std::cout << "Adder attack!\n";
    if (const int opus = (i == 0) ? 1 : 0; board.get_slot(opus, j)->is_empty())
    // verifica daca exista carte, daca nu updateaza scales
    {
        scales.update(damage, opus);
    } else
        deal_damage(100, board, opus, j);
}

Wolf::Wolf(const sf::Font &font) : Card("pictures/wolf.png", "Wolf", 2, 3, 2, Effect::none, font)
{
    std::cout << "Wolf created\n";
}

void Wolf::action(const Board &board, const int i, const int j, Scales &scales)
{
    std::cout << "Wolf attack\n";
    if (const int opus = (i == 0) ? 1 : 0; board.get_slot(opus, j)->is_empty())
    {
        scales.update(damage, opus);
    } else
    {
        deal_damage(damage, board, opus, j);
    }
}

Mantis::Mantis(const sf::Font &font) : Card("pictures/mantis.png", "Mantis", 1, 1, 1, Effect::bifurcated, font)
{
    std::cout << "Mantis created\n";
}

void Mantis::action(const Board &board, const int i, const int j,Scales& scales)
{
    std::cout << "Bifurcated attack\n";
    const int opus = (i == 0) ? 1 : 0;

    if (j + 1 <= 3) // daca slotul e valid
    {
        if (board.get_slot(opus, j + 1)->is_empty()) // daca e gol update
            scales.update(damage, opus);
        else
            deal_damage(damage, board, opus, j + 1); // daca nu deal damage
    }
    if (j - 1 >= 0)
    {
        if (board.get_slot(opus, j - 1)->is_empty())
            scales.update(damage, opus);
        else
            deal_damage(damage, board, opus,j-1);
    }
}


Bullfrog::Bullfrog(const sf::Font &font): Card("pictures/bullfrog.png", "Bullfrog", 2, 1, 1, Effect::air_defence, font)
{
    std::cout << "Bullfrog created\n";
}

void Bullfrog::action(const Board &board, const int i, const int j,Scales& scales)
{
    std::cout << "Bullfrog attack\n";
    if (const int opus = (i == 0) ? 1 : 0; board.get_slot(opus, j)->is_empty())
    // verifica daca exista carte, daca nu updateaza scales
    {
        scales.update(damage, opus);
    } else
        deal_damage(damage, board, opus, j);
}

Beaver::Beaver(const sf::Font &font) : Card("pictures/beaver.png", "Beaver", 3, 1, 2, Effect::dam, font)
{
    std::cout << "Beaver created\n";
}

void Beaver::action(const Board &board, const int i, const int j, Scales &scales)
{
    std::cout << "Beaver attack\n";
    if (const int opus = (i == 0) ? 1 : 0; board.get_slot(opus, j)->is_empty())
    {
        scales.update(damage, opus);
    } else { deal_damage(damage, board, opus, j); }
}

void Beaver::on_place_action(const Board &board, const int i, const int j,const CardFactory& card_factory)
{
    std::cout << "Building dams\n";

    if (j - 1 >= 0 && board.get_slot(i, j - 1)->is_empty())
    {
        board.get_slot(i, j - 1)->place_card(card_factory.create_card(CardType::Dam));
        // de aici in colo slot e responsabil sa stearga
    }
    if (j + 1 <= 3 && board.get_slot(i, j + 1)->is_empty())
    {
        board.get_slot(i, j + 1)->place_card(card_factory.create_card(CardType::Dam));
    }
}

Rattler::Rattler(const sf::Font &font) : Card("pictures/rattler.png", "Rattler", 1, 3, 6, Effect::none, true, font)
{
    std::cout << "Rattler created\n";
}

void Rattler::action(const Board &board, const int i, const int j, Scales &scales)
{
    std::cout << "Rattler attack\n";
    if (const int opus = (i == 0) ? 1 : 0; board.get_slot(opus, j)->is_empty())
    {
        scales.update(damage, opus);
    } else { deal_damage(damage, board, opus, j); }
}

Bat::Bat(const sf::Font &font) : Card("pictures/bat.png", "Bat", 1, 2, 4, Effect::air, true, font)
{
    std::cout << "Bat created\n";
}

void Bat::action(const Board &board, const int i, const int j, Scales &scales)
{
    std::cout << "Bat attack\n";
    if (const int opus = (i == 0) ? 1 : 0; board.get_slot(opus, j)->is_empty() || board.get_slot(opus, j)->get_card()->get_name() != "Bullfrog")
    {
        scales.update(damage, opus);
    } else { deal_damage(damage, board, opus, j); }
}


