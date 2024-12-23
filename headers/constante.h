#ifndef CONSTANTE_H
#define CONSTANTE_H

enum class CardType;

#ifndef LIN
#define LIN 2
#endif
#ifndef COL
#define COL 4
#endif

// increment num of types si excluded types de fiecare data cand se adaug un tip
// daca tipul de carte nu are actiune pune l in lista de types la inceput, dupa prima poz 0
#ifndef NUM_OF_TYPES // ultima pozitie din enum class types
#define NUM_OF_TYPES (static_cast<int>(CardType::Last)-1)
#endif

#ifndef EXCLUDED_TYPES // prima pozitie care are carti valide din enum class types
#define EXCLUDED_TYPES 2
#endif

#ifndef PILE_SIZE
#define PILE_SIZE 15
#endif

#ifndef ONE_SLOT_WIDTH
#define ONE_SLOT_WIDTH 154
#endif

#ifndef ONE_SLOT_HEIGHT
#define ONE_SLOT_HEIGHT 226
#endif

#ifndef SPACING
#define SPACING (ONE_SLOT_HEIGHT*0.25f)
#endif

#endif //CONSTANTE_H
