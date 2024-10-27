#include <iostream>
#include <string>
#include "include/headers/cards.h"
#include "include/headers/cards_factory.h"
#include "include/headers/player.h"
#include <time.h> // pentru generare de carti random in pile si in deck-ul jucatorului

///to do: constructor de mutare, operator egal, game logic

class Board{
private:
   Card board[2][4]; // original board[3][4]
public:
    Board() = default;
    void card_placed(){}
    void card_dead(){}
    void move_on(){} //avanseaza cartile la urmatoarea tura ca sa intre in joc
    //daca sunt 2 jucatori pe acelasi ecran board [4][4] fiecare cu linie de avans
};

class Scale{
private:
    int floor; // cat damage trebuie sa fie dat ca talerul balantei sa atinga masa
    int left; // cat damage a dat un player
    int right; // cat damage a dat celalat player
public:
    void check_scale(){
        if(left == floor) {}//win Player2, AI
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

    // void game(){
    //     Board board; // definesc tabla de joc o matrice de 2 pe 4 de tip card
    //     Player player1{"Player1",1};
    //     Player player2{"Player2",2};
    //     Scale scale;
    //     Pile squirell_pile;
    //     Pile draw_pile;
    // };

int main() {
    srand(time(nullptr));
    int r = rand()%4;
    Card c = card_factory(CardType(r));
    std::cout<<"Random card test: \n";
    std::cout<<c;

    std::cout<<"info about a player: \n";
    Player player1{"Player1",1};
    std::cout<<player1;

    Pile Squirrel_pile(10,1); // 10 cards of type squirrel
    std::cout<<Squirrel_pile;
    Pile Normal_pile(6,2); // 6 cards of anyother type than squirell

    player1.draw_card(Squirrel_pile);
    player1.draw_card(Normal_pile);
    std::cout<<player1;

    std::cout<<Normal_pile;
    std::cout<<Squirrel_pile;

    return 0;
}

// Q: what is [[nodiscard]]

