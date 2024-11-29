#include "headers/game.h"
#include "headers/cards_factory.h"
#include "headers/font_manager.h"
#include <iostream>

Game::Game() : window(sf::VideoMode::getDesktopMode(), "My Window", sf::Style::Fullscreen),
               font_manager_("heaviwei.ttf"),
               squirrel_pile(1, font_manager_.getFont()),
               normal_pile(2, font_manager_.getFont()),
               player1{"Player1", 1, font_manager_.getFont()},
               player2{"Player2", 2, font_manager_.getFont()}
{
    window.setFramerateLimit(60);
}

void Game::play_game()
{
    board.make_offset(window); //

    player1.make_deck();
    player2.make_deck();

    init_background();
    init_bell(); // init texture bell
    init_sacrifice();

    Card *selected_card = nullptr; // la momentul inceperii nicio carte nu este selectata
    bool card_selected = false;
    bool sacrifice_on = false;

    int current_phase = 0; // 0 means draw phase // 1 means playing phase - jucatorii pot sacrifica sau juca carti
    int current_player = 1;

    auto [deck_fst1, deck_snd1] = Deck::get_start_positions(window, 1); // pozitii calc relativ la window
    auto [deck_fst2, deck_snd2] = Deck::get_start_positions(window, 2);

    //// pozitiile la care se vor pune pile urile
    const float x1 = board.get_slot(0, 3)->get_sprite().getPosition().x;
    const float y1 = board.get_slot(0, 3)->get_sprite().getPosition().y;
    squirrel_pile.setPos(x1 + 2 * one_slot_width, y1- 10);
    // pentru pile 1 set pos la  x1 + 2 * one_slot_width, y1- 10

    const float x2 = board.get_slot(1, 3)->get_sprite().getPosition().x;
    const float y2 = board.get_slot(1, 3)->get_sprite().getPosition().y;
    normal_pile.setPos(x2 + 2 * one_slot_width, y2 + 5);
    // pentru pile 2 set pos la x2 + 2 * one_slot_width, y2 + 5

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
                if (event.type == sf::Event::KeyPressed)
                    if (event.key.code == sf::Keyboard::Escape) { window.close(); }
                if (squirrel_pile.get_size() == 0 && normal_pile.get_size() == 0)
                {
                    current_phase = 1;
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (current_phase == 0) // draw phase
                    {
                        if (const int pile_id = pile_clicked(mousePos); pile_id == 1 || pile_id == 2)
                        {
                            auto &pile = (pile_id == 1) ? squirrel_pile : normal_pile;
                            auto &player = (current_player == 1) ? player1 : player2;

                            player.draw_card(pile);
                            current_phase = 1; // playing phase
                        }

                    } else // e playing phase
                    {
                        if (selected_card == nullptr && sacrifice_sprite.getGlobalBounds().contains(
                                static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                        {
                            sacrifice_on = true;
                        }
                        if (sacrifice_on)
                        {
                            const int board_index = (current_player == 1) ? 1 : 0;
                            auto &player = (current_player == 1) ? player1 : player2;
                            if (sacrifice(mousePos, board_index))
                            {
                                //std::cout << "Sacrifice detected giving player too blood\n";
                                player.add_blood(1); // daca cartea are effect worthy sacrifice va fi 3
                                std::cout << player;
                                sacrifice_on = false;
                            }
                        }

                        if (!card_selected)
                        {
                            //inainte de selectie un player va fi obligat sa traga o carte din pile
                            //am selectat o carte daca, dupa ce am mers prin deck, selected card !=nullptr
                            if (current_player == 1)
                                select_card(mousePos, 1, selected_card);
                            else
                                select_card(mousePos, 2, selected_card);
                            if (selected_card != nullptr) { card_selected = true; }
                        } else if (selected_card)
                        {
                            // functia returneaza daca am plasat sau nu o carte, ca sa stiu daca o sterg din deck sau nu
                            const int board_index2 = (current_player == 1) ? 1 : 0;
                            auto &player_again = (current_player == 1) ? player1 : player2;

                            if (place_in_board(mousePos, board_index2, selected_card))
                            {
                                delete_from_deck(player_again.get_deck(), selected_card);
                            }

                            selected_card->on_click_unselect();
                            selected_card = nullptr;
                            card_selected = false;
                        }
                        if(ring_bell(mousePos))
                        {
                            current_phase = 0; // inapoi la drawing phase
                            current_player = (current_player == 1) ? 2 : 1;
                        }
                    }
                }
        }
        window.clear();

        window.draw(background_sprite);

        //bellSetUp(); called in init bell
        window.draw(bell_sprite);


        if (squirrel_pile.get_size() > 0)
            window.draw(squirrel_pile.get_sprite());
            //squirrel_pile.draw(window, x1 + 2 * one_slot_width, y1- 10); nu mai este nevoie de pozitie specificat la fiecare iteration


        if (normal_pile.get_size() > 0)
            window.draw(normal_pile.get_sprite());
            //normal_pile.draw(window, x2 + 2 * one_slot_width, y2 + 5);


        board.draw(window);

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 4; j++)
                if (!board.get_slot(i, j)->is_empty())
                    board.get_slot(i, j)->update(window);

        player1.deck_draw(window, deck_fst1, deck_snd1);
        player2.deck_draw(window, deck_fst2, deck_snd2);

        //sacrificeSetUp(); apelat o sg data in sacrifice init
        window.draw(sacrifice_sprite);

        //player1.count_draw(window, deck_fst1 - one_slot_width * 1.2f, deck_snd1);
        player1.setPos(deck_fst1 - one_slot_width * 1.2f, deck_snd1);
        player2.setPos(deck_fst2 + one_slot_width * 1.0f, deck_snd2);
        player1.count_draw(window);
        player2.count_draw(window);
        //player2.count_draw(window, deck_fst2 + one_slot_width * 1.0f, deck_snd2);
        player1.update_numbers(window);
        player2.update_numbers(window);

        window.display();
    }
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
                board.get_slot(row, j)->remove_card(); // sterg cartea din slot definitiv ;)
                return true;
            }
        }
    }
    return false;
}

void Game::select_card(const sf::Vector2i mousePos,const int id, Card *&selected_card) // vreau sa modific selectia
{
    Card *temp_card;
    if (id == 1)
    {
        temp_card = go_through_deck(mousePos, player1.get_deck());
        //ia deck-ul playerului care apeleaza// un pic unintuitive get_deck era deja luat ;)
        selected_card = temp_card;
    } else if (id == 2)
    {
        temp_card = go_through_deck(mousePos, player2.get_deck());
        //ia deck-ul playerului care apeleaza// un pic unintuitive get_deck era deja luat ;)
        selected_card = temp_card;
    }
}

Card *Game::go_through_deck(const sf::Vector2i mousePos, std::vector<Card *> &deck)
{
    for (Card *c: deck) // parcurge deckul si verifica daca click-il a fost in spatiul unei carti
    {
        if(!c->is_clicked()) // maybe a bit extra?
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
                //std::cout <<"from place in board\n"<<player<<std::endl;
                //std::cout <<"Player" << row << " has "<< player.get_blood()<<" wants to play "<< selected_card->get_name()<<" which has "<<selected_card->get_blood()<<"\n";

                if (auto &player = (row == 1) ? player1 : player2; player.get_blood() >= selected_card->get_blood())
                // daca playerul are suficient blood sa joace cartea
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

void Game::delete_from_deck(std::vector<Card *> &deck, const Card *selected_card)
{
    // parcurg decku-ul si cand am ajuns la cartea plasata o sterg
    const Card *temp_card = nullptr;
    for(int i = 0; i < static_cast<int>(deck.size()); i++)
    {
        temp_card = deck[i];
        if(temp_card == selected_card)
        {
            deck.erase(deck.begin() + i);
            deck.shrink_to_fit();
        }
    }
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
    bellSetUp();
}

    //eturn std::make_pair(std::make_pair(x1,y1),std::make_pair(x2,y2));

void Game::bellSetUp()
{
    bell_sprite.setScale(5.5f, 5.5f);
    bell_sprite.setOrigin(static_cast<float>(bell_texture.getSize().x) / 2,
                          static_cast<float>(bell_texture.getSize().y) / 2);
    const float pos_xb = board.get_slot(0, 0)->get_sprite().getPosition().x;
    const float pos_yb = board.get_slot(0, 0)->get_sprite().getPosition().y;
    bell_sprite.setPosition(pos_xb - 1.5f * one_slot_width, pos_yb + one_slot_height / 2); // 729,427
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


void Game::init_sacrifice()
{
    if (!sacrifice_texture.loadFromFile("pictures/sacrifice_mark.png")) { std::cout << " Unable to load sacrifice\n"; }
    sacrifice_sprite.setTexture(sacrifice_texture);
    sacrificeSetUp();
}


void Game::sacrificeSetUp()
{
    const float x = board.get_slot(0, 3)->get_sprite().getPosition().x;
    const float y = board.get_slot(0, 3)->get_sprite().getPosition().y;
    sacrifice_sprite.setOrigin(static_cast<float>(sacrifice_texture.getSize().x) / 2,
                               static_cast<float>(sacrifice_texture.getSize().y) / 2);
    sacrifice_sprite.setPosition(x+one_slot_width*3.5f, y + one_slot_height/2);
}
