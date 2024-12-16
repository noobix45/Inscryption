#include "onPlaceCard.h"
#include <iostream>

#include "cards_factory.h"

Beaver::Beaver(const sf::Font &font) : onPlaceCard("pictures/beaver.png","Beaver",3,1,2,Effect::dam,font)
{
    std::cout<<"Beaver created\n";
}

void Beaver::action(const Board &board,const int i, const int j, Scales &scales)
{
    std::cout << "Beaver attack\n";
    if(const int opus = (i==0)? 1 :0; board.get_slot(opus,j)->is_empty())
    {
        scales.update(get_damage(),opus);
    }
    else
    {
        deal_damage(get_damage(), board, opus, j);
    }
}

void Beaver::on_place_action(const Board &board, const int i,const int j, Scales &)
{
    std::cout << "Building dams\n";
    if(j-1 >=0 && board.get_slot(i,j-1)->is_empty())
    {
        board.get_slot(i,j-1)->place_card(card_factory(CardType::Dam,get_font())); // de aici in colo slot e responsabil sa stearga
    }
    if(j+1 <=3 && board.get_slot(i,j+1)->is_empty())
    {
        board.get_slot(i,j+1)->place_card(card_factory(CardType::Dam,get_font()));
    }
}


