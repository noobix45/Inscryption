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
    Card("Squirrel",1,0,0,none,textures["Squirrel"],font),
        Card("Adder",1,1,2,poison,textures["Adder"],font),
        Card("Wolf",2,3,2,none,textures["Wolf"],font),
        Card("Beaver",2,1,2,dam,textures["Beaver"],font),
        Card("Mantis",1,1,1,bifurcated,textures["Mantis"],font),
        Card("Bullfrog",2,1,1,air_defence,textures["Bullfrog"],font)
    };
    std::cout<<"Predefined cards created\n";
}

CardsFactory::~CardsFactory()
{
    std::cout<<"Predefined cards destroyed\n";
}


const std::vector<Card>& CardsFactory::getPreDef()
{
    return predefined_cards;
}


/*
case CardType::Squirrel:
            return {"pictures/squirrel.png", "Squirrel", 1, 0, 0, none,font};
        case CardType::Adder:
            return {"pictures/adder.png", "Adder", 1, 1, 2, poison,font};
        case CardType::Wolf:
            return {"pictures/wolf.png", "Wolf", 2, 3, 2, none,font};
        case CardType::Beaver:
            return {"pictures/beaver.png", "Beaver", 2, 1, 2, dam,font};
        case CardType::Mantis:
            return {"pictures/mantis.png", "Mantis", 1, 1, 1, bifurcated,font};
        case CardType::Bullfrog:
            return {"pictures/bullfrog.png", "Bullfrog", 2, 1, 1, air_defence,font};
        default:
            return {};
 */
