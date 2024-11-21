#include "headers/game.h"
#include "headers/cards_factory.h"
#include <iostream>

Game::Game() : squirrel_pile(1),
               normal_pile(2),
               player1{"Player1", 1},
               player2{"Player2", 2},
               window(sf::VideoMode::getDesktopMode(), "Inscryption", sf::Style::Fullscreen) { play_game(); }

void Game::play_game()
{
    //la inceputul turei unui jucator, acesta trebuie sa traga o carte, apoi poate sa joace oricate carti din deck.
    //Cand considera ca si-a terminat tura apasa pe clopotel.
    // sus, nu e inca implementat
    Card *selected_card = nullptr; // la momentul inceperii nicio carte nu este selectata
    bool card_selected = false;
    int current_phase = 0; // 0 means draw phase
    int current_player = 1;
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
                if (event.type == sf::Event::KeyPressed)
                    if (event.key.code == sf::Keyboard::Escape) { window.close(); }
                // daca se da un click tratez cazurile
                if(event.type ==  sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (current_phase == 0) // draw phase
                    {
                        if (pile_clicked(mousePos) == 1) // returneaza pile_id
                        {
                            if (current_player == 1)
                                player1.draw_card(squirrel_pile);
                            else
                                player2.draw_card(squirrel_pile);
                            current_phase = 1; // playing phase
                        } else if (pile_clicked(mousePos) == 2)
                        {
                            if (current_player == 1)
                                player1.draw_card(normal_pile);
                            else
                                player2.draw_card(normal_pile);
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
                        }
                        // la urmatorul click cu o carte selectata vreau sa verific daca am dat click in board
                        // daca am dat click in board pun cartea si o sterg din deck
                        // apoi orice ar fi selected card = nullptr
                        else
                        {
                            /*
                            std::cout<<"from event cu card non null: "<<*selected_card;  // debugg
                            std::cout << "Mouse pos before placing: " << mousePos.x << ", " << mousePos.y << "\n";*/
                            // functia returneaza daca am plasat sau nu o carte, ca sa stiu daca o sterg din deck sau nu
                            if (current_player == 1)
                            {
                                if (place_in_board(mousePos, 1, selected_card))
                                {
                                    // delete from deck;
                                    // cauta selcted card in deck si sterge-o de acolo
                                    delete_from_deck(player1.whose_deck(), selected_card);
                                    // debugg std::cout<<"deleted from deck: "<<*selected_card;
                                    selected_card->on_click_unselect();
                                    selected_card = nullptr;
                                    card_selected = false;
                                } else
                                {
                                    selected_card->on_click_unselect();
                                    selected_card = nullptr;
                                    card_selected = false;
                                }
                            } else
                            {
                                if (place_in_board(mousePos, 0, selected_card)) // player 2 foloseste randul 0 din board
                                {
                                    delete_from_deck(player2.whose_deck(), selected_card);
                                    selected_card->on_click_unselect();
                                    selected_card = nullptr;
                                    card_selected = false;
                                } else
                                {
                                    selected_card->on_click_unselect();
                                    selected_card = nullptr;
                                    card_selected = false;
                                }
                            }
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

        init_background();
        init_bell();
        float pos_x = board.get_slot(0,3).get_sprite().getPosition().x;
        float pos_y = board.get_slot(0,3).get_sprite().getPosition().y;
        squirrel_pile.draw(window,pos_x +2*one_slot_width,pos_y-10);
        pos_x = board.get_slot(1,3).get_sprite().getPosition().x;
        pos_y = board.get_slot(1,3).get_sprite().getPosition().y;
        normal_pile.draw(window,pos_x + 2*one_slot_width,pos_y+5);
        board.get_offset(window, one_slot_width, one_slot_height);
        board.draw(window);
        //std::cout << "Center of last slot: "<< board.get_slot(1,3)->get_sprite().getPosition().x << std::endl;
        //std::cout << "Center of last slot: "<< board.get_slot(1,3)->get_sprite().getPosition().y << std::endl;

        /*Card c1 = card_factory(CardType::Adder);
        Card c2 = card_factory(CardType::Squirrel);
        Card c3 = card_factory(CardType::Mantis);
        board.place_card(&c1, 1, 2);
        board.place_card(&c2, 0, 2);
        board.place_card(&c3, 0, 0);*/
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 4; j++)
                if (!board.get_slot(i, j).is_empty())
                    board.get_slot(i, j).update(window);
        //board.remove_card(1,2); // this might not work after the changes
        player1.deck_draw(window);

        //do not uncomment this //player1.draw_card(squirrel_pile);
        // draws from pile until null then it breaks ;)

        player2.deck_draw(window);
        window.display();
    }
}

void Game::select_card(const sf::Vector2i mousePos,const int id, Card *&selected_card) // vreau sa modific selectia
{
    Card *temp_card;
    if(id==1)
    {
        temp_card = go_through_deck(mousePos, player1.whose_deck()); //ia deck-ul playerului care apeleaza// un pic unintuitive get_deck era deja luat ;)
        selected_card = temp_card;
    }
    else if (id == 2)
    {
        temp_card = go_through_deck(mousePos, player2.whose_deck());
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
    /*
    std::cout <<"top place_in_board function\n";   // debugg
    std::cout<< "Mouse pos: "<<mousePos.x<< " "<<mousePos.y<< " \n";*/
    for(int j = 0; j < 4; j++)
    {
        if(board.get_slot(row,j).get_sprite().getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            // debugg std::cout<<"in bounds\n";
            if(board.get_slot(row, j).is_empty())
            {
                // debugg std::cout<<"empty\n";
                selected_card->on_click_unselect(); // trece la animatia de unclicked
                board.place_card(selected_card, row, j);
                //debugg std::cout<<"placed in board\n";
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
    sf::Texture background;
    background.loadFromFile("pictures/woodPlanks_albedo.png");
    sf::Sprite background_sprite;
    background_sprite.setTexture(background);

    const sf::Vector2u window_size = window.getSize();
    const sf::Vector2u background_size = background.getSize();

    const auto scale_x = static_cast<float>(window_size.x) / static_cast<float>(background_size.x);
    const auto scale_y = static_cast<float>(window_size.y) / static_cast<float>(background_size.y);

    background_sprite.setScale(scale_x, scale_y);
    window.draw(background_sprite);
}

void Game::init_bell()
{
    if(!bell_texture.loadFromFile("pictures/bell.png")) { std::cout<< " Unable to load bell\n"; }
    bell_sprite.setTexture(bell_texture);
    bell_sprite.setScale(5.5f, 5.5f);
    bell_sprite.setOrigin(static_cast<float>(bell_texture.getSize().x) / 2,
                          static_cast<float>(bell_texture.getSize().y) / 2);
    const float pos_x = board.get_slot(0,0).get_sprite().getPosition().x;
    const float pos_y = board.get_slot(0,0).get_sprite().getPosition().y;
    bell_sprite.setPosition(pos_x - 1.5f * one_slot_width, pos_y + one_slot_height / 2); // 729,427
    window.draw(bell_sprite);
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