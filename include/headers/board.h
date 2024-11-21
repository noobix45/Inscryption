#ifndef BOARD_H
#define BOARD_H
#include "slot.h"
#include <array>
#include <SFML/Graphics.hpp>

class Board
{
    std::array<std::array<Slot*, 4>, 2> board;
    unsigned int board_width = 0;
    unsigned int board_height = 0;
    float offset_x = 0;
    float offset_y = 0;

public:
    Board();

    ~Board();

    void draw(sf::RenderWindow &window) const; // to elimiate from board
    void place_card(Card *, int, int) const;

    void remove_card(int, int) const;

    void get_offset(const sf::RenderWindow &window, const unsigned int &, const unsigned int &);

    [[nodiscard]] Slot* get_slot(const unsigned int &, const unsigned int &) const;

};

#endif //BOARD_H