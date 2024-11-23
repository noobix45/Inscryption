#ifndef BOARD_H
#define BOARD_H
#include "slot.h"
#include <array>
#include <SFML/Graphics.hpp>


class Board
{
    static Slot predefined_slot;
    std::array<std::array<Slot,4>,2> board;
    unsigned int board_width = 0;
    unsigned int board_height = 0;
    float offset_x = 0;
    float offset_y = 0;
    sf::Texture texture;

public:
    static void initializePredefinedSlot(const sf::Texture &texture);

    Board();
    ~Board();
    void draw(sf::RenderWindow &window); // to elimiate from board
    void place_card(Card *, int, int);

    void remove_card(int, int);

    void get_offset(const sf::RenderWindow &window, const unsigned int &, const unsigned int &);

    Slot& get_slot(const unsigned int &, const unsigned int &);

    void texture_init();
};

#endif //BOARD_H