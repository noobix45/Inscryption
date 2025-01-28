#ifndef END_SCREEN_H
#define END_SCREEN_H
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "singleton.h"

class EndScreen : public Singleton<EndScreen>
{
    sf::RenderWindow& window;
    const sf::Font& font;
    int player_id=0;
    sf::Text winner_text; // text pentru castigator
    sf::Text play_again_text; //text pentru interbare
    sf::Text no_button; // buton pentru close game
    sf::Text yes_button; // buton pentru restart
    sf::Color text_color=sf::Color::Red;
    bool restart=false;
    void init_text();
protected:
    // acelasi window, font din fontmanager si player_id-ul castigatorului
    EndScreen(sf::RenderWindow& window, const sf::Font& font);
public:
    void render() const; // afiseaza
    void handleClick(const sf::RenderWindow& window);
    bool gameStatus() const;
    void set_player_id(int);
    //true = yes, restart game
    //false = no, close window, stop program
};

#endif //END_SCREEN_H
