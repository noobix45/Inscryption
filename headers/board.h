#ifndef BOARD_H
#define BOARD_H
#include "slot.h"
#include "constante.h"
#include <array>
#include <SFML/Graphics.hpp>

class Player;

class Board
{
    std::array<std::array<Slot *, COL>, LIN> board;
    unsigned int board_width = 0;
    unsigned int board_height = 0;
    float offset_x = 0;
    float offset_y = 0;

public:
    explicit Board(const sf::RenderWindow &window);

    ~Board();

    void place_card(Card *, int, int) const;
    void remove_card(int, int) const;

    [[nodiscard]] Slot *get_slot(const unsigned int &, const unsigned int &) const;

    void update(sf::RenderWindow &window, Player &) const;

    void draw(sf::RenderWindow &window) const; // to elimiate from board

    friend std::ostream& operator<<(std::ostream &os, const Board &board);
};

#endif //BOARD_H