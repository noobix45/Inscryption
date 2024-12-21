#include <iostream>
#include "font_manager.h"
#include "exceptii.h"

FontManager::FontManager(const std::string &filePath)
{
    std::cout << "loading font...\n";
    if (!font.loadFromFile(filePath)) { throw Font_error(filePath); }
    std::cout << "font loaded\n";
}

sf::Font &FontManager::getFont() { return font; }

std::ostream & operator<<(std::ostream &os, const FontManager &fontManager)
{
    os<<"Font Name: "<<fontManager.font.getInfo().family<<std::endl;
    return os;
}

FontManager& FontManager::operator=(const FontManager &other)
= default;