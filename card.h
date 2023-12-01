#ifndef CARD_H
#define CARD_H

#include <string>

class Card
{
public:
    std::string suit;
    int rank;

    // Constructor for new card with given suit and rank
    Card(std::string suit, int rank) : suit(suit), rank(rank) {}
    std::string toString() const;
};

#endif // CARD_H
