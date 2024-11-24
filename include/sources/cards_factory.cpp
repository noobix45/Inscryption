#include "headers/cards_factory.h"

#include <iostream>

void CardsFactory::loadResources()
{
    sf::Texture texture;
    if(texture.loadFromFile("pictures/squirrel.png"))
    {
        textures["Squirrel"] = texture;
    }
    else
    {
        std::cout<<"Failed to load squirrel.png"<<std::endl;
    }
    if(texture.loadFromFile("pictures/adder.png"))
    {
        textures["Adder"] = texture;
    }
    else
    {
        std::cout<<"Failed to load adder.png"<<std::endl;
    }
    if(texture.loadFromFile("pictures/beaver.png"))
    {
        textures["Beaver"] = texture;
    }
    else
    {
        std::cout<<"Failed to load beaver.png"<<std::endl;
    }
    if(texture.loadFromFile("pictures/mantis.png"))
    {
        textures["Mantis"] = texture;
    }
    else
    {
        std::cout<<"Failed to load mantis.png"<<std::endl;
    }
    if(texture.loadFromFile("pictures/bullfrog.png"))
    {
        textures["Bullfrog"] = texture;
    }
    else
    {
        std::cout<<"Failed to load bullfrog.png"<<std::endl;
    }
    if(texture.loadFromFile("pictures/wolf.png"))
    {
        textures["Wolf"] = texture;
    }
    else
    {
        std::cout<<"Failed to load wolf.png"<<std::endl;
    }
    if(!font.loadFromFile("heaviwei.ttf"))
    {
        std::cout<<"Failed to load heaviwei.ttf"<<std::endl;
    }
}

CardsFactory::CardsFactory()
{
    std::cout << "Loading resources...\n";
    loadResources();
    std::cout << "Loading finished\n";

    predefined_cards = {
        new Card("Squirrel", 1, 0, 0, Effect::none, textures["Squirrel"], font),
        new Card("Adder", 1, 1, 2, Effect::poison, textures["Adder"], font),
        new Card("Wolf", 2, 3, 2, Effect::none, textures["Wolf"], font),
        new Card("Beaver", 2, 1, 2, Effect::dam, textures["Beaver"], font),
        new Card("Mantis", 1, 1, 1, Effect::bifurcated, textures["Mantis"], font),
        new Card("Bullfrog", 2, 1, 1, Effect::air_defence, textures["Bullfrog"], font)
    };

    std::cout << "Predefined cards created\n";
}

CardsFactory::~CardsFactory() {
    // Clean up dynamically allocated cards
    for (const Card* card : predefined_cards) {
        delete card;
    }
    std::cout<<"Predefined cards destroyed\n";
}


const std::vector<Card*>& CardsFactory::getPreDef()
{
    return predefined_cards;
}
