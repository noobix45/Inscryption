#include "board.h"
#include <iostream>

Board::Board(const sf::RenderWindow &window)  : board()
{
    for (int i = 0; i < LIN; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            board[i][j] = new Slot();
        }
    }
    std::cout << "board created" << std::endl;
    board_width = ONE_SLOT_WIDTH * COL;
    board_height = ONE_SLOT_HEIGHT * LIN;

    const sf::Vector2u size = window.getSize();
    const auto window_x = static_cast<float>(size.x);
    const auto window_y = static_cast<float>(size.y);

    offset_x = (window_x - static_cast<float>(board_width)) / 2;
    offset_y = (window_y - static_cast<float>(board_height)) / 2;

    for (int i = 0; i < LIN; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            auto x = offset_x + static_cast<float>(j * ONE_SLOT_WIDTH) + ONE_SLOT_WIDTH/2;
            auto y = offset_y + static_cast<float>(i * ONE_SLOT_HEIGHT) + ONE_SLOT_HEIGHT/2;
            board[i][j]->setPos(x, y);
        }
    }
}

Board::~Board()
{
    for (int i = 0; i < LIN; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            delete board[i][j];
        }
    }
    std::cout << "Board Destroyed" << std::endl;
    std::cout.flush();
}

void Board::place_card(Card *card, const int l, const int c) const
{
    if (l < 0 || l > LIN || c < 0 || c > COL)
    {
        std::cout << "Slot is out of bounds\n";
        return;
    }
    if (board[l][c]->is_empty() == true) { board[l][c]->place_card(card); } else
    {
        //std::cout << "Slot is already occupied\n";
    }
}

void Board::remove_card(const int l, const int c) const
{
    if (board[l][c]->is_empty() == true) { std::cout << "Slot is already empty\n"; } else { board[l][c]->remove_card(); }
}

Slot *Board::get_slot(const unsigned int &i, const unsigned int &j) const { return board[i][j]; }

void Board::update(sf::RenderWindow &window, Player &p) const
{
    for (int i = 0; i < 2; i++) // updateaza cartile din board
        for (int j = 0; j < 4; j++)
            if (!get_slot(i, j)->is_empty())
                get_slot(i, j)->update(window, p);
}


void Board::draw(sf::RenderWindow &window) const
{
    for (int i = 0; i < LIN; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            window.draw(board[i][j]->get_sprite());
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Board &board)
{
    for (int i = 0; i < LIN; ++i)
        for (int j = 0; j < COL; ++j) { os << board.get_slot(i, j); }
    return os;
}