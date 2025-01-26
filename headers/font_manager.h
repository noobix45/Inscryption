#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H
#include <SFML/Graphics.hpp>

#include "singleton.h"

class FontManager : public Singleton<FontManager>
{
    sf::Font font;
protected:
     FontManager();
public:
    sf::Font& getFont();
    friend std::ostream& operator<<(std::ostream& os, const FontManager& fontManager);
};

#endif
