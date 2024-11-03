#include "../headers/board.h"

Board::Board() : board(2,std::vector<Slot>(4)){}

void Board::draw(sf::RenderWindow &window) {
    for(int i = 0; i < 2; i++) {
        for(int j=0; j < 4; j++) {
            board[i][j].textures_init();
            auto x = offset_x + static_cast<float>(j*board[0][0].get_slot_width());
            auto y = offset_y + static_cast<float>(i*board[0][0].get_slot_height());
            board[i][j].draw(window,x,y);
        }
    }
}

void Board::place_card(Card *card, const int l, const int c) {
    if(l<0 || l>2 || c<0 ||c>4)
    {
        std::cout<<"Slot is out of bounds\n";
        return;
    }
    if(board[l][c].is_empty() == true) {
        board[l][c].place_card(card);
    }
    else {
        std::cout<<"Slot is already occupied\n";
    }
}

void Board::remove_card(const int l, const int c) {
    if(board[l][c].is_empty() == true) {
        std::cout<<"Slot is already empty\n";
    } else {
        board[l][c].remove_card();
    }
}

void Board::get_offset(const sf::RenderWindow &window,const unsigned int &slot_width, const unsigned int &slot_height) {
    board_width = slot_width * 4;
    board_height = slot_height * 2;

    const sf::Vector2u size = window.getSize();
    const auto window_x = static_cast<float>(size.x);
    const auto window_y = static_cast<float>(size.y);

    offset_x = (window_x - static_cast<float>(board_width))/2;
    offset_y = (window_y - static_cast<float>(board_height))/2;
}