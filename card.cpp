#include "card.h"

std::string Card::toString() const
{
    static const std::string ranks[] = {"", "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    return ranks[rank] + " of " + suit;
}
