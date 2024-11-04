#ifndef BOARD_H
#define BOARD_H
#include "slot.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Board
{
    std::vector<std::vector<Slot> > board;
    unsigned int one_slot_width = 0;
    unsigned int one_slot_height = 0;
    unsigned int frame_width = 0;
    unsigned int frame_height = 0;
    unsigned int board_width = 0;
    unsigned int board_height = 0;
    float offset_x = 0;
    float offset_y = 0;

public:
    Board();

    void draw(sf::RenderWindow &window); // to elimiate from board
    void place_card(Card *, int, int);

    void remove_card(int, int);

    void get_offset(const sf::RenderWindow &window, const unsigned int &, const unsigned int &);
};

#endif //BOARD_H
