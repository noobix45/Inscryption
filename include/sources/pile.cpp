#include "../headers/pile.h"
#include "../headers/cards_factory.h"
#include <random>
#define pile_size 20

Pile::Pile(const int n, const int id) : number_of_cards{n}, pile_id{id} { get_pile(); }

void Pile::get_pile()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, num_of_types);
    if (this->pile_id == 1)
        for (int i = 0; i < pile_size; i++) { pile.push(new Card(card_factory(CardType::Squirrel))); }
    else
    {
        for (int i = 0; i < pile_size; i++)
        {
            int r = dis(gen); // 1 2 3... possible outcomes
            pile.push(new Card(card_factory(static_cast<CardType>(r))));
        }
    }
}

Card *Pile::get_card()
{
    Card *card = pile.top();
    pile.pop();
    number_of_cards--;
    return card;
}

//get top card, remove top
Card *Pile::get_top()
{
    Card *card = pile.top();
    return card;
}

std::ostream &operator<<(std::ostream &out, Pile &pile)
{
    if (pile.pile_id == 1)
    {
        // squirell
        out << "There are " << pile.number_of_cards << " cards of type " << pile.get_top()->get_name() << "\n";
        return out;
    } else // other cards
    {
        out << "You shouldn't peek ;) \n";
        return out;
    }
}
