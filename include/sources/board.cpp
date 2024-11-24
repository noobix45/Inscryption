#include "headers/board.h"
#include <iostream>


Board::Board()  : board()
{
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            board[i][j] = new Slot();
        }
    }
    std::cout << "board created" << std::endl;
}

Board::~Board()
{
    for (int i = 0; i < lin; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            if (board[i][j]->get_card() != nullptr)
            {
                std::cout << "deleting " << board[i][j]->get_card()->get_name() << "from slot\n";
                delete board[i][j]->get_card();
            }
            delete board[i][j];
        }
    }
    std::cout << "Board Destroyed" << std::endl;
    std::cout.flush();
}

/*
void Board::setUp() const
{
    for (int i = 0; i < lin; ++i)
    {
        for (int j = 0; j < col; ++j)
        {

            board[i][j]->setPos(x, y);
        }
    }
}*/

void Board::draw(sf::RenderWindow &window) const
{
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            board[i][j]->textures_init();
            auto x = offset_x + static_cast<float>(j * one_slot_width);
            auto y = offset_y + static_cast<float>(i * one_slot_height);
            board[i][j]->draw(window,x,y);
        }
    }
}

void Board::place_card(Card *card, const int l, const int c) const
{
    if (l < 0 || l > lin || c < 0 || c > col)
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

void Board::get_offset(const sf::RenderWindow &window, const unsigned int &slot_width, const unsigned int &slot_height)
{
    board_width = slot_width * col;
    board_height = slot_height * lin;

    const sf::Vector2u size = window.getSize();
    const auto window_x = static_cast<float>(size.x);
    const auto window_y = static_cast<float>(size.y);

    offset_x = (window_x - static_cast<float>(board_width)) / 2;
    offset_y = (window_y - static_cast<float>(board_height)) / 2;
}

Slot *Board::get_slot(const unsigned int &i, const unsigned int &j) const { return board[i][j]; }

std::ostream &operator<<(std::ostream &os, const Board &board)
{
    for (int i = 0; i < lin; ++i)
        for (int j = 0; j < col; ++j) { os << board.get_slot(i, j); }
    return os;
}