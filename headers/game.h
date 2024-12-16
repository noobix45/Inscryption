#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "pile.h"
#include "board.h"
#include "font_manager.h"
#include "scales.h"
#include <SFML/Graphics.hpp>


class Game
{
public:
    Game();



    void play_game();


private:
    sf::RenderWindow window;
    FontManager font_manager_;
    Pile squirrel_pile;
    Pile normal_pile;
    Player player1;
    Player player2;
    Scales scales;
    sf::Texture background_texture;
    sf::Sprite background_sprite;
    sf::Texture bell_texture;
    sf::Sprite bell_sprite;
    sf::Texture sacrifice_texture;
    sf::Sprite sacrifice_sprite;
    Board board;

    Card *selected_card; // la momentul inceperii nicio carte nu este selectata
    bool card_selected;
    bool sacrifice_on;

    int current_phase; // 0 means draw phase // 1 means playing phase - jucatorii pot sacrifica sau juca carti
    int current_player;


    void first_round(bool &first_round1,bool &first_round2);

    void handle_round_event(const sf::Vector2i &mousePos);

    void handle_draw_phase(sf::Vector2i mousePos);
    void handle_sacrifice(sf::Vector2i mousePos);
    void handle_place_card(sf::Vector2i mousePos);

    void perform_row_action(int);

    void drawEverything();
    void initEverything();

    void check_winner();
    int pile_clicked(sf::Vector2i mousePos);
    bool ring_bell(sf::Vector2i mousePos);

    bool sacrifice(sf::Vector2i mousePos, int) const;

    void select_card(sf::Vector2i, int);

    static Card* go_through_deck(sf::Vector2i mousePos,std::vector<Card*>&);

    bool place_in_board(sf::Vector2i mousePos, int);

    void init_background();
    void init_bell();
    void init_sacrifice();
};

/*    supeeeeeeeeeer old
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