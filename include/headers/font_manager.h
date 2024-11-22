#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H
#include <SFML/Graphics.hpp>

class FontManager
{
    sf::Font font;
public:
    explicit FontManager(const std::string &filePath);
    sf::Font& getFont();
};

#endif
