#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "pile.h"
#include "board.h"
#include <SFML/Graphics.hpp>

class Game
{
private:
    Pile squirrel_pile;
    Pile normal_pile;
    Player player1;
    Player player2;
    //Scale scale
    Board board;
    sf::RenderWindow window;

public:
    Game();

    void play_game();

    void init_background();
};

/*
int r = rand()%4;
    Card c = card_factory(CardType(r));
    std::cout<<"Random card test: \n";
    std::cout<<c;

    std::cout<<"info about a player: \n";
    Player player1{"Player1",1};
    std::cout<<player1;

    Pile Squirrel_pile(10,1); // 10 cards of type squirrel
    std::cout<<Squirrel_pile;
    Pile Normal_pile(6,2); // 6 cards of anyother type than squirell

    player1.draw_card(Squirrel_pile);
    player1.draw_card(Normal_pile);
    std::cout<<player1;

    std::cout<<Normal_pile;
    std::cout<<Squirrel_pile;
*/

#endif
