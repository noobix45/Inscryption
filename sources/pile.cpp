#include "pile.h"
#include "cards_factory.h"
#include "constante.h"
#include <random>
#include <iostream>


Pile::Pile(const int id, const sf::Font &font) : pile_id{id}, font_(font)
{
    make_pile();
    init_texture();
    std::cout << "Pile " << pile_id << " created" << std::endl;
}

Pile::~Pile()
{
    if (pile.empty())
        std::cout << "Pile " << pile_id << " empty" << std::endl;
    else
    {
        while(!pile.empty())
        {
            delete pile.top();
            pile.pop();

        }
        std::cout << "Pile "<<pile_id<<" deleted" << std::endl;
    }

    std::cout.flush();
}

void Pile::make_pile()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(EXCLUDED_TYPES, NUM_OF_TYPES);
    if (this->pile_id == 1)
        for (int i = 0; i < PILE_SIZE; i++) { pile.push(card_factory(CardType::Squirrel,font_)); }
    else
    {
        for (int i = 0; i < PILE_SIZE; i++)
        {
            int r = dis(gen); // 1 2 3... possible outcomes
            pile.push(card_factory(static_cast<CardType>(r),font_));
        }
    }
}

//get top card, remove top
Card *Pile::get_top()
{
    Card *card = pile.top();
    return card;
}
Card *Pile::get_card()
{
    Card *card = pile.top();
    pile.pop();
    return card;
}

bool Pile::is_clicked(const sf::Vector2i mousePos) const {
    return pile_sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

int Pile::get_size() const
{
    return static_cast<int>(pile.size());
}

std::ostream &operator<<(std::ostream &out, Pile &pile)
{
    if (pile.pile_id == 1)
    {
        // squirell
        out << "There are " << pile.pile.size() << " cards of type " << pile.get_top()->get_name() << "\n";
        return out;
    } else // other cards
    {
        out << "There are "<<pile.pile.size() << " cards inside this pile\n";
        std::stack <Card*>temp = pile.pile;
        while (!temp.empty())
        {
            out << temp.top() << "\n";
            temp.pop();
        }
        out << "\nYou shouldn't peek ;) \n";
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
        pile_sprite.setPosition(1191 + 2*ONE_SLOT_WIDTH,420); // intial 427
    }
    else
    {
        if(!pile_texture.loadFromFile("pictures/common_back.png"))
        {
            std::cout << "Error in loading card back texture\n";
        }
        pile_sprite.setPosition(1191 + 2*ONE_SLOT_WIDTH,660); //initial 653
    }
    pile_sprite.setTexture(pile_texture);
    pile_sprite.setOrigin(static_cast<float>(pile_texture.getSize().x) / 2, static_cast<float>(pile_texture.getSize().y) / 2);
    scale();
}

void Pile::scale()
{
    const sf::Vector2u textureSize = pile_texture.getSize();
    const float scaleX = ONE_SLOT_WIDTH / static_cast<float>(textureSize.x);
    const float scaleY = ONE_SLOT_HEIGHT / static_cast<float>(textureSize.y);
    pile_sprite.setScale(scaleX, scaleY);
}

void Pile::setPos(const float &x, const float &y)
{
    pile_sprite.setPosition(x, y);
}



sf::Sprite& Pile::get_sprite()
{
    return pile_sprite;
}

// nu sunt folosite in joc, doar pentru tema 2
// constructor de copiere foloseste op egal

/*
const std::stack<Card *> Pile::getPile() const
{
    return pile;
}

void Pile::customPop()
{
    pile.pop();
}
*/
Pile::Pile(const Pile &other)
{
    std::cout << "Pile copy constructor start\n";

    std::stack<Card*> tempStack;

    std::stack<Card*> reverseStack = other.pile;  // shallow copy
    while (!reverseStack.empty()) {
        tempStack.push(reverseStack.top()->clone());
        reverseStack.pop();
    }

    while (!tempStack.empty()) {
        pile.push(tempStack.top());
        tempStack.pop();
    }

    pile_id = other.pile_id;
    font_ = other.font_;
    pile_texture = other.pile_texture;
    pile_sprite = other.pile_sprite;
    std::cout << "Pile copy constructor end\n";
}

Pile & Pile::operator=(Pile other)
{
    std::cout << "Pile copy assignment operator start\n";
    swap(*this,other);
    std::cout << "Pile copy assignment operator end\n";
    return *this;
}
void swap(Pile &first, Pile &second) noexcept
{
    std::cout<<"swap function start\n";
    using std::swap;
    swap(first.pile,second.pile);
    swap(first.pile_id,second.pile_id);
    swap(first.font_,second.font_);
    swap(first.pile_texture,second.pile_texture);
    swap(first.pile_sprite,second.pile_sprite);
    std::cout<<"swap function end\n";
}