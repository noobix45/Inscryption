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
    sf::Texture bell_texture;
    sf::Sprite bell_sprite;
    Board board;
    sf::RenderWindow window;

public:
    Game();

    void play_game();

    void init_background();

    void select_card(sf::Vector2i, int, Card *&selected_card);

    static Card* go_through_deck(sf::Vector2i mousePos,std::vector<Card*>&);

    bool place_in_board(sf::Vector2i mousePos, int, Card *) const;

    static void delete_from_deck(std::vector<Card*>&, const Card* );

    void init_bell();

    int pile_clicked(sf::Vector2i mousePos);

    bool ring_bell(sf::Vector2i mousePos) const;
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