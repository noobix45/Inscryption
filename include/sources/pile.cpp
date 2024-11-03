#include "../headers/pile.h"
#include "../headers/cards_factory.h"

Pile::Pile(int n, int id) : number_of_cards{n}, pile_id{id} {get_pile();}

void Pile::get_pile() {
    if(this->pile_id==1)
    for(int i=0;i<number_of_cards;i++) {
        pile.push(card_factory((CardType::Squirrel)));
    }
    else {
        for(int i=0;i<number_of_cards;i++) {
            int r = rand()%num_of_types+1; // 1 2 3 possible outcomes
            pile.push(card_factory(static_cast<CardType>(r)));
        }
    }
}

Card Pile::get_card() {pile.pop(); number_of_cards--; return get_top();} //get top card, remove top
Card Pile::get_top() const {Card card = pile.top(); return card;}
int Pile::get_size() const {return static_cast<int>(pile.size());}

std::ostream& operator<<(std::ostream& out, const Pile& pile) {
    if(pile.pile_id == 1) {
        // squirell
        out << "There are "<< pile.number_of_cards << " cards of type "<< (pile.get_top()).get_name() << "\n";
        return out;
    }
    else // other cards
    {
        out<< "You shouldn't peek ;) \n";
        return out;
    }
}

