#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "end_screen.h"
#include "game.h"
#include "SFML/Graphics/RenderWindow.hpp"

class GameManager : public Singleton<GameManager>
{
    sf::RenderWindow window;
    FontManager& fontManager;
    Game &game;
    EndScreen &endScreen;
    bool game_is_running = true;

    static FontManager& init_FontManager();
    Game& init_Game();
    EndScreen& init_EndScreen();
    void gameLoop(const sf::Event& event);
    void endScreenLoop(const sf::Event& event);
public:
    GameManager();
    ~GameManager();
    void run();
};

#endif //GAMEMANAGER_H
