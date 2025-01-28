#include "GameManager.h"

GameManager::GameManager() : window(sf::VideoMode::getDesktopMode(), "My Window", sf::Style::Fullscreen),
                             fontManager(init_FontManager()),game(init_Game()),endScreen(init_EndScreen())
{
    window.setFramerateLimit(60);
}

FontManager &GameManager::init_FontManager()
{
    //FontManager::init();
    return FontManager::getInstance();
}

Game &GameManager::init_Game()
{
    Game::init(window);
    return Game::getInstance();
}


EndScreen &GameManager::init_EndScreen()
{
    EndScreen::init(window,fontManager.getFont());
    return EndScreen::getInstance();
}

GameManager::~GameManager()
{
    FontManager::destroyInstance();
    Game::destroyInstance();
    EndScreen::destroyInstance();
}

void GameManager::run()
{
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape) { window.close(); }
            if (game_is_running)
            {
                gameLoop(event);
            }
            else // endscreen is running
            {
                endScreenLoop(event);
            }
        }
    }
}

void GameManager::gameLoop(const sf::Event& event)
{
    if (const int w = Game::getInstance().check_winner(); w==-1) // game is running
        Game::getInstance().play_game(event);
    else
    {
        game_is_running = false;
        endScreen.set_player_id(w);
    }
}

void GameManager::endScreenLoop(const sf::Event& event)
{
    Game::destroyInstance();

    endScreen.render();
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (const int click = endScreen.handleClick(mousePos); click==1)
        {
            Game::init(window);
            game_is_running = true;
            endScreen.reset();
        }
        else if (click==0)
        {
            window.close();
        } // else do nothing
    }
}

