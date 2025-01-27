#include <iostream>
#include "end_screen.h"
#include "exceptii.h"
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
    /*
     *merge dar daca apas escape sa inchid window spune

    *AL lib: (EE) alc_cleanup: 1 device not closed

    Process finished with exit code 0

 si nici nu se apeleaza destructori, chestia cu Al lib apare imediat dupa ultimul constructor
*/
    try
    {

        //sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "My Window", sf::Style::Fullscreen);
        //Game::init(window);
        Game::init(); // daca scot Game::init() - segmentation fault
        Game& game= Game::getInstance();
        game.play_game();
        //FontManager::init();
        //const FontManager& fm = FontManager::getInstance();
        //std::cout<<fm;
    } catch (const FontError &err) { std::cout << err.what() << std::endl; }
    catch (const TextureError &err) { std::cout << err.what() << std::endl; }
    catch (const SoundError &err) {std::cout << err.what() << std::endl; }


/////////// merge cu exit code 0
/*
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Inscryption", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile("heaviwei.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }
    EndScreen::init(window,font,1);
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
    }*/
    return 0;
}

