#include "scales.h"
#include "constante.h"
//#include <iostream>

#include "exceptii.h"

Scales::Scales(const sf::Font& font_) : font(font_)
{
    init_textures();
}

sf::Sprite& Scales::getSprite()
{
    return counter_sprite;
}

void Scales::setStartPos(const float &x, const float &y)
{
    start_x = x;
    start_y = y;
}

void Scales::init_textures()
{
    if(!counter_texture.loadFromFile("pictures/counter.png"))
    {
        throw Texture_error("Scales","pictures/counter.png");
    }
    counter_sprite.setTexture(counter_texture);
    counter_sprite.setOrigin(static_cast<float>(counter_texture.getSize().x),
        static_cast<float>(counter_texture.getSize().y) / 2);
}

void Scales::make_scales()
{
    const std::vector<int> v  ={5,4,3,2,1,0,1,2,3,4,5};
    numbers.resize(v.size());
    for(int i = 0; i < static_cast<int>(v.size()); i++)
    {
        numbers[i].setFont(font);
        numbers[i].setString(std::to_string(v[i]));
        numbers[i].setCharacterSize(60.0f);
        numbers[i].setFillColor(sf::Color::White);
        numbers[i].setOrigin(numbers[i].getGlobalBounds().width / 2, numbers[i].getGlobalBounds().height / 2);
        numbers[i].setPosition(start_x, start_y - SPACING*static_cast<float>(i));
    }
    counter_sprite.setPosition(numbers[counter_pos].getPosition().x, numbers[counter_pos].getPosition().y);
}

void Scales::update(const int m,const int direction)
{
    //std::cout << "\n\n\nCurrent counter pos: "<<counter_pos<<"\n";
    if(direction==0)
        counter_pos+=m;
    else if(direction==1)
        counter_pos-=m;
    if(counter_pos > 10)
        counter_sprite.setPosition(numbers[10].getPosition().x, numbers[10].getPosition().y);
    else if(counter_pos < 0)
        counter_sprite.setPosition(numbers[0].getPosition().x, numbers[0].getPosition().y);
    else
        counter_sprite.setPosition(numbers[counter_pos].getPosition().x, numbers[counter_pos].getPosition().y);
    //std::cout<<"Counter pos after update: "<<counter_pos<<"\n\n\n";
}

bool Scales::winner() const
{
    if(counter_pos >= 10 || counter_pos <= 0)
        return true;
    return false;
}

void Scales::draw_scales(sf::RenderWindow &window) const
{
    for(const auto & number : numbers)
    {
        window.draw(number);
    }
}
