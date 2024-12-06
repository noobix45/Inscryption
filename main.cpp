#include "headers/game.h"
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

// to do: finish the logic, cards do damage
// to do: inside the function handle_actions() in gmae.cpp


// to do: tema2 - exceptii si derivate pentru efect fiecare carte devine o derivata

int main() {
    Game game;
    game.play_game();
    return 0;
}

