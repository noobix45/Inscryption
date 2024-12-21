#ifndef SCALES_H
#define SCALES_H
#include <SFML/Graphics.hpp>

class Scales
{
public:
    Scales() = default;
    explicit Scales(const sf::Font&);
    sf::Sprite& getSprite();
    void setStartPos(const float &,const float &);
    void draw_scales(sf::RenderWindow&) const;
    void make_scales();
    void update(int,int);
    bool winner() const;

private:
    sf::Texture counter_texture; // textura si sprite pentru counter
    sf::Sprite counter_sprite;
    sf::Font font;
    std::vector<sf::Text> numbers; // vector cu numere
    float start_x=0;
    float start_y=0;
    int counter_pos=5;

    void init_textures();
};


#endif //SCALES_H
