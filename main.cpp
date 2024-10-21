#include <iostream>
#include <string>
#include "include/headers/cards.h"
#include "include/headers/cards_factory.h"
#include "include/headers/player.h"
#include <vector>
#include <time.h> // pentru generare de carti random in pile si in deck-ul jucatorului

///to do: get_deck function, ring bell function

class Board{
private:
   Card board[2][4]; // original board[3][4]
public:
    Board(){}
    void card_placed(){}
    void card_dead(){}
    void move_on(){} //avanseaza cartile la urmatoarea tura ca sa intre in joc
    //daca sunt 2 jucatori pe acelasi ecran board [4][4] fiecare cu linie de avans
};

class Pile{ // se vor defini doua pile-uri una cu carti, alta cu veverite
private:
    int number_of_cards; // cate carti sunt in pile
    std::vector <Card> pile; // un fel de stiva se ia mereu ultima carte (varf) si se scade numarul de carti cu 1
    void remove_card(){}
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

/////// to do: create the piles of cards and squirrels.
// modify the draw card function of a player to get the card from a specific pile. argument of the functino will be of class type pile

////to do: operator << pentru toate clasele
// operator = copy si drestructor pentru o clasa

int main() {
    srand(time(0));
    int r = rand()%4;
    Card c = card_factory(CardType(r));
    std::cout<<"Random card test: \n";
    std::cout<<c;
    std::cout<<"info about a player: \n";
    Player player1{"Player1",1};
    std::cout<<player1;
    player1.draw_card(card_factory(CardType::Adder));
    std::cout<<player1;
    return 0;
}

