#include "../headers/game.h"
#include "../headers/cards_factory.h"

Game::Game() : squirrel_pile(10, 1),
               normal_pile(6, 2),
               player1{"Player1", 1},
               player2{"Player2", 2},
               window(sf::VideoMode::getDesktopMode(), "Inscryption", sf::Style::Fullscreen) { play_game(); }

void Game::play_game()
{
    //la inceputul turei unui jucator, acesta trebuie sa traga o carte, apoi poate sa joace oricate carti din deck.
    //Cand considera ca si-a terminat tura apasa pe clopotel.

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape) { window.close(); }
        }
        window.clear();

        init_background();
        board.get_offset(window, one_slot_width, one_slot_height);
        board.draw(window);

        Card c1 = card_factory(CardType::Adder);
        Card c2 = card_factory(CardType::Squirrel);
        Card c3 = card_factory(CardType::Stinkbug);
        board.place_card(&c1,1,2);
        board.place_card(&c2,0,2);
        board.place_card(&c3,0,0);
        for(int i=0;i<2;i++)
            for(int j=0;j<4;j++)
            if(!board.get_slot(i, j).is_empty())
                board.get_slot(i, j).update(window);
        //board.remove_card(1,2);
        window.display();
    }
}

void Game::init_background()
{
    sf::Texture background;
    background.loadFromFile("../include/pictures/woodPlanks_albedo.png");
    sf::Sprite background_sprite;
    background_sprite.setTexture(background);

    const sf::Vector2u window_size = window.getSize();
    const sf::Vector2u background_size = background.getSize();

    const auto scale_x = static_cast<float>(window_size.x) / static_cast<float>(background_size.x);
    const auto scale_y = static_cast<float>(window_size.y) / static_cast<float>(background_size.y);

    background_sprite.setScale(scale_x, scale_y);
    window.draw(background_sprite);
}
