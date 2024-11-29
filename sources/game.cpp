#include "game.h"
#include "cards_factory.h"
#include "font_manager.h"
#include <iostream>

Game::Game() : window(sf::VideoMode::getDesktopMode(), "My Window", sf::Style::Fullscreen),
               font_manager_("heaviwei.ttf"),
               squirrel_pile(1, font_manager_.getFont()),
               normal_pile(2, font_manager_.getFont()),
               player1{"Player1", 1, font_manager_.getFont()},
               player2{"Player2", 2, font_manager_.getFont()},
               selected_card(nullptr), card_selected(false), sacrifice_on(false), current_phase(0), current_player(1)
{
    window.setFramerateLimit(60);
}

void Game::play_game()
{
    initEverything();

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape) { window.close(); }

            if (squirrel_pile.get_size() == 0 && normal_pile.get_size() == 0) // daca s-au terminat cartile
            {current_phase = 1;}

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                const sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (current_phase == 0) // draw phase
                {
                    draw_phase_logic(mousePos);
                }

                else // e playing phase
                {
                    sacrifice_logic(mousePos);

                    if (!card_selected)
                    {
                        if (current_player == 1)
                            select_card(mousePos, 1); //selecteaza o carte din deck sau nu
                        else
                            select_card(mousePos, 2);
                        if (selected_card != nullptr) { card_selected = true; }
                    }
                    else if (selected_card)
                    {
                        place_card_logic(mousePos);
                    }
                    if(ring_bell(mousePos))
                    {
                        current_phase = 0; // inapoi la drawing phase
                        current_player = (current_player == 1) ? 2 : 1; // schimba jucatorul
                    }
                }
            }
        }
        drawEverything();
    }
}

void Game::draw_phase_logic(const sf::Vector2i mousePos)
{
    if (const int pile_id = pile_clicked(mousePos); pile_id == 1 || pile_id == 2) // verifica daca s-a dat click pe un pile
    {
        auto &pile = (pile_id == 1) ? squirrel_pile : normal_pile;
        auto &player = (current_player == 1) ? player1 : player2;

        player.draw_card(pile);
        current_phase = 1; // playing phase
    }
}

void Game::sacrifice_logic(const sf::Vector2i mousePos)
{
    if (selected_card == nullptr && sacrifice_sprite.getGlobalBounds().contains(
                                static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) // daca se da click pe sacrifice
    {
        sacrifice_on = true;
    }
    if (sacrifice_on)
    {
        const int board_index = (current_player == 1) ? 1 : 0;
        auto &player = (current_player == 1) ? player1 : player2;
        if (sacrifice(mousePos, board_index)) // daca sacrificiul s-a facut
        {
            //std::cout << "Sacrifice detected giving blood to player\n";
            player.add_blood(1); // daca cartea are effect worthy sacrifice va fi 3 (in viitor)
            //std::cout << player;
            sacrifice_on = false;
        }
    }
}

void Game::place_card_logic(const sf::Vector2i mousePos)
{
    const int board_index2 = (current_player == 1) ? 1 : 0;
    auto &player_again = (current_player == 1) ? player1 : player2;

    if (place_in_board(mousePos, board_index2, selected_card)) // returneaza true daca s-a plasat o carte
    {
        player_again.delete_from_deck(selected_card); // se muta cartea din deck in board
    }

    selected_card->on_click_unselect(); // chiar daca s-a plasat sau nu se deselecteaza cartea
    selected_card = nullptr;
    card_selected = false;
}

void Game::drawEverything()
{
    window.clear();

    window.draw(background_sprite);

    window.draw(bell_sprite);

    if (squirrel_pile.get_size() > 0)
        window.draw(squirrel_pile.get_sprite());

    if (normal_pile.get_size() > 0)
        window.draw(normal_pile.get_sprite());

    board.draw(window);

    for (int i = 0; i < 2; i++) // updateaza cartile din board (pentru cand damage va fi implementat)
        for (int j = 0; j < 4; j++)
            if (!board.get_slot(i, j)->is_empty())
                board.get_slot(i, j)->update(window);

    player1.deck_draw(window);
    player2.deck_draw(window);

    window.draw(sacrifice_sprite);


    player1.count_draw(window); // draws how much blood or bones a player has
    player2.count_draw(window);

    window.display();
}

void Game::initEverything()
{
    player1.make_deck(); // apel catre deck sa se umple cu carti
    player2.make_deck();

    board.make_offset(window);

    init_background();
    init_bell();
    init_sacrifice();

    auto [deck_fst1, deck_snd1] = Deck::get_start_positions(window, 1); // pozitii calc relativ la window
    auto [deck_fst2, deck_snd2] = Deck::get_start_positions(window, 2);

    player1.setDeckPos(deck_fst1, deck_snd1);
    player2.setDeckPos(deck_fst2, deck_snd2);

    player1.setSpritesPos(deck_fst1 - ONE_SLOT_WIDTH * 1.2f, deck_snd1);
    player2.setSpritesPos(deck_fst2 + ONE_SLOT_WIDTH * 1.0f, deck_snd2);

    const float x1 = board.get_slot(0, 3)->get_sprite().getPosition().x;
    const float y1 = board.get_slot(0, 3)->get_sprite().getPosition().y;
    squirrel_pile.setPos(x1 + 2 * ONE_SLOT_WIDTH, y1 - 10);

    const float x2 = board.get_slot(1, 3)->get_sprite().getPosition().x;
    const float y2 = board.get_slot(1, 3)->get_sprite().getPosition().y;
    normal_pile.setPos(x2 + 2 * ONE_SLOT_WIDTH, y2 + 5);
}

int Game::pile_clicked(const sf::Vector2i mousePos)
{
    if (squirrel_pile.get_sprite().getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                                              static_cast<float>(mousePos.y))) { return 1; }
    if (normal_pile.get_sprite().getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                                            static_cast<float>(mousePos.y))) { return 2; }
    return 0; // nu s a dat click pe niciun pile
}

bool Game::ring_bell(const sf::Vector2i mousePos) const
{
    if (bell_sprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
    {
        return true;
    }
    return false;
}

bool Game::sacrifice(const sf::Vector2i mousePos, const int row) const
{
    for (int j = 0; j < 4; j++)
    {
        if (board.get_slot(row, j)->get_sprite().getGlobalBounds().contains(
            static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            //std::cout << "sacrifice was clicked\n";
            if (!(board.get_slot(row, j)->is_empty())) // daca slotul are carte in el
            {
                //std::cout << "sacrifice done\n";
                board.get_slot(row, j)->remove_card(); // sterg cartea din slot definitiv ;) i.e. delete
                return true;
            }
        }
    }
    return false;
}

void Game::select_card(const sf::Vector2i mousePos, const int id) // vreau sa selectez o carte
{
    if (id == 1)
    {
        selected_card = go_through_deck(mousePos, player1.get_deck());
    } else if (id == 2)
    {
        selected_card = go_through_deck(mousePos, player2.get_deck());
    }
}

Card *Game::go_through_deck(const sf::Vector2i mousePos, std::vector<Card *> &deck)
{
    for (Card *c: deck) // parcurge deckul si verifica daca click-il a fost in spatiul unei carti
    {
        if(!c->is_clicked())
        if(c->get_sprite().getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            c->on_click_select();
                return c; // either returning card that was selected
            }
    }
    return nullptr; //or if none was selected I am returning nullptr
}

bool Game::place_in_board(const sf::Vector2i mousePos, const int row, Card *selected_card)
{
    for (int j = 0; j < 4; j++)
    {
        if (board.get_slot(row, j)->get_sprite().getGlobalBounds().contains(
            static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            if (board.get_slot(row, j)->is_empty())
            {
                if (auto &player = (row == 1) ? player1 : player2; player.get_blood() >= selected_card->get_blood()) // daca playerul are suficient blood sa joace cartea
                {
                    //std::cout<<"card will be placed\n";
                    selected_card->on_click_unselect(); // trece la animatia de unclicked
                    board.place_card(selected_card, row, j);
                    player.take_blood(selected_card->get_blood());
                    return true; // am plasat
                }
            }
        }
    }
    return false; // n am plasat cartea in board so don't delete from deck
}

void Game::init_background()
{
    background_texture.loadFromFile("pictures/woodPlanks_albedo.png");
    background_sprite.setTexture(background_texture);

    const sf::Vector2u window_size = window.getSize();
    const sf::Vector2u background_size = background_texture.getSize();

    const auto scale_x = static_cast<float>(window_size.x) / static_cast<float>(background_size.x);
    const auto scale_y = static_cast<float>(window_size.y) / static_cast<float>(background_size.y);

    background_sprite.setScale(scale_x, scale_y);
}

void Game::init_bell()
{
    if(!bell_texture.loadFromFile("pictures/bell.png")) { std::cout<< " Unable to load bell\n"; }
    bell_sprite.setTexture(bell_texture);
    bell_sprite.setScale(5.5f, 5.5f);
    bell_sprite.setOrigin(static_cast<float>(bell_texture.getSize().x) / 2,
                          static_cast<float>(bell_texture.getSize().y) / 2);
    const float pos_xb = board.get_slot(0, 0)->get_sprite().getPosition().x;
    const float pos_yb = board.get_slot(0, 0)->get_sprite().getPosition().y;
    bell_sprite.setPosition(pos_xb - 1.5f * ONE_SLOT_WIDTH, pos_yb + ONE_SLOT_HEIGHT / 2); // 729,427
}

void Game::init_sacrifice()
{
    if (!sacrifice_texture.loadFromFile("pictures/sacrifice_mark.png")) { std::cout << " Unable to load sacrifice\n"; }
    sacrifice_sprite.setTexture(sacrifice_texture);
    const float x = board.get_slot(0, 3)->get_sprite().getPosition().x;
    const float y = board.get_slot(0, 3)->get_sprite().getPosition().y;
    sacrifice_sprite.setOrigin(static_cast<float>(sacrifice_texture.getSize().x) / 2,
                               static_cast<float>(sacrifice_texture.getSize().y) / 2);
    sacrifice_sprite.setPosition(x+ONE_SLOT_WIDTH*3.5f, y + ONE_SLOT_HEIGHT/2);
}