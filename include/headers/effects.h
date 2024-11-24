#ifndef EFFECTS_H
#define EFFECTS_H
#include <ostream>

enum class Effect { none, poison, dam, air_defence, bifurcated };

inline std::ostream& operator<<(std::ostream& os, const Effect& effect)
{
    switch (effect)
    {
        case Effect::none:
            os << "none";
        case Effect::air_defence:
            os << "air_defence";
        case Effect::dam:
            os << "dam";
        case Effect::bifurcated:
            os << "bifurcated";
        default:
            os << "none";
    }
    return os;
}

#endif

