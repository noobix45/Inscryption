#include "headers/pile.h"
#include "headers/cards_factory.h"
#include "headers/slot.h"
#include <random>
#include <iostream>
#define pile_size 5

Pile::Pile(const int id, const std::vector<Card> &predefined) : pile_id{id}
{
    std::cout << "Creating new pile. Calling Make pile function..." << std::endl;
    make_pile(predefined);
    std::cout << "Calling pile init textures...\n";
    init_texture();
    std::cout << "Pile " << pile_id << " pile created\n";
}

Pile::~Pile()
{
    std::cout << "Pile " << pile_id << " destroyed" << std::endl;
}


void Pile::make_pile(const std::vector<Card> &predefined)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, num_of_types);
    if (pile_id == 1)
        for (int i = 0; i < pile_size; i++) { pile.push(predefined[0]); }
    else
    {
        for (int i = 0; i < pile_size; i++)
        {
            const int r = dis(gen); // 1 2 3... possible outcomes
            pile.push(predefined[r]);
        }
    }
}

Card Pile::get_card() // get top card, remove top
{
    Card card = pile.top();
    pile.pop();
    return card;
}

const Card& Pile::get_top() // asta doar ia info despre o carte fara sa o scoata din pile
{
    Card &card = pile.top();
    return card;
}

std::ostream &operator<<(std::ostream &out, Pile &pile)
{
    if (pile.pile_id == 1)
    {
        // squirell
        out << "There are " << pile.pile.size() << " cards of type " << pile.get_top().get_name() << "\n";
        return out;
    } else // other cards
    {
        out << "You shouldn't peek ;) \n";
        return out;
    }
}

void Pile::init_texture()
{

    if(pile_id == 1)
    {
        if (!pile_texture.loadFromFile("pictures/squirrel_back.png"))
        {
            // incarca textura
            std::cout << "Error in loading card back texture\n";
            // maybe throw exception and stop launch of program??
        }
        pile_sprite.setPosition(1191 + 2*one_slot_width,420); // intial 427
    }
    else
    {
        if(!pile_texture.loadFromFile("pictures/common_back.png"))
        {
            std::cout << "Error in loading card back texture\n";
        }
        pile_sprite.setPosition(1191 + 2*one_slot_width,660); //initial 653
    }
    pile_sprite.setTexture(pile_texture);
    pile_sprite.setOrigin(static_cast<float>(pile_texture.getSize().x) / 2, static_cast<float>(pile_texture.getSize().y) / 2);
    scale();
}

void Pile::scale()
{
    const sf::Vector2u textureSize = pile_texture.getSize();
    const float scaleX = one_slot_width / static_cast<float>(textureSize.x);
    const float scaleY = one_slot_height / static_cast<float>(textureSize.y);
    pile_sprite.setScale(scaleX, scaleY);
}

void Pile::draw(sf::RenderWindow &window,const float &x, const float &y)
{
    pile_sprite.setPosition(x, y);
    window.draw(pile_sprite);
}

bool Pile::is_clicked(const sf::Vector2i mousePos) const {
    return pile_sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

sf::Sprite& Pile::get_sprite()
{
    return pile_sprite;
}

int Pile::get_size() const { return static_cast<int>(pile.size()); }
