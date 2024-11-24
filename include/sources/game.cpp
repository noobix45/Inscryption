#include "headers/game.h"
#include "headers/cards_factory.h"
#include <iostream>
//#include "headers/font_manager.h"

Game::Game() :
squirrel_pile(1, cardsFactory.getPreDef()),
normal_pile(2, cardsFactory.getPreDef()),
deck1(1, cardsFactory.getPreDef()),
deck2(2, cardsFactory.getPreDef()),
//player1{"Player1", 1, font_manager_.getFont()},
//player2{"Player2", 2, font_manager_.getFont()},
window(sf::VideoMode::getDesktopMode(), "My Window", sf::Style::Fullscreen)
{
    std::cout<<"Game Constructor"<<std::endl;
    play_game();
}

Game::~Game()
{
    std::cout << "Deck1 destroyed! - from game destructor\n";
    std::cout << "Deck2 destroyed! - from game destructor\n";
    std::cout << "Game destroyed!\n";
}


void Game::play_game()
{
    //player1.make_deck(); //deck are made upon construction now
    //player2.make_deck();
    auto [fst1, snd1] = Deck::get_start_positions(window, 1);
    auto [fst2, snd2] = Deck::get_start_positions(window, 2);
    Card selected_card; // la momentul inceperii nicio carte nu este selectata
    bool card_selected = false;
    int current_phase = 0; // 0 means draw phase
    int current_player = 1;
    init_background();
    init_bell();

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
                // daca se da un click tratez cazurile
                if(event.type ==  sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (current_phase == 0) // draw phase
                    {
                        if (pile_clicked(mousePos) == 1) // returneaza pile_id
                        {
                            if (current_player == 1)
                                deck1.draw_card(squirrel_pile);
                            else
                                deck2.draw_card(squirrel_pile);
                            current_phase = 1; // playing phase
                        } else if (pile_clicked(mousePos) == 2)
                        {
                            if (current_player == 1)
                                deck1.draw_card(normal_pile);
                            else
                                deck2.draw_card(normal_pile);
                            current_phase = 1; // playing phase
                        }
                    } else // e playing phase
                    {
                        if (!card_selected)
                        {
                            //inainte de selectie un player va fi obligat sa traga o carte din pile
                            //am selectat o carte daca, dupa ce am mers prin deck, selected card !=nullptr
                            if (current_player == 1)
                            {
                                if (has_selected(mousePos, 1, selected_card)) { card_selected = true; }
                            } else
                            {
                                if (has_selected(mousePos, 2, selected_card)) { card_selected = true; }
                            }
                            //if (selected_card != nullptr) { card_selected = true; }
                        }
                        // la urmatorul click cu o carte selectata vreau sa verific daca am dat click in board
                        // daca am dat click in board pun cartea si o sterg din deck
                        // apoi orice ar fi selected card = nullptr
                        else // meaning a card is currently selected
                        {
                            /*
                            std::cout<<"from event cu card non null: "<<*selected_card;  // debugg
                            std::cout << "Mouse pos before placing: " << mousePos.x << ", " << mousePos.y << "\n";*/
                            // functia returneaza daca am plasat sau nu o carte, ca sa stiu daca o sterg din deck sau nu
                            if (current_player == 1)
                            {
                                if (place_in_board(mousePos, 1, selected_card))// delete from deck; // cauta selcted card in deck si sterge-o de acolo
                                    delete_from_deck(deck1.get_all(), selected_card);
                                // debugg std::cout<<"deleted from deck: "<<*selected_card;
                                //debug selected_card.on_click_unselect();
                                //debug card_selected = false;

                                selected_card.on_click_unselect();
                                card_selected = false;
                            } else
                            {
                                if (place_in_board(mousePos, 0, selected_card)) // player 2 foloseste randul 0 din board
                                    delete_from_deck(deck2.get_all(), selected_card);
                                selected_card.on_click_unselect();
                                card_selected = false;
                            }
                        }
                        if (ring_bell(mousePos))
                        {
                            current_phase = 0; // inapoi la drawing phase
                            current_player = (current_player == 1) ? 2 : 1;
                        }
                    }
                }
        }
        window.clear();
        window.draw(background_sprite);

        bell_sprite.setScale(5.5f, 5.5f);
        bell_sprite.setOrigin(static_cast<float>(bell_texture.getSize().x) / 2,
                              static_cast<float>(bell_texture.getSize().y) / 2);
        float pos_x = board.get_slot(0,0).get_sprite().getPosition().x;
        float pos_y = board.get_slot(0, 0).get_sprite().getPosition().y;
        bell_sprite.setPosition(pos_x - 1.5f * one_slot_width, pos_y + one_slot_height / 2); // 729,427
        window.draw(bell_sprite);

        pos_x = board.get_slot(0, 3).get_sprite().getPosition().x;
        pos_y = board.get_slot(0,3).get_sprite().getPosition().y;
        if (squirrel_pile.get_size() > 0)
            squirrel_pile.draw(window, pos_x + 2 * one_slot_width, pos_y - 10);

        pos_x = board.get_slot(1, 3).get_sprite().getPosition().x;
        pos_y = board.get_slot(1, 3).get_sprite().getPosition().y;
        if (normal_pile.get_size() > 0)
            normal_pile.draw(window, pos_x + 2 * one_slot_width, pos_y + 5);
        board.get_offset(window, one_slot_width, one_slot_height);
        board.draw(window);
        //std::cout << "Center of last slot: "<< board.get_slot(1,3)->get_sprite().getPosition().x << std::endl;
        //std::cout << "Center of last slot: "<< board.get_slot(1,3)->get_sprite().getPosition().y << std::endl;

        // Card card(card_factory(CardType::Adder,font_manager_.getFont()));
        // board.place_card(&card,0,0);

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 4; j++)
                if (!board.get_slot(i, j).is_empty())
                    board.get_slot(i, j).update(window);
        //board.remove_card(1,2); // this might not work after the changes
        deck1.deck_draw(window,fst1,snd1);
        deck2.deck_draw(window,fst2,snd2);

        window.display();
    }
}

bool Game::has_selected(const sf::Vector2i mousePos, const int id, Card &selected_card)
{
    if (id == 1)
    {
        for (Card &c: deck1.get_all())
        {
            if (!c.is_clicked() && c.get_sprite().getGlobalBounds().contains(
                    static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
            {
                c.on_click_select();
                selected_card = c;
                return true;
            }
        }
    } else if (id == 2)
    {
        for (Card &c: deck2.get_all())
        {
            if (!c.is_clicked() && c.get_sprite().getGlobalBounds().contains(
                    static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
            {
                c.on_click_select();
                selected_card = c;
                return true;
            }
        }
    }
    return false;
}

bool Game::place_in_board(const sf::Vector2i mousePos, const int rand, Card &selected_card)
{
    for (int j = 0; j < 4; j++)
    {
        if (board.get_slot(rand, j).get_sprite().getGlobalBounds().
            contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            if (board.get_slot(rand, j).is_empty())
            {
                selected_card.on_click_unselect();
                board.place_card(&selected_card, rand, j);
                return true;
            }
        }
    }
    return false;
}

void Game::delete_from_deck(std::vector<Card> &deck, const Card &c)
{
    if (const auto f = std::ranges::find(deck, c); f != deck.end())
    {
        deck.erase(f);
        deck.shrink_to_fit();
        std::cout << "Deleted: " << c.get_name() << "from deck" << std::endl;
    } else { std::cout << "No such card" << std::endl; }
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
    if (!bell_texture.loadFromFile("pictures/bell.png")) { std::cout<< " Unable to load bell\n"; }
    bell_sprite.setTexture(bell_texture);
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