#include "include/headers/game.h"
/*
class Scale{
private:
    int floor; // cat damage trebuie sa fie dat ca talerul balantei sa atinga masa
    int left; // cat damage a dat un player
    int right; // cat damage a dat celalat player
public:
    void check_scale(){
        if(left == floor) {}//win Player2,
        if(right == floor) {}//win Player1
    }
    void moved_by_right(){
        // modifica balanta dupa damage-ul data de jucatorul care pune in dreapta (adica input player 1; NU AI)
        // add damage to right // decrease damage from left
    }
    void moved_by_left(){
        // modifica balanta dupa damage-ul data de jucatorul care pune in stanga (adica player 2 sau AI)
        // add damage to left // decrease damage from right
    }
};
*/

// to do: mai multi operatori de afisare - Check
// to do: la deck suprascris toti operatorii
// to do: board constante pentru nr de linii si nr de coloane - Check
// to do: enum effect pus ori in namespace ori facut enumclass - Check
// to do: schimba numele la get deck si la whose deck - Check
// to do: clean up the logic, see if you can get rid of repetitions.
// to do: move the play game outside the constructor - the constructor does too much, it only needds to build essential - Check
// to do: start working on the logic of sacrificing, taking and dealing damage.

int main() {
    Game game;
    game.play_game();
    return 0;
}

// slot.png has 154 width, 226 height
