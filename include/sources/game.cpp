#include "../headers/game.h"

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
        Slot *slot = new Slot;
        slot->textures_init();
        board.get_offset(window, slot->get_slot_width(), slot->get_slot_height());
        delete slot;
        board.draw(window);
        window.display();
    }
}

void Game::init_background()
{
    sf::Texture background;
    background.loadFromFile("../include/pictures/woodPlanks_albedo.png");
    sf::Sprite background_sprite;
    background_sprite.setTexture(background);

    sf::Vector2u window_size = window.getSize();
    sf::Vector2u background_size = background.getSize();

    auto scale_x = static_cast<float>(window_size.x) / static_cast<float>(background_size.x);
    auto scale_y = static_cast<float>(window_size.y) / static_cast<float>(background_size.y);

    background_sprite.setScale(scale_x, scale_y);
    window.draw(background_sprite);
}
