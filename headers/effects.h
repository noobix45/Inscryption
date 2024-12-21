#ifndef EFFECTS_H
#define EFFECTS_H
#include <ostream>

enum class Effect { none, poison, dam, air_defence, bifurcated, air };

inline std::ostream& operator<<(std::ostream& os, const Effect& effect)
{
    switch (effect)
    {
        case Effect::none:
            os << "none";
            break;
        case Effect::air_defence:
            os << "air_defence";
            break;
        case Effect::dam:
            os << "dam";
            break;
        case Effect::bifurcated:
            os << "bifurcated";
            break;
        case Effect::air:
            os << "air";
            break;
        default:
            os << "none";
            break;
    }
    return os;
}

#endif

