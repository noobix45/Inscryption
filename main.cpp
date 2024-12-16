//#include <iostream>

#include "headers/game.h"

//#include "cards_factory.h"
//#include <iostream>

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



/*
 *tip1 - efecte care se produc odata cu deal damage: posion, bifurcated, air
 *tip2 - efecte care se plaseaza pe slot la plasarea cartii in board
 *          si care se termina la stergerea derivatei respective in destructor
 *      pentru astea in update board slotul va avea o proprietate de add/remove damage/hp
 *alte efecte to be continued
 *
 *
 *Player isi joaca cartile apoi suna suna clopotelul, cartile lui actioneaza
 *Atunci cand un player plaseaza o carte, efectul cartii respective se produce daca are efect de tip2
*/
//whenever a card dies it give 1 bone to the player it belongs to
/*
 *SAU
 *cartile cu tip efect 1 for avea doar functia action pentru damage si posibil effect
 *cartile cu tip efect 2 si poate 3 vor da damage in action si for face downcast ca sa isi faca efectul
 */

///to do!!!! op= copy pentru slot!!! tine pointeri deci e pentru tema2
// to do: add beaver and option for can_sacrifice;
// to do: divide the card class into action on attack and action on place - > slot will have buffs and nerfs
// to do: tema2 - downcast si exceptii

int main() {
    Game game;
    game.play_game();

    return 0;
}

