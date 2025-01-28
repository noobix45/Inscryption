#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "end_screen.h"
#include "game.h"
#include "SFML/Graphics/RenderWindow.hpp"

class GameManager
{
    sf::RenderWindow window;
    FontManager& fontManager;
    Game &game;
    EndScreen &endScreen;

    static FontManager& init_FontManager();
    Game& init_Game();
    EndScreen& init_EndScreen();
public:
    GameManager();
    ~GameManager();
    void run() const;
};

#endif //GAMEMANAGER_H
