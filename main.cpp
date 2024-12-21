#include <iostream>

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

// to do: fix win logic
// to do: dupa comit separat cu inca o derivata

int main() {
    try
    {
        Game game;
        game.play_game();
    } catch (const Font_error &err) { std::cout << err.what() << std::endl; }
    catch (const Texture_error &err) { std::cout << err.what() << std::endl; }
    return 0;
}

