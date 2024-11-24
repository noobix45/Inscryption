#include "headers/game.h"
#include "headers/cards_factory.h"
#include <iostream>
//#include "headers/font_manager.h"

Game::Game() :
                squirrel_pile(1,cardsFactory.getPreDef()),
               normal_pile(2,cardsFactory.getPreDef()),
               player1{"Player1", 1},
               player2{"Player2", 2},
                window(sf::VideoMode::getDesktopMode(), "Inscryption", sf::Style::Fullscreen) {}

void Game::play_game()
{
    board.get_offset(window, one_slot_width, one_slot_height);

    player1.make_deck(cardsFactory.getPreDef());
    player2.make_deck(cardsFactory.getPreDef());

    init_background();
    init_bell(); // init texture bell

    Card *selected_card = nullptr; // la momentul inceperii nicio carte nu este selectata
    bool card_selected = false;

    int current_phase = 0; // 0 means draw phase // 1 means playing phase - jucatorii pot sacrifica sau juca carti
    int current_player = 1;

    auto [deck_fst1, deck_snd1] = Deck::get_start_positions(window, 1);
    auto [deck_fst2, deck_snd2] = Deck::get_start_positions(window, 2);

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
                            const int board_index = (current_player == 1) ? 1 : 0;
                            auto &player = (current_player == 1) ? player1 : player2;

                            if (place_in_board(mousePos, board_index, selected_card))
                            {
                                delete_from_deck(player.get_deck(), selected_card);
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

        bellSetUp();
        window.draw(bell_sprite);

        const float x1 = board.get_slot(0, 3)->get_sprite().getPosition().x;
        //// pozitiile la care se vor pune pile urile
        const float y1 = board.get_slot(0, 3)->get_sprite().getPosition().y;

        const float x2 = board.get_slot(1, 3)->get_sprite().getPosition().x;
        const float y2 = board.get_slot(1, 3)->get_sprite().getPosition().y;
        if (squirrel_pile.get_size() > 0)
            squirrel_pile.draw(window, x1 + 2 * one_slot_width, y1- 10);


        if (normal_pile.get_size() > 0)
            normal_pile.draw(window, x2 + 2 * one_slot_width, y2 + 5);


        board.draw(window);

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 4; j++)
                if (!board.get_slot(i, j)->is_empty())
                    board.get_slot(i, j)->update(window);
        //board.remove_card(1,2); // this might not work after the changes

        player1.deck_draw(window, deck_fst1, deck_snd1);
        player2.deck_draw(window,deck_fst2,deck_snd2);
        window.display();
    }
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

bool Game::place_in_board(const sf::Vector2i mousePos, const int row, Card *selected_card) const
{
    for(int j = 0; j < 4; j++)
    {
        if (board.get_slot(row, j)->get_sprite().getGlobalBounds().contains(
            static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            if (board.get_slot(row, j)->is_empty())
            {
                selected_card->on_click_unselect(); // trece la animatia de unclicked
                board.place_card(selected_card, row, j);
                return true; // am plasat cartea
            }
        }
    }
    return false; // n am plasat cartea in board so don't delete from deck
}

void Game::delete_from_deck(std::vector<Card *>& deck,const Card *selected_card)
{ // parcurg decku-ul si cand am ajuns la cartea plasata o sterg
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


    //eturn std::make_pair(std::make_pair(x1,y1),std::make_pair(x2,y2));
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

void Game::bellSetUp()
{
    bell_sprite.setScale(5.5f, 5.5f);
    bell_sprite.setOrigin(static_cast<float>(bell_texture.getSize().x) / 2,
                          static_cast<float>(bell_texture.getSize().y) / 2);
    const float pos_xb = board.get_slot(0, 0)->get_sprite().getPosition().x;
    const float pos_yb = board.get_slot(0, 0)->get_sprite().getPosition().y;
    bell_sprite.setPosition(pos_xb - 1.5f * one_slot_width, pos_yb + one_slot_height / 2); // 729,427
}
