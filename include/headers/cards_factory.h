#ifndef CARDS_FACTORY_H
#define CARDS_FACTORY_H
#include "cards.h"

#ifndef num_of_types
#define num_of_types 5   // cate carti pot exista - squirrel
#endif

class CardsFactory
{
public:
    CardsFactory();
    ~CardsFactory();
    const std::vector<Card*>& getPreDef();
private:
    std::vector<Card*> predefined_cards;
    std::map<std::string, sf::Texture> textures;
    sf::Font font;
    void loadResources();
};

#endif