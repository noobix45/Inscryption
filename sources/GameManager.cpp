#include "GameManager.h"

GameManager::GameManager() : window(sf::VideoMode::getDesktopMode(), "My Window", sf::Style::Fullscreen),
                            fontManager(init_FontManager()),game(init_Game()),endScreen(init_EndScreen())
{
    window.setFramerateLimit(60);
}

FontManager &GameManager::init_FontManager()
{
    FontManager::init();
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

void GameManager::run() const
{
    // aici vine logica pentru joc
    // dupa ce se termina game afiseaza endscreen
    // restart daca tebuie
    game.play_game();
}
