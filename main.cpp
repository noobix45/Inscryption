#include <iostream>
#include "end_screen.h"
//#include "exceptii.h"
#include "headers/game.h"

/* copy swap pentru deck si pile, se schimba clasa pentru test de pile
sf::Font font;
font.loadFromFile("heaviwei.ttf");
Deck p1(3,font);
std::cout << "after p1 construct\n";
Deck p2(p1);
std::cout << "after p2 copy\n";
Deck p3;
p3 = p2;
std::cout << "after p3=p2\n";
*/

/* slot op= copy test
sf::Font font;
font.loadFromFile("heaviwei.ttf");
std::cout << "creating card in main\n";
Card* a = new Adder(font);
std::cout<<"creating first slot\n";
Slot s1;
std::cout<<"placing a in s1\n";
s1.place_card(a);
std::cout << "after p1 construct\n";
Slot s2(s1);
std::cout << "after p2 copy\n";
Slot s3;
s3 = s2;
std::cout << s3;
std::cout << "after p3=p2\n";
*/

// to do: ecran de final
// to do: optiune de restart
// to do: fisier.txt numar de coloane in scales condigurabil
//scalare in functie de numar ca sa incapa in acelasi spatiu


int main() {
/*    try
    {
        Game& game= Game::getInstance();
        Game& game2 = Game::getInstance();
        game.play_game();
        std::cout << "Address of game: " << &game << std::endl;
        std::cout << "Address of game2: " << &game2 << std::endl;
    } catch (const FontError &err) { std::cout << err.what() << std::endl; }
    catch (const TextureError &err) { std::cout << err.what() << std::endl; }
    catch (const SoundError &err) {std::cout << err.what() << std::endl; }
*/
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Inscryption", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile("heaviwei.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }
    EndScreen::initialize(window,font,1);
    EndScreen& end_screen = EndScreen::getInstance();
    while (window.isOpen())
    {

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
        }
        window.clear();
        end_screen.render();
        window.display();
    }
    return 0;
}

