#include <iostream>
#include "headers/font_manager.h"

FontManager::FontManager(const std::string &filePath)
{
    if (!font.loadFromFile(filePath)) { std::cout << "Error loading font" << std::endl; }
}

sf::Font &FontManager::getFont() { return font; }

std::ostream & operator<<(std::ostream &os, const FontManager &fontManager)
{
    os<<"Font Name: "<<fontManager.font.getInfo().family<<std::endl;
    return os;
}
