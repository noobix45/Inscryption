#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "pile.h"
#include "board.h"
#include "font_manager.h"
#include "scales.h"
#include <SFML/Graphics.hpp>

#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

#include "card_factory.h"


class Game : public Singleton<Game>
{
public:
    void play_game();
protected:
    Game(sf::RenderWindow& window_);
private:
    static FontManager& initialize_font();
    sf::RenderWindow& window;
    FontManager& font_manager_;
    CardFactory card_factory;
    Pile squirrel_pile;
    Pile normal_pile;
    Player player1;
    Player player2;
    Scales scales;
    sf::Texture background_texture;
    sf::Sprite background_sprite;
    sf::Texture bell_texture;
    sf::Sprite bell_sprite;
    sf::SoundBuffer bell_buffer;
    sf::Sound bell_sound;
    sf::Texture sacrifice_texture;
    sf::Sprite sacrifice_sprite;
    sf::Texture cursor_marker_texture;
    sf::Sprite cursor_marker_sprite;
    sf::Cursor custom_cursor;
    sf::Image cursor_image;
    Board board;

    Card *selected_card; // la momentul inceperii nicio carte nu este selectata
    bool card_selected;
    bool sacrifice_on;

    int current_phase; // 0 means draw phase // 1 means playing phase - jucatorii pot sacrifica sau juca carti
    int current_player;


    void first_round(bool &first_round1, bool &first_round2);

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


#endif